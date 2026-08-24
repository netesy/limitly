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
  .byte 31
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 31
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
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 79
  .byte 112
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 115
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
str_hdr_2:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 5
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 5
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 72
  .byte 101
  .byte 108
  .byte 108
  .byte 111
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
  .byte 5
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 5
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 87
  .byte 111
  .byte 114
  .byte 108
  .byte 100
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
  .byte 32
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
  .byte 5
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 5
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 72
  .byte 101
  .byte 108
  .byte 108
  .byte 111
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
  .byte 115
  .byte 116
  .byte 114
  .byte 49
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 98
  .byte 101
  .byte 32
  .byte 39
  .byte 72
  .byte 101
  .byte 108
  .byte 108
  .byte 111
  .byte 39
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
  .byte 5
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 5
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 87
  .byte 111
  .byte 114
  .byte 108
  .byte 100
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
  .byte 115
  .byte 116
  .byte 114
  .byte 50
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 98
  .byte 101
  .byte 32
  .byte 39
  .byte 87
  .byte 111
  .byte 114
  .byte 108
  .byte 100
  .byte 39
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
  .byte 32
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
  .byte 115
  .byte 112
  .byte 97
  .byte 99
  .byte 101
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 98
  .byte 101
  .byte 32
  .byte 97
  .byte 32
  .byte 115
  .byte 105
  .byte 110
  .byte 103
  .byte 108
  .byte 101
  .byte 32
  .byte 115
  .byte 112
  .byte 97
  .byte 99
  .byte 101
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
  .byte 32
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 32
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 67
  .byte 111
  .byte 110
  .byte 99
  .byte 97
  .byte 116
  .byte 101
  .byte 110
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 32
  .byte 43
  .byte 32
  .byte 37
  .byte 115
  .byte 32
  .byte 43
  .byte 32
  .byte 37
  .byte 115
  .byte 32
  .byte 61
  .byte 32
  .byte 37
  .byte 115
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
  .byte 72
  .byte 101
  .byte 108
  .byte 108
  .byte 111
  .byte 32
  .byte 87
  .byte 111
  .byte 114
  .byte 108
  .byte 100
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
  .byte 32
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 32
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
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 99
  .byte 111
  .byte 110
  .byte 99
  .byte 97
  .byte 116
  .byte 101
  .byte 110
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 119
  .byte 111
  .byte 114
  .byte 107
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
  .byte 83
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 99
  .byte 111
  .byte 109
  .byte 112
  .byte 97
  .byte 114
  .byte 105
  .byte 115
  .byte 111
  .byte 110
  .byte 115
  .byte 58
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
  .byte 37
  .byte 115
  .byte 32
  .byte 61
  .byte 61
  .byte 32
  .byte 37
  .byte 115
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 0
.align 8
str_true:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 4
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 4
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 116
  .byte 114
  .byte 117
  .byte 101
  .byte 0
.align 8
str_false:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 5
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 5
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 102
  .byte 97
  .byte 108
  .byte 115
  .byte 101
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
  .byte 37
  .byte 115
  .byte 32
  .byte 33
  .byte 61
  .byte 32
  .byte 37
  .byte 115
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 32
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 32
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 39
  .byte 72
  .byte 101
  .byte 108
  .byte 108
  .byte 111
  .byte 39
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 110
  .byte 111
  .byte 116
  .byte 32
  .byte 101
  .byte 113
  .byte 117
  .byte 97
  .byte 108
  .byte 32
  .byte 39
  .byte 87
  .byte 111
  .byte 114
  .byte 108
  .byte 100
  .byte 39
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
  .byte 44
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 44
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 39
  .byte 72
  .byte 101
  .byte 108
  .byte 108
  .byte 111
  .byte 39
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 110
  .byte 111
  .byte 116
  .byte 32
  .byte 101
  .byte 113
  .byte 117
  .byte 97
  .byte 108
  .byte 32
  .byte 39
  .byte 87
  .byte 111
  .byte 114
  .byte 108
  .byte 100
  .byte 39
  .byte 32
  .byte 40
  .byte 110
  .byte 111
  .byte 116
  .byte 32
  .byte 101
  .byte 113
  .byte 117
  .byte 97
  .byte 108
  .byte 41
  .byte 0
.align 8
str_hdr_29:
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
  .byte 52
  .byte 50
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
  .byte 83
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 118
  .byte 115
  .byte 32
  .byte 110
  .byte 117
  .byte 109
  .byte 98
  .byte 101
  .byte 114
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 32
  .byte 61
  .byte 61
  .byte 32
  .byte 37
  .byte 115
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 0
.align 8
str_hdr_32:
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
  .byte 83
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 39
  .byte 52
  .byte 50
  .byte 39
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 110
  .byte 111
  .byte 116
  .byte 32
  .byte 101
  .byte 113
  .byte 117
  .byte 97
  .byte 108
  .byte 32
  .byte 110
  .byte 117
  .byte 109
  .byte 98
  .byte 101
  .byte 114
  .byte 32
  .byte 52
  .byte 50
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
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
.align 8
str_hdr_35:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
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
  .byte 18
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 18
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 69
  .byte 109
  .byte 112
  .byte 116
  .byte 121
  .byte 32
  .byte 115
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 58
  .byte 32
  .byte 39
  .byte 37
  .byte 115
  .byte 39
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
  .byte 69
  .byte 109
  .byte 112
  .byte 116
  .byte 121
  .byte 32
  .byte 108
  .byte 101
  .byte 110
  .byte 103
  .byte 116
  .byte 104
  .byte 32
  .byte 99
  .byte 104
  .byte 101
  .byte 99
  .byte 107
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 0
.align 8
str_hdr_40:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
.align 8
str_hdr_41:
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
  .byte 69
  .byte 109
  .byte 112
  .byte 116
  .byte 121
  .byte 32
  .byte 115
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 98
  .byte 101
  .byte 32
  .byte 101
  .byte 109
  .byte 112
  .byte 116
  .byte 121
  .byte 0
.align 8
str_hdr_43:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 33
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 33
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 84
  .byte 119
  .byte 111
  .byte 32
  .byte 101
  .byte 109
  .byte 112
  .byte 116
  .byte 121
  .byte 32
  .byte 115
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 115
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 98
  .byte 101
  .byte 32
  .byte 101
  .byte 113
  .byte 117
  .byte 97
  .byte 108
  .byte 0
.align 8
str_hdr_45:
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
  .byte 76
  .byte 105
  .byte 110
  .byte 101
  .byte 32
  .byte 49
  .byte 10
  .byte 76
  .byte 105
  .byte 110
  .byte 101
  .byte 32
  .byte 50
  .byte 9
  .byte 84
  .byte 97
  .byte 98
  .byte 98
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_46:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 17
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 17
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 83
  .byte 112
  .byte 101
  .byte 99
  .byte 105
  .byte 97
  .byte 108
  .byte 32
  .byte 99
  .byte 104
  .byte 97
  .byte 114
  .byte 115
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 0
.align 8
str_hdr_48:
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
  .byte 76
  .byte 105
  .byte 110
  .byte 101
  .byte 32
  .byte 49
  .byte 10
  .byte 76
  .byte 105
  .byte 110
  .byte 101
  .byte 32
  .byte 50
  .byte 9
  .byte 84
  .byte 97
  .byte 98
  .byte 98
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_49:
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
  .byte 83
  .byte 112
  .byte 101
  .byte 99
  .byte 105
  .byte 97
  .byte 108
  .byte 32
  .byte 99
  .byte 104
  .byte 97
  .byte 114
  .byte 97
  .byte 99
  .byte 116
  .byte 101
  .byte 114
  .byte 115
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 98
  .byte 101
  .byte 32
  .byte 112
  .byte 114
  .byte 101
  .byte 115
  .byte 101
  .byte 114
  .byte 118
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_51:
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
  .byte 72
  .byte 101
  .byte 32
  .byte 115
  .byte 97
  .byte 105
  .byte 100
  .byte 32
  .byte 34
  .byte 72
  .byte 101
  .byte 108
  .byte 108
  .byte 111
  .byte 34
  .byte 0
.align 8
str_hdr_52:
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
  .byte 81
  .byte 117
  .byte 111
  .byte 116
  .byte 101
  .byte 100
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 0
.align 8
str_hdr_54:
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
  .byte 72
  .byte 101
  .byte 32
  .byte 115
  .byte 97
  .byte 105
  .byte 100
  .byte 32
  .byte 34
  .byte 72
  .byte 101
  .byte 108
  .byte 108
  .byte 111
  .byte 34
  .byte 0
.align 8
str_hdr_55:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 26
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 26
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 81
  .byte 117
  .byte 111
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 115
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 115
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 119
  .byte 111
  .byte 114
  .byte 107
  .byte 0
.align 8
str_hdr_57:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 5
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 5
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 76
  .byte 105
  .byte 109
  .byte 105
  .byte 116
  .byte 0
.align 8
str_hdr_58:
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
  .byte 76
  .byte 0
.align 8
str_hdr_59:
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
  .byte 70
  .byte 105
  .byte 114
  .byte 115
  .byte 116
  .byte 32
  .byte 99
  .byte 104
  .byte 97
  .byte 114
  .byte 97
  .byte 99
  .byte 116
  .byte 101
  .byte 114
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 98
  .byte 101
  .byte 32
  .byte 39
  .byte 76
  .byte 39
  .byte 0
.align 8
str_hdr_61:
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
  .byte 116
  .byte 0
.align 8
str_hdr_62:
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
  .byte 76
  .byte 97
  .byte 115
  .byte 116
  .byte 32
  .byte 99
  .byte 104
  .byte 97
  .byte 114
  .byte 97
  .byte 99
  .byte 116
  .byte 101
  .byte 114
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 98
  .byte 101
  .byte 32
  .byte 39
  .byte 116
  .byte 39
  .byte 0
.align 8
str_hdr_64:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 44
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 44
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
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 39
  .byte 76
  .byte 105
  .byte 109
  .byte 105
  .byte 116
  .byte 39
  .byte 32
  .byte 102
  .byte 105
  .byte 114
  .byte 115
  .byte 116
  .byte 32
  .byte 99
  .byte 104
  .byte 97
  .byte 114
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 108
  .byte 97
  .byte 115
  .byte 116
  .byte 32
  .byte 99
  .byte 104
  .byte 97
  .byte 114
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 0
.align 8
str_hdr_66:
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
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 83
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 79
  .byte 112
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 115
  .byte 32
  .byte 84
  .byte 101
  .byte 115
  .byte 116
  .byte 115
  .byte 32
  .byte 67
  .byte 111
  .byte 109
  .byte 112
  .byte 108
  .byte 101
  .byte 116
  .byte 101
  .byte 32
  .byte 61
  .byte 61
  .byte 61
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
  subq $10200, %rsp
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
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -816(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -824(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -832(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -840(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -848(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -856(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -864(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -872(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -880(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -888(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -896(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -904(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -912(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -920(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -928(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -936(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -936(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -944(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -952(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -960(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -960(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -968(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -968(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -976(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -984(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -992(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -992(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1000(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1000(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1008(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1008(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1016(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1024(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1024(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1032(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1032(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1040(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1040(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1048(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1048(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1056(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1056(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1064(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1072(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1072(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1080(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1080(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1088(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1088(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1096(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1096(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1120(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_0
main_block_0:
  leaq str_hdr_0(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1128(%rbp)
  movq -1128(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -1136(%rbp)
  movq -1128(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -1144(%rbp)
  movq -1144(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1152(%rbp)
  movq -1136(%rbp), %rax
  andq -1152(%rbp), %rax
  movq %rax, -1160(%rbp)
  movq -1160(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_1
  jmp main_pr_int_0_1
main_pr_ptr_0_1:
  movq -1128(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1168(%rbp)
  movq -1128(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1176(%rbp)
  movq -1168(%rbp), %rax
  orq -1176(%rbp), %rax
  movq %rax, -1184(%rbp)
  movq -1184(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1
  jmp main_pr_obj_0_1
main_pr_int_0_1:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -1192(%rbp)
  movq $11, %rax
  movq -1192(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1192(%rbp), %rax
  addq $4, %rax
  movq %rax, -1200(%rbp)
  movq $0, %rax
  movq -1200(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1192(%rbp), %rax
  addq $63, %rax
  movq %rax, -1208(%rbp)
  movq $0, %rax
  movq -1208(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1208(%rbp), %rax
  movq -1216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1128(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1240(%rbp)
  movq -1240(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_1
  jmp main_i2s_pos_1
main_pr_nil_0_1:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1248(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1248(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1256(%rbp)
  jmp main_pr_next_0_1
main_pr_obj_0_1:
  movq -1128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1264(%rbp)
  movq -1264(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -1272(%rbp)
  movq -1272(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1280(%rbp)
  movq -1280(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_1
  jmp main_pr_nonstr_0_1
main_pr_next_0_1:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1288(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1288(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1296(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_2(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_3(%rip), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_4(%rip), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_5(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1304(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1312(%rbp)
  movq -1304(%rbp), %rdi
  movq -1312(%rbp), %rsi
  call lm_key_eq
  mov -1320(%rbp), rax
  movq -1320(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_6(%rip), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1328(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1336(%rbp)
  movq -1328(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_7
  jmp main_assert_fail_7
main_i2s_neg_1:
  movq $1, %rax
  movq -1232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1128(%rbp), %rax
  negq %rax
  movq %rax, -1344(%rbp)
  movq -1344(%rbp), %rax
  movq -1224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_1
main_i2s_pos_1:
  movq $0, %rax
  movq -1232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1128(%rbp), %rax
  movq -1224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_1
main_i2s_loop_1:
  movq -1224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1352(%rbp)
  movq -1352(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -1360(%rbp)
  movq -1352(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -1368(%rbp)
  movq -1368(%rbp), %rax
  movq -1224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1360(%rbp), %rax
  addq $48, %rax
  movq %rax, -1376(%rbp)
  movq -1216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1384(%rbp)
  movq -1384(%rbp), %rax
  subq $1, %rax
  movq %rax, -1392(%rbp)
  movq -1376(%rbp), %rax
  movq -1392(%rbp), %rdx
  movb %al, (%rdx)
  movq -1392(%rbp), %rax
  movq -1216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1352(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -1400(%rbp)
  movq -1400(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_1
  jmp main_i2s_sign_1
main_i2s_sign_1:
  movq -1232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1408(%rbp)
  movq -1408(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1416(%rbp)
  movq -1416(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_1
  jmp main_i2s_done_1
main_i2s_minus_1:
  movq -1216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1424(%rbp)
  movq -1424(%rbp), %rax
  subq $1, %rax
  movq %rax, -1432(%rbp)
  movq $45, %rax
  movq -1432(%rbp), %rdx
  movb %al, (%rdx)
  movq -1432(%rbp), %rax
  movq -1216(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_1
main_i2s_done_1:
  movq -1216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1440(%rbp)
  movq -1208(%rbp), %rax
  subq -1440(%rbp), %rax
  movq %rax, -1448(%rbp)
  movq -1192(%rbp), %rax
  addq $8, %rax
  movq %rax, -1456(%rbp)
  movq -1448(%rbp), %rax
  movq -1456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1192(%rbp), %rax
  addq $16, %rax
  movq %rax, -1464(%rbp)
  movq -1448(%rbp), %rax
  movq -1464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1192(%rbp), %rax
  addq $24, %rax
  movq %rax, -1472(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1480(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1448(%rbp), %rax
  addq $1, %rax
  movq %rax, -1488(%rbp)
  jmp main_d2s_copy_loop_1
main_d2s_copy_loop_1:
  movq -1480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1496(%rbp)
  movq -1496(%rbp), %rax
  cmpq -1488(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1504(%rbp)
  movq -1504(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_1
  jmp main_d2s_copy_done_1
main_d2s_copy_body_1:
  movq -1440(%rbp), %rax
  addq -1496(%rbp), %rax
  movq %rax, -1512(%rbp)
  movq -1512(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -1520(%rbp)
  movq -1472(%rbp), %rax
  addq -1496(%rbp), %rax
  movq %rax, -1528(%rbp)
  movq -1520(%rbp), %rax
  movq -1528(%rbp), %rdx
  movb %al, (%rdx)
  movq -1496(%rbp), %rax
  addq $1, %rax
  movq %rax, -1536(%rbp)
  movq -1536(%rbp), %rax
  movq -1480(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_1
main_d2s_copy_done_1:
  movq -1192(%rbp), %rax
  addq $24, %rax
  movq %rax, -1544(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1552(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1552(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1448(%rbp), %rax
  addq $1, %rax
  movq %rax, -1560(%rbp)
  jmp main_i2s_copy_loop_1
main_i2s_copy_loop_1:
  movq -1552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1568(%rbp)
  movq -1568(%rbp), %rax
  cmpq -1560(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1576(%rbp)
  movq -1576(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_1
  jmp main_i2s_copy_done_1
main_i2s_copy_body_1:
  movq -1440(%rbp), %rax
  addq -1568(%rbp), %rax
  movq %rax, -1584(%rbp)
  movq -1584(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -1592(%rbp)
  movq -1544(%rbp), %rax
  addq -1568(%rbp), %rax
  movq %rax, -1600(%rbp)
  movq -1592(%rbp), %rax
  movq -1600(%rbp), %rdx
  movb %al, (%rdx)
  movq -1568(%rbp), %rax
  addq $1, %rax
  movq %rax, -1608(%rbp)
  movq -1608(%rbp), %rax
  movq -1552(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_1
main_i2s_copy_done_1:
  movq -1192(%rbp), %rax
  addq $8, %rax
  movq %rax, -1616(%rbp)
  movq -1616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1624(%rbp)
  movq -1192(%rbp), %rax
  addq $24, %rax
  movq %rax, -1632(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1632(%rbp), %rsi
  movq -1624(%rbp), %rdx
  syscall
  movq %rax, -1640(%rbp)
  jmp main_pr_next_0_1
main_pr_str_0_1:
  movq -1128(%rbp), %rax
  addq $8, %rax
  movq %rax, -1648(%rbp)
  movq -1648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1656(%rbp)
  movq -1128(%rbp), %rax
  addq $24, %rax
  movq %rax, -1664(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1664(%rbp), %rsi
  movq -1656(%rbp), %rdx
  syscall
  movq %rax, -1672(%rbp)
  jmp main_pr_next_0_1
main_pr_enum_0_1:
  movq -1128(%rbp), %rdi
  call lm_enum_to_str
  mov -1680(%rbp), rax
  movq -1680(%rbp), %rax
  addq $8, %rax
  movq %rax, -1688(%rbp)
  movq -1688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1696(%rbp)
  movq -1680(%rbp), %rax
  addq $24, %rax
  movq %rax, -1704(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1704(%rbp), %rsi
  movq -1696(%rbp), %rdx
  syscall
  movq %rax, -1712(%rbp)
  jmp main_pr_next_0_1
main_pr_list_0_1:
  movq -1128(%rbp), %rdi
  call lm_list_to_str
  mov -1720(%rbp), rax
  movq -1720(%rbp), %rax
  addq $8, %rax
  movq %rax, -1728(%rbp)
  movq -1728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1736(%rbp)
  movq -1720(%rbp), %rax
  addq $24, %rax
  movq %rax, -1744(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1744(%rbp), %rsi
  movq -1736(%rbp), %rdx
  syscall
  movq %rax, -1752(%rbp)
  jmp main_pr_next_0_1
main_pr_nonstr_0_1:
  movq -1264(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1760(%rbp)
  movq -1760(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_1
  jmp main_pr_list_0_1
main_assert_pass_7:
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_8(%rip), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1768(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1776(%rbp)
  movq -1768(%rbp), %rdi
  movq -1776(%rbp), %rsi
  call lm_key_eq
  mov -1784(%rbp), rax
  movq -1784(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_9(%rip), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1792(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1800(%rbp)
  movq -1792(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_10
  jmp main_assert_fail_10
main_assert_fail_7:
  movq -1336(%rbp), %rax
  addq $8, %rax
  movq %rax, -1808(%rbp)
  movq -1808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1816(%rbp)
  movq -1336(%rbp), %rax
  addq $24, %rax
  movq %rax, -1824(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1824(%rbp), %rsi
  movq -1816(%rbp), %rdx
  syscall
  movq %rax, -1832(%rbp)
  movq $50397203, %rax
  movq %rax, -1840(%rbp)
  jmp main_assert_pass_7
main_assert_pass_10:
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_11(%rip), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1848(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1856(%rbp)
  movq -1848(%rbp), %rdi
  movq -1856(%rbp), %rsi
  call lm_key_eq
  mov -1864(%rbp), rax
  movq -1864(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_12(%rip), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1872(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1880(%rbp)
  movq -1872(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_13
  jmp main_assert_fail_13
main_assert_fail_10:
  movq -1800(%rbp), %rax
  addq $8, %rax
  movq %rax, -1888(%rbp)
  movq -1888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1896(%rbp)
  movq -1800(%rbp), %rax
  addq $24, %rax
  movq %rax, -1904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1904(%rbp), %rsi
  movq -1896(%rbp), %rdx
  syscall
  movq %rax, -1912(%rbp)
  movq $50397203, %rax
  movq %rax, -1920(%rbp)
  jmp main_assert_pass_10
main_assert_pass_13:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1928(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1936(%rbp)
  movq -1928(%rbp), %rdi
  movq -1936(%rbp), %rsi
  call lm_str_concat
  mov -1944(%rbp), rax
  movq -1944(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1952(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1960(%rbp)
  movq -1952(%rbp), %rdi
  movq -1960(%rbp), %rsi
  call lm_str_concat
  mov -1968(%rbp), rax
  movq -1968(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1976(%rbp)
  movq -1976(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_14(%rip), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1984(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1992(%rbp)
  movq -1984(%rbp), %rdi
  movq -1992(%rbp), %rsi
  call lm_rt_str_format
  mov -2000(%rbp), rax
  movq -2000(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2008(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2016(%rbp)
  movq -2008(%rbp), %rdi
  movq -2016(%rbp), %rsi
  call lm_rt_str_format
  mov -2024(%rbp), rax
  movq -2024(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2032(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2040(%rbp)
  movq -2032(%rbp), %rdi
  movq -2040(%rbp), %rsi
  call lm_rt_str_format
  mov -2048(%rbp), rax
  movq -2048(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2056(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2064(%rbp)
  movq -2056(%rbp), %rdi
  movq -2064(%rbp), %rsi
  call lm_rt_str_format
  mov -2072(%rbp), rax
  movq -2072(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2080(%rbp)
  movq -2080(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2088(%rbp)
  movq -2088(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -2096(%rbp)
  movq -2088(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -2104(%rbp)
  movq -2104(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2112(%rbp)
  movq -2096(%rbp), %rax
  andq -2112(%rbp), %rax
  movq %rax, -2120(%rbp)
  movq -2120(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_15
  jmp main_pr_int_0_15
main_assert_fail_13:
  movq -1880(%rbp), %rax
  addq $8, %rax
  movq %rax, -2128(%rbp)
  movq -2128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2136(%rbp)
  movq -1880(%rbp), %rax
  addq $24, %rax
  movq %rax, -2144(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2144(%rbp), %rsi
  movq -2136(%rbp), %rdx
  syscall
  movq %rax, -2152(%rbp)
  movq $50397203, %rax
  movq %rax, -2160(%rbp)
  jmp main_assert_pass_13
main_pr_ptr_0_15:
  movq -2088(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2168(%rbp)
  movq -2088(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2176(%rbp)
  movq -2168(%rbp), %rax
  orq -2176(%rbp), %rax
  movq %rax, -2184(%rbp)
  movq -2184(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_15
  jmp main_pr_obj_0_15
main_pr_int_0_15:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -2192(%rbp)
  movq $11, %rax
  movq -2192(%rbp), %rdx
  movl %eax, (%rdx)
  movq -2192(%rbp), %rax
  addq $4, %rax
  movq %rax, -2200(%rbp)
  movq $0, %rax
  movq -2200(%rbp), %rdx
  movl %eax, (%rdx)
  movq -2192(%rbp), %rax
  addq $63, %rax
  movq %rax, -2208(%rbp)
  movq $0, %rax
  movq -2208(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -2208(%rbp), %rax
  movq -2216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -2088(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2240(%rbp)
  movq -2240(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_5
  jmp main_i2s_pos_5
main_pr_nil_0_15:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2248(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2248(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2256(%rbp)
  jmp main_pr_next_0_15
main_pr_obj_0_15:
  movq -2088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2264(%rbp)
  movq -2264(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -2272(%rbp)
  movq -2272(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2280(%rbp)
  movq -2280(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_15
  jmp main_pr_nonstr_0_15
main_pr_next_0_15:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2288(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2288(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2296(%rbp)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_16(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2304(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2312(%rbp)
  movq -2304(%rbp), %rdi
  movq -2312(%rbp), %rsi
  call lm_key_eq
  mov -2320(%rbp), rax
  movq -2320(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_17(%rip), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2328(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2336(%rbp)
  movq -2328(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_18
  jmp main_assert_fail_18
main_i2s_neg_5:
  movq $1, %rax
  movq -2232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2088(%rbp), %rax
  negq %rax
  movq %rax, -2344(%rbp)
  movq -2344(%rbp), %rax
  movq -2224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_5
main_i2s_pos_5:
  movq $0, %rax
  movq -2232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2088(%rbp), %rax
  movq -2224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_5
main_i2s_loop_5:
  movq -2224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2352(%rbp)
  movq -2352(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -2360(%rbp)
  movq -2352(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -2368(%rbp)
  movq -2368(%rbp), %rax
  movq -2224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2360(%rbp), %rax
  addq $48, %rax
  movq %rax, -2376(%rbp)
  movq -2216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2384(%rbp)
  movq -2384(%rbp), %rax
  subq $1, %rax
  movq %rax, -2392(%rbp)
  movq -2376(%rbp), %rax
  movq -2392(%rbp), %rdx
  movb %al, (%rdx)
  movq -2392(%rbp), %rax
  movq -2216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2352(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -2400(%rbp)
  movq -2400(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_5
  jmp main_i2s_sign_5
main_i2s_sign_5:
  movq -2232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2408(%rbp)
  movq -2408(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2416(%rbp)
  movq -2416(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_5
  jmp main_i2s_done_5
main_i2s_minus_5:
  movq -2216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2424(%rbp)
  movq -2424(%rbp), %rax
  subq $1, %rax
  movq %rax, -2432(%rbp)
  movq $45, %rax
  movq -2432(%rbp), %rdx
  movb %al, (%rdx)
  movq -2432(%rbp), %rax
  movq -2216(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_5
main_i2s_done_5:
  movq -2216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2440(%rbp)
  movq -2208(%rbp), %rax
  subq -2440(%rbp), %rax
  movq %rax, -2448(%rbp)
  movq -2192(%rbp), %rax
  addq $8, %rax
  movq %rax, -2456(%rbp)
  movq -2448(%rbp), %rax
  movq -2456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2192(%rbp), %rax
  addq $16, %rax
  movq %rax, -2464(%rbp)
  movq -2448(%rbp), %rax
  movq -2464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2192(%rbp), %rax
  addq $24, %rax
  movq %rax, -2472(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2480(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2448(%rbp), %rax
  addq $1, %rax
  movq %rax, -2488(%rbp)
  jmp main_d2s_copy_loop_5
main_d2s_copy_loop_5:
  movq -2480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2496(%rbp)
  movq -2496(%rbp), %rax
  cmpq -2488(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2504(%rbp)
  movq -2504(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_5
  jmp main_d2s_copy_done_5
main_d2s_copy_body_5:
  movq -2440(%rbp), %rax
  addq -2496(%rbp), %rax
  movq %rax, -2512(%rbp)
  movq -2512(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -2520(%rbp)
  movq -2472(%rbp), %rax
  addq -2496(%rbp), %rax
  movq %rax, -2528(%rbp)
  movq -2520(%rbp), %rax
  movq -2528(%rbp), %rdx
  movb %al, (%rdx)
  movq -2496(%rbp), %rax
  addq $1, %rax
  movq %rax, -2536(%rbp)
  movq -2536(%rbp), %rax
  movq -2480(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_5
main_d2s_copy_done_5:
  movq -2192(%rbp), %rax
  addq $24, %rax
  movq %rax, -2544(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2552(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2552(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2448(%rbp), %rax
  addq $1, %rax
  movq %rax, -2560(%rbp)
  jmp main_i2s_copy_loop_5
main_i2s_copy_loop_5:
  movq -2552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2568(%rbp)
  movq -2568(%rbp), %rax
  cmpq -2560(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2576(%rbp)
  movq -2576(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_5
  jmp main_i2s_copy_done_5
main_i2s_copy_body_5:
  movq -2440(%rbp), %rax
  addq -2568(%rbp), %rax
  movq %rax, -2584(%rbp)
  movq -2584(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -2592(%rbp)
  movq -2544(%rbp), %rax
  addq -2568(%rbp), %rax
  movq %rax, -2600(%rbp)
  movq -2592(%rbp), %rax
  movq -2600(%rbp), %rdx
  movb %al, (%rdx)
  movq -2568(%rbp), %rax
  addq $1, %rax
  movq %rax, -2608(%rbp)
  movq -2608(%rbp), %rax
  movq -2552(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_5
main_i2s_copy_done_5:
  movq -2192(%rbp), %rax
  addq $8, %rax
  movq %rax, -2616(%rbp)
  movq -2616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2624(%rbp)
  movq -2192(%rbp), %rax
  addq $24, %rax
  movq %rax, -2632(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2632(%rbp), %rsi
  movq -2624(%rbp), %rdx
  syscall
  movq %rax, -2640(%rbp)
  jmp main_pr_next_0_15
main_pr_str_0_15:
  movq -2088(%rbp), %rax
  addq $8, %rax
  movq %rax, -2648(%rbp)
  movq -2648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2656(%rbp)
  movq -2088(%rbp), %rax
  addq $24, %rax
  movq %rax, -2664(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2664(%rbp), %rsi
  movq -2656(%rbp), %rdx
  syscall
  movq %rax, -2672(%rbp)
  jmp main_pr_next_0_15
main_pr_enum_0_15:
  movq -2088(%rbp), %rdi
  call lm_enum_to_str
  mov -2680(%rbp), rax
  movq -2680(%rbp), %rax
  addq $8, %rax
  movq %rax, -2688(%rbp)
  movq -2688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2696(%rbp)
  movq -2680(%rbp), %rax
  addq $24, %rax
  movq %rax, -2704(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2704(%rbp), %rsi
  movq -2696(%rbp), %rdx
  syscall
  movq %rax, -2712(%rbp)
  jmp main_pr_next_0_15
main_pr_list_0_15:
  movq -2088(%rbp), %rdi
  call lm_list_to_str
  mov -2720(%rbp), rax
  movq -2720(%rbp), %rax
  addq $8, %rax
  movq %rax, -2728(%rbp)
  movq -2728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2736(%rbp)
  movq -2720(%rbp), %rax
  addq $24, %rax
  movq %rax, -2744(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2744(%rbp), %rsi
  movq -2736(%rbp), %rdx
  syscall
  movq %rax, -2752(%rbp)
  jmp main_pr_next_0_15
main_pr_nonstr_0_15:
  movq -2264(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2760(%rbp)
  movq -2760(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_15
  jmp main_pr_list_0_15
main_assert_pass_18:
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_19(%rip), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2768(%rbp)
  movq -2768(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -2776(%rbp)
  movq -2768(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -2784(%rbp)
  movq -2784(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2792(%rbp)
  movq -2776(%rbp), %rax
  andq -2792(%rbp), %rax
  movq %rax, -2800(%rbp)
  movq -2800(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_20
  jmp main_pr_int_0_20
main_assert_fail_18:
  movq -2336(%rbp), %rax
  addq $8, %rax
  movq %rax, -2808(%rbp)
  movq -2808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2816(%rbp)
  movq -2336(%rbp), %rax
  addq $24, %rax
  movq %rax, -2824(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2824(%rbp), %rsi
  movq -2816(%rbp), %rdx
  syscall
  movq %rax, -2832(%rbp)
  movq $50397203, %rax
  movq %rax, -2840(%rbp)
  jmp main_assert_pass_18
main_pr_ptr_0_20:
  movq -2768(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2848(%rbp)
  movq -2768(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2856(%rbp)
  movq -2848(%rbp), %rax
  orq -2856(%rbp), %rax
  movq %rax, -2864(%rbp)
  movq -2864(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_20
  jmp main_pr_obj_0_20
main_pr_int_0_20:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -2872(%rbp)
  movq $11, %rax
  movq -2872(%rbp), %rdx
  movl %eax, (%rdx)
  movq -2872(%rbp), %rax
  addq $4, %rax
  movq %rax, -2880(%rbp)
  movq $0, %rax
  movq -2880(%rbp), %rdx
  movl %eax, (%rdx)
  movq -2872(%rbp), %rax
  addq $63, %rax
  movq %rax, -2888(%rbp)
  movq $0, %rax
  movq -2888(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2896(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -2888(%rbp), %rax
  movq -2896(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2904(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2912(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -2768(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2920(%rbp)
  movq -2920(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_6
  jmp main_i2s_pos_6
main_pr_nil_0_20:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2928(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2928(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2936(%rbp)
  jmp main_pr_next_0_20
main_pr_obj_0_20:
  movq -2768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2944(%rbp)
  movq -2944(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -2952(%rbp)
  movq -2952(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2960(%rbp)
  movq -2960(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_20
  jmp main_pr_nonstr_0_20
main_pr_next_0_20:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2968(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2968(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2976(%rbp)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2984(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2992(%rbp)
  movq -2984(%rbp), %rdi
  movq -2992(%rbp), %rsi
  call lm_key_eq
  mov -3000(%rbp), rax
  movq -3000(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3008(%rbp)
  movq -3008(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3016(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3024(%rbp)
  movq -3016(%rbp), %rdi
  movq -3024(%rbp), %rsi
  call lm_key_eq
  mov -3032(%rbp), rax
  movq -3032(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3040(%rbp)
  movq -3040(%rbp), %rax
  movq -320(%rbp), %rdx
  movl %eax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3048(%rbp)
  movq -3048(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_21(%rip), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3056(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3064(%rbp)
  movq -3056(%rbp), %rdi
  movq -3064(%rbp), %rsi
  call lm_rt_str_format
  mov -3072(%rbp), rax
  movq -3072(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3080(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3088(%rbp)
  movq -3080(%rbp), %rdi
  movq -3088(%rbp), %rsi
  call lm_rt_str_format
  mov -3096(%rbp), rax
  movq -3096(%rbp), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3104(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3112(%rbp)
  movq -3112(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -3120(%rbp)
  movq -3120(%rbp), %rax
  testq %rax, %rax
  jne main_b2s_t_1
  jmp main_b2s_f_1
main_i2s_neg_6:
  movq $1, %rax
  movq -2912(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2768(%rbp), %rax
  negq %rax
  movq %rax, -3128(%rbp)
  movq -3128(%rbp), %rax
  movq -2904(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_6
main_i2s_pos_6:
  movq $0, %rax
  movq -2912(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2768(%rbp), %rax
  movq -2904(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_6
main_i2s_loop_6:
  movq -2904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3136(%rbp)
  movq -3136(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -3144(%rbp)
  movq -3136(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -3152(%rbp)
  movq -3152(%rbp), %rax
  movq -2904(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3144(%rbp), %rax
  addq $48, %rax
  movq %rax, -3160(%rbp)
  movq -2896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3168(%rbp)
  movq -3168(%rbp), %rax
  subq $1, %rax
  movq %rax, -3176(%rbp)
  movq -3160(%rbp), %rax
  movq -3176(%rbp), %rdx
  movb %al, (%rdx)
  movq -3176(%rbp), %rax
  movq -2896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3136(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -3184(%rbp)
  movq -3184(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_6
  jmp main_i2s_sign_6
main_i2s_sign_6:
  movq -2912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3192(%rbp)
  movq -3192(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3200(%rbp)
  movq -3200(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_6
  jmp main_i2s_done_6
main_i2s_minus_6:
  movq -2896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3208(%rbp)
  movq -3208(%rbp), %rax
  subq $1, %rax
  movq %rax, -3216(%rbp)
  movq $45, %rax
  movq -3216(%rbp), %rdx
  movb %al, (%rdx)
  movq -3216(%rbp), %rax
  movq -2896(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_6
main_i2s_done_6:
  movq -2896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3224(%rbp)
  movq -2888(%rbp), %rax
  subq -3224(%rbp), %rax
  movq %rax, -3232(%rbp)
  movq -2872(%rbp), %rax
  addq $8, %rax
  movq %rax, -3240(%rbp)
  movq -3232(%rbp), %rax
  movq -3240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2872(%rbp), %rax
  addq $16, %rax
  movq %rax, -3248(%rbp)
  movq -3232(%rbp), %rax
  movq -3248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2872(%rbp), %rax
  addq $24, %rax
  movq %rax, -3256(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3232(%rbp), %rax
  addq $1, %rax
  movq %rax, -3272(%rbp)
  jmp main_d2s_copy_loop_6
main_d2s_copy_loop_6:
  movq -3264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3280(%rbp)
  movq -3280(%rbp), %rax
  cmpq -3272(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -3288(%rbp)
  movq -3288(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_6
  jmp main_d2s_copy_done_6
main_d2s_copy_body_6:
  movq -3224(%rbp), %rax
  addq -3280(%rbp), %rax
  movq %rax, -3296(%rbp)
  movq -3296(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -3304(%rbp)
  movq -3256(%rbp), %rax
  addq -3280(%rbp), %rax
  movq %rax, -3312(%rbp)
  movq -3304(%rbp), %rax
  movq -3312(%rbp), %rdx
  movb %al, (%rdx)
  movq -3280(%rbp), %rax
  addq $1, %rax
  movq %rax, -3320(%rbp)
  movq -3320(%rbp), %rax
  movq -3264(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_6
main_d2s_copy_done_6:
  movq -2872(%rbp), %rax
  addq $24, %rax
  movq %rax, -3328(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3336(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3232(%rbp), %rax
  addq $1, %rax
  movq %rax, -3344(%rbp)
  jmp main_i2s_copy_loop_6
main_i2s_copy_loop_6:
  movq -3336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3352(%rbp)
  movq -3352(%rbp), %rax
  cmpq -3344(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -3360(%rbp)
  movq -3360(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_6
  jmp main_i2s_copy_done_6
main_i2s_copy_body_6:
  movq -3224(%rbp), %rax
  addq -3352(%rbp), %rax
  movq %rax, -3368(%rbp)
  movq -3368(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -3376(%rbp)
  movq -3328(%rbp), %rax
  addq -3352(%rbp), %rax
  movq %rax, -3384(%rbp)
  movq -3376(%rbp), %rax
  movq -3384(%rbp), %rdx
  movb %al, (%rdx)
  movq -3352(%rbp), %rax
  addq $1, %rax
  movq %rax, -3392(%rbp)
  movq -3392(%rbp), %rax
  movq -3336(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_6
main_i2s_copy_done_6:
  movq -2872(%rbp), %rax
  addq $8, %rax
  movq %rax, -3400(%rbp)
  movq -3400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3408(%rbp)
  movq -2872(%rbp), %rax
  addq $24, %rax
  movq %rax, -3416(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3416(%rbp), %rsi
  movq -3408(%rbp), %rdx
  syscall
  movq %rax, -3424(%rbp)
  jmp main_pr_next_0_20
main_pr_str_0_20:
  movq -2768(%rbp), %rax
  addq $8, %rax
  movq %rax, -3432(%rbp)
  movq -3432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3440(%rbp)
  movq -2768(%rbp), %rax
  addq $24, %rax
  movq %rax, -3448(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3448(%rbp), %rsi
  movq -3440(%rbp), %rdx
  syscall
  movq %rax, -3456(%rbp)
  jmp main_pr_next_0_20
main_pr_enum_0_20:
  movq -2768(%rbp), %rdi
  call lm_enum_to_str
  mov -3464(%rbp), rax
  movq -3464(%rbp), %rax
  addq $8, %rax
  movq %rax, -3472(%rbp)
  movq -3472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3480(%rbp)
  movq -3464(%rbp), %rax
  addq $24, %rax
  movq %rax, -3488(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3488(%rbp), %rsi
  movq -3480(%rbp), %rdx
  syscall
  movq %rax, -3496(%rbp)
  jmp main_pr_next_0_20
main_pr_list_0_20:
  movq -2768(%rbp), %rdi
  call lm_list_to_str
  mov -3504(%rbp), rax
  movq -3504(%rbp), %rax
  addq $8, %rax
  movq %rax, -3512(%rbp)
  movq -3512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3520(%rbp)
  movq -3504(%rbp), %rax
  addq $24, %rax
  movq %rax, -3528(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3528(%rbp), %rsi
  movq -3520(%rbp), %rdx
  syscall
  movq %rax, -3536(%rbp)
  jmp main_pr_next_0_20
main_pr_nonstr_0_20:
  movq -2944(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3544(%rbp)
  movq -3544(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_20
  jmp main_pr_list_0_20
main_b2s_t_1:
  movq str_true(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -3552(%rbp)
  jmp main_b2s_d_1
main_b2s_f_1:
  movq str_false(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -3552(%rbp)
  jmp main_b2s_d_1
main_b2s_d_1:
  movq -3104(%rbp), %rdi
  movq -3552(%rbp), %rsi
  call lm_rt_str_format
  mov -3560(%rbp), rax
  movq -3560(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3568(%rbp)
  movq -3568(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3576(%rbp)
  movq -3576(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -3584(%rbp)
  movq -3576(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -3592(%rbp)
  movq -3592(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3600(%rbp)
  movq -3584(%rbp), %rax
  andq -3600(%rbp), %rax
  movq %rax, -3608(%rbp)
  movq -3608(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_22
  jmp main_pr_int_0_22
main_pr_ptr_0_22:
  movq -3576(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3616(%rbp)
  movq -3576(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3624(%rbp)
  movq -3616(%rbp), %rax
  orq -3624(%rbp), %rax
  movq %rax, -3632(%rbp)
  movq -3632(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_22
  jmp main_pr_obj_0_22
main_pr_int_0_22:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -3640(%rbp)
  movq $11, %rax
  movq -3640(%rbp), %rdx
  movl %eax, (%rdx)
  movq -3640(%rbp), %rax
  addq $4, %rax
  movq %rax, -3648(%rbp)
  movq $0, %rax
  movq -3648(%rbp), %rdx
  movl %eax, (%rdx)
  movq -3640(%rbp), %rax
  addq $63, %rax
  movq %rax, -3656(%rbp)
  movq $0, %rax
  movq -3656(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3664(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -3656(%rbp), %rax
  movq -3664(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3672(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3680(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -3576(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -3688(%rbp)
  movq -3688(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_7
  jmp main_i2s_pos_7
main_pr_nil_0_22:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3696(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3696(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3704(%rbp)
  jmp main_pr_next_0_22
main_pr_obj_0_22:
  movq -3576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3712(%rbp)
  movq -3712(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -3720(%rbp)
  movq -3720(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3728(%rbp)
  movq -3728(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_22
  jmp main_pr_nonstr_0_22
main_pr_next_0_22:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3736(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3736(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3744(%rbp)
  movq $0, %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_23(%rip), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3752(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3760(%rbp)
  movq -3752(%rbp), %rdi
  movq -3760(%rbp), %rsi
  call lm_rt_str_format
  mov -3768(%rbp), rax
  movq -3768(%rbp), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3776(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3784(%rbp)
  movq -3776(%rbp), %rdi
  movq -3784(%rbp), %rsi
  call lm_rt_str_format
  mov -3792(%rbp), rax
  movq -3792(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3800(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3808(%rbp)
  movq -3808(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -3816(%rbp)
  movq -3816(%rbp), %rax
  testq %rax, %rax
  jne main_b2s_t_2
  jmp main_b2s_f_2
main_i2s_neg_7:
  movq $1, %rax
  movq -3680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3576(%rbp), %rax
  negq %rax
  movq %rax, -3824(%rbp)
  movq -3824(%rbp), %rax
  movq -3672(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_7
main_i2s_pos_7:
  movq $0, %rax
  movq -3680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3576(%rbp), %rax
  movq -3672(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_7
main_i2s_loop_7:
  movq -3672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3832(%rbp)
  movq -3832(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -3840(%rbp)
  movq -3832(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -3848(%rbp)
  movq -3848(%rbp), %rax
  movq -3672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3840(%rbp), %rax
  addq $48, %rax
  movq %rax, -3856(%rbp)
  movq -3664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3864(%rbp)
  movq -3864(%rbp), %rax
  subq $1, %rax
  movq %rax, -3872(%rbp)
  movq -3856(%rbp), %rax
  movq -3872(%rbp), %rdx
  movb %al, (%rdx)
  movq -3872(%rbp), %rax
  movq -3664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3832(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -3880(%rbp)
  movq -3880(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_7
  jmp main_i2s_sign_7
main_i2s_sign_7:
  movq -3680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3888(%rbp)
  movq -3888(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3896(%rbp)
  movq -3896(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_7
  jmp main_i2s_done_7
main_i2s_minus_7:
  movq -3664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3904(%rbp)
  movq -3904(%rbp), %rax
  subq $1, %rax
  movq %rax, -3912(%rbp)
  movq $45, %rax
  movq -3912(%rbp), %rdx
  movb %al, (%rdx)
  movq -3912(%rbp), %rax
  movq -3664(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_7
main_i2s_done_7:
  movq -3664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3920(%rbp)
  movq -3656(%rbp), %rax
  subq -3920(%rbp), %rax
  movq %rax, -3928(%rbp)
  movq -3640(%rbp), %rax
  addq $8, %rax
  movq %rax, -3936(%rbp)
  movq -3928(%rbp), %rax
  movq -3936(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3640(%rbp), %rax
  addq $16, %rax
  movq %rax, -3944(%rbp)
  movq -3928(%rbp), %rax
  movq -3944(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3640(%rbp), %rax
  addq $24, %rax
  movq %rax, -3952(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3960(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3928(%rbp), %rax
  addq $1, %rax
  movq %rax, -3968(%rbp)
  jmp main_d2s_copy_loop_7
main_d2s_copy_loop_7:
  movq -3960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3976(%rbp)
  movq -3976(%rbp), %rax
  cmpq -3968(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -3984(%rbp)
  movq -3984(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_7
  jmp main_d2s_copy_done_7
main_d2s_copy_body_7:
  movq -3920(%rbp), %rax
  addq -3976(%rbp), %rax
  movq %rax, -3992(%rbp)
  movq -3992(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -4000(%rbp)
  movq -3952(%rbp), %rax
  addq -3976(%rbp), %rax
  movq %rax, -4008(%rbp)
  movq -4000(%rbp), %rax
  movq -4008(%rbp), %rdx
  movb %al, (%rdx)
  movq -3976(%rbp), %rax
  addq $1, %rax
  movq %rax, -4016(%rbp)
  movq -4016(%rbp), %rax
  movq -3960(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_7
main_d2s_copy_done_7:
  movq -3640(%rbp), %rax
  addq $24, %rax
  movq %rax, -4024(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4032(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -4032(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3928(%rbp), %rax
  addq $1, %rax
  movq %rax, -4040(%rbp)
  jmp main_i2s_copy_loop_7
main_i2s_copy_loop_7:
  movq -4032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4048(%rbp)
  movq -4048(%rbp), %rax
  cmpq -4040(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -4056(%rbp)
  movq -4056(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_7
  jmp main_i2s_copy_done_7
main_i2s_copy_body_7:
  movq -3920(%rbp), %rax
  addq -4048(%rbp), %rax
  movq %rax, -4064(%rbp)
  movq -4064(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -4072(%rbp)
  movq -4024(%rbp), %rax
  addq -4048(%rbp), %rax
  movq %rax, -4080(%rbp)
  movq -4072(%rbp), %rax
  movq -4080(%rbp), %rdx
  movb %al, (%rdx)
  movq -4048(%rbp), %rax
  addq $1, %rax
  movq %rax, -4088(%rbp)
  movq -4088(%rbp), %rax
  movq -4032(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_7
main_i2s_copy_done_7:
  movq -3640(%rbp), %rax
  addq $8, %rax
  movq %rax, -4096(%rbp)
  movq -4096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4104(%rbp)
  movq -3640(%rbp), %rax
  addq $24, %rax
  movq %rax, -4112(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4112(%rbp), %rsi
  movq -4104(%rbp), %rdx
  syscall
  movq %rax, -4120(%rbp)
  jmp main_pr_next_0_22
main_pr_str_0_22:
  movq -3576(%rbp), %rax
  addq $8, %rax
  movq %rax, -4128(%rbp)
  movq -4128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4136(%rbp)
  movq -3576(%rbp), %rax
  addq $24, %rax
  movq %rax, -4144(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4144(%rbp), %rsi
  movq -4136(%rbp), %rdx
  syscall
  movq %rax, -4152(%rbp)
  jmp main_pr_next_0_22
main_pr_enum_0_22:
  movq -3576(%rbp), %rdi
  call lm_enum_to_str
  mov -4160(%rbp), rax
  movq -4160(%rbp), %rax
  addq $8, %rax
  movq %rax, -4168(%rbp)
  movq -4168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4176(%rbp)
  movq -4160(%rbp), %rax
  addq $24, %rax
  movq %rax, -4184(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4184(%rbp), %rsi
  movq -4176(%rbp), %rdx
  syscall
  movq %rax, -4192(%rbp)
  jmp main_pr_next_0_22
main_pr_list_0_22:
  movq -3576(%rbp), %rdi
  call lm_list_to_str
  mov -4200(%rbp), rax
  movq -4200(%rbp), %rax
  addq $8, %rax
  movq %rax, -4208(%rbp)
  movq -4208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4216(%rbp)
  movq -4200(%rbp), %rax
  addq $24, %rax
  movq %rax, -4224(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4224(%rbp), %rsi
  movq -4216(%rbp), %rdx
  syscall
  movq %rax, -4232(%rbp)
  jmp main_pr_next_0_22
main_pr_nonstr_0_22:
  movq -3712(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4240(%rbp)
  movq -4240(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_22
  jmp main_pr_list_0_22
main_b2s_t_2:
  movq str_true(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -4248(%rbp)
  jmp main_b2s_d_2
main_b2s_f_2:
  movq str_false(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -4248(%rbp)
  jmp main_b2s_d_2
main_b2s_d_2:
  movq -3800(%rbp), %rdi
  movq -4248(%rbp), %rsi
  call lm_rt_str_format
  mov -4256(%rbp), rax
  movq -4256(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4264(%rbp)
  movq -4264(%rbp), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4272(%rbp)
  movq -4272(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -4280(%rbp)
  movq -4272(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -4288(%rbp)
  movq -4288(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4296(%rbp)
  movq -4280(%rbp), %rax
  andq -4296(%rbp), %rax
  movq %rax, -4304(%rbp)
  movq -4304(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_24
  jmp main_pr_int_0_24
main_pr_ptr_0_24:
  movq -4272(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4312(%rbp)
  movq -4272(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4320(%rbp)
  movq -4312(%rbp), %rax
  orq -4320(%rbp), %rax
  movq %rax, -4328(%rbp)
  movq -4328(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_24
  jmp main_pr_obj_0_24
main_pr_int_0_24:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -4336(%rbp)
  movq $11, %rax
  movq -4336(%rbp), %rdx
  movl %eax, (%rdx)
  movq -4336(%rbp), %rax
  addq $4, %rax
  movq %rax, -4344(%rbp)
  movq $0, %rax
  movq -4344(%rbp), %rdx
  movl %eax, (%rdx)
  movq -4336(%rbp), %rax
  addq $63, %rax
  movq %rax, -4352(%rbp)
  movq $0, %rax
  movq -4352(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4360(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -4352(%rbp), %rax
  movq -4360(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4368(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4376(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -4272(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -4384(%rbp)
  movq -4384(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_8
  jmp main_i2s_pos_8
main_pr_nil_0_24:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4392(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4392(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4400(%rbp)
  jmp main_pr_next_0_24
main_pr_obj_0_24:
  movq -4272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4408(%rbp)
  movq -4408(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -4416(%rbp)
  movq -4416(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4424(%rbp)
  movq -4424(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_24
  jmp main_pr_nonstr_0_24
main_pr_next_0_24:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4432(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4432(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4440(%rbp)
  movq $0, %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4448(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4456(%rbp)
  movq -4456(%rbp), %rax
  cmpq -4448(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4464(%rbp)
  movq -4464(%rbp), %rax
  movq -424(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_25(%rip), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4472(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4480(%rbp)
  movq -4472(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_26
  jmp main_assert_fail_26
main_i2s_neg_8:
  movq $1, %rax
  movq -4376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4272(%rbp), %rax
  negq %rax
  movq %rax, -4488(%rbp)
  movq -4488(%rbp), %rax
  movq -4368(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_8
main_i2s_pos_8:
  movq $0, %rax
  movq -4376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4272(%rbp), %rax
  movq -4368(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_8
main_i2s_loop_8:
  movq -4368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4496(%rbp)
  movq -4496(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -4504(%rbp)
  movq -4496(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -4512(%rbp)
  movq -4512(%rbp), %rax
  movq -4368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4504(%rbp), %rax
  addq $48, %rax
  movq %rax, -4520(%rbp)
  movq -4360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4528(%rbp)
  movq -4528(%rbp), %rax
  subq $1, %rax
  movq %rax, -4536(%rbp)
  movq -4520(%rbp), %rax
  movq -4536(%rbp), %rdx
  movb %al, (%rdx)
  movq -4536(%rbp), %rax
  movq -4360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4496(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -4544(%rbp)
  movq -4544(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_8
  jmp main_i2s_sign_8
main_i2s_sign_8:
  movq -4376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4552(%rbp)
  movq -4552(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4560(%rbp)
  movq -4560(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_8
  jmp main_i2s_done_8
main_i2s_minus_8:
  movq -4360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4568(%rbp)
  movq -4568(%rbp), %rax
  subq $1, %rax
  movq %rax, -4576(%rbp)
  movq $45, %rax
  movq -4576(%rbp), %rdx
  movb %al, (%rdx)
  movq -4576(%rbp), %rax
  movq -4360(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_8
main_i2s_done_8:
  movq -4360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4584(%rbp)
  movq -4352(%rbp), %rax
  subq -4584(%rbp), %rax
  movq %rax, -4592(%rbp)
  movq -4336(%rbp), %rax
  addq $8, %rax
  movq %rax, -4600(%rbp)
  movq -4592(%rbp), %rax
  movq -4600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4336(%rbp), %rax
  addq $16, %rax
  movq %rax, -4608(%rbp)
  movq -4592(%rbp), %rax
  movq -4608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4336(%rbp), %rax
  addq $24, %rax
  movq %rax, -4616(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4624(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -4624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4592(%rbp), %rax
  addq $1, %rax
  movq %rax, -4632(%rbp)
  jmp main_d2s_copy_loop_8
main_d2s_copy_loop_8:
  movq -4624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4640(%rbp)
  movq -4640(%rbp), %rax
  cmpq -4632(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -4648(%rbp)
  movq -4648(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_8
  jmp main_d2s_copy_done_8
main_d2s_copy_body_8:
  movq -4584(%rbp), %rax
  addq -4640(%rbp), %rax
  movq %rax, -4656(%rbp)
  movq -4656(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -4664(%rbp)
  movq -4616(%rbp), %rax
  addq -4640(%rbp), %rax
  movq %rax, -4672(%rbp)
  movq -4664(%rbp), %rax
  movq -4672(%rbp), %rdx
  movb %al, (%rdx)
  movq -4640(%rbp), %rax
  addq $1, %rax
  movq %rax, -4680(%rbp)
  movq -4680(%rbp), %rax
  movq -4624(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_8
main_d2s_copy_done_8:
  movq -4336(%rbp), %rax
  addq $24, %rax
  movq %rax, -4688(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4696(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -4696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4592(%rbp), %rax
  addq $1, %rax
  movq %rax, -4704(%rbp)
  jmp main_i2s_copy_loop_8
main_i2s_copy_loop_8:
  movq -4696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4712(%rbp)
  movq -4712(%rbp), %rax
  cmpq -4704(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -4720(%rbp)
  movq -4720(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_8
  jmp main_i2s_copy_done_8
main_i2s_copy_body_8:
  movq -4584(%rbp), %rax
  addq -4712(%rbp), %rax
  movq %rax, -4728(%rbp)
  movq -4728(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -4736(%rbp)
  movq -4688(%rbp), %rax
  addq -4712(%rbp), %rax
  movq %rax, -4744(%rbp)
  movq -4736(%rbp), %rax
  movq -4744(%rbp), %rdx
  movb %al, (%rdx)
  movq -4712(%rbp), %rax
  addq $1, %rax
  movq %rax, -4752(%rbp)
  movq -4752(%rbp), %rax
  movq -4696(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_8
main_i2s_copy_done_8:
  movq -4336(%rbp), %rax
  addq $8, %rax
  movq %rax, -4760(%rbp)
  movq -4760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4768(%rbp)
  movq -4336(%rbp), %rax
  addq $24, %rax
  movq %rax, -4776(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4776(%rbp), %rsi
  movq -4768(%rbp), %rdx
  syscall
  movq %rax, -4784(%rbp)
  jmp main_pr_next_0_24
main_pr_str_0_24:
  movq -4272(%rbp), %rax
  addq $8, %rax
  movq %rax, -4792(%rbp)
  movq -4792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4800(%rbp)
  movq -4272(%rbp), %rax
  addq $24, %rax
  movq %rax, -4808(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4808(%rbp), %rsi
  movq -4800(%rbp), %rdx
  syscall
  movq %rax, -4816(%rbp)
  jmp main_pr_next_0_24
main_pr_enum_0_24:
  movq -4272(%rbp), %rdi
  call lm_enum_to_str
  mov -4824(%rbp), rax
  movq -4824(%rbp), %rax
  addq $8, %rax
  movq %rax, -4832(%rbp)
  movq -4832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4840(%rbp)
  movq -4824(%rbp), %rax
  addq $24, %rax
  movq %rax, -4848(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4848(%rbp), %rsi
  movq -4840(%rbp), %rdx
  syscall
  movq %rax, -4856(%rbp)
  jmp main_pr_next_0_24
main_pr_list_0_24:
  movq -4272(%rbp), %rdi
  call lm_list_to_str
  mov -4864(%rbp), rax
  movq -4864(%rbp), %rax
  addq $8, %rax
  movq %rax, -4872(%rbp)
  movq -4872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4880(%rbp)
  movq -4864(%rbp), %rax
  addq $24, %rax
  movq %rax, -4888(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4888(%rbp), %rsi
  movq -4880(%rbp), %rdx
  syscall
  movq %rax, -4896(%rbp)
  jmp main_pr_next_0_24
main_pr_nonstr_0_24:
  movq -4408(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4904(%rbp)
  movq -4904(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_24
  jmp main_pr_list_0_24
main_assert_pass_26:
  movq $0, %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4912(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4920(%rbp)
  movq -4920(%rbp), %rax
  cmpq -4912(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4928(%rbp)
  movq -4928(%rbp), %rax
  movq -456(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_27(%rip), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4936(%rbp)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4944(%rbp)
  movq -4936(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_28
  jmp main_assert_fail_28
main_assert_fail_26:
  movq -4480(%rbp), %rax
  addq $8, %rax
  movq %rax, -4952(%rbp)
  movq -4952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4960(%rbp)
  movq -4480(%rbp), %rax
  addq $24, %rax
  movq %rax, -4968(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4968(%rbp), %rsi
  movq -4960(%rbp), %rdx
  syscall
  movq %rax, -4976(%rbp)
  movq $50397203, %rax
  movq %rax, -4984(%rbp)
  jmp main_assert_pass_26
main_assert_pass_28:
  movq $0, %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_29(%rip), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq $42, %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4992(%rbp)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5000(%rbp)
  movq -4992(%rbp), %rdi
  movq -5000(%rbp), %rsi
  call lm_key_eq
  mov -5008(%rbp), rax
  movq -5008(%rbp), %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5016(%rbp)
  movq -5016(%rbp), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_30(%rip), %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5024(%rbp)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5032(%rbp)
  movq -5024(%rbp), %rdi
  movq -5032(%rbp), %rsi
  call lm_rt_str_format
  mov -5040(%rbp), rax
  movq -5040(%rbp), %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5048(%rbp)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5056(%rbp)
  movq -5056(%rbp), %rdi
  call lm_to_string
  mov -5064(%rbp), rax
  movq -5048(%rbp), %rdi
  movq -5064(%rbp), %rsi
  call lm_rt_str_format
  mov -5072(%rbp), rax
  movq -5072(%rbp), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5080(%rbp)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5088(%rbp)
  movq -5088(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -5096(%rbp)
  movq -5096(%rbp), %rax
  testq %rax, %rax
  jne main_b2s_t_3
  jmp main_b2s_f_3
main_assert_fail_28:
  movq -4944(%rbp), %rax
  addq $8, %rax
  movq %rax, -5104(%rbp)
  movq -5104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5112(%rbp)
  movq -4944(%rbp), %rax
  addq $24, %rax
  movq %rax, -5120(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5120(%rbp), %rsi
  movq -5112(%rbp), %rdx
  syscall
  movq %rax, -5128(%rbp)
  movq $50397203, %rax
  movq %rax, -5136(%rbp)
  jmp main_assert_pass_28
main_b2s_t_3:
  movq str_true(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -5144(%rbp)
  jmp main_b2s_d_3
main_b2s_f_3:
  movq str_false(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -5144(%rbp)
  jmp main_b2s_d_3
main_b2s_d_3:
  movq -5080(%rbp), %rdi
  movq -5144(%rbp), %rsi
  call lm_rt_str_format
  mov -5152(%rbp), rax
  movq -5152(%rbp), %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5160(%rbp)
  movq -5160(%rbp), %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5168(%rbp)
  movq -5168(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -5176(%rbp)
  movq -5168(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -5184(%rbp)
  movq -5184(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5192(%rbp)
  movq -5176(%rbp), %rax
  andq -5192(%rbp), %rax
  movq %rax, -5200(%rbp)
  movq -5200(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_31
  jmp main_pr_int_0_31
main_pr_ptr_0_31:
  movq -5168(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5208(%rbp)
  movq -5168(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5216(%rbp)
  movq -5208(%rbp), %rax
  orq -5216(%rbp), %rax
  movq %rax, -5224(%rbp)
  movq -5224(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_31
  jmp main_pr_obj_0_31
main_pr_int_0_31:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -5232(%rbp)
  movq $11, %rax
  movq -5232(%rbp), %rdx
  movl %eax, (%rdx)
  movq -5232(%rbp), %rax
  addq $4, %rax
  movq %rax, -5240(%rbp)
  movq $0, %rax
  movq -5240(%rbp), %rdx
  movl %eax, (%rdx)
  movq -5232(%rbp), %rax
  addq $63, %rax
  movq %rax, -5248(%rbp)
  movq $0, %rax
  movq -5248(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -5256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -5248(%rbp), %rax
  movq -5256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -5264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -5272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -5168(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -5280(%rbp)
  movq -5280(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_9
  jmp main_i2s_pos_9
main_pr_nil_0_31:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5288(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5288(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5296(%rbp)
  jmp main_pr_next_0_31
main_pr_obj_0_31:
  movq -5168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5304(%rbp)
  movq -5304(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -5312(%rbp)
  movq -5312(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5320(%rbp)
  movq -5320(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_31
  jmp main_pr_nonstr_0_31
main_pr_next_0_31:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5328(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5328(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5336(%rbp)
  movq $0, %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5344(%rbp)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5352(%rbp)
  movq -5352(%rbp), %rax
  cmpq -5344(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5360(%rbp)
  movq -5360(%rbp), %rax
  movq -560(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_32(%rip), %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5368(%rbp)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5376(%rbp)
  movq -5368(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_33
  jmp main_assert_fail_33
main_i2s_neg_9:
  movq $1, %rax
  movq -5272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5168(%rbp), %rax
  negq %rax
  movq %rax, -5384(%rbp)
  movq -5384(%rbp), %rax
  movq -5264(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_9
main_i2s_pos_9:
  movq $0, %rax
  movq -5272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5168(%rbp), %rax
  movq -5264(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_9
main_i2s_loop_9:
  movq -5264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5392(%rbp)
  movq -5392(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -5400(%rbp)
  movq -5392(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -5408(%rbp)
  movq -5408(%rbp), %rax
  movq -5264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5400(%rbp), %rax
  addq $48, %rax
  movq %rax, -5416(%rbp)
  movq -5256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5424(%rbp)
  movq -5424(%rbp), %rax
  subq $1, %rax
  movq %rax, -5432(%rbp)
  movq -5416(%rbp), %rax
  movq -5432(%rbp), %rdx
  movb %al, (%rdx)
  movq -5432(%rbp), %rax
  movq -5256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5392(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -5440(%rbp)
  movq -5440(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_9
  jmp main_i2s_sign_9
main_i2s_sign_9:
  movq -5272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5448(%rbp)
  movq -5448(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5456(%rbp)
  movq -5456(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_9
  jmp main_i2s_done_9
main_i2s_minus_9:
  movq -5256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5464(%rbp)
  movq -5464(%rbp), %rax
  subq $1, %rax
  movq %rax, -5472(%rbp)
  movq $45, %rax
  movq -5472(%rbp), %rdx
  movb %al, (%rdx)
  movq -5472(%rbp), %rax
  movq -5256(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_9
main_i2s_done_9:
  movq -5256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5480(%rbp)
  movq -5248(%rbp), %rax
  subq -5480(%rbp), %rax
  movq %rax, -5488(%rbp)
  movq -5232(%rbp), %rax
  addq $8, %rax
  movq %rax, -5496(%rbp)
  movq -5488(%rbp), %rax
  movq -5496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5232(%rbp), %rax
  addq $16, %rax
  movq %rax, -5504(%rbp)
  movq -5488(%rbp), %rax
  movq -5504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5232(%rbp), %rax
  addq $24, %rax
  movq %rax, -5512(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -5520(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -5520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5488(%rbp), %rax
  addq $1, %rax
  movq %rax, -5528(%rbp)
  jmp main_d2s_copy_loop_9
main_d2s_copy_loop_9:
  movq -5520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5536(%rbp)
  movq -5536(%rbp), %rax
  cmpq -5528(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -5544(%rbp)
  movq -5544(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_9
  jmp main_d2s_copy_done_9
main_d2s_copy_body_9:
  movq -5480(%rbp), %rax
  addq -5536(%rbp), %rax
  movq %rax, -5552(%rbp)
  movq -5552(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -5560(%rbp)
  movq -5512(%rbp), %rax
  addq -5536(%rbp), %rax
  movq %rax, -5568(%rbp)
  movq -5560(%rbp), %rax
  movq -5568(%rbp), %rdx
  movb %al, (%rdx)
  movq -5536(%rbp), %rax
  addq $1, %rax
  movq %rax, -5576(%rbp)
  movq -5576(%rbp), %rax
  movq -5520(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_9
main_d2s_copy_done_9:
  movq -5232(%rbp), %rax
  addq $24, %rax
  movq %rax, -5584(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -5592(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -5592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5488(%rbp), %rax
  addq $1, %rax
  movq %rax, -5600(%rbp)
  jmp main_i2s_copy_loop_9
main_i2s_copy_loop_9:
  movq -5592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5608(%rbp)
  movq -5608(%rbp), %rax
  cmpq -5600(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -5616(%rbp)
  movq -5616(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_9
  jmp main_i2s_copy_done_9
main_i2s_copy_body_9:
  movq -5480(%rbp), %rax
  addq -5608(%rbp), %rax
  movq %rax, -5624(%rbp)
  movq -5624(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -5632(%rbp)
  movq -5584(%rbp), %rax
  addq -5608(%rbp), %rax
  movq %rax, -5640(%rbp)
  movq -5632(%rbp), %rax
  movq -5640(%rbp), %rdx
  movb %al, (%rdx)
  movq -5608(%rbp), %rax
  addq $1, %rax
  movq %rax, -5648(%rbp)
  movq -5648(%rbp), %rax
  movq -5592(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_9
main_i2s_copy_done_9:
  movq -5232(%rbp), %rax
  addq $8, %rax
  movq %rax, -5656(%rbp)
  movq -5656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5664(%rbp)
  movq -5232(%rbp), %rax
  addq $24, %rax
  movq %rax, -5672(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5672(%rbp), %rsi
  movq -5664(%rbp), %rdx
  syscall
  movq %rax, -5680(%rbp)
  jmp main_pr_next_0_31
main_pr_str_0_31:
  movq -5168(%rbp), %rax
  addq $8, %rax
  movq %rax, -5688(%rbp)
  movq -5688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5696(%rbp)
  movq -5168(%rbp), %rax
  addq $24, %rax
  movq %rax, -5704(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5704(%rbp), %rsi
  movq -5696(%rbp), %rdx
  syscall
  movq %rax, -5712(%rbp)
  jmp main_pr_next_0_31
main_pr_enum_0_31:
  movq -5168(%rbp), %rdi
  call lm_enum_to_str
  mov -5720(%rbp), rax
  movq -5720(%rbp), %rax
  addq $8, %rax
  movq %rax, -5728(%rbp)
  movq -5728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5736(%rbp)
  movq -5720(%rbp), %rax
  addq $24, %rax
  movq %rax, -5744(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5744(%rbp), %rsi
  movq -5736(%rbp), %rdx
  syscall
  movq %rax, -5752(%rbp)
  jmp main_pr_next_0_31
main_pr_list_0_31:
  movq -5168(%rbp), %rdi
  call lm_list_to_str
  mov -5760(%rbp), rax
  movq -5760(%rbp), %rax
  addq $8, %rax
  movq %rax, -5768(%rbp)
  movq -5768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5776(%rbp)
  movq -5760(%rbp), %rax
  addq $24, %rax
  movq %rax, -5784(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5784(%rbp), %rsi
  movq -5776(%rbp), %rdx
  syscall
  movq %rax, -5792(%rbp)
  jmp main_pr_next_0_31
main_pr_nonstr_0_31:
  movq -5304(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5800(%rbp)
  movq -5800(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_31
  jmp main_pr_list_0_31
main_assert_pass_33:
  movq $0, %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_34(%rip), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_35(%rip), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5808(%rbp)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5816(%rbp)
  movq -5808(%rbp), %rdi
  movq -5816(%rbp), %rsi
  call lm_key_eq
  mov -5824(%rbp), rax
  movq -5824(%rbp), %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5832(%rbp)
  movq -5832(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_36(%rip), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5840(%rbp)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5848(%rbp)
  movq -5840(%rbp), %rdi
  movq -5848(%rbp), %rsi
  call lm_rt_str_format
  mov -5856(%rbp), rax
  movq -5856(%rbp), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5864(%rbp)
  movq -5864(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -5872(%rbp)
  movq -5864(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -5880(%rbp)
  movq -5880(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5888(%rbp)
  movq -5872(%rbp), %rax
  andq -5888(%rbp), %rax
  movq %rax, -5896(%rbp)
  movq -5896(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_37
  jmp main_pr_int_0_37
main_assert_fail_33:
  movq -5376(%rbp), %rax
  addq $8, %rax
  movq %rax, -5904(%rbp)
  movq -5904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5912(%rbp)
  movq -5376(%rbp), %rax
  addq $24, %rax
  movq %rax, -5920(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5920(%rbp), %rsi
  movq -5912(%rbp), %rdx
  syscall
  movq %rax, -5928(%rbp)
  movq $50397203, %rax
  movq %rax, -5936(%rbp)
  jmp main_assert_pass_33
main_pr_ptr_0_37:
  movq -5864(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5944(%rbp)
  movq -5864(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5952(%rbp)
  movq -5944(%rbp), %rax
  orq -5952(%rbp), %rax
  movq %rax, -5960(%rbp)
  movq -5960(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_37
  jmp main_pr_obj_0_37
main_pr_int_0_37:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -5968(%rbp)
  movq $11, %rax
  movq -5968(%rbp), %rdx
  movl %eax, (%rdx)
  movq -5968(%rbp), %rax
  addq $4, %rax
  movq %rax, -5976(%rbp)
  movq $0, %rax
  movq -5976(%rbp), %rdx
  movl %eax, (%rdx)
  movq -5968(%rbp), %rax
  addq $63, %rax
  movq %rax, -5984(%rbp)
  movq $0, %rax
  movq -5984(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -5992(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -5984(%rbp), %rax
  movq -5992(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6000(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6008(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -5864(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -6016(%rbp)
  movq -6016(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_10
  jmp main_i2s_pos_10
main_pr_nil_0_37:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6024(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6024(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6032(%rbp)
  jmp main_pr_next_0_37
main_pr_obj_0_37:
  movq -5864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6040(%rbp)
  movq -6040(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -6048(%rbp)
  movq -6048(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6056(%rbp)
  movq -6056(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_37
  jmp main_pr_nonstr_0_37
main_pr_next_0_37:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6064(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6064(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6072(%rbp)
  movq $0, %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_38(%rip), %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6080(%rbp)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6088(%rbp)
  movq -6088(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -6096(%rbp)
  movq -6096(%rbp), %rax
  testq %rax, %rax
  jne main_b2s_t_4
  jmp main_b2s_f_4
main_i2s_neg_10:
  movq $1, %rax
  movq -6008(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5864(%rbp), %rax
  negq %rax
  movq %rax, -6104(%rbp)
  movq -6104(%rbp), %rax
  movq -6000(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_10
main_i2s_pos_10:
  movq $0, %rax
  movq -6008(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5864(%rbp), %rax
  movq -6000(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_10
main_i2s_loop_10:
  movq -6000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6112(%rbp)
  movq -6112(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -6120(%rbp)
  movq -6112(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -6128(%rbp)
  movq -6128(%rbp), %rax
  movq -6000(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6120(%rbp), %rax
  addq $48, %rax
  movq %rax, -6136(%rbp)
  movq -5992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6144(%rbp)
  movq -6144(%rbp), %rax
  subq $1, %rax
  movq %rax, -6152(%rbp)
  movq -6136(%rbp), %rax
  movq -6152(%rbp), %rdx
  movb %al, (%rdx)
  movq -6152(%rbp), %rax
  movq -5992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6112(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -6160(%rbp)
  movq -6160(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_10
  jmp main_i2s_sign_10
main_i2s_sign_10:
  movq -6008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6168(%rbp)
  movq -6168(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6176(%rbp)
  movq -6176(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_10
  jmp main_i2s_done_10
main_i2s_minus_10:
  movq -5992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6184(%rbp)
  movq -6184(%rbp), %rax
  subq $1, %rax
  movq %rax, -6192(%rbp)
  movq $45, %rax
  movq -6192(%rbp), %rdx
  movb %al, (%rdx)
  movq -6192(%rbp), %rax
  movq -5992(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_10
main_i2s_done_10:
  movq -5992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6200(%rbp)
  movq -5984(%rbp), %rax
  subq -6200(%rbp), %rax
  movq %rax, -6208(%rbp)
  movq -5968(%rbp), %rax
  addq $8, %rax
  movq %rax, -6216(%rbp)
  movq -6208(%rbp), %rax
  movq -6216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5968(%rbp), %rax
  addq $16, %rax
  movq %rax, -6224(%rbp)
  movq -6208(%rbp), %rax
  movq -6224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5968(%rbp), %rax
  addq $24, %rax
  movq %rax, -6232(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -6240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6208(%rbp), %rax
  addq $1, %rax
  movq %rax, -6248(%rbp)
  jmp main_d2s_copy_loop_10
main_d2s_copy_loop_10:
  movq -6240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6256(%rbp)
  movq -6256(%rbp), %rax
  cmpq -6248(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -6264(%rbp)
  movq -6264(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_10
  jmp main_d2s_copy_done_10
main_d2s_copy_body_10:
  movq -6200(%rbp), %rax
  addq -6256(%rbp), %rax
  movq %rax, -6272(%rbp)
  movq -6272(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -6280(%rbp)
  movq -6232(%rbp), %rax
  addq -6256(%rbp), %rax
  movq %rax, -6288(%rbp)
  movq -6280(%rbp), %rax
  movq -6288(%rbp), %rdx
  movb %al, (%rdx)
  movq -6256(%rbp), %rax
  addq $1, %rax
  movq %rax, -6296(%rbp)
  movq -6296(%rbp), %rax
  movq -6240(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_10
main_d2s_copy_done_10:
  movq -5968(%rbp), %rax
  addq $24, %rax
  movq %rax, -6304(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6312(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -6312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6208(%rbp), %rax
  addq $1, %rax
  movq %rax, -6320(%rbp)
  jmp main_i2s_copy_loop_10
main_i2s_copy_loop_10:
  movq -6312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6328(%rbp)
  movq -6328(%rbp), %rax
  cmpq -6320(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -6336(%rbp)
  movq -6336(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_10
  jmp main_i2s_copy_done_10
main_i2s_copy_body_10:
  movq -6200(%rbp), %rax
  addq -6328(%rbp), %rax
  movq %rax, -6344(%rbp)
  movq -6344(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -6352(%rbp)
  movq -6304(%rbp), %rax
  addq -6328(%rbp), %rax
  movq %rax, -6360(%rbp)
  movq -6352(%rbp), %rax
  movq -6360(%rbp), %rdx
  movb %al, (%rdx)
  movq -6328(%rbp), %rax
  addq $1, %rax
  movq %rax, -6368(%rbp)
  movq -6368(%rbp), %rax
  movq -6312(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_10
main_i2s_copy_done_10:
  movq -5968(%rbp), %rax
  addq $8, %rax
  movq %rax, -6376(%rbp)
  movq -6376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6384(%rbp)
  movq -5968(%rbp), %rax
  addq $24, %rax
  movq %rax, -6392(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6392(%rbp), %rsi
  movq -6384(%rbp), %rdx
  syscall
  movq %rax, -6400(%rbp)
  jmp main_pr_next_0_37
main_pr_str_0_37:
  movq -5864(%rbp), %rax
  addq $8, %rax
  movq %rax, -6408(%rbp)
  movq -6408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6416(%rbp)
  movq -5864(%rbp), %rax
  addq $24, %rax
  movq %rax, -6424(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6424(%rbp), %rsi
  movq -6416(%rbp), %rdx
  syscall
  movq %rax, -6432(%rbp)
  jmp main_pr_next_0_37
main_pr_enum_0_37:
  movq -5864(%rbp), %rdi
  call lm_enum_to_str
  mov -6440(%rbp), rax
  movq -6440(%rbp), %rax
  addq $8, %rax
  movq %rax, -6448(%rbp)
  movq -6448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6456(%rbp)
  movq -6440(%rbp), %rax
  addq $24, %rax
  movq %rax, -6464(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6464(%rbp), %rsi
  movq -6456(%rbp), %rdx
  syscall
  movq %rax, -6472(%rbp)
  jmp main_pr_next_0_37
main_pr_list_0_37:
  movq -5864(%rbp), %rdi
  call lm_list_to_str
  mov -6480(%rbp), rax
  movq -6480(%rbp), %rax
  addq $8, %rax
  movq %rax, -6488(%rbp)
  movq -6488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6496(%rbp)
  movq -6480(%rbp), %rax
  addq $24, %rax
  movq %rax, -6504(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6504(%rbp), %rsi
  movq -6496(%rbp), %rdx
  syscall
  movq %rax, -6512(%rbp)
  jmp main_pr_next_0_37
main_pr_nonstr_0_37:
  movq -6040(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6520(%rbp)
  movq -6520(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_37
  jmp main_pr_list_0_37
main_b2s_t_4:
  movq str_true(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -6528(%rbp)
  jmp main_b2s_d_4
main_b2s_f_4:
  movq str_false(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -6528(%rbp)
  jmp main_b2s_d_4
main_b2s_d_4:
  movq -6080(%rbp), %rdi
  movq -6528(%rbp), %rsi
  call lm_rt_str_format
  mov -6536(%rbp), rax
  movq -6536(%rbp), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6544(%rbp)
  movq -6544(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -6552(%rbp)
  movq -6544(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -6560(%rbp)
  movq -6560(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6568(%rbp)
  movq -6552(%rbp), %rax
  andq -6568(%rbp), %rax
  movq %rax, -6576(%rbp)
  movq -6576(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_39
  jmp main_pr_int_0_39
main_pr_ptr_0_39:
  movq -6544(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6584(%rbp)
  movq -6544(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6592(%rbp)
  movq -6584(%rbp), %rax
  orq -6592(%rbp), %rax
  movq %rax, -6600(%rbp)
  movq -6600(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_39
  jmp main_pr_obj_0_39
main_pr_int_0_39:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -6608(%rbp)
  movq $11, %rax
  movq -6608(%rbp), %rdx
  movl %eax, (%rdx)
  movq -6608(%rbp), %rax
  addq $4, %rax
  movq %rax, -6616(%rbp)
  movq $0, %rax
  movq -6616(%rbp), %rdx
  movl %eax, (%rdx)
  movq -6608(%rbp), %rax
  addq $63, %rax
  movq %rax, -6624(%rbp)
  movq $0, %rax
  movq -6624(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6632(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -6624(%rbp), %rax
  movq -6632(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6640(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6648(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -6544(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -6656(%rbp)
  movq -6656(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_11
  jmp main_i2s_pos_11
main_pr_nil_0_39:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6664(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6664(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6672(%rbp)
  jmp main_pr_next_0_39
main_pr_obj_0_39:
  movq -6544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6680(%rbp)
  movq -6680(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -6688(%rbp)
  movq -6688(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6696(%rbp)
  movq -6696(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_39
  jmp main_pr_nonstr_0_39
main_pr_next_0_39:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6704(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6704(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6712(%rbp)
  movq $0, %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_40(%rip), %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6720(%rbp)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6728(%rbp)
  movq -6720(%rbp), %rdi
  movq -6728(%rbp), %rsi
  call lm_key_eq
  mov -6736(%rbp), rax
  movq -6736(%rbp), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_41(%rip), %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6744(%rbp)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6752(%rbp)
  movq -6744(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_42
  jmp main_assert_fail_42
main_i2s_neg_11:
  movq $1, %rax
  movq -6648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6544(%rbp), %rax
  negq %rax
  movq %rax, -6760(%rbp)
  movq -6760(%rbp), %rax
  movq -6640(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_11
main_i2s_pos_11:
  movq $0, %rax
  movq -6648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6544(%rbp), %rax
  movq -6640(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_11
main_i2s_loop_11:
  movq -6640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6768(%rbp)
  movq -6768(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -6776(%rbp)
  movq -6768(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -6784(%rbp)
  movq -6784(%rbp), %rax
  movq -6640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6776(%rbp), %rax
  addq $48, %rax
  movq %rax, -6792(%rbp)
  movq -6632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6800(%rbp)
  movq -6800(%rbp), %rax
  subq $1, %rax
  movq %rax, -6808(%rbp)
  movq -6792(%rbp), %rax
  movq -6808(%rbp), %rdx
  movb %al, (%rdx)
  movq -6808(%rbp), %rax
  movq -6632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6768(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -6816(%rbp)
  movq -6816(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_11
  jmp main_i2s_sign_11
main_i2s_sign_11:
  movq -6648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6824(%rbp)
  movq -6824(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6832(%rbp)
  movq -6832(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_11
  jmp main_i2s_done_11
main_i2s_minus_11:
  movq -6632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6840(%rbp)
  movq -6840(%rbp), %rax
  subq $1, %rax
  movq %rax, -6848(%rbp)
  movq $45, %rax
  movq -6848(%rbp), %rdx
  movb %al, (%rdx)
  movq -6848(%rbp), %rax
  movq -6632(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_11
main_i2s_done_11:
  movq -6632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6856(%rbp)
  movq -6624(%rbp), %rax
  subq -6856(%rbp), %rax
  movq %rax, -6864(%rbp)
  movq -6608(%rbp), %rax
  addq $8, %rax
  movq %rax, -6872(%rbp)
  movq -6864(%rbp), %rax
  movq -6872(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6608(%rbp), %rax
  addq $16, %rax
  movq %rax, -6880(%rbp)
  movq -6864(%rbp), %rax
  movq -6880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6608(%rbp), %rax
  addq $24, %rax
  movq %rax, -6888(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6896(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -6896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6864(%rbp), %rax
  addq $1, %rax
  movq %rax, -6904(%rbp)
  jmp main_d2s_copy_loop_11
main_d2s_copy_loop_11:
  movq -6896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6912(%rbp)
  movq -6912(%rbp), %rax
  cmpq -6904(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -6920(%rbp)
  movq -6920(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_11
  jmp main_d2s_copy_done_11
main_d2s_copy_body_11:
  movq -6856(%rbp), %rax
  addq -6912(%rbp), %rax
  movq %rax, -6928(%rbp)
  movq -6928(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -6936(%rbp)
  movq -6888(%rbp), %rax
  addq -6912(%rbp), %rax
  movq %rax, -6944(%rbp)
  movq -6936(%rbp), %rax
  movq -6944(%rbp), %rdx
  movb %al, (%rdx)
  movq -6912(%rbp), %rax
  addq $1, %rax
  movq %rax, -6952(%rbp)
  movq -6952(%rbp), %rax
  movq -6896(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_11
main_d2s_copy_done_11:
  movq -6608(%rbp), %rax
  addq $24, %rax
  movq %rax, -6960(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6968(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -6968(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6864(%rbp), %rax
  addq $1, %rax
  movq %rax, -6976(%rbp)
  jmp main_i2s_copy_loop_11
main_i2s_copy_loop_11:
  movq -6968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6984(%rbp)
  movq -6984(%rbp), %rax
  cmpq -6976(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -6992(%rbp)
  movq -6992(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_11
  jmp main_i2s_copy_done_11
main_i2s_copy_body_11:
  movq -6856(%rbp), %rax
  addq -6984(%rbp), %rax
  movq %rax, -7000(%rbp)
  movq -7000(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -7008(%rbp)
  movq -6960(%rbp), %rax
  addq -6984(%rbp), %rax
  movq %rax, -7016(%rbp)
  movq -7008(%rbp), %rax
  movq -7016(%rbp), %rdx
  movb %al, (%rdx)
  movq -6984(%rbp), %rax
  addq $1, %rax
  movq %rax, -7024(%rbp)
  movq -7024(%rbp), %rax
  movq -6968(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_11
main_i2s_copy_done_11:
  movq -6608(%rbp), %rax
  addq $8, %rax
  movq %rax, -7032(%rbp)
  movq -7032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7040(%rbp)
  movq -6608(%rbp), %rax
  addq $24, %rax
  movq %rax, -7048(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7048(%rbp), %rsi
  movq -7040(%rbp), %rdx
  syscall
  movq %rax, -7056(%rbp)
  jmp main_pr_next_0_39
main_pr_str_0_39:
  movq -6544(%rbp), %rax
  addq $8, %rax
  movq %rax, -7064(%rbp)
  movq -7064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7072(%rbp)
  movq -6544(%rbp), %rax
  addq $24, %rax
  movq %rax, -7080(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7080(%rbp), %rsi
  movq -7072(%rbp), %rdx
  syscall
  movq %rax, -7088(%rbp)
  jmp main_pr_next_0_39
main_pr_enum_0_39:
  movq -6544(%rbp), %rdi
  call lm_enum_to_str
  mov -7096(%rbp), rax
  movq -7096(%rbp), %rax
  addq $8, %rax
  movq %rax, -7104(%rbp)
  movq -7104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7112(%rbp)
  movq -7096(%rbp), %rax
  addq $24, %rax
  movq %rax, -7120(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7120(%rbp), %rsi
  movq -7112(%rbp), %rdx
  syscall
  movq %rax, -7128(%rbp)
  jmp main_pr_next_0_39
main_pr_list_0_39:
  movq -6544(%rbp), %rdi
  call lm_list_to_str
  mov -7136(%rbp), rax
  movq -7136(%rbp), %rax
  addq $8, %rax
  movq %rax, -7144(%rbp)
  movq -7144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7152(%rbp)
  movq -7136(%rbp), %rax
  addq $24, %rax
  movq %rax, -7160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7160(%rbp), %rsi
  movq -7152(%rbp), %rdx
  syscall
  movq %rax, -7168(%rbp)
  jmp main_pr_next_0_39
main_pr_nonstr_0_39:
  movq -6680(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7176(%rbp)
  movq -7176(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_39
  jmp main_pr_list_0_39
main_assert_pass_42:
  movq $0, %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7184(%rbp)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7192(%rbp)
  movq -7192(%rbp), %rax
  cmpq -7184(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7200(%rbp)
  movq -7200(%rbp), %rax
  movq -704(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_43(%rip), %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7208(%rbp)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7216(%rbp)
  movq -7208(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_44
  jmp main_assert_fail_44
main_assert_fail_42:
  movq -6752(%rbp), %rax
  addq $8, %rax
  movq %rax, -7224(%rbp)
  movq -7224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7232(%rbp)
  movq -6752(%rbp), %rax
  addq $24, %rax
  movq %rax, -7240(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7240(%rbp), %rsi
  movq -7232(%rbp), %rdx
  syscall
  movq %rax, -7248(%rbp)
  movq $50397203, %rax
  movq %rax, -7256(%rbp)
  jmp main_assert_pass_42
main_assert_pass_44:
  movq $0, %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_45(%rip), %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_46(%rip), %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7264(%rbp)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7272(%rbp)
  movq -7264(%rbp), %rdi
  movq -7272(%rbp), %rsi
  call lm_rt_str_format
  mov -7280(%rbp), rax
  movq -7280(%rbp), %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7288(%rbp)
  movq -7288(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -7296(%rbp)
  movq -7288(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -7304(%rbp)
  movq -7304(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7312(%rbp)
  movq -7296(%rbp), %rax
  andq -7312(%rbp), %rax
  movq %rax, -7320(%rbp)
  movq -7320(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_47
  jmp main_pr_int_0_47
main_assert_fail_44:
  movq -7216(%rbp), %rax
  addq $8, %rax
  movq %rax, -7328(%rbp)
  movq -7328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7336(%rbp)
  movq -7216(%rbp), %rax
  addq $24, %rax
  movq %rax, -7344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7344(%rbp), %rsi
  movq -7336(%rbp), %rdx
  syscall
  movq %rax, -7352(%rbp)
  movq $50397203, %rax
  movq %rax, -7360(%rbp)
  jmp main_assert_pass_44
main_pr_ptr_0_47:
  movq -7288(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7368(%rbp)
  movq -7288(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7376(%rbp)
  movq -7368(%rbp), %rax
  orq -7376(%rbp), %rax
  movq %rax, -7384(%rbp)
  movq -7384(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_47
  jmp main_pr_obj_0_47
main_pr_int_0_47:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -7392(%rbp)
  movq $11, %rax
  movq -7392(%rbp), %rdx
  movl %eax, (%rdx)
  movq -7392(%rbp), %rax
  addq $4, %rax
  movq %rax, -7400(%rbp)
  movq $0, %rax
  movq -7400(%rbp), %rdx
  movl %eax, (%rdx)
  movq -7392(%rbp), %rax
  addq $63, %rax
  movq %rax, -7408(%rbp)
  movq $0, %rax
  movq -7408(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -7416(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -7408(%rbp), %rax
  movq -7416(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -7424(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -7432(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -7288(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -7440(%rbp)
  movq -7440(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_12
  jmp main_i2s_pos_12
main_pr_nil_0_47:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7448(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7448(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7456(%rbp)
  jmp main_pr_next_0_47
main_pr_obj_0_47:
  movq -7288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7464(%rbp)
  movq -7464(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -7472(%rbp)
  movq -7472(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7480(%rbp)
  movq -7480(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_47
  jmp main_pr_nonstr_0_47
main_pr_next_0_47:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7488(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7488(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7496(%rbp)
  movq $0, %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_48(%rip), %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7504(%rbp)
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7512(%rbp)
  movq -7504(%rbp), %rdi
  movq -7512(%rbp), %rsi
  call lm_key_eq
  mov -7520(%rbp), rax
  movq -7520(%rbp), %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_49(%rip), %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7528(%rbp)
  movq -776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7536(%rbp)
  movq -7528(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_50
  jmp main_assert_fail_50
main_i2s_neg_12:
  movq $1, %rax
  movq -7432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7288(%rbp), %rax
  negq %rax
  movq %rax, -7544(%rbp)
  movq -7544(%rbp), %rax
  movq -7424(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_12
main_i2s_pos_12:
  movq $0, %rax
  movq -7432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7288(%rbp), %rax
  movq -7424(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_12
main_i2s_loop_12:
  movq -7424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7552(%rbp)
  movq -7552(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -7560(%rbp)
  movq -7552(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -7568(%rbp)
  movq -7568(%rbp), %rax
  movq -7424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7560(%rbp), %rax
  addq $48, %rax
  movq %rax, -7576(%rbp)
  movq -7416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7584(%rbp)
  movq -7584(%rbp), %rax
  subq $1, %rax
  movq %rax, -7592(%rbp)
  movq -7576(%rbp), %rax
  movq -7592(%rbp), %rdx
  movb %al, (%rdx)
  movq -7592(%rbp), %rax
  movq -7416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7552(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -7600(%rbp)
  movq -7600(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_12
  jmp main_i2s_sign_12
main_i2s_sign_12:
  movq -7432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7608(%rbp)
  movq -7608(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7616(%rbp)
  movq -7616(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_12
  jmp main_i2s_done_12
main_i2s_minus_12:
  movq -7416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7624(%rbp)
  movq -7624(%rbp), %rax
  subq $1, %rax
  movq %rax, -7632(%rbp)
  movq $45, %rax
  movq -7632(%rbp), %rdx
  movb %al, (%rdx)
  movq -7632(%rbp), %rax
  movq -7416(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_12
main_i2s_done_12:
  movq -7416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7640(%rbp)
  movq -7408(%rbp), %rax
  subq -7640(%rbp), %rax
  movq %rax, -7648(%rbp)
  movq -7392(%rbp), %rax
  addq $8, %rax
  movq %rax, -7656(%rbp)
  movq -7648(%rbp), %rax
  movq -7656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7392(%rbp), %rax
  addq $16, %rax
  movq %rax, -7664(%rbp)
  movq -7648(%rbp), %rax
  movq -7664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7392(%rbp), %rax
  addq $24, %rax
  movq %rax, -7672(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -7680(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -7680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7648(%rbp), %rax
  addq $1, %rax
  movq %rax, -7688(%rbp)
  jmp main_d2s_copy_loop_12
main_d2s_copy_loop_12:
  movq -7680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7696(%rbp)
  movq -7696(%rbp), %rax
  cmpq -7688(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -7704(%rbp)
  movq -7704(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_12
  jmp main_d2s_copy_done_12
main_d2s_copy_body_12:
  movq -7640(%rbp), %rax
  addq -7696(%rbp), %rax
  movq %rax, -7712(%rbp)
  movq -7712(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -7720(%rbp)
  movq -7672(%rbp), %rax
  addq -7696(%rbp), %rax
  movq %rax, -7728(%rbp)
  movq -7720(%rbp), %rax
  movq -7728(%rbp), %rdx
  movb %al, (%rdx)
  movq -7696(%rbp), %rax
  addq $1, %rax
  movq %rax, -7736(%rbp)
  movq -7736(%rbp), %rax
  movq -7680(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_12
main_d2s_copy_done_12:
  movq -7392(%rbp), %rax
  addq $24, %rax
  movq %rax, -7744(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -7752(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -7752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7648(%rbp), %rax
  addq $1, %rax
  movq %rax, -7760(%rbp)
  jmp main_i2s_copy_loop_12
main_i2s_copy_loop_12:
  movq -7752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7768(%rbp)
  movq -7768(%rbp), %rax
  cmpq -7760(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -7776(%rbp)
  movq -7776(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_12
  jmp main_i2s_copy_done_12
main_i2s_copy_body_12:
  movq -7640(%rbp), %rax
  addq -7768(%rbp), %rax
  movq %rax, -7784(%rbp)
  movq -7784(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -7792(%rbp)
  movq -7744(%rbp), %rax
  addq -7768(%rbp), %rax
  movq %rax, -7800(%rbp)
  movq -7792(%rbp), %rax
  movq -7800(%rbp), %rdx
  movb %al, (%rdx)
  movq -7768(%rbp), %rax
  addq $1, %rax
  movq %rax, -7808(%rbp)
  movq -7808(%rbp), %rax
  movq -7752(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_12
main_i2s_copy_done_12:
  movq -7392(%rbp), %rax
  addq $8, %rax
  movq %rax, -7816(%rbp)
  movq -7816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7824(%rbp)
  movq -7392(%rbp), %rax
  addq $24, %rax
  movq %rax, -7832(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7832(%rbp), %rsi
  movq -7824(%rbp), %rdx
  syscall
  movq %rax, -7840(%rbp)
  jmp main_pr_next_0_47
main_pr_str_0_47:
  movq -7288(%rbp), %rax
  addq $8, %rax
  movq %rax, -7848(%rbp)
  movq -7848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7856(%rbp)
  movq -7288(%rbp), %rax
  addq $24, %rax
  movq %rax, -7864(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7864(%rbp), %rsi
  movq -7856(%rbp), %rdx
  syscall
  movq %rax, -7872(%rbp)
  jmp main_pr_next_0_47
main_pr_enum_0_47:
  movq -7288(%rbp), %rdi
  call lm_enum_to_str
  mov -7880(%rbp), rax
  movq -7880(%rbp), %rax
  addq $8, %rax
  movq %rax, -7888(%rbp)
  movq -7888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7896(%rbp)
  movq -7880(%rbp), %rax
  addq $24, %rax
  movq %rax, -7904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7904(%rbp), %rsi
  movq -7896(%rbp), %rdx
  syscall
  movq %rax, -7912(%rbp)
  jmp main_pr_next_0_47
main_pr_list_0_47:
  movq -7288(%rbp), %rdi
  call lm_list_to_str
  mov -7920(%rbp), rax
  movq -7920(%rbp), %rax
  addq $8, %rax
  movq %rax, -7928(%rbp)
  movq -7928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7936(%rbp)
  movq -7920(%rbp), %rax
  addq $24, %rax
  movq %rax, -7944(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7944(%rbp), %rsi
  movq -7936(%rbp), %rdx
  syscall
  movq %rax, -7952(%rbp)
  jmp main_pr_next_0_47
main_pr_nonstr_0_47:
  movq -7464(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7960(%rbp)
  movq -7960(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_47
  jmp main_pr_list_0_47
main_assert_pass_50:
  movq $0, %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_51(%rip), %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_52(%rip), %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7968(%rbp)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7976(%rbp)
  movq -7968(%rbp), %rdi
  movq -7976(%rbp), %rsi
  call lm_rt_str_format
  mov -7984(%rbp), rax
  movq -7984(%rbp), %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7992(%rbp)
  movq -7992(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -8000(%rbp)
  movq -7992(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -8008(%rbp)
  movq -8008(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8016(%rbp)
  movq -8000(%rbp), %rax
  andq -8016(%rbp), %rax
  movq %rax, -8024(%rbp)
  movq -8024(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_53
  jmp main_pr_int_0_53
main_assert_fail_50:
  movq -7536(%rbp), %rax
  addq $8, %rax
  movq %rax, -8032(%rbp)
  movq -8032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8040(%rbp)
  movq -7536(%rbp), %rax
  addq $24, %rax
  movq %rax, -8048(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8048(%rbp), %rsi
  movq -8040(%rbp), %rdx
  syscall
  movq %rax, -8056(%rbp)
  movq $50397203, %rax
  movq %rax, -8064(%rbp)
  jmp main_assert_pass_50
main_pr_ptr_0_53:
  movq -7992(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8072(%rbp)
  movq -7992(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8080(%rbp)
  movq -8072(%rbp), %rax
  orq -8080(%rbp), %rax
  movq %rax, -8088(%rbp)
  movq -8088(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_53
  jmp main_pr_obj_0_53
main_pr_int_0_53:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -8096(%rbp)
  movq $11, %rax
  movq -8096(%rbp), %rdx
  movl %eax, (%rdx)
  movq -8096(%rbp), %rax
  addq $4, %rax
  movq %rax, -8104(%rbp)
  movq $0, %rax
  movq -8104(%rbp), %rdx
  movl %eax, (%rdx)
  movq -8096(%rbp), %rax
  addq $63, %rax
  movq %rax, -8112(%rbp)
  movq $0, %rax
  movq -8112(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -8120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -8112(%rbp), %rax
  movq -8120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -8128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -8136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -7992(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -8144(%rbp)
  movq -8144(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_13
  jmp main_i2s_pos_13
main_pr_nil_0_53:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8152(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8152(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8160(%rbp)
  jmp main_pr_next_0_53
main_pr_obj_0_53:
  movq -7992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8168(%rbp)
  movq -8168(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -8176(%rbp)
  movq -8176(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8184(%rbp)
  movq -8184(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_53
  jmp main_pr_nonstr_0_53
main_pr_next_0_53:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8192(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8192(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8200(%rbp)
  movq $0, %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_54(%rip), %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8208(%rbp)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8216(%rbp)
  movq -8208(%rbp), %rdi
  movq -8216(%rbp), %rsi
  call lm_key_eq
  mov -8224(%rbp), rax
  movq -8224(%rbp), %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_55(%rip), %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8232(%rbp)
  movq -840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8240(%rbp)
  movq -8232(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_56
  jmp main_assert_fail_56
main_i2s_neg_13:
  movq $1, %rax
  movq -8136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7992(%rbp), %rax
  negq %rax
  movq %rax, -8248(%rbp)
  movq -8248(%rbp), %rax
  movq -8128(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_13
main_i2s_pos_13:
  movq $0, %rax
  movq -8136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7992(%rbp), %rax
  movq -8128(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_13
main_i2s_loop_13:
  movq -8128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8256(%rbp)
  movq -8256(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -8264(%rbp)
  movq -8256(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -8272(%rbp)
  movq -8272(%rbp), %rax
  movq -8128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -8264(%rbp), %rax
  addq $48, %rax
  movq %rax, -8280(%rbp)
  movq -8120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8288(%rbp)
  movq -8288(%rbp), %rax
  subq $1, %rax
  movq %rax, -8296(%rbp)
  movq -8280(%rbp), %rax
  movq -8296(%rbp), %rdx
  movb %al, (%rdx)
  movq -8296(%rbp), %rax
  movq -8120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -8256(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -8304(%rbp)
  movq -8304(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_13
  jmp main_i2s_sign_13
main_i2s_sign_13:
  movq -8136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8312(%rbp)
  movq -8312(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8320(%rbp)
  movq -8320(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_13
  jmp main_i2s_done_13
main_i2s_minus_13:
  movq -8120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8328(%rbp)
  movq -8328(%rbp), %rax
  subq $1, %rax
  movq %rax, -8336(%rbp)
  movq $45, %rax
  movq -8336(%rbp), %rdx
  movb %al, (%rdx)
  movq -8336(%rbp), %rax
  movq -8120(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_13
main_i2s_done_13:
  movq -8120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8344(%rbp)
  movq -8112(%rbp), %rax
  subq -8344(%rbp), %rax
  movq %rax, -8352(%rbp)
  movq -8096(%rbp), %rax
  addq $8, %rax
  movq %rax, -8360(%rbp)
  movq -8352(%rbp), %rax
  movq -8360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -8096(%rbp), %rax
  addq $16, %rax
  movq %rax, -8368(%rbp)
  movq -8352(%rbp), %rax
  movq -8368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -8096(%rbp), %rax
  addq $24, %rax
  movq %rax, -8376(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -8384(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -8384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -8352(%rbp), %rax
  addq $1, %rax
  movq %rax, -8392(%rbp)
  jmp main_d2s_copy_loop_13
main_d2s_copy_loop_13:
  movq -8384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8400(%rbp)
  movq -8400(%rbp), %rax
  cmpq -8392(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -8408(%rbp)
  movq -8408(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_13
  jmp main_d2s_copy_done_13
main_d2s_copy_body_13:
  movq -8344(%rbp), %rax
  addq -8400(%rbp), %rax
  movq %rax, -8416(%rbp)
  movq -8416(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -8424(%rbp)
  movq -8376(%rbp), %rax
  addq -8400(%rbp), %rax
  movq %rax, -8432(%rbp)
  movq -8424(%rbp), %rax
  movq -8432(%rbp), %rdx
  movb %al, (%rdx)
  movq -8400(%rbp), %rax
  addq $1, %rax
  movq %rax, -8440(%rbp)
  movq -8440(%rbp), %rax
  movq -8384(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_13
main_d2s_copy_done_13:
  movq -8096(%rbp), %rax
  addq $24, %rax
  movq %rax, -8448(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -8456(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -8456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -8352(%rbp), %rax
  addq $1, %rax
  movq %rax, -8464(%rbp)
  jmp main_i2s_copy_loop_13
main_i2s_copy_loop_13:
  movq -8456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8472(%rbp)
  movq -8472(%rbp), %rax
  cmpq -8464(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -8480(%rbp)
  movq -8480(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_13
  jmp main_i2s_copy_done_13
main_i2s_copy_body_13:
  movq -8344(%rbp), %rax
  addq -8472(%rbp), %rax
  movq %rax, -8488(%rbp)
  movq -8488(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -8496(%rbp)
  movq -8448(%rbp), %rax
  addq -8472(%rbp), %rax
  movq %rax, -8504(%rbp)
  movq -8496(%rbp), %rax
  movq -8504(%rbp), %rdx
  movb %al, (%rdx)
  movq -8472(%rbp), %rax
  addq $1, %rax
  movq %rax, -8512(%rbp)
  movq -8512(%rbp), %rax
  movq -8456(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_13
main_i2s_copy_done_13:
  movq -8096(%rbp), %rax
  addq $8, %rax
  movq %rax, -8520(%rbp)
  movq -8520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8528(%rbp)
  movq -8096(%rbp), %rax
  addq $24, %rax
  movq %rax, -8536(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8536(%rbp), %rsi
  movq -8528(%rbp), %rdx
  syscall
  movq %rax, -8544(%rbp)
  jmp main_pr_next_0_53
main_pr_str_0_53:
  movq -7992(%rbp), %rax
  addq $8, %rax
  movq %rax, -8552(%rbp)
  movq -8552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8560(%rbp)
  movq -7992(%rbp), %rax
  addq $24, %rax
  movq %rax, -8568(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8568(%rbp), %rsi
  movq -8560(%rbp), %rdx
  syscall
  movq %rax, -8576(%rbp)
  jmp main_pr_next_0_53
main_pr_enum_0_53:
  movq -7992(%rbp), %rdi
  call lm_enum_to_str
  mov -8584(%rbp), rax
  movq -8584(%rbp), %rax
  addq $8, %rax
  movq %rax, -8592(%rbp)
  movq -8592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8600(%rbp)
  movq -8584(%rbp), %rax
  addq $24, %rax
  movq %rax, -8608(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8608(%rbp), %rsi
  movq -8600(%rbp), %rdx
  syscall
  movq %rax, -8616(%rbp)
  jmp main_pr_next_0_53
main_pr_list_0_53:
  movq -7992(%rbp), %rdi
  call lm_list_to_str
  mov -8624(%rbp), rax
  movq -8624(%rbp), %rax
  addq $8, %rax
  movq %rax, -8632(%rbp)
  movq -8632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8640(%rbp)
  movq -8624(%rbp), %rax
  addq $24, %rax
  movq %rax, -8648(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8648(%rbp), %rsi
  movq -8640(%rbp), %rdx
  syscall
  movq %rax, -8656(%rbp)
  jmp main_pr_next_0_53
main_pr_nonstr_0_53:
  movq -8168(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8664(%rbp)
  movq -8664(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_53
  jmp main_pr_list_0_53
main_assert_pass_56:
  movq $0, %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_57(%rip), %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8672(%rbp)
  movq -864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8680(%rbp)
  movq -8672(%rbp), %rdi
  movq -8680(%rbp), %rsi
  call _builtin_string_byte_at
  mov -8688(%rbp), rax
  movq -8688(%rbp), %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_58(%rip), %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8696(%rbp)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8704(%rbp)
  movq -8696(%rbp), %rdi
  movq -8704(%rbp), %rsi
  call lm_key_eq
  mov -8712(%rbp), rax
  movq -8712(%rbp), %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_59(%rip), %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8720(%rbp)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8728(%rbp)
  movq -8720(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_60
  jmp main_assert_fail_60
main_assert_fail_56:
  movq -8240(%rbp), %rax
  addq $8, %rax
  movq %rax, -8736(%rbp)
  movq -8736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8744(%rbp)
  movq -8240(%rbp), %rax
  addq $24, %rax
  movq %rax, -8752(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8752(%rbp), %rsi
  movq -8744(%rbp), %rdx
  syscall
  movq %rax, -8760(%rbp)
  movq $50397203, %rax
  movq %rax, -8768(%rbp)
  jmp main_assert_pass_56
main_assert_pass_60:
  movq $0, %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4, %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8776(%rbp)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8784(%rbp)
  movq -8776(%rbp), %rdi
  movq -8784(%rbp), %rsi
  call _builtin_string_byte_at
  mov -8792(%rbp), rax
  movq -8792(%rbp), %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_61(%rip), %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8800(%rbp)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8808(%rbp)
  movq -8800(%rbp), %rdi
  movq -8808(%rbp), %rsi
  call lm_key_eq
  mov -8816(%rbp), rax
  movq -8816(%rbp), %rax
  movq -936(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_62(%rip), %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8824(%rbp)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8832(%rbp)
  movq -8824(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_63
  jmp main_assert_fail_63
main_assert_fail_60:
  movq -8728(%rbp), %rax
  addq $8, %rax
  movq %rax, -8840(%rbp)
  movq -8840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8848(%rbp)
  movq -8728(%rbp), %rax
  addq $24, %rax
  movq %rax, -8856(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8856(%rbp), %rsi
  movq -8848(%rbp), %rdx
  syscall
  movq %rax, -8864(%rbp)
  movq $50397203, %rax
  movq %rax, -8872(%rbp)
  jmp main_assert_pass_60
main_assert_pass_63:
  movq $0, %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8880(%rbp)
  movq -960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8888(%rbp)
  movq -8880(%rbp), %rdi
  movq -8888(%rbp), %rsi
  call _builtin_string_byte_at
  mov -8896(%rbp), rax
  movq -8896(%rbp), %rax
  movq -968(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4, %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8904(%rbp)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8912(%rbp)
  movq -8904(%rbp), %rdi
  movq -8912(%rbp), %rsi
  call _builtin_string_byte_at
  mov -8920(%rbp), rax
  movq -8920(%rbp), %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_64(%rip), %rax
  movq -1000(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8928(%rbp)
  movq -968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8936(%rbp)
  movq -8936(%rbp), %rdi
  call lm_to_string
  mov -8944(%rbp), rax
  movq -8928(%rbp), %rdi
  movq -8944(%rbp), %rsi
  call lm_rt_str_format
  mov -8952(%rbp), rax
  movq -8952(%rbp), %rax
  movq -992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8960(%rbp)
  movq -984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8968(%rbp)
  movq -8968(%rbp), %rdi
  call lm_to_string
  mov -8976(%rbp), rax
  movq -8960(%rbp), %rdi
  movq -8976(%rbp), %rsi
  call lm_rt_str_format
  mov -8984(%rbp), rax
  movq -8984(%rbp), %rax
  movq -1008(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8992(%rbp)
  movq -8992(%rbp), %rax
  movq -992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9000(%rbp)
  movq -9000(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -9008(%rbp)
  movq -9000(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -9016(%rbp)
  movq -9016(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9024(%rbp)
  movq -9008(%rbp), %rax
  andq -9024(%rbp), %rax
  movq %rax, -9032(%rbp)
  movq -9032(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_65
  jmp main_pr_int_0_65
main_assert_fail_63:
  movq -8832(%rbp), %rax
  addq $8, %rax
  movq %rax, -9040(%rbp)
  movq -9040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9048(%rbp)
  movq -8832(%rbp), %rax
  addq $24, %rax
  movq %rax, -9056(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9056(%rbp), %rsi
  movq -9048(%rbp), %rdx
  syscall
  movq %rax, -9064(%rbp)
  movq $50397203, %rax
  movq %rax, -9072(%rbp)
  jmp main_assert_pass_63
main_pr_ptr_0_65:
  movq -9000(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9080(%rbp)
  movq -9000(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9088(%rbp)
  movq -9080(%rbp), %rax
  orq -9088(%rbp), %rax
  movq %rax, -9096(%rbp)
  movq -9096(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_65
  jmp main_pr_obj_0_65
main_pr_int_0_65:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -9104(%rbp)
  movq $11, %rax
  movq -9104(%rbp), %rdx
  movl %eax, (%rdx)
  movq -9104(%rbp), %rax
  addq $4, %rax
  movq %rax, -9112(%rbp)
  movq $0, %rax
  movq -9112(%rbp), %rdx
  movl %eax, (%rdx)
  movq -9104(%rbp), %rax
  addq $63, %rax
  movq %rax, -9120(%rbp)
  movq $0, %rax
  movq -9120(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -9128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -9120(%rbp), %rax
  movq -9128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -9136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -9144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -9000(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -9152(%rbp)
  movq -9152(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_14
  jmp main_i2s_pos_14
main_pr_nil_0_65:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9160(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9168(%rbp)
  jmp main_pr_next_0_65
main_pr_obj_0_65:
  movq -9000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9176(%rbp)
  movq -9176(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -9184(%rbp)
  movq -9184(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9192(%rbp)
  movq -9192(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_65
  jmp main_pr_nonstr_0_65
main_pr_next_0_65:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9200(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9200(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9208(%rbp)
  movq $0, %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_66(%rip), %rax
  movq -1024(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9216(%rbp)
  movq -9216(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -9224(%rbp)
  movq -9216(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -9232(%rbp)
  movq -9232(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9240(%rbp)
  movq -9224(%rbp), %rax
  andq -9240(%rbp), %rax
  movq %rax, -9248(%rbp)
  movq -9248(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_67
  jmp main_pr_int_0_67
main_i2s_neg_14:
  movq $1, %rax
  movq -9144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9000(%rbp), %rax
  negq %rax
  movq %rax, -9256(%rbp)
  movq -9256(%rbp), %rax
  movq -9136(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_14
main_i2s_pos_14:
  movq $0, %rax
  movq -9144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9000(%rbp), %rax
  movq -9136(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_14
main_i2s_loop_14:
  movq -9136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9264(%rbp)
  movq -9264(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -9272(%rbp)
  movq -9264(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -9280(%rbp)
  movq -9280(%rbp), %rax
  movq -9136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9272(%rbp), %rax
  addq $48, %rax
  movq %rax, -9288(%rbp)
  movq -9128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9296(%rbp)
  movq -9296(%rbp), %rax
  subq $1, %rax
  movq %rax, -9304(%rbp)
  movq -9288(%rbp), %rax
  movq -9304(%rbp), %rdx
  movb %al, (%rdx)
  movq -9304(%rbp), %rax
  movq -9128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9264(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -9312(%rbp)
  movq -9312(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_14
  jmp main_i2s_sign_14
main_i2s_sign_14:
  movq -9144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9320(%rbp)
  movq -9320(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9328(%rbp)
  movq -9328(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_14
  jmp main_i2s_done_14
main_i2s_minus_14:
  movq -9128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9336(%rbp)
  movq -9336(%rbp), %rax
  subq $1, %rax
  movq %rax, -9344(%rbp)
  movq $45, %rax
  movq -9344(%rbp), %rdx
  movb %al, (%rdx)
  movq -9344(%rbp), %rax
  movq -9128(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_14
main_i2s_done_14:
  movq -9128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9352(%rbp)
  movq -9120(%rbp), %rax
  subq -9352(%rbp), %rax
  movq %rax, -9360(%rbp)
  movq -9104(%rbp), %rax
  addq $8, %rax
  movq %rax, -9368(%rbp)
  movq -9360(%rbp), %rax
  movq -9368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9104(%rbp), %rax
  addq $16, %rax
  movq %rax, -9376(%rbp)
  movq -9360(%rbp), %rax
  movq -9376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9104(%rbp), %rax
  addq $24, %rax
  movq %rax, -9384(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -9392(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -9392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9360(%rbp), %rax
  addq $1, %rax
  movq %rax, -9400(%rbp)
  jmp main_d2s_copy_loop_14
main_d2s_copy_loop_14:
  movq -9392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9408(%rbp)
  movq -9408(%rbp), %rax
  cmpq -9400(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -9416(%rbp)
  movq -9416(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_14
  jmp main_d2s_copy_done_14
main_d2s_copy_body_14:
  movq -9352(%rbp), %rax
  addq -9408(%rbp), %rax
  movq %rax, -9424(%rbp)
  movq -9424(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -9432(%rbp)
  movq -9384(%rbp), %rax
  addq -9408(%rbp), %rax
  movq %rax, -9440(%rbp)
  movq -9432(%rbp), %rax
  movq -9440(%rbp), %rdx
  movb %al, (%rdx)
  movq -9408(%rbp), %rax
  addq $1, %rax
  movq %rax, -9448(%rbp)
  movq -9448(%rbp), %rax
  movq -9392(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_14
main_d2s_copy_done_14:
  movq -9104(%rbp), %rax
  addq $24, %rax
  movq %rax, -9456(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -9464(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -9464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9360(%rbp), %rax
  addq $1, %rax
  movq %rax, -9472(%rbp)
  jmp main_i2s_copy_loop_14
main_i2s_copy_loop_14:
  movq -9464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9480(%rbp)
  movq -9480(%rbp), %rax
  cmpq -9472(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -9488(%rbp)
  movq -9488(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_14
  jmp main_i2s_copy_done_14
main_i2s_copy_body_14:
  movq -9352(%rbp), %rax
  addq -9480(%rbp), %rax
  movq %rax, -9496(%rbp)
  movq -9496(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -9504(%rbp)
  movq -9456(%rbp), %rax
  addq -9480(%rbp), %rax
  movq %rax, -9512(%rbp)
  movq -9504(%rbp), %rax
  movq -9512(%rbp), %rdx
  movb %al, (%rdx)
  movq -9480(%rbp), %rax
  addq $1, %rax
  movq %rax, -9520(%rbp)
  movq -9520(%rbp), %rax
  movq -9464(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_14
main_i2s_copy_done_14:
  movq -9104(%rbp), %rax
  addq $8, %rax
  movq %rax, -9528(%rbp)
  movq -9528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9536(%rbp)
  movq -9104(%rbp), %rax
  addq $24, %rax
  movq %rax, -9544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9544(%rbp), %rsi
  movq -9536(%rbp), %rdx
  syscall
  movq %rax, -9552(%rbp)
  jmp main_pr_next_0_65
main_pr_str_0_65:
  movq -9000(%rbp), %rax
  addq $8, %rax
  movq %rax, -9560(%rbp)
  movq -9560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9568(%rbp)
  movq -9000(%rbp), %rax
  addq $24, %rax
  movq %rax, -9576(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9576(%rbp), %rsi
  movq -9568(%rbp), %rdx
  syscall
  movq %rax, -9584(%rbp)
  jmp main_pr_next_0_65
main_pr_enum_0_65:
  movq -9000(%rbp), %rdi
  call lm_enum_to_str
  mov -9592(%rbp), rax
  movq -9592(%rbp), %rax
  addq $8, %rax
  movq %rax, -9600(%rbp)
  movq -9600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9608(%rbp)
  movq -9592(%rbp), %rax
  addq $24, %rax
  movq %rax, -9616(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9616(%rbp), %rsi
  movq -9608(%rbp), %rdx
  syscall
  movq %rax, -9624(%rbp)
  jmp main_pr_next_0_65
main_pr_list_0_65:
  movq -9000(%rbp), %rdi
  call lm_list_to_str
  mov -9632(%rbp), rax
  movq -9632(%rbp), %rax
  addq $8, %rax
  movq %rax, -9640(%rbp)
  movq -9640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9648(%rbp)
  movq -9632(%rbp), %rax
  addq $24, %rax
  movq %rax, -9656(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9656(%rbp), %rsi
  movq -9648(%rbp), %rdx
  syscall
  movq %rax, -9664(%rbp)
  jmp main_pr_next_0_65
main_pr_nonstr_0_65:
  movq -9176(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9672(%rbp)
  movq -9672(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_65
  jmp main_pr_list_0_65
main_pr_ptr_0_67:
  movq -9216(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9680(%rbp)
  movq -9216(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9688(%rbp)
  movq -9680(%rbp), %rax
  orq -9688(%rbp), %rax
  movq %rax, -9696(%rbp)
  movq -9696(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_67
  jmp main_pr_obj_0_67
main_pr_int_0_67:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -9704(%rbp)
  movq $11, %rax
  movq -9704(%rbp), %rdx
  movl %eax, (%rdx)
  movq -9704(%rbp), %rax
  addq $4, %rax
  movq %rax, -9712(%rbp)
  movq $0, %rax
  movq -9712(%rbp), %rdx
  movl %eax, (%rdx)
  movq -9704(%rbp), %rax
  addq $63, %rax
  movq %rax, -9720(%rbp)
  movq $0, %rax
  movq -9720(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -9728(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -9720(%rbp), %rax
  movq -9728(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -9736(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -9744(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -9216(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -9752(%rbp)
  movq -9752(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_15
  jmp main_i2s_pos_15
main_pr_nil_0_67:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9760(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9760(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9768(%rbp)
  jmp main_pr_next_0_67
main_pr_obj_0_67:
  movq -9216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9776(%rbp)
  movq -9776(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -9784(%rbp)
  movq -9784(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9792(%rbp)
  movq -9792(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_67
  jmp main_pr_nonstr_0_67
main_pr_next_0_67:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9800(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9800(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9808(%rbp)
  movq $0, %rax
  movq -1032(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp main_epilogue
main_i2s_neg_15:
  movq $1, %rax
  movq -9744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9216(%rbp), %rax
  negq %rax
  movq %rax, -9816(%rbp)
  movq -9816(%rbp), %rax
  movq -9736(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_15
main_i2s_pos_15:
  movq $0, %rax
  movq -9744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9216(%rbp), %rax
  movq -9736(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_15
main_i2s_loop_15:
  movq -9736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9824(%rbp)
  movq -9824(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -9832(%rbp)
  movq -9824(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -9840(%rbp)
  movq -9840(%rbp), %rax
  movq -9736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9832(%rbp), %rax
  addq $48, %rax
  movq %rax, -9848(%rbp)
  movq -9728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9856(%rbp)
  movq -9856(%rbp), %rax
  subq $1, %rax
  movq %rax, -9864(%rbp)
  movq -9848(%rbp), %rax
  movq -9864(%rbp), %rdx
  movb %al, (%rdx)
  movq -9864(%rbp), %rax
  movq -9728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9824(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -9872(%rbp)
  movq -9872(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_15
  jmp main_i2s_sign_15
main_i2s_sign_15:
  movq -9744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9880(%rbp)
  movq -9880(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9888(%rbp)
  movq -9888(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_15
  jmp main_i2s_done_15
main_i2s_minus_15:
  movq -9728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9896(%rbp)
  movq -9896(%rbp), %rax
  subq $1, %rax
  movq %rax, -9904(%rbp)
  movq $45, %rax
  movq -9904(%rbp), %rdx
  movb %al, (%rdx)
  movq -9904(%rbp), %rax
  movq -9728(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_15
main_i2s_done_15:
  movq -9728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9912(%rbp)
  movq -9720(%rbp), %rax
  subq -9912(%rbp), %rax
  movq %rax, -9920(%rbp)
  movq -9704(%rbp), %rax
  addq $8, %rax
  movq %rax, -9928(%rbp)
  movq -9920(%rbp), %rax
  movq -9928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9704(%rbp), %rax
  addq $16, %rax
  movq %rax, -9936(%rbp)
  movq -9920(%rbp), %rax
  movq -9936(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9704(%rbp), %rax
  addq $24, %rax
  movq %rax, -9944(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -9952(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -9952(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9920(%rbp), %rax
  addq $1, %rax
  movq %rax, -9960(%rbp)
  jmp main_d2s_copy_loop_15
main_d2s_copy_loop_15:
  movq -9952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9968(%rbp)
  movq -9968(%rbp), %rax
  cmpq -9960(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -9976(%rbp)
  movq -9976(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_15
  jmp main_d2s_copy_done_15
main_d2s_copy_body_15:
  movq -9912(%rbp), %rax
  addq -9968(%rbp), %rax
  movq %rax, -9984(%rbp)
  movq -9984(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -9992(%rbp)
  movq -9944(%rbp), %rax
  addq -9968(%rbp), %rax
  movq %rax, -10000(%rbp)
  movq -9992(%rbp), %rax
  movq -10000(%rbp), %rdx
  movb %al, (%rdx)
  movq -9968(%rbp), %rax
  addq $1, %rax
  movq %rax, -10008(%rbp)
  movq -10008(%rbp), %rax
  movq -9952(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_15
main_d2s_copy_done_15:
  movq -9704(%rbp), %rax
  addq $24, %rax
  movq %rax, -10016(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -10024(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -10024(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9920(%rbp), %rax
  addq $1, %rax
  movq %rax, -10032(%rbp)
  jmp main_i2s_copy_loop_15
main_i2s_copy_loop_15:
  movq -10024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10040(%rbp)
  movq -10040(%rbp), %rax
  cmpq -10032(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -10048(%rbp)
  movq -10048(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_15
  jmp main_i2s_copy_done_15
main_i2s_copy_body_15:
  movq -9912(%rbp), %rax
  addq -10040(%rbp), %rax
  movq %rax, -10056(%rbp)
  movq -10056(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -10064(%rbp)
  movq -10016(%rbp), %rax
  addq -10040(%rbp), %rax
  movq %rax, -10072(%rbp)
  movq -10064(%rbp), %rax
  movq -10072(%rbp), %rdx
  movb %al, (%rdx)
  movq -10040(%rbp), %rax
  addq $1, %rax
  movq %rax, -10080(%rbp)
  movq -10080(%rbp), %rax
  movq -10024(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_15
main_i2s_copy_done_15:
  movq -9704(%rbp), %rax
  addq $8, %rax
  movq %rax, -10088(%rbp)
  movq -10088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10096(%rbp)
  movq -9704(%rbp), %rax
  addq $24, %rax
  movq %rax, -10104(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10104(%rbp), %rsi
  movq -10096(%rbp), %rdx
  syscall
  movq %rax, -10112(%rbp)
  jmp main_pr_next_0_67
main_pr_str_0_67:
  movq -9216(%rbp), %rax
  addq $8, %rax
  movq %rax, -10120(%rbp)
  movq -10120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10128(%rbp)
  movq -9216(%rbp), %rax
  addq $24, %rax
  movq %rax, -10136(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10136(%rbp), %rsi
  movq -10128(%rbp), %rdx
  syscall
  movq %rax, -10144(%rbp)
  jmp main_pr_next_0_67
main_pr_enum_0_67:
  movq -9216(%rbp), %rdi
  call lm_enum_to_str
  mov -10152(%rbp), rax
  movq -10152(%rbp), %rax
  addq $8, %rax
  movq %rax, -10160(%rbp)
  movq -10160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10168(%rbp)
  movq -10152(%rbp), %rax
  addq $24, %rax
  movq %rax, -10176(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10176(%rbp), %rsi
  movq -10168(%rbp), %rdx
  syscall
  movq %rax, -10184(%rbp)
  jmp main_pr_next_0_67
main_pr_list_0_67:
  movq -9216(%rbp), %rdi
  call lm_list_to_str
  mov -10192(%rbp), rax
  movq -10192(%rbp), %rax
  addq $8, %rax
  movq %rax, -10200(%rbp)
  movq -10200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10208(%rbp)
  movq -10192(%rbp), %rax
  addq $24, %rax
  movq %rax, -10216(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10216(%rbp), %rsi
  movq -10208(%rbp), %rdx
  syscall
  movq %rax, -10224(%rbp)
  jmp main_pr_next_0_67
main_pr_nonstr_0_67:
  movq -9776(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10232(%rbp)
  movq -10232(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_67
  jmp main_pr_list_0_67
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
  subq $936, %rsp
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
  movl %eax, (%rdx)
  movq -144(%rbp), %rax
  addq $4, %rax
  movq %rax, -152(%rbp)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movl %eax, (%rdx)
  movq -144(%rbp), %rax
  addq $63, %rax
  movq %rax, -160(%rbp)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -160(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -72(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -192(%rbp)
  movq -192(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_neg_2
  jmp lm_enum_to_str_i2s_pos_2
lm_enum_to_str_has_pay:
  movq -88(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -200(%rbp)
  movq -88(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -208(%rbp)
  movq -208(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -216(%rbp)
  movq -200(%rbp), %rax
  andq -216(%rbp), %rax
  movq %rax, -224(%rbp)
  movq -224(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_pay_ptr
  jmp lm_enum_to_str_pay_int
lm_enum_to_str_pay_int:
  movq -208(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -232(%rbp)
  movq -232(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_pay_float
  jmp lm_enum_to_str_pay_i64
lm_enum_to_str_pay_ptr:
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -240(%rbp)
  movq -240(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -248(%rbp)
  movq -248(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_pay_enum
  jmp lm_enum_to_str_pay_rawstr
lm_enum_to_str_pay_enum:
  movq -88(%rbp), %rdi
  call lm_enum_to_str
  mov -256(%rbp), rax
  movq -256(%rbp), %rax
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
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rax
  jmp lm_enum_to_str_epilogue
lm_enum_to_str_i2s_neg_2:
  movq $1, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  negq %rax
  movq %rax, -272(%rbp)
  movq -272(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_2
lm_enum_to_str_i2s_pos_2:
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_2
lm_enum_to_str_i2s_loop_2:
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -280(%rbp)
  movq -280(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -288(%rbp)
  movq -280(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -296(%rbp)
  movq -296(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  addq $48, %rax
  movq %rax, -304(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -312(%rbp)
  movq -312(%rbp), %rax
  subq $1, %rax
  movq %rax, -320(%rbp)
  movq -304(%rbp), %rax
  movq -320(%rbp), %rdx
  movb %al, (%rdx)
  movq -320(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_loop_2
  jmp lm_enum_to_str_i2s_sign_2
lm_enum_to_str_i2s_sign_2:
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -344(%rbp)
  movq -344(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_minus_2
  jmp lm_enum_to_str_i2s_done_2
lm_enum_to_str_i2s_minus_2:
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -352(%rbp)
  movq -352(%rbp), %rax
  subq $1, %rax
  movq %rax, -360(%rbp)
  movq $45, %rax
  movq -360(%rbp), %rdx
  movb %al, (%rdx)
  movq -360(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_done_2
lm_enum_to_str_i2s_done_2:
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -160(%rbp), %rax
  subq -368(%rbp), %rax
  movq %rax, -376(%rbp)
  movq -144(%rbp), %rax
  addq $8, %rax
  movq %rax, -384(%rbp)
  movq -376(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  addq $16, %rax
  movq %rax, -392(%rbp)
  movq -376(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  addq $24, %rax
  movq %rax, -400(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -408(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -376(%rbp), %rax
  addq $1, %rax
  movq %rax, -416(%rbp)
  jmp lm_enum_to_str_d2s_copy_loop_2
lm_enum_to_str_d2s_copy_loop_2:
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  cmpq -416(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_d2s_copy_body_2
  jmp lm_enum_to_str_d2s_copy_done_2
lm_enum_to_str_d2s_copy_body_2:
  movq -368(%rbp), %rax
  addq -424(%rbp), %rax
  movq %rax, -440(%rbp)
  movq -440(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -400(%rbp), %rax
  addq -424(%rbp), %rax
  movq %rax, -456(%rbp)
  movq -448(%rbp), %rax
  movq -456(%rbp), %rdx
  movb %al, (%rdx)
  movq -424(%rbp), %rax
  addq $1, %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_d2s_copy_loop_2
lm_enum_to_str_d2s_copy_done_2:
  movq -144(%rbp), %rax
  addq $24, %rax
  movq %rax, -472(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -480(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -376(%rbp), %rax
  addq $1, %rax
  movq %rax, -488(%rbp)
  jmp lm_enum_to_str_i2s_copy_loop_2
lm_enum_to_str_i2s_copy_loop_2:
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  cmpq -488(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_copy_body_2
  jmp lm_enum_to_str_i2s_copy_done_2
lm_enum_to_str_i2s_copy_body_2:
  movq -368(%rbp), %rax
  addq -496(%rbp), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -472(%rbp), %rax
  addq -496(%rbp), %rax
  movq %rax, -528(%rbp)
  movq -520(%rbp), %rax
  movq -528(%rbp), %rdx
  movb %al, (%rdx)
  movq -496(%rbp), %rax
  addq $1, %rax
  movq %rax, -536(%rbp)
  movq -536(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_copy_loop_2
lm_enum_to_str_i2s_copy_done_2:
  movq -144(%rbp), %rax
  jmp lm_enum_to_str_epilogue
lm_enum_to_str_pay_float:
  movq $184614912, %rax
  movq %rax, -544(%rbp)
  movq $184614912, %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rdi
  call lm_str_alloc
  mov -560(%rbp), rax
  movq -560(%rbp), %rax
  addq $24, %rax
  movq %rax, -568(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -576(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -552(%rbp), %rax
  addq $1, %rax
  movq %rax, -584(%rbp)
  jmp lm_enum_to_str_f2s_copy_loop_1
lm_enum_to_str_pay_i64:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -592(%rbp)
  movq $11, %rax
  movq -592(%rbp), %rdx
  movl %eax, (%rdx)
  movq -592(%rbp), %rax
  addq $4, %rax
  movq %rax, -600(%rbp)
  movq $0, %rax
  movq -600(%rbp), %rdx
  movl %eax, (%rdx)
  movq -592(%rbp), %rax
  addq $63, %rax
  movq %rax, -608(%rbp)
  movq $0, %rax
  movq -608(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -616(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -608(%rbp), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -624(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -632(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -88(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -640(%rbp)
  movq -640(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_neg_3
  jmp lm_enum_to_str_i2s_pos_3
lm_enum_to_str_f2s_copy_loop_1:
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  cmpq -584(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_f2s_copy_body_1
  jmp lm_enum_to_str_f2s_copy_done_1
lm_enum_to_str_f2s_copy_body_1:
  movq -544(%rbp), %rax
  addq -648(%rbp), %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -568(%rbp), %rax
  addq -648(%rbp), %rax
  movq %rax, -680(%rbp)
  movq -672(%rbp), %rax
  movq -680(%rbp), %rdx
  movb %al, (%rdx)
  movq -648(%rbp), %rax
  addq $1, %rax
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_f2s_copy_loop_1
lm_enum_to_str_f2s_copy_done_1:
  movq $184614912, %rax
  movq -560(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_build_pay
lm_enum_to_str_i2s_neg_3:
  movq $1, %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  negq %rax
  movq %rax, -696(%rbp)
  movq -696(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_3
lm_enum_to_str_i2s_pos_3:
  movq $0, %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_3
lm_enum_to_str_i2s_loop_3:
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -704(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -712(%rbp)
  movq -704(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -720(%rbp)
  movq -720(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -712(%rbp), %rax
  addq $48, %rax
  movq %rax, -728(%rbp)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -736(%rbp), %rax
  subq $1, %rax
  movq %rax, -744(%rbp)
  movq -728(%rbp), %rax
  movq -744(%rbp), %rdx
  movb %al, (%rdx)
  movq -744(%rbp), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -704(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_loop_3
  jmp lm_enum_to_str_i2s_sign_3
lm_enum_to_str_i2s_sign_3:
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -760(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -768(%rbp)
  movq -768(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_minus_3
  jmp lm_enum_to_str_i2s_done_3
lm_enum_to_str_i2s_minus_3:
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -776(%rbp), %rax
  subq $1, %rax
  movq %rax, -784(%rbp)
  movq $45, %rax
  movq -784(%rbp), %rdx
  movb %al, (%rdx)
  movq -784(%rbp), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_done_3
lm_enum_to_str_i2s_done_3:
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -608(%rbp), %rax
  subq -792(%rbp), %rax
  movq %rax, -800(%rbp)
  movq -592(%rbp), %rax
  addq $8, %rax
  movq %rax, -808(%rbp)
  movq -800(%rbp), %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  addq $16, %rax
  movq %rax, -816(%rbp)
  movq -800(%rbp), %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  addq $24, %rax
  movq %rax, -824(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -832(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  movq -800(%rbp), %rax
  addq $1, %rax
  movq %rax, -840(%rbp)
  jmp lm_enum_to_str_d2s_copy_loop_3
lm_enum_to_str_d2s_copy_loop_3:
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -848(%rbp), %rax
  cmpq -840(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -856(%rbp)
  movq -856(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_d2s_copy_body_3
  jmp lm_enum_to_str_d2s_copy_done_3
lm_enum_to_str_d2s_copy_body_3:
  movq -792(%rbp), %rax
  addq -848(%rbp), %rax
  movq %rax, -864(%rbp)
  movq -864(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -824(%rbp), %rax
  addq -848(%rbp), %rax
  movq %rax, -880(%rbp)
  movq -872(%rbp), %rax
  movq -880(%rbp), %rdx
  movb %al, (%rdx)
  movq -848(%rbp), %rax
  addq $1, %rax
  movq %rax, -888(%rbp)
  movq -888(%rbp), %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_d2s_copy_loop_3
lm_enum_to_str_d2s_copy_done_3:
  movq -592(%rbp), %rax
  addq $24, %rax
  movq %rax, -896(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -904(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq -800(%rbp), %rax
  addq $1, %rax
  movq %rax, -912(%rbp)
  jmp lm_enum_to_str_i2s_copy_loop_3
lm_enum_to_str_i2s_copy_loop_3:
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -920(%rbp), %rax
  cmpq -912(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -928(%rbp)
  movq -928(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_copy_body_3
  jmp lm_enum_to_str_i2s_copy_done_3
lm_enum_to_str_i2s_copy_body_3:
  movq -792(%rbp), %rax
  addq -920(%rbp), %rax
  movq %rax, -936(%rbp)
  movq -936(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -896(%rbp), %rax
  addq -920(%rbp), %rax
  movq %rax, -952(%rbp)
  movq -944(%rbp), %rax
  movq -952(%rbp), %rdx
  movb %al, (%rdx)
  movq -920(%rbp), %rax
  addq $1, %rax
  movq %rax, -960(%rbp)
  movq -960(%rbp), %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_copy_loop_3
lm_enum_to_str_i2s_copy_done_3:
  movq -592(%rbp), %rax
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
  movl %eax, (%rdx)
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
  jmp lm_str_concat_concat_c1_loop
lm_str_concat_done:
  movq -112(%rbp), %rax
  jmp lm_str_concat_epilogue
lm_str_concat_concat_c1_loop:
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
  jne lm_str_concat_concat_c1_body
  jmp lm_str_concat_concat_c1_done
lm_str_concat_concat_c1_body:
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
  jmp lm_str_concat_concat_c1_loop
lm_str_concat_concat_c1_done:
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_str_concat_concat_c2_loop
lm_str_concat_concat_c2_loop:
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
  jne lm_str_concat_concat_c2_body
  jmp lm_str_concat_concat_c2_done
lm_str_concat_concat_c2_body:
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
  jmp lm_str_concat_concat_c2_loop
lm_str_concat_concat_c2_done:
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
  subq $536, %rsp
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
  movl %eax, (%rdx)
  movq -200(%rbp), %rax
  addq $4, %rax
  movq %rax, -208(%rbp)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movl %eax, (%rdx)
  movq -200(%rbp), %rax
  addq $63, %rax
  movq %rax, -216(%rbp)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -216(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -184(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -248(%rbp)
  movq -248(%rbp), %rax
  testq %rax, %rax
  jne lm_list_to_str_i2s_neg_4
  jmp lm_list_to_str_i2s_pos_4
lm_list_to_str_e_ptr:
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -256(%rbp)
  movq -256(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rax
  testq %rax, %rax
  jne lm_list_to_str_e_enum
  jmp lm_list_to_str_e_str
lm_list_to_str_e_done:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -272(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -280(%rbp)
  movq -280(%rbp), %rdi
  movq -272(%rbp), %rsi
  call lm_str_concat
  mov -288(%rbp), rax
  movq -288(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_next
lm_list_to_str_i2s_neg_4:
  movq $1, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  negq %rax
  movq %rax, -296(%rbp)
  movq -296(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_i2s_loop_4
lm_list_to_str_i2s_pos_4:
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_i2s_loop_4
lm_list_to_str_i2s_loop_4:
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -304(%rbp)
  movq -304(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -312(%rbp)
  movq -304(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  addq $48, %rax
  movq %rax, -328(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rax
  subq $1, %rax
  movq %rax, -344(%rbp)
  movq -328(%rbp), %rax
  movq -344(%rbp), %rdx
  movb %al, (%rdx)
  movq -344(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -352(%rbp)
  movq -352(%rbp), %rax
  testq %rax, %rax
  jne lm_list_to_str_i2s_loop_4
  jmp lm_list_to_str_i2s_sign_4
lm_list_to_str_i2s_sign_4:
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -360(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rax
  testq %rax, %rax
  jne lm_list_to_str_i2s_minus_4
  jmp lm_list_to_str_i2s_done_4
lm_list_to_str_i2s_minus_4:
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -376(%rbp)
  movq -376(%rbp), %rax
  subq $1, %rax
  movq %rax, -384(%rbp)
  movq $45, %rax
  movq -384(%rbp), %rdx
  movb %al, (%rdx)
  movq -384(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_i2s_done_4
lm_list_to_str_i2s_done_4:
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -216(%rbp), %rax
  subq -392(%rbp), %rax
  movq %rax, -400(%rbp)
  movq -200(%rbp), %rax
  addq $8, %rax
  movq %rax, -408(%rbp)
  movq -400(%rbp), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  addq $16, %rax
  movq %rax, -416(%rbp)
  movq -400(%rbp), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  addq $24, %rax
  movq %rax, -424(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -432(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  addq $1, %rax
  movq %rax, -440(%rbp)
  jmp lm_list_to_str_d2s_copy_loop_4
lm_list_to_str_d2s_copy_loop_4:
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  cmpq -440(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  testq %rax, %rax
  jne lm_list_to_str_d2s_copy_body_4
  jmp lm_list_to_str_d2s_copy_done_4
lm_list_to_str_d2s_copy_body_4:
  movq -392(%rbp), %rax
  addq -448(%rbp), %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -424(%rbp), %rax
  addq -448(%rbp), %rax
  movq %rax, -480(%rbp)
  movq -472(%rbp), %rax
  movq -480(%rbp), %rdx
  movb %al, (%rdx)
  movq -448(%rbp), %rax
  addq $1, %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_d2s_copy_loop_4
lm_list_to_str_d2s_copy_done_4:
  movq -200(%rbp), %rax
  addq $24, %rax
  movq %rax, -496(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -504(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  addq $1, %rax
  movq %rax, -512(%rbp)
  jmp lm_list_to_str_i2s_copy_loop_4
lm_list_to_str_i2s_copy_loop_4:
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  cmpq -512(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rax
  testq %rax, %rax
  jne lm_list_to_str_i2s_copy_body_4
  jmp lm_list_to_str_i2s_copy_done_4
lm_list_to_str_i2s_copy_body_4:
  movq -392(%rbp), %rax
  addq -520(%rbp), %rax
  movq %rax, -536(%rbp)
  movq -536(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -496(%rbp), %rax
  addq -520(%rbp), %rax
  movq %rax, -552(%rbp)
  movq -544(%rbp), %rax
  movq -552(%rbp), %rdx
  movb %al, (%rdx)
  movq -520(%rbp), %rax
  addq $1, %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_i2s_copy_loop_4
lm_list_to_str_i2s_copy_done_4:
  movq -200(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_e_done
lm_list_to_str_e_enum:
  movq -184(%rbp), %rdi
  call lm_enum_to_str
  mov -568(%rbp), rax
  movq -568(%rbp), %rax
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
  subq $472, %rsp
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
  setae %al
  movzbq %al, %rax
  movq %rax, -72(%rbp)
  movq -48(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -80(%rbp)
  movq -80(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -88(%rbp)
  movq -72(%rbp), %rax
  andq -88(%rbp), %rax
  movq %rax, -96(%rbp)
  movq -56(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -104(%rbp)
  movq -56(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -112(%rbp)
  movq -112(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -120(%rbp)
  movq -104(%rbp), %rax
  andq -120(%rbp), %rax
  movq %rax, -128(%rbp)
  movq -96(%rbp), %rax
  andq -128(%rbp), %rax
  movq %rax, -136(%rbp)
  movq -136(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_chk_enum
  jmp lm_key_eq_ret_false
lm_key_eq_loop_init:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_key_eq_loop_cond
lm_key_eq_loop_cond:
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -152(%rbp)
  movq -48(%rbp), %rax
  addq -152(%rbp), %rax
  movq %rax, -160(%rbp)
  movq -56(%rbp), %rax
  addq -152(%rbp), %rax
  movq %rax, -168(%rbp)
  movq -160(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -176(%rbp)
  movq -168(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -184(%rbp)
  movq -176(%rbp), %rax
  cmpq -184(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -192(%rbp)
  movq -192(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_ret_false
  jmp lm_key_eq_check_end
lm_key_eq_check_end:
  movq -176(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -200(%rbp)
  movq -200(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_ret_true
  jmp lm_key_eq_advance
lm_key_eq_advance:
  movq -152(%rbp), %rax
  addq $1, %rax
  movq %rax, -208(%rbp)
  movq -208(%rbp), %rax
  movq -144(%rbp), %rdx
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
  movq %rax, -216(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -224(%rbp)
  movq -216(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -232(%rbp)
  movq -224(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -240(%rbp)
  movq -232(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -248(%rbp)
  movq -240(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -256(%rbp)
  movq -248(%rbp), %rax
  andq -256(%rbp), %rax
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_str_hdr_cmp
  jmp lm_key_eq_enum_chk
lm_key_eq_str_hdr_cmp:
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -272(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -280(%rbp)
  movq -56(%rbp), %rax
  addq $8, %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -296(%rbp)
  movq -280(%rbp), %rax
  cmpq -296(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -304(%rbp)
  movq -304(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_str_hdr_bytes
  jmp lm_key_eq_ret_false
lm_key_eq_enum_chk:
  movq -216(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -312(%rbp)
  movq -224(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -320(%rbp)
  movq -312(%rbp), %rax
  andq -320(%rbp), %rax
  movq %rax, -328(%rbp)
  movq -312(%rbp), %rax
  orq -320(%rbp), %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_enum_only
  jmp lm_key_eq_loop_init
lm_key_eq_str_hdr_bytes:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -344(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_key_eq_str_hdr_loop
lm_key_eq_str_hdr_loop:
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -352(%rbp)
  movq -352(%rbp), %rax
  cmpq -280(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -360(%rbp)
  movq -360(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_ret_true
  jmp lm_key_eq_str_hdr_body
lm_key_eq_str_hdr_body:
  movq -48(%rbp), %rax
  addq $24, %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rax
  addq -352(%rbp), %rax
  movq %rax, -376(%rbp)
  movq -376(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -384(%rbp)
  movq -56(%rbp), %rax
  addq $24, %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rax
  addq -352(%rbp), %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -384(%rbp), %rax
  cmpq -408(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -416(%rbp)
  movq -352(%rbp), %rax
  addq $1, %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_ret_false
  jmp lm_key_eq_str_hdr_loop
lm_key_eq_enum_only:
  movq -328(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_enum_cmp
  jmp lm_key_eq_ret_false
lm_key_eq_enum_cmp:
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -56(%rbp), %rax
  addq $8, %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -440(%rbp), %rax
  cmpq -456(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_pay_cmp
  jmp lm_key_eq_ret_false
lm_key_eq_pay_cmp:
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -56(%rbp), %rax
  addq $16, %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -480(%rbp), %rdi
  movq -496(%rbp), %rsi
  call lm_key_eq
  mov -504(%rbp), rax
  movq -504(%rbp), %rax
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
  subq $808, %rsp
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
  movq $184614912, %rax
  movq %rax, -120(%rbp)
  movq $184614912, %rax
  movq %rax, -128(%rbp)
  movq -128(%rbp), %rdi
  call lm_str_alloc
  mov -136(%rbp), rax
  movq -136(%rbp), %rax
  addq $24, %rax
  movq %rax, -144(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  addq $1, %rax
  movq %rax, -160(%rbp)
  jmp lm_rt_str_format_f2s_copy_loop_2
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
lm_rt_str_format_f2s_copy_loop_2:
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rax
  cmpq -160(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -296(%rbp)
  movq -296(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_f2s_copy_body_2
  jmp lm_rt_str_format_f2s_copy_done_2
lm_rt_str_format_f2s_copy_body_2:
  movq -120(%rbp), %rax
  addq -288(%rbp), %rax
  movq %rax, -304(%rbp)
  movq -304(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -312(%rbp)
  movq -144(%rbp), %rax
  addq -288(%rbp), %rax
  movq %rax, -320(%rbp)
  movq -312(%rbp), %rax
  movq -320(%rbp), %rdx
  movb %al, (%rdx)
  movq -288(%rbp), %rax
  addq $1, %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_f2s_copy_loop_2
lm_rt_str_format_f2s_copy_done_2:
  movq $184614912, %rax
  movq -136(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_slen_prep
lm_rt_str_format_fmt_num_loop:
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -344(%rbp)
  movq -336(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -352(%rbp)
  movq -344(%rbp), %rax
  addq $48, %rax
  movq %rax, -360(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rax
  subq $1, %rax
  movq %rax, -376(%rbp)
  movq -360(%rbp), %rax
  movq -376(%rbp), %rdx
  movb %al, (%rdx)
  movq -352(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -376(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  cmpq $1, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -384(%rbp)
  movq -384(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_num_loop
  jmp lm_rt_str_format_fmt_num_done
lm_rt_str_format_fmt_num_done:
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -176(%rbp), %rax
  subq -392(%rbp), %rax
  movq %rax, -400(%rbp)
  movq -392(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_proc
lm_rt_str_format_fmt_is_enum_p:
  movq -56(%rbp), %rdi
  call lm_enum_to_str
  mov -408(%rbp), rax
  movq -408(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_slen_prep
lm_rt_str_format_fmt_is_enum_c:
  movq -200(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -416(%rbp)
  movq -416(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_is_enum_p
  jmp lm_rt_str_format_fmt_is_list
lm_rt_str_format_fmt_is_list:
  movq -56(%rbp), %rdi
  call lm_list_to_str
  mov -424(%rbp), rax
  movq -424(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_slen_prep
lm_rt_str_format_fmt_is_rawstr:
  movq -56(%rbp), %rax
  addq $24, %rax
  movq %rax, -432(%rbp)
  movq -56(%rbp), %rax
  addq $8, %rax
  movq %rax, -440(%rbp)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -432(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -448(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_proc
lm_rt_str_format_fmt_scan_loop:
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  cmpq -248(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_no_pct
  jmp lm_rt_str_format_fmt_check_s
lm_rt_str_format_fmt_check_s:
  movq -232(%rbp), %rax
  addq -456(%rbp), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -480(%rbp), %rax
  cmpq $37, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -488(%rbp)
  movq -456(%rbp), %rax
  addq $1, %rax
  movq %rax, -496(%rbp)
  movq -232(%rbp), %rax
  addq -496(%rbp), %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  cmpq $115, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -520(%rbp)
  movq -488(%rbp), %rax
  andq -520(%rbp), %rax
  movq %rax, -528(%rbp)
  movq -480(%rbp), %rax
  cmpq $123, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -536(%rbp)
  movq -512(%rbp), %rax
  cmpq $125, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -544(%rbp)
  movq -536(%rbp), %rax
  andq -544(%rbp), %rax
  movq %rax, -552(%rbp)
  movq -528(%rbp), %rax
  orq -552(%rbp), %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_do_replace
  jmp lm_rt_str_format_fmt_scan_next
lm_rt_str_format_fmt_scan_next:
  movq -456(%rbp), %rax
  addq $1, %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_scan_loop
lm_rt_str_format_fmt_no_pct:
  movq -48(%rbp), %rax
  jmp lm_rt_str_format_epilogue
lm_rt_str_format_fmt_do_replace:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -456(%rbp), %rax
  addq $2, %rax
  movq %rax, -592(%rbp)
  movq -248(%rbp), %rax
  subq -592(%rbp), %rax
  movq %rax, -600(%rbp)
  movq -456(%rbp), %rax
  addq -584(%rbp), %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  addq -600(%rbp), %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rdi
  call lm_str_alloc
  mov -624(%rbp), rax
  movq -624(%rbp), %rax
  addq $24, %rax
  movq %rax, -632(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -640(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_c1_loop
lm_rt_str_format_fmt_c1_loop:
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  cmpq -456(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_c1_body
  jmp lm_rt_str_format_fmt_c1_done
lm_rt_str_format_fmt_c1_body:
  movq -232(%rbp), %rax
  addq -648(%rbp), %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -632(%rbp), %rax
  addq -648(%rbp), %rax
  movq %rax, -680(%rbp)
  movq -672(%rbp), %rax
  movq -680(%rbp), %rdx
  movb %al, (%rdx)
  movq -648(%rbp), %rax
  addq $1, %rax
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_c1_loop
lm_rt_str_format_fmt_c1_done:
  movq $0, %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_c2_loop
lm_rt_str_format_fmt_c2_loop:
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -696(%rbp), %rax
  cmpq -584(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -704(%rbp)
  movq -704(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_c2_body
  jmp lm_rt_str_format_fmt_c2_done
lm_rt_str_format_fmt_c2_body:
  movq -576(%rbp), %rax
  addq -696(%rbp), %rax
  movq %rax, -712(%rbp)
  movq -712(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -456(%rbp), %rax
  addq -696(%rbp), %rax
  movq %rax, -728(%rbp)
  movq -632(%rbp), %rax
  addq -728(%rbp), %rax
  movq %rax, -736(%rbp)
  movq -720(%rbp), %rax
  movq -736(%rbp), %rdx
  movb %al, (%rdx)
  movq -696(%rbp), %rax
  addq $1, %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_c2_loop
lm_rt_str_format_fmt_c2_done:
  movq $0, %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_c3_loop
lm_rt_str_format_fmt_c3_loop:
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rax
  cmpq -600(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -760(%rbp)
  movq -760(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_c3_body
  jmp lm_rt_str_format_fmt_c3_done
lm_rt_str_format_fmt_c3_body:
  movq -456(%rbp), %rax
  addq $2, %rax
  movq %rax, -768(%rbp)
  movq -768(%rbp), %rax
  addq -752(%rbp), %rax
  movq %rax, -776(%rbp)
  movq -232(%rbp), %rax
  addq -776(%rbp), %rax
  movq %rax, -784(%rbp)
  movq -784(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -456(%rbp), %rax
  addq -584(%rbp), %rax
  movq %rax, -800(%rbp)
  movq -800(%rbp), %rax
  addq -752(%rbp), %rax
  movq %rax, -808(%rbp)
  movq -632(%rbp), %rax
  addq -808(%rbp), %rax
  movq %rax, -816(%rbp)
  movq -792(%rbp), %rax
  movq -816(%rbp), %rdx
  movb %al, (%rdx)
  movq -752(%rbp), %rax
  addq $1, %rax
  movq %rax, -824(%rbp)
  movq -824(%rbp), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_c3_loop
lm_rt_str_format_fmt_c3_done:
  movq -632(%rbp), %rax
  addq -616(%rbp), %rax
  movq %rax, -832(%rbp)
  movq $0, %rax
  movq -832(%rbp), %rdx
  movb %al, (%rdx)
  movq -624(%rbp), %rax
  addq $8, %rax
  movq %rax, -840(%rbp)
  movq -616(%rbp), %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
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

.globl lm_to_string
lm_to_string:
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
lm_to_string_entry:
  movq $9, %rax
  movq $0, %rdi
  movq $32, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -56(%rbp)
  movq -48(%rbp), %rax
  jmp lm_to_string_epilogue
lm_to_string_epilogue:
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
.Lfunc_end_lm_to_string:

.globl _builtin_string_byte_at
_builtin_string_byte_at:
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
_builtin_string_byte_at_entry:
  movq -48(%rbp), %rax
  addq $24, %rax
  movq %rax, -64(%rbp)
  movq -64(%rbp), %rax
  addq -56(%rbp), %rax
  movq %rax, -72(%rbp)
  movq -72(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -80(%rbp)
  movq -80(%rbp), %rax
  movq %rax, -88(%rbp)
  movq -88(%rbp), %rax
  jmp _builtin_string_byte_at_epilogue
_builtin_string_byte_at_epilogue:
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
.Lfunc_end__builtin_string_byte_at:

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

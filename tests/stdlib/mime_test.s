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
  .byte 46
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
  .byte 104
  .byte 116
  .byte 109
  .byte 108
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
  .byte 104
  .byte 116
  .byte 109
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
  .byte 99
  .byte 115
  .byte 115
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
  .byte 106
  .byte 115
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
  .byte 106
  .byte 115
  .byte 111
  .byte 110
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
  .byte 120
  .byte 109
  .byte 108
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
  .byte 99
  .byte 115
  .byte 118
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
  .byte 116
  .byte 120
  .byte 116
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
  .byte 112
  .byte 110
  .byte 103
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
  .byte 106
  .byte 112
  .byte 103
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
  .byte 106
  .byte 112
  .byte 101
  .byte 103
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
  .byte 103
  .byte 105
  .byte 102
  .byte 0
.align 8
str_hdr_13:
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
  .byte 119
  .byte 101
  .byte 98
  .byte 112
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
  .byte 115
  .byte 118
  .byte 103
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
  .byte 98
  .byte 109
  .byte 112
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
  .byte 105
  .byte 102
  .byte 102
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
  .byte 105
  .byte 99
  .byte 111
  .byte 0
.align 8
str_hdr_18:
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
  .byte 109
  .byte 112
  .byte 51
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
  .byte 119
  .byte 97
  .byte 118
  .byte 0
.align 8
str_hdr_20:
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
  .byte 111
  .byte 103
  .byte 103
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
  .byte 109
  .byte 112
  .byte 52
  .byte 0
.align 8
str_hdr_22:
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
  .byte 119
  .byte 101
  .byte 98
  .byte 109
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
  .byte 109
  .byte 112
  .byte 101
  .byte 103
  .byte 0
.align 8
str_hdr_24:
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
  .byte 112
  .byte 100
  .byte 102
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
  .byte 122
  .byte 105
  .byte 112
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
  .byte 103
  .byte 122
  .byte 105
  .byte 112
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
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 104
  .byte 116
  .byte 109
  .byte 108
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
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 104
  .byte 116
  .byte 109
  .byte 108
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 99
  .byte 115
  .byte 115
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 106
  .byte 97
  .byte 118
  .byte 97
  .byte 115
  .byte 99
  .byte 114
  .byte 105
  .byte 112
  .byte 116
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
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 106
  .byte 115
  .byte 111
  .byte 110
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 120
  .byte 109
  .byte 108
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 99
  .byte 115
  .byte 118
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 112
  .byte 108
  .byte 97
  .byte 105
  .byte 110
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
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 112
  .byte 110
  .byte 103
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
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 106
  .byte 112
  .byte 101
  .byte 103
  .byte 0
.align 8
str_hdr_37:
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
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 106
  .byte 112
  .byte 101
  .byte 103
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
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 103
  .byte 105
  .byte 102
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
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 119
  .byte 101
  .byte 98
  .byte 112
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
  .byte 13
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 13
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 115
  .byte 118
  .byte 103
  .byte 43
  .byte 120
  .byte 109
  .byte 108
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
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 98
  .byte 109
  .byte 112
  .byte 0
.align 8
str_hdr_42:
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
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 116
  .byte 105
  .byte 102
  .byte 102
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
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 120
  .byte 45
  .byte 105
  .byte 99
  .byte 111
  .byte 110
  .byte 0
.align 8
str_hdr_44:
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
  .byte 97
  .byte 117
  .byte 100
  .byte 105
  .byte 111
  .byte 47
  .byte 109
  .byte 112
  .byte 101
  .byte 103
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
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 97
  .byte 117
  .byte 100
  .byte 105
  .byte 111
  .byte 47
  .byte 119
  .byte 97
  .byte 118
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
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 97
  .byte 117
  .byte 100
  .byte 105
  .byte 111
  .byte 47
  .byte 111
  .byte 103
  .byte 103
  .byte 0
.align 8
str_hdr_47:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 118
  .byte 105
  .byte 100
  .byte 101
  .byte 111
  .byte 47
  .byte 109
  .byte 112
  .byte 52
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
  .byte 118
  .byte 105
  .byte 100
  .byte 101
  .byte 111
  .byte 47
  .byte 119
  .byte 101
  .byte 98
  .byte 109
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
  .byte 118
  .byte 105
  .byte 100
  .byte 101
  .byte 111
  .byte 47
  .byte 109
  .byte 112
  .byte 101
  .byte 103
  .byte 0
.align 8
str_hdr_50:
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
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 112
  .byte 100
  .byte 102
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
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 122
  .byte 105
  .byte 112
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
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 103
  .byte 122
  .byte 105
  .byte 112
  .byte 0
.align 8
str_hdr_53:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 24
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 24
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 111
  .byte 99
  .byte 116
  .byte 101
  .byte 116
  .byte 45
  .byte 115
  .byte 116
  .byte 114
  .byte 101
  .byte 97
  .byte 109
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
str_hdr_55:
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
  .byte 47
  .byte 0
.align 8
str_hdr_56:
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
  .byte 104
  .byte 116
  .byte 109
  .byte 108
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
  .byte 99
  .byte 115
  .byte 115
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
  .byte 106
  .byte 115
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
  .byte 106
  .byte 115
  .byte 111
  .byte 110
  .byte 0
.align 8
str_hdr_60:
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
  .byte 120
  .byte 109
  .byte 108
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
  .byte 99
  .byte 115
  .byte 118
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
  .byte 116
  .byte 120
  .byte 116
  .byte 0
.align 8
str_hdr_63:
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
  .byte 112
  .byte 110
  .byte 103
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
  .byte 106
  .byte 112
  .byte 103
  .byte 0
.align 8
str_hdr_65:
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
  .byte 103
  .byte 105
  .byte 102
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
  .byte 119
  .byte 101
  .byte 98
  .byte 112
  .byte 0
.align 8
str_hdr_67:
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
  .byte 115
  .byte 118
  .byte 103
  .byte 0
.align 8
str_hdr_68:
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
  .byte 98
  .byte 109
  .byte 112
  .byte 0
.align 8
str_hdr_69:
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
  .byte 105
  .byte 102
  .byte 102
  .byte 0
.align 8
str_hdr_70:
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
  .byte 105
  .byte 99
  .byte 111
  .byte 0
.align 8
str_hdr_71:
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
  .byte 109
  .byte 112
  .byte 51
  .byte 0
.align 8
str_hdr_72:
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
  .byte 119
  .byte 97
  .byte 118
  .byte 0
.align 8
str_hdr_73:
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
  .byte 111
  .byte 103
  .byte 103
  .byte 0
.align 8
str_hdr_74:
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
  .byte 109
  .byte 112
  .byte 52
  .byte 0
.align 8
str_hdr_75:
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
  .byte 119
  .byte 101
  .byte 98
  .byte 109
  .byte 0
.align 8
str_hdr_76:
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
  .byte 109
  .byte 112
  .byte 101
  .byte 103
  .byte 0
.align 8
str_hdr_77:
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
  .byte 112
  .byte 100
  .byte 102
  .byte 0
.align 8
str_hdr_78:
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
  .byte 122
  .byte 105
  .byte 112
  .byte 0
.align 8
str_hdr_79:
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
  .byte 103
  .byte 122
  .byte 105
  .byte 112
  .byte 0
.align 8
str_hdr_80:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_81:
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 99
  .byte 115
  .byte 115
  .byte 0
.align 8
str_hdr_82:
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 106
  .byte 97
  .byte 118
  .byte 97
  .byte 115
  .byte 99
  .byte 114
  .byte 105
  .byte 112
  .byte 116
  .byte 0
.align 8
str_hdr_83:
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
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 106
  .byte 115
  .byte 111
  .byte 110
  .byte 0
.align 8
str_hdr_84:
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 120
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_85:
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 99
  .byte 115
  .byte 118
  .byte 0
.align 8
str_hdr_86:
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 112
  .byte 108
  .byte 97
  .byte 105
  .byte 110
  .byte 0
.align 8
str_hdr_87:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 112
  .byte 110
  .byte 103
  .byte 0
.align 8
str_hdr_88:
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
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 106
  .byte 112
  .byte 101
  .byte 103
  .byte 0
.align 8
str_hdr_89:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 103
  .byte 105
  .byte 102
  .byte 0
.align 8
str_hdr_90:
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
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 119
  .byte 101
  .byte 98
  .byte 112
  .byte 0
.align 8
str_hdr_91:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 13
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 13
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 115
  .byte 118
  .byte 103
  .byte 43
  .byte 120
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_92:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 98
  .byte 109
  .byte 112
  .byte 0
.align 8
str_hdr_93:
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
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 116
  .byte 105
  .byte 102
  .byte 102
  .byte 0
.align 8
str_hdr_94:
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
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 120
  .byte 45
  .byte 105
  .byte 99
  .byte 111
  .byte 110
  .byte 0
.align 8
str_hdr_95:
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
  .byte 97
  .byte 117
  .byte 100
  .byte 105
  .byte 111
  .byte 47
  .byte 109
  .byte 112
  .byte 101
  .byte 103
  .byte 0
.align 8
str_hdr_96:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 97
  .byte 117
  .byte 100
  .byte 105
  .byte 111
  .byte 47
  .byte 119
  .byte 97
  .byte 118
  .byte 0
.align 8
str_hdr_97:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 97
  .byte 117
  .byte 100
  .byte 105
  .byte 111
  .byte 47
  .byte 111
  .byte 103
  .byte 103
  .byte 0
.align 8
str_hdr_98:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 118
  .byte 105
  .byte 100
  .byte 101
  .byte 111
  .byte 47
  .byte 109
  .byte 112
  .byte 52
  .byte 0
.align 8
str_hdr_99:
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
  .byte 118
  .byte 105
  .byte 100
  .byte 101
  .byte 111
  .byte 47
  .byte 119
  .byte 101
  .byte 98
  .byte 109
  .byte 0
.align 8
str_hdr_100:
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
  .byte 118
  .byte 105
  .byte 100
  .byte 101
  .byte 111
  .byte 47
  .byte 109
  .byte 112
  .byte 101
  .byte 103
  .byte 0
.align 8
str_hdr_101:
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
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 112
  .byte 100
  .byte 102
  .byte 0
.align 8
str_hdr_102:
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
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 122
  .byte 105
  .byte 112
  .byte 0
.align 8
str_hdr_103:
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
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 103
  .byte 122
  .byte 105
  .byte 112
  .byte 0
.align 8
str_hdr_104:
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
  .byte 46
  .byte 0
.align 8
str_hdr_105:
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
str_hdr_106:
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
str_hdr_107:
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
  .byte 65
  .byte 66
  .byte 67
  .byte 68
  .byte 69
  .byte 70
  .byte 71
  .byte 72
  .byte 73
  .byte 74
  .byte 75
  .byte 76
  .byte 77
  .byte 78
  .byte 79
  .byte 80
  .byte 81
  .byte 82
  .byte 83
  .byte 84
  .byte 85
  .byte 86
  .byte 87
  .byte 88
  .byte 89
  .byte 90
  .byte 0
.align 8
str_hdr_108:
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
  .byte 97
  .byte 98
  .byte 99
  .byte 100
  .byte 101
  .byte 102
  .byte 103
  .byte 104
  .byte 105
  .byte 106
  .byte 107
  .byte 108
  .byte 109
  .byte 110
  .byte 111
  .byte 112
  .byte 113
  .byte 114
  .byte 115
  .byte 116
  .byte 117
  .byte 118
  .byte 119
  .byte 120
  .byte 121
  .byte 122
  .byte 0
.align 8
str_hdr_109:
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
  .byte 82
  .byte 117
  .byte 110
  .byte 110
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 77
  .byte 73
  .byte 77
  .byte 69
  .byte 32
  .byte 112
  .byte 97
  .byte 114
  .byte 115
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
  .byte 115
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
str_hdr_110:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_111:
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
  .byte 109
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
  .byte 118
  .byte 97
  .byte 108
  .byte 105
  .byte 100
  .byte 0
.align 8
str_hdr_113:
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
  .byte 101
  .byte 120
  .byte 116
  .byte 0
.align 8
str_hdr_114:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 27
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 27
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 109
  .byte 49
  .byte 46
  .byte 109
  .byte 97
  .byte 105
  .byte 110
  .byte 95
  .byte 116
  .byte 121
  .byte 112
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 0
.align 8
str_hdr_116:
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
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_117:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 25
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 25
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 109
  .byte 49
  .byte 46
  .byte 115
  .byte 117
  .byte 98
  .byte 116
  .byte 121
  .byte 112
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
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_119:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_120:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 21
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 21
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 109
  .byte 49
  .byte 46
  .byte 116
  .byte 111
  .byte 95
  .byte 115
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 40
  .byte 41
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_122:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 52
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 52
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 32
  .byte 32
  .byte 84
  .byte 69
  .byte 88
  .byte 84
  .byte 47
  .byte 72
  .byte 116
  .byte 109
  .byte 108
  .byte 59
  .byte 32
  .byte 99
  .byte 104
  .byte 97
  .byte 114
  .byte 115
  .byte 101
  .byte 116
  .byte 61
  .byte 117
  .byte 116
  .byte 102
  .byte 45
  .byte 56
  .byte 59
  .byte 32
  .byte 66
  .byte 111
  .byte 117
  .byte 110
  .byte 100
  .byte 97
  .byte 114
  .byte 121
  .byte 61
  .byte 115
  .byte 111
  .byte 109
  .byte 101
  .byte 45
  .byte 98
  .byte 111
  .byte 117
  .byte 110
  .byte 100
  .byte 97
  .byte 114
  .byte 121
  .byte 32
  .byte 32
  .byte 0
.align 8
str_hdr_123:
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
  .byte 109
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
  .byte 118
  .byte 97
  .byte 108
  .byte 105
  .byte 100
  .byte 0
.align 8
str_hdr_125:
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
  .byte 101
  .byte 120
  .byte 116
  .byte 0
.align 8
str_hdr_126:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 27
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 27
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 109
  .byte 50
  .byte 46
  .byte 109
  .byte 97
  .byte 105
  .byte 110
  .byte 95
  .byte 116
  .byte 121
  .byte 112
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 0
.align 8
str_hdr_128:
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
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_129:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 25
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 25
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 109
  .byte 50
  .byte 46
  .byte 115
  .byte 117
  .byte 98
  .byte 116
  .byte 121
  .byte 112
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
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_131:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 7
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 7
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 99
  .byte 104
  .byte 97
  .byte 114
  .byte 115
  .byte 101
  .byte 116
  .byte 0
.align 8
str_hdr_132:
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
  .byte 117
  .byte 116
  .byte 102
  .byte 45
  .byte 56
  .byte 0
.align 8
str_hdr_133:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 14
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 14
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 99
  .byte 104
  .byte 97
  .byte 114
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
str_hdr_135:
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
  .byte 98
  .byte 111
  .byte 117
  .byte 110
  .byte 100
  .byte 97
  .byte 114
  .byte 121
  .byte 0
.align 8
str_hdr_136:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 13
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 13
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 115
  .byte 111
  .byte 109
  .byte 101
  .byte 45
  .byte 98
  .byte 111
  .byte 117
  .byte 110
  .byte 100
  .byte 97
  .byte 114
  .byte 121
  .byte 0
.align 8
str_hdr_137:
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
  .byte 98
  .byte 111
  .byte 117
  .byte 110
  .byte 100
  .byte 97
  .byte 114
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
str_hdr_139:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 21
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 21
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 105
  .byte 110
  .byte 118
  .byte 97
  .byte 108
  .byte 105
  .byte 100
  .byte 45
  .byte 109
  .byte 105
  .byte 109
  .byte 101
  .byte 45
  .byte 110
  .byte 111
  .byte 45
  .byte 115
  .byte 108
  .byte 97
  .byte 115
  .byte 104
  .byte 0
.align 8
str_hdr_140:
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
  .byte 109
  .byte 51
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
  .byte 105
  .byte 110
  .byte 118
  .byte 97
  .byte 108
  .byte 105
  .byte 100
  .byte 0
.align 8
str_hdr_142:
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 0
.align 8
str_hdr_143:
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
  .byte 109
  .byte 52
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
  .byte 105
  .byte 110
  .byte 118
  .byte 97
  .byte 108
  .byte 105
  .byte 100
  .byte 0
.align 8
str_hdr_145:
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
  .byte 47
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_146:
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
  .byte 109
  .byte 53
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
  .byte 105
  .byte 110
  .byte 118
  .byte 97
  .byte 108
  .byte 105
  .byte 100
  .byte 0
.align 8
str_hdr_148:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 21
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 21
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 80
  .byte 97
  .byte 114
  .byte 115
  .byte 105
  .byte 110
  .byte 103
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
str_hdr_149:
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
  .byte 82
  .byte 117
  .byte 110
  .byte 110
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 77
  .byte 73
  .byte 77
  .byte 69
  .byte 32
  .byte 112
  .byte 97
  .byte 114
  .byte 97
  .byte 109
  .byte 101
  .byte 116
  .byte 101
  .byte 114
  .byte 115
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
  .byte 115
  .byte 46
  .byte 46
  .byte 46
  .byte 0
.align 8
str_hdr_150:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 7
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 7
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 99
  .byte 104
  .byte 97
  .byte 114
  .byte 115
  .byte 101
  .byte 116
  .byte 0
.align 8
str_hdr_151:
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
  .byte 117
  .byte 116
  .byte 102
  .byte 45
  .byte 56
  .byte 0
.align 8
str_hdr_152:
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
  .byte 98
  .byte 111
  .byte 117
  .byte 110
  .byte 100
  .byte 97
  .byte 114
  .byte 121
  .byte 0
.align 8
str_hdr_153:
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
  .byte 120
  .byte 121
  .byte 122
  .byte 0
.align 8
str_hdr_154:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 7
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 7
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 99
  .byte 104
  .byte 97
  .byte 114
  .byte 115
  .byte 101
  .byte 116
  .byte 0
.align 8
str_hdr_155:
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
  .byte 117
  .byte 116
  .byte 102
  .byte 45
  .byte 56
  .byte 0
.align 8
str_hdr_156:
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
  .byte 103
  .byte 101
  .byte 116
  .byte 32
  .byte 99
  .byte 104
  .byte 97
  .byte 114
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
str_hdr_158:
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
  .byte 98
  .byte 111
  .byte 117
  .byte 110
  .byte 100
  .byte 97
  .byte 114
  .byte 121
  .byte 0
.align 8
str_hdr_159:
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
  .byte 120
  .byte 121
  .byte 122
  .byte 0
.align 8
str_hdr_160:
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
  .byte 103
  .byte 101
  .byte 116
  .byte 32
  .byte 98
  .byte 111
  .byte 117
  .byte 110
  .byte 100
  .byte 97
  .byte 114
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
str_hdr_162:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 7
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 7
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 99
  .byte 104
  .byte 97
  .byte 114
  .byte 115
  .byte 101
  .byte 116
  .byte 0
.align 8
str_hdr_163:
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
  .byte 104
  .byte 97
  .byte 115
  .byte 32
  .byte 99
  .byte 104
  .byte 97
  .byte 114
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
str_hdr_165:
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
  .byte 110
  .byte 111
  .byte 110
  .byte 101
  .byte 0
.align 8
str_hdr_166:
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
  .byte 104
  .byte 97
  .byte 115
  .byte 32
  .byte 110
  .byte 111
  .byte 110
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
str_hdr_168:
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
  .byte 98
  .byte 111
  .byte 117
  .byte 110
  .byte 100
  .byte 97
  .byte 114
  .byte 121
  .byte 0
.align 8
str_hdr_169:
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
  .byte 98
  .byte 111
  .byte 117
  .byte 110
  .byte 100
  .byte 97
  .byte 114
  .byte 121
  .byte 0
.align 8
str_hdr_170:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 13
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 13
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 114
  .byte 101
  .byte 109
  .byte 111
  .byte 118
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
str_hdr_172:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 24
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 24
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 80
  .byte 97
  .byte 114
  .byte 97
  .byte 109
  .byte 101
  .byte 116
  .byte 101
  .byte 114
  .byte 115
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
str_hdr_173:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 34
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 34
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 82
  .byte 117
  .byte 110
  .byte 110
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 101
  .byte 120
  .byte 116
  .byte 101
  .byte 110
  .byte 115
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 109
  .byte 97
  .byte 112
  .byte 112
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
  .byte 115
  .byte 46
  .byte 46
  .byte 46
  .byte 0
.align 8
str_hdr_174:
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
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_175:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_176:
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
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_178:
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
  .byte 46
  .byte 99
  .byte 115
  .byte 115
  .byte 0
.align 8
str_hdr_179:
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 99
  .byte 115
  .byte 115
  .byte 0
.align 8
str_hdr_180:
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
  .byte 46
  .byte 99
  .byte 115
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
str_hdr_182:
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
  .byte 106
  .byte 115
  .byte 111
  .byte 110
  .byte 0
.align 8
str_hdr_183:
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
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 106
  .byte 115
  .byte 111
  .byte 110
  .byte 0
.align 8
str_hdr_184:
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
  .byte 106
  .byte 115
  .byte 111
  .byte 110
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_186:
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
  .byte 74
  .byte 83
  .byte 0
.align 8
str_hdr_187:
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 106
  .byte 97
  .byte 118
  .byte 97
  .byte 115
  .byte 99
  .byte 114
  .byte 105
  .byte 112
  .byte 116
  .byte 0
.align 8
str_hdr_188:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 14
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 14
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 74
  .byte 83
  .byte 32
  .byte 99
  .byte 97
  .byte 115
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
str_hdr_190:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 7
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 7
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 117
  .byte 110
  .byte 107
  .byte 110
  .byte 111
  .byte 119
  .byte 110
  .byte 0
.align 8
str_hdr_191:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 24
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 24
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 111
  .byte 99
  .byte 116
  .byte 101
  .byte 116
  .byte 45
  .byte 115
  .byte 116
  .byte 114
  .byte 101
  .byte 97
  .byte 109
  .byte 0
.align 8
str_hdr_192:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 14
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 14
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 117
  .byte 110
  .byte 107
  .byte 110
  .byte 111
  .byte 119
  .byte 110
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_194:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_195:
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
  .byte 46
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 0
.align 8
str_hdr_196:
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
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 104
  .byte 116
  .byte 109
  .byte 108
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_198:
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
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 106
  .byte 115
  .byte 111
  .byte 110
  .byte 0
.align 8
str_hdr_199:
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
  .byte 46
  .byte 106
  .byte 115
  .byte 111
  .byte 110
  .byte 0
.align 8
str_hdr_200:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 23
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 23
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 106
  .byte 115
  .byte 111
  .byte 110
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_202:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 112
  .byte 110
  .byte 103
  .byte 0
.align 8
str_hdr_203:
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
  .byte 46
  .byte 112
  .byte 110
  .byte 103
  .byte 0
.align 8
str_hdr_204:
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
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 112
  .byte 110
  .byte 103
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_206:
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 112
  .byte 108
  .byte 97
  .byte 105
  .byte 110
  .byte 0
.align 8
str_hdr_207:
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
  .byte 46
  .byte 116
  .byte 120
  .byte 116
  .byte 0
.align 8
str_hdr_208:
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 112
  .byte 108
  .byte 97
  .byte 105
  .byte 110
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_210:
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
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 117
  .byte 110
  .byte 107
  .byte 110
  .byte 111
  .byte 119
  .byte 110
  .byte 0
.align 8
str_hdr_211:
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
str_hdr_212:
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
  .byte 117
  .byte 110
  .byte 107
  .byte 110
  .byte 111
  .byte 119
  .byte 110
  .byte 32
  .byte 109
  .byte 105
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
str_hdr_214:
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
  .byte 69
  .byte 120
  .byte 116
  .byte 101
  .byte 110
  .byte 115
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 109
  .byte 97
  .byte 112
  .byte 112
  .byte 105
  .byte 110
  .byte 103
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
str_hdr_215:
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
  .byte 77
  .byte 73
  .byte 77
  .byte 69
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
str_hdr_216:
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
  .byte 80
  .byte 97
  .byte 114
  .byte 115
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
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
str_hdr_218:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 27
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 27
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 67
  .byte 108
  .byte 97
  .byte 115
  .byte 115
  .byte 105
  .byte 102
  .byte 105
  .byte 99
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
str_hdr_220:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 23
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 23
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 80
  .byte 97
  .byte 114
  .byte 97
  .byte 109
  .byte 101
  .byte 116
  .byte 101
  .byte 114
  .byte 115
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
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
str_hdr_222:
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
  .byte 69
  .byte 120
  .byte 116
  .byte 101
  .byte 110
  .byte 115
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 109
  .byte 97
  .byte 112
  .byte 112
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
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
str_hdr_224:
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
  .byte 65
  .byte 108
  .byte 108
  .byte 32
  .byte 77
  .byte 73
  .byte 77
  .byte 69
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
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
str_hdr_225:
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
str_hdr_226:
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
str_hdr_227:
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
str_hdr_228:
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
  .byte 59
  .byte 0
.align 8
str_hdr_229:
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
  .byte 47
  .byte 0
.align 8
str_hdr_230:
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
str_hdr_231:
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
str_hdr_232:
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
str_hdr_233:
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
str_hdr_234:
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
str_hdr_235:
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
str_hdr_236:
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
str_hdr_237:
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
  .byte 61
  .byte 0
.align 8
str_hdr_238:
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
str_hdr_239:
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
  .byte 34
  .byte 0
.align 8
str_hdr_240:
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
  .byte 34
  .byte 0
.align 8
str_hdr_241:
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
str_hdr_242:
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
str_hdr_243:
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
str_hdr_244:
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
  .byte 9
  .byte 0
.align 8
str_hdr_245:
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
str_hdr_246:
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
  .byte 13
  .byte 0
.align 8
str_hdr_247:
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
str_hdr_248:
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
  .byte 9
  .byte 0
.align 8
str_hdr_249:
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
str_hdr_250:
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
  .byte 13
  .byte 0
.align 8
str_hdr_251:
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
str_hdr_252:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 36
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 36
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 82
  .byte 117
  .byte 110
  .byte 110
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 77
  .byte 73
  .byte 77
  .byte 69
  .byte 32
  .byte 99
  .byte 108
  .byte 97
  .byte 115
  .byte 115
  .byte 105
  .byte 102
  .byte 105
  .byte 99
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
  .byte 115
  .byte 46
  .byte 46
  .byte 46
  .byte 0
.align 8
str_hdr_253:
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 47
  .byte 112
  .byte 108
  .byte 97
  .byte 105
  .byte 110
  .byte 0
.align 8
str_hdr_254:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 47
  .byte 112
  .byte 110
  .byte 103
  .byte 0
.align 8
str_hdr_255:
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
  .byte 97
  .byte 117
  .byte 100
  .byte 105
  .byte 111
  .byte 47
  .byte 109
  .byte 112
  .byte 101
  .byte 103
  .byte 0
.align 8
str_hdr_256:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 9
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 118
  .byte 105
  .byte 100
  .byte 101
  .byte 111
  .byte 47
  .byte 109
  .byte 112
  .byte 52
  .byte 0
.align 8
str_hdr_257:
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
  .byte 97
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 47
  .byte 106
  .byte 115
  .byte 111
  .byte 110
  .byte 0
.align 8
str_hdr_258:
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
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
  .byte 116
  .byte 101
  .byte 120
  .byte 116
  .byte 0
.align 8
str_hdr_260:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 24
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 24
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 116
  .byte 101
  .byte 120
  .byte 116
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
  .byte 98
  .byte 101
  .byte 32
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 0
.align 8
str_hdr_262:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 21
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 21
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 105
  .byte 109
  .byte 97
  .byte 103
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
  .byte 105
  .byte 109
  .byte 97
  .byte 103
  .byte 101
  .byte 0
.align 8
str_hdr_264:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 21
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 21
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 97
  .byte 117
  .byte 100
  .byte 105
  .byte 111
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
  .byte 117
  .byte 100
  .byte 105
  .byte 111
  .byte 0
.align 8
str_hdr_266:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 21
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 21
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 118
  .byte 105
  .byte 100
  .byte 101
  .byte 111
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
  .byte 118
  .byte 105
  .byte 100
  .byte 101
  .byte 111
  .byte 0
.align 8
str_hdr_268:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 25
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 25
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 97
  .byte 112
  .byte 112
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
  .byte 112
  .byte 112
  .byte 108
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 0
.align 8
str_hdr_270:
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
  .byte 67
  .byte 108
  .byte 97
  .byte 115
  .byte 115
  .byte 105
  .byte 102
  .byte 105
  .byte 99
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
  subq $168, %rsp
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
  jmp main_block_0
main_block_0:
  call std.mime.types.__init__
  mov -176(%rbp), rax
  movq -176(%rbp), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  call std.mime.index.__init__
  mov -184(%rbp), rax
  movq -184(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  call std.mime.types.__init__
  mov -192(%rbp), rax
  movq -192(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  call __user_main
  mov -200(%rbp), rax
  movq -200(%rbp), %rax
  movq -80(%rbp), %rdx
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

.globl std.mime.index.mime_to_extension
std.mime.index.mime_to_extension:
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
std.mime.index.mime_to_extension_entry:
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
  jmp std.mime.index.mime_to_extension_block_0
std.mime.index.mime_to_extension_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -152(%rbp)
  movq -152(%rbp), %rdi
  call std.mime.types.mime_to_extension
  mov -160(%rbp), rax
  movq -160(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rax
  jmp std.mime.index.mime_to_extension_epilogue
std.mime.index.mime_to_extension_epilogue:
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
.Lfunc_end_std.mime.index.mime_to_extension:

.globl std.mime.types.MIMEParams.remove
std.mime.types.MIMEParams.remove:
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
std.mime.types.MIMEParams.remove_entry:
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
  jmp std.mime.types.MIMEParams.remove_epilogue
std.mime.types.MIMEParams.remove_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.remove:

.globl std.mime.types.extension_to_mime
std.mime.types.extension_to_mime:
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
  subq $2888, %rsp
  movq %rdi, -48(%rbp)
std.mime.types.extension_to_mime_entry:
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
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.extension_to_mime_block_0
std.mime.types.extension_to_mime_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1224(%rbp)
  movq -1224(%rbp), %rdi
  call std.mime.types.trim
  mov -1232(%rbp), rax
  movq -1232(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1240(%rbp)
  movq -1240(%rbp), %rdi
  call std.mime.types.to_lower
  mov -1248(%rbp), rax
  movq -1248(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1256(%rbp)
  movq -1256(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1264(%rbp)
  movq -1264(%rbp), %rdi
  call lm_list_len
  mov -1272(%rbp), rax
  movq -1272(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1280(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -1288(%rbp), %rax
  cmpq -1280(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -1296(%rbp)
  movq -1296(%rbp), %rax
  movq -112(%rbp), %rdx
  movl %eax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1304(%rbp)
  movq -1304(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1312(%rbp)
  movq -1312(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.extension_to_mime_block_8
  jmp std.mime.types.extension_to_mime_block_15
std.mime.types.extension_to_mime_block_8:
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1320(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1328(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1336(%rbp)
  movq -1320(%rbp), %rdi
  movq -1328(%rbp), %rsi
  movq -1336(%rbp), %rdx
  call _builtin_substring
  mov -1344(%rbp), rax
  movq -1344(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_0(%rip), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1352(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1360(%rbp)
  movq -1352(%rbp), %rdi
  movq -1360(%rbp), %rsi
  call lm_key_eq
  mov -1368(%rbp), rax
  movq -1368(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1376(%rbp)
  movq -1376(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.extension_to_mime_block_15
std.mime.types.extension_to_mime_block_15:
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1384(%rbp)
  movq -1384(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.extension_to_mime_block_16
  jmp std.mime.types.extension_to_mime_block_21
std.mime.types.extension_to_mime_block_16:
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1392(%rbp)
  movq -1392(%rbp), %rdi
  call lm_list_len
  mov -1400(%rbp), rax
  movq -1400(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1408(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1416(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1424(%rbp)
  movq -1408(%rbp), %rdi
  movq -1416(%rbp), %rsi
  movq -1424(%rbp), %rdx
  call _builtin_substring
  mov -1432(%rbp), rax
  movq -1432(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1440(%rbp)
  movq -1440(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.extension_to_mime_block_21
std.mime.types.extension_to_mime_block_21:
  movq $0, %rdi
  call lm_list_new
  mov -1448(%rbp), rax
  movq -1448(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_1(%rip), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1456(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1464(%rbp)
  movq -1456(%rbp), %rdi
  movq -1464(%rbp), %rsi
  call lm_list_append
  mov -1472(%rbp), rax
  leaq str_hdr_2(%rip), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1480(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1488(%rbp)
  movq -1480(%rbp), %rdi
  movq -1488(%rbp), %rsi
  call lm_list_append
  mov -1496(%rbp), rax
  leaq str_hdr_3(%rip), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1504(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1512(%rbp)
  movq -1504(%rbp), %rdi
  movq -1512(%rbp), %rsi
  call lm_list_append
  mov -1520(%rbp), rax
  leaq str_hdr_4(%rip), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1528(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1536(%rbp)
  movq -1528(%rbp), %rdi
  movq -1536(%rbp), %rsi
  call lm_list_append
  mov -1544(%rbp), rax
  leaq str_hdr_5(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1552(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1560(%rbp)
  movq -1552(%rbp), %rdi
  movq -1560(%rbp), %rsi
  call lm_list_append
  mov -1568(%rbp), rax
  leaq str_hdr_6(%rip), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1576(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1584(%rbp)
  movq -1576(%rbp), %rdi
  movq -1584(%rbp), %rsi
  call lm_list_append
  mov -1592(%rbp), rax
  leaq str_hdr_7(%rip), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1600(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1608(%rbp)
  movq -1600(%rbp), %rdi
  movq -1608(%rbp), %rsi
  call lm_list_append
  mov -1616(%rbp), rax
  leaq str_hdr_8(%rip), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1624(%rbp)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1632(%rbp)
  movq -1624(%rbp), %rdi
  movq -1632(%rbp), %rsi
  call lm_list_append
  mov -1640(%rbp), rax
  leaq str_hdr_9(%rip), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1648(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1656(%rbp)
  movq -1648(%rbp), %rdi
  movq -1656(%rbp), %rsi
  call lm_list_append
  mov -1664(%rbp), rax
  leaq str_hdr_10(%rip), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1672(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1680(%rbp)
  movq -1672(%rbp), %rdi
  movq -1680(%rbp), %rsi
  call lm_list_append
  mov -1688(%rbp), rax
  leaq str_hdr_11(%rip), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1696(%rbp)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1704(%rbp)
  movq -1696(%rbp), %rdi
  movq -1704(%rbp), %rsi
  call lm_list_append
  mov -1712(%rbp), rax
  leaq str_hdr_12(%rip), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1720(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1728(%rbp)
  movq -1720(%rbp), %rdi
  movq -1728(%rbp), %rsi
  call lm_list_append
  mov -1736(%rbp), rax
  leaq str_hdr_13(%rip), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1744(%rbp)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1752(%rbp)
  movq -1744(%rbp), %rdi
  movq -1752(%rbp), %rsi
  call lm_list_append
  mov -1760(%rbp), rax
  leaq str_hdr_14(%rip), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1768(%rbp)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1776(%rbp)
  movq -1768(%rbp), %rdi
  movq -1776(%rbp), %rsi
  call lm_list_append
  mov -1784(%rbp), rax
  leaq str_hdr_15(%rip), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1792(%rbp)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1800(%rbp)
  movq -1792(%rbp), %rdi
  movq -1800(%rbp), %rsi
  call lm_list_append
  mov -1808(%rbp), rax
  leaq str_hdr_16(%rip), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1816(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1824(%rbp)
  movq -1816(%rbp), %rdi
  movq -1824(%rbp), %rsi
  call lm_list_append
  mov -1832(%rbp), rax
  leaq str_hdr_17(%rip), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1840(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1848(%rbp)
  movq -1840(%rbp), %rdi
  movq -1848(%rbp), %rsi
  call lm_list_append
  mov -1856(%rbp), rax
  leaq str_hdr_18(%rip), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1864(%rbp)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1872(%rbp)
  movq -1864(%rbp), %rdi
  movq -1872(%rbp), %rsi
  call lm_list_append
  mov -1880(%rbp), rax
  leaq str_hdr_19(%rip), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1888(%rbp)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1896(%rbp)
  movq -1888(%rbp), %rdi
  movq -1896(%rbp), %rsi
  call lm_list_append
  mov -1904(%rbp), rax
  leaq str_hdr_20(%rip), %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1912(%rbp)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1920(%rbp)
  movq -1912(%rbp), %rdi
  movq -1920(%rbp), %rsi
  call lm_list_append
  mov -1928(%rbp), rax
  leaq str_hdr_21(%rip), %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1936(%rbp)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1944(%rbp)
  movq -1936(%rbp), %rdi
  movq -1944(%rbp), %rsi
  call lm_list_append
  mov -1952(%rbp), rax
  leaq str_hdr_22(%rip), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1960(%rbp)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1968(%rbp)
  movq -1960(%rbp), %rdi
  movq -1968(%rbp), %rsi
  call lm_list_append
  mov -1976(%rbp), rax
  leaq str_hdr_23(%rip), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1984(%rbp)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1992(%rbp)
  movq -1984(%rbp), %rdi
  movq -1992(%rbp), %rsi
  call lm_list_append
  mov -2000(%rbp), rax
  leaq str_hdr_24(%rip), %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2008(%rbp)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2016(%rbp)
  movq -2008(%rbp), %rdi
  movq -2016(%rbp), %rsi
  call lm_list_append
  mov -2024(%rbp), rax
  leaq str_hdr_25(%rip), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2032(%rbp)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2040(%rbp)
  movq -2032(%rbp), %rdi
  movq -2040(%rbp), %rsi
  call lm_list_append
  mov -2048(%rbp), rax
  leaq str_hdr_26(%rip), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2056(%rbp)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2064(%rbp)
  movq -2056(%rbp), %rdi
  movq -2064(%rbp), %rsi
  call lm_list_append
  mov -2072(%rbp), rax
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2080(%rbp)
  movq -2080(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2088(%rbp)
  movq -2088(%rbp), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -2096(%rbp), rax
  movq -2096(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_27(%rip), %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2104(%rbp)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2112(%rbp)
  movq -2104(%rbp), %rdi
  movq -2112(%rbp), %rsi
  call lm_list_append
  mov -2120(%rbp), rax
  leaq str_hdr_28(%rip), %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2128(%rbp)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2136(%rbp)
  movq -2128(%rbp), %rdi
  movq -2136(%rbp), %rsi
  call lm_list_append
  mov -2144(%rbp), rax
  leaq str_hdr_29(%rip), %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2152(%rbp)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2160(%rbp)
  movq -2152(%rbp), %rdi
  movq -2160(%rbp), %rsi
  call lm_list_append
  mov -2168(%rbp), rax
  leaq str_hdr_30(%rip), %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2176(%rbp)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2184(%rbp)
  movq -2176(%rbp), %rdi
  movq -2184(%rbp), %rsi
  call lm_list_append
  mov -2192(%rbp), rax
  leaq str_hdr_31(%rip), %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2200(%rbp)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2208(%rbp)
  movq -2200(%rbp), %rdi
  movq -2208(%rbp), %rsi
  call lm_list_append
  mov -2216(%rbp), rax
  leaq str_hdr_32(%rip), %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2224(%rbp)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2232(%rbp)
  movq -2224(%rbp), %rdi
  movq -2232(%rbp), %rsi
  call lm_list_append
  mov -2240(%rbp), rax
  leaq str_hdr_33(%rip), %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2248(%rbp)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2256(%rbp)
  movq -2248(%rbp), %rdi
  movq -2256(%rbp), %rsi
  call lm_list_append
  mov -2264(%rbp), rax
  leaq str_hdr_34(%rip), %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2272(%rbp)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2280(%rbp)
  movq -2272(%rbp), %rdi
  movq -2280(%rbp), %rsi
  call lm_list_append
  mov -2288(%rbp), rax
  leaq str_hdr_35(%rip), %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2296(%rbp)
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2304(%rbp)
  movq -2296(%rbp), %rdi
  movq -2304(%rbp), %rsi
  call lm_list_append
  mov -2312(%rbp), rax
  leaq str_hdr_36(%rip), %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2320(%rbp)
  movq -776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2328(%rbp)
  movq -2320(%rbp), %rdi
  movq -2328(%rbp), %rsi
  call lm_list_append
  mov -2336(%rbp), rax
  leaq str_hdr_37(%rip), %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2344(%rbp)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2352(%rbp)
  movq -2344(%rbp), %rdi
  movq -2352(%rbp), %rsi
  call lm_list_append
  mov -2360(%rbp), rax
  leaq str_hdr_38(%rip), %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2368(%rbp)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2376(%rbp)
  movq -2368(%rbp), %rdi
  movq -2376(%rbp), %rsi
  call lm_list_append
  mov -2384(%rbp), rax
  leaq str_hdr_39(%rip), %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2392(%rbp)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2400(%rbp)
  movq -2392(%rbp), %rdi
  movq -2400(%rbp), %rsi
  call lm_list_append
  mov -2408(%rbp), rax
  leaq str_hdr_40(%rip), %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2416(%rbp)
  movq -840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2424(%rbp)
  movq -2416(%rbp), %rdi
  movq -2424(%rbp), %rsi
  call lm_list_append
  mov -2432(%rbp), rax
  leaq str_hdr_41(%rip), %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2440(%rbp)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2448(%rbp)
  movq -2440(%rbp), %rdi
  movq -2448(%rbp), %rsi
  call lm_list_append
  mov -2456(%rbp), rax
  leaq str_hdr_42(%rip), %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2464(%rbp)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2472(%rbp)
  movq -2464(%rbp), %rdi
  movq -2472(%rbp), %rsi
  call lm_list_append
  mov -2480(%rbp), rax
  leaq str_hdr_43(%rip), %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2488(%rbp)
  movq -888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2496(%rbp)
  movq -2488(%rbp), %rdi
  movq -2496(%rbp), %rsi
  call lm_list_append
  mov -2504(%rbp), rax
  leaq str_hdr_44(%rip), %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2512(%rbp)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2520(%rbp)
  movq -2512(%rbp), %rdi
  movq -2520(%rbp), %rsi
  call lm_list_append
  mov -2528(%rbp), rax
  leaq str_hdr_45(%rip), %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2536(%rbp)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2544(%rbp)
  movq -2536(%rbp), %rdi
  movq -2544(%rbp), %rsi
  call lm_list_append
  mov -2552(%rbp), rax
  leaq str_hdr_46(%rip), %rax
  movq -936(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2560(%rbp)
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2568(%rbp)
  movq -2560(%rbp), %rdi
  movq -2568(%rbp), %rsi
  call lm_list_append
  mov -2576(%rbp), rax
  leaq str_hdr_47(%rip), %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2584(%rbp)
  movq -952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2592(%rbp)
  movq -2584(%rbp), %rdi
  movq -2592(%rbp), %rsi
  call lm_list_append
  mov -2600(%rbp), rax
  leaq str_hdr_48(%rip), %rax
  movq -968(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2608(%rbp)
  movq -968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2616(%rbp)
  movq -2608(%rbp), %rdi
  movq -2616(%rbp), %rsi
  call lm_list_append
  mov -2624(%rbp), rax
  leaq str_hdr_49(%rip), %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2632(%rbp)
  movq -984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2640(%rbp)
  movq -2632(%rbp), %rdi
  movq -2640(%rbp), %rsi
  call lm_list_append
  mov -2648(%rbp), rax
  leaq str_hdr_50(%rip), %rax
  movq -1000(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2656(%rbp)
  movq -1000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2664(%rbp)
  movq -2656(%rbp), %rdi
  movq -2664(%rbp), %rsi
  call lm_list_append
  mov -2672(%rbp), rax
  leaq str_hdr_51(%rip), %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2680(%rbp)
  movq -1016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2688(%rbp)
  movq -2680(%rbp), %rdi
  movq -2688(%rbp), %rsi
  call lm_list_append
  mov -2696(%rbp), rax
  leaq str_hdr_52(%rip), %rax
  movq -1032(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2704(%rbp)
  movq -1032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2712(%rbp)
  movq -2704(%rbp), %rdi
  movq -2712(%rbp), %rsi
  call lm_list_append
  mov -2720(%rbp), rax
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2728(%rbp)
  movq -2728(%rbp), %rax
  movq -1048(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2736(%rbp)
  movq -2736(%rbp), %rax
  movq -1056(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.extension_to_mime_block_133
std.mime.types.extension_to_mime_block_133:
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2744(%rbp)
  movq -2744(%rbp), %rdi
  call lm_list_len
  mov -2752(%rbp), rax
  movq -2752(%rbp), %rax
  movq -1072(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2760(%rbp)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2768(%rbp)
  movq -2768(%rbp), %rax
  cmpq -2760(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2776(%rbp)
  movq -2776(%rbp), %rax
  movq -1080(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2784(%rbp)
  movq -2784(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.extension_to_mime_block_136
  jmp std.mime.types.extension_to_mime_block_146
std.mime.types.extension_to_mime_block_136:
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2792(%rbp)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2800(%rbp)
  movq -2792(%rbp), %rdi
  movq -2800(%rbp), %rsi
  call lm_list_get
  mov -2808(%rbp), rax
  movq -2808(%rbp), %rax
  movq -1088(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2816(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2824(%rbp)
  movq -2816(%rbp), %rdi
  movq -2824(%rbp), %rsi
  call lm_key_eq
  mov -2832(%rbp), rax
  movq -2832(%rbp), %rax
  movq -1096(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2840(%rbp)
  movq -2840(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.extension_to_mime_block_139
  jmp std.mime.types.extension_to_mime_block_141
std.mime.types.extension_to_mime_block_139:
  movq -1056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2848(%rbp)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2856(%rbp)
  movq -2848(%rbp), %rdi
  movq -2856(%rbp), %rsi
  call lm_list_get
  mov -2864(%rbp), rax
  movq -2864(%rbp), %rax
  movq -1104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2872(%rbp)
  movq -2872(%rbp), %rax
  jmp std.mime.types.extension_to_mime_epilogue
std.mime.types.extension_to_mime_block_141:
  movq $1, %rax
  movq -1112(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2880(%rbp)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2888(%rbp)
  movq -2888(%rbp), %rax
  addq -2880(%rbp), %rax
  movq %rax, -2896(%rbp)
  movq -2896(%rbp), %rax
  movq -1128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2904(%rbp)
  movq -2904(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.extension_to_mime_block_133
std.mime.types.extension_to_mime_block_146:
  leaq str_hdr_53(%rip), %rax
  movq -1136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2912(%rbp)
  movq -2912(%rbp), %rax
  jmp std.mime.types.extension_to_mime_epilogue
std.mime.types.extension_to_mime_epilogue:
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
.Lfunc_end_std.mime.types.extension_to_mime:

.globl std.mime.types.MIMEType.is_audio
std.mime.types.MIMEType.is_audio:
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
std.mime.types.MIMEType.is_audio_entry:
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
  jmp std.mime.types.MIMEType.is_audio_epilogue
std.mime.types.MIMEType.is_audio_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.is_audio:

.globl std.mime.types.mime_to_extension
std.mime.types.mime_to_extension:
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
  subq $2712, %rsp
  movq %rdi, -48(%rbp)
std.mime.types.mime_to_extension_entry:
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
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.mime_to_extension_block_0
std.mime.types.mime_to_extension_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1152(%rbp)
  movq -1152(%rbp), %rdi
  call std.mime.types.parse
  mov -1160(%rbp), rax
  movq -1160(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1168(%rbp)
  movq -1168(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1176(%rbp)
  movq -1176(%rbp), %rax
  addq $0, %rax
  movq %rax, -1184(%rbp)
  movq -1184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1192(%rbp)
  movq -1192(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1200(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1208(%rbp)
  movq -1208(%rbp), %rax
  cmpq -1200(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -1216(%rbp)
  movq -1216(%rbp), %rax
  movq -88(%rbp), %rdx
  movl %eax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1224(%rbp)
  movq -1224(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.mime_to_extension_block_6
  jmp std.mime.types.mime_to_extension_block_8
std.mime.types.mime_to_extension_block_6:
  leaq str_hdr_54(%rip), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1232(%rbp)
  movq -1232(%rbp), %rax
  jmp std.mime.types.mime_to_extension_epilogue
std.mime.types.mime_to_extension_block_8:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1240(%rbp)
  movq -1240(%rbp), %rax
  addq $8, %rax
  movq %rax, -1248(%rbp)
  movq -1248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1256(%rbp)
  movq -1256(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_55(%rip), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1264(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1272(%rbp)
  movq -1264(%rbp), %rdi
  movq -1272(%rbp), %rsi
  call lm_str_concat
  mov -1280(%rbp), rax
  movq -1280(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -1288(%rbp), %rax
  addq $24, %rax
  movq %rax, -1296(%rbp)
  movq -1296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1304(%rbp)
  movq -1304(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1312(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1320(%rbp)
  movq -1312(%rbp), %rdi
  movq -1320(%rbp), %rsi
  call lm_str_concat
  mov -1328(%rbp), rax
  movq -1328(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1336(%rbp)
  movq -1336(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -1344(%rbp), rax
  movq -1344(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_56(%rip), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1352(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1360(%rbp)
  movq -1352(%rbp), %rdi
  movq -1360(%rbp), %rsi
  call lm_list_append
  mov -1368(%rbp), rax
  leaq str_hdr_57(%rip), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1376(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1384(%rbp)
  movq -1376(%rbp), %rdi
  movq -1384(%rbp), %rsi
  call lm_list_append
  mov -1392(%rbp), rax
  leaq str_hdr_58(%rip), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1400(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1408(%rbp)
  movq -1400(%rbp), %rdi
  movq -1408(%rbp), %rsi
  call lm_list_append
  mov -1416(%rbp), rax
  leaq str_hdr_59(%rip), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1424(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1432(%rbp)
  movq -1424(%rbp), %rdi
  movq -1432(%rbp), %rsi
  call lm_list_append
  mov -1440(%rbp), rax
  leaq str_hdr_60(%rip), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1448(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1456(%rbp)
  movq -1448(%rbp), %rdi
  movq -1456(%rbp), %rsi
  call lm_list_append
  mov -1464(%rbp), rax
  leaq str_hdr_61(%rip), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1472(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1480(%rbp)
  movq -1472(%rbp), %rdi
  movq -1480(%rbp), %rsi
  call lm_list_append
  mov -1488(%rbp), rax
  leaq str_hdr_62(%rip), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1496(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1504(%rbp)
  movq -1496(%rbp), %rdi
  movq -1504(%rbp), %rsi
  call lm_list_append
  mov -1512(%rbp), rax
  leaq str_hdr_63(%rip), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1520(%rbp)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1528(%rbp)
  movq -1520(%rbp), %rdi
  movq -1528(%rbp), %rsi
  call lm_list_append
  mov -1536(%rbp), rax
  leaq str_hdr_64(%rip), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1544(%rbp)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1552(%rbp)
  movq -1544(%rbp), %rdi
  movq -1552(%rbp), %rsi
  call lm_list_append
  mov -1560(%rbp), rax
  leaq str_hdr_65(%rip), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1568(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1576(%rbp)
  movq -1568(%rbp), %rdi
  movq -1576(%rbp), %rsi
  call lm_list_append
  mov -1584(%rbp), rax
  leaq str_hdr_66(%rip), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1592(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1600(%rbp)
  movq -1592(%rbp), %rdi
  movq -1600(%rbp), %rsi
  call lm_list_append
  mov -1608(%rbp), rax
  leaq str_hdr_67(%rip), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1616(%rbp)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1624(%rbp)
  movq -1616(%rbp), %rdi
  movq -1624(%rbp), %rsi
  call lm_list_append
  mov -1632(%rbp), rax
  leaq str_hdr_68(%rip), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1640(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1648(%rbp)
  movq -1640(%rbp), %rdi
  movq -1648(%rbp), %rsi
  call lm_list_append
  mov -1656(%rbp), rax
  leaq str_hdr_69(%rip), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1664(%rbp)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1672(%rbp)
  movq -1664(%rbp), %rdi
  movq -1672(%rbp), %rsi
  call lm_list_append
  mov -1680(%rbp), rax
  leaq str_hdr_70(%rip), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1688(%rbp)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1696(%rbp)
  movq -1688(%rbp), %rdi
  movq -1696(%rbp), %rsi
  call lm_list_append
  mov -1704(%rbp), rax
  leaq str_hdr_71(%rip), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1712(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1720(%rbp)
  movq -1712(%rbp), %rdi
  movq -1720(%rbp), %rsi
  call lm_list_append
  mov -1728(%rbp), rax
  leaq str_hdr_72(%rip), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1736(%rbp)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1744(%rbp)
  movq -1736(%rbp), %rdi
  movq -1744(%rbp), %rsi
  call lm_list_append
  mov -1752(%rbp), rax
  leaq str_hdr_73(%rip), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1760(%rbp)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1768(%rbp)
  movq -1760(%rbp), %rdi
  movq -1768(%rbp), %rsi
  call lm_list_append
  mov -1776(%rbp), rax
  leaq str_hdr_74(%rip), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1784(%rbp)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1792(%rbp)
  movq -1784(%rbp), %rdi
  movq -1792(%rbp), %rsi
  call lm_list_append
  mov -1800(%rbp), rax
  leaq str_hdr_75(%rip), %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1808(%rbp)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1816(%rbp)
  movq -1808(%rbp), %rdi
  movq -1816(%rbp), %rsi
  call lm_list_append
  mov -1824(%rbp), rax
  leaq str_hdr_76(%rip), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1832(%rbp)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1840(%rbp)
  movq -1832(%rbp), %rdi
  movq -1840(%rbp), %rsi
  call lm_list_append
  mov -1848(%rbp), rax
  leaq str_hdr_77(%rip), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1856(%rbp)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1864(%rbp)
  movq -1856(%rbp), %rdi
  movq -1864(%rbp), %rsi
  call lm_list_append
  mov -1872(%rbp), rax
  leaq str_hdr_78(%rip), %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1880(%rbp)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1888(%rbp)
  movq -1880(%rbp), %rdi
  movq -1888(%rbp), %rsi
  call lm_list_append
  mov -1896(%rbp), rax
  leaq str_hdr_79(%rip), %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1904(%rbp)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1912(%rbp)
  movq -1904(%rbp), %rdi
  movq -1912(%rbp), %rsi
  call lm_list_append
  mov -1920(%rbp), rax
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1928(%rbp)
  movq -1928(%rbp), %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1936(%rbp)
  movq -1936(%rbp), %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -1944(%rbp), rax
  movq -1944(%rbp), %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_80(%rip), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1952(%rbp)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1960(%rbp)
  movq -1952(%rbp), %rdi
  movq -1960(%rbp), %rsi
  call lm_list_append
  mov -1968(%rbp), rax
  leaq str_hdr_81(%rip), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1976(%rbp)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1984(%rbp)
  movq -1976(%rbp), %rdi
  movq -1984(%rbp), %rsi
  call lm_list_append
  mov -1992(%rbp), rax
  leaq str_hdr_82(%rip), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2000(%rbp)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2008(%rbp)
  movq -2000(%rbp), %rdi
  movq -2008(%rbp), %rsi
  call lm_list_append
  mov -2016(%rbp), rax
  leaq str_hdr_83(%rip), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2024(%rbp)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2032(%rbp)
  movq -2024(%rbp), %rdi
  movq -2032(%rbp), %rsi
  call lm_list_append
  mov -2040(%rbp), rax
  leaq str_hdr_84(%rip), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2048(%rbp)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2056(%rbp)
  movq -2048(%rbp), %rdi
  movq -2056(%rbp), %rsi
  call lm_list_append
  mov -2064(%rbp), rax
  leaq str_hdr_85(%rip), %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2072(%rbp)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2080(%rbp)
  movq -2072(%rbp), %rdi
  movq -2080(%rbp), %rsi
  call lm_list_append
  mov -2088(%rbp), rax
  leaq str_hdr_86(%rip), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2096(%rbp)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2104(%rbp)
  movq -2096(%rbp), %rdi
  movq -2104(%rbp), %rsi
  call lm_list_append
  mov -2112(%rbp), rax
  leaq str_hdr_87(%rip), %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2120(%rbp)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2128(%rbp)
  movq -2120(%rbp), %rdi
  movq -2128(%rbp), %rsi
  call lm_list_append
  mov -2136(%rbp), rax
  leaq str_hdr_88(%rip), %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2144(%rbp)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2152(%rbp)
  movq -2144(%rbp), %rdi
  movq -2152(%rbp), %rsi
  call lm_list_append
  mov -2160(%rbp), rax
  leaq str_hdr_89(%rip), %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2168(%rbp)
  movq -720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2176(%rbp)
  movq -2168(%rbp), %rdi
  movq -2176(%rbp), %rsi
  call lm_list_append
  mov -2184(%rbp), rax
  leaq str_hdr_90(%rip), %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2192(%rbp)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2200(%rbp)
  movq -2192(%rbp), %rdi
  movq -2200(%rbp), %rsi
  call lm_list_append
  mov -2208(%rbp), rax
  leaq str_hdr_91(%rip), %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2216(%rbp)
  movq -752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2224(%rbp)
  movq -2216(%rbp), %rdi
  movq -2224(%rbp), %rsi
  call lm_list_append
  mov -2232(%rbp), rax
  leaq str_hdr_92(%rip), %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2240(%rbp)
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2248(%rbp)
  movq -2240(%rbp), %rdi
  movq -2248(%rbp), %rsi
  call lm_list_append
  mov -2256(%rbp), rax
  leaq str_hdr_93(%rip), %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2264(%rbp)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2272(%rbp)
  movq -2264(%rbp), %rdi
  movq -2272(%rbp), %rsi
  call lm_list_append
  mov -2280(%rbp), rax
  leaq str_hdr_94(%rip), %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2288(%rbp)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2296(%rbp)
  movq -2288(%rbp), %rdi
  movq -2296(%rbp), %rsi
  call lm_list_append
  mov -2304(%rbp), rax
  leaq str_hdr_95(%rip), %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2312(%rbp)
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2320(%rbp)
  movq -2312(%rbp), %rdi
  movq -2320(%rbp), %rsi
  call lm_list_append
  mov -2328(%rbp), rax
  leaq str_hdr_96(%rip), %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2336(%rbp)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2344(%rbp)
  movq -2336(%rbp), %rdi
  movq -2344(%rbp), %rsi
  call lm_list_append
  mov -2352(%rbp), rax
  leaq str_hdr_97(%rip), %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2360(%rbp)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2368(%rbp)
  movq -2360(%rbp), %rdi
  movq -2368(%rbp), %rsi
  call lm_list_append
  mov -2376(%rbp), rax
  leaq str_hdr_98(%rip), %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2384(%rbp)
  movq -864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2392(%rbp)
  movq -2384(%rbp), %rdi
  movq -2392(%rbp), %rsi
  call lm_list_append
  mov -2400(%rbp), rax
  leaq str_hdr_99(%rip), %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2408(%rbp)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2416(%rbp)
  movq -2408(%rbp), %rdi
  movq -2416(%rbp), %rsi
  call lm_list_append
  mov -2424(%rbp), rax
  leaq str_hdr_100(%rip), %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2432(%rbp)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2440(%rbp)
  movq -2432(%rbp), %rdi
  movq -2440(%rbp), %rsi
  call lm_list_append
  mov -2448(%rbp), rax
  leaq str_hdr_101(%rip), %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2456(%rbp)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2464(%rbp)
  movq -2456(%rbp), %rdi
  movq -2464(%rbp), %rsi
  call lm_list_append
  mov -2472(%rbp), rax
  leaq str_hdr_102(%rip), %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2480(%rbp)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2488(%rbp)
  movq -2480(%rbp), %rdi
  movq -2488(%rbp), %rsi
  call lm_list_append
  mov -2496(%rbp), rax
  leaq str_hdr_103(%rip), %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2504(%rbp)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2512(%rbp)
  movq -2504(%rbp), %rdi
  movq -2512(%rbp), %rsi
  call lm_list_append
  mov -2520(%rbp), rax
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2528(%rbp)
  movq -2528(%rbp), %rax
  movq -960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2536(%rbp)
  movq -2536(%rbp), %rax
  movq -968(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.mime_to_extension_block_118
std.mime.types.mime_to_extension_block_118:
  movq -968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2544(%rbp)
  movq -2544(%rbp), %rdi
  call lm_list_len
  mov -2552(%rbp), rax
  movq -2552(%rbp), %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  movq -984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2560(%rbp)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2568(%rbp)
  movq -2568(%rbp), %rax
  cmpq -2560(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2576(%rbp)
  movq -2576(%rbp), %rax
  movq -992(%rbp), %rdx
  movl %eax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2584(%rbp)
  movq -2584(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.mime_to_extension_block_121
  jmp std.mime.types.mime_to_extension_block_133
std.mime.types.mime_to_extension_block_121:
  movq -968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2592(%rbp)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2600(%rbp)
  movq -2592(%rbp), %rdi
  movq -2600(%rbp), %rsi
  call lm_list_get
  mov -2608(%rbp), rax
  movq -2608(%rbp), %rax
  movq -1000(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2616(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2624(%rbp)
  movq -2616(%rbp), %rdi
  movq -2624(%rbp), %rsi
  call lm_key_eq
  mov -2632(%rbp), rax
  movq -2632(%rbp), %rax
  movq -1008(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2640(%rbp)
  movq -2640(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.mime_to_extension_block_124
  jmp std.mime.types.mime_to_extension_block_128
std.mime.types.mime_to_extension_block_124:
  leaq str_hdr_104(%rip), %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2648(%rbp)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2656(%rbp)
  movq -2648(%rbp), %rdi
  movq -2656(%rbp), %rsi
  call lm_list_get
  mov -2664(%rbp), rax
  movq -2664(%rbp), %rax
  movq -1024(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2672(%rbp)
  movq -1024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2680(%rbp)
  movq -2672(%rbp), %rdi
  movq -2680(%rbp), %rsi
  call lm_str_concat
  mov -2688(%rbp), rax
  movq -2688(%rbp), %rax
  movq -1032(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2696(%rbp)
  movq -2696(%rbp), %rax
  jmp std.mime.types.mime_to_extension_epilogue
std.mime.types.mime_to_extension_block_128:
  movq $1, %rax
  movq -1040(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1048(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2704(%rbp)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2712(%rbp)
  movq -2712(%rbp), %rax
  addq -2704(%rbp), %rax
  movq %rax, -2720(%rbp)
  movq -2720(%rbp), %rax
  movq -1056(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2728(%rbp)
  movq -2728(%rbp), %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.mime_to_extension_block_118
std.mime.types.mime_to_extension_block_133:
  leaq str_hdr_105(%rip), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2736(%rbp)
  movq -2736(%rbp), %rax
  jmp std.mime.types.mime_to_extension_epilogue
std.mime.types.mime_to_extension_epilogue:
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
.Lfunc_end_std.mime.types.mime_to_extension:

.globl std.mime.types.index_of
std.mime.types.index_of:
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
  subq $520, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.mime.types.index_of_entry:
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
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.index_of_block_0
std.mime.types.index_of_block_0:
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.index_of_block_2
std.mime.types.index_of_block_2:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -280(%rbp)
  movq -280(%rbp), %rdi
  call lm_list_len
  mov -288(%rbp), rax
  movq -288(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -296(%rbp)
  movq -296(%rbp), %rdi
  call lm_list_len
  mov -304(%rbp), rax
  movq -304(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -312(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rax
  subq -312(%rbp), %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -344(%rbp)
  movq -344(%rbp), %rax
  cmpq -336(%rbp), %rax
  setle %al
  movzbq %al, %rax
  movq %rax, -352(%rbp)
  movq -352(%rbp), %rax
  movq -112(%rbp), %rdx
  movl %eax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -360(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.index_of_block_7
  jmp std.mime.types.index_of_block_19
std.mime.types.index_of_block_7:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rdi
  call lm_list_len
  mov -376(%rbp), rax
  movq -376(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -384(%rbp)
  movq -384(%rbp), %rdi
  call lm_list_len
  mov -392(%rbp), rax
  movq -392(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -408(%rbp), %rax
  addq -400(%rbp), %rax
  movq %rax, -416(%rbp)
  movq -416(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -424(%rbp), %rdi
  movq -432(%rbp), %rsi
  movq -440(%rbp), %rdx
  call _builtin_substring
  mov -448(%rbp), rax
  movq -448(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -456(%rbp), %rdi
  movq -464(%rbp), %rsi
  call lm_key_eq
  mov -472(%rbp), rax
  movq -472(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -480(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.index_of_block_13
  jmp std.mime.types.index_of_block_14
std.mime.types.index_of_block_13:
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rax
  jmp std.mime.types.index_of_epilogue
std.mime.types.index_of_block_14:
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  addq -496(%rbp), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.index_of_block_2
std.mime.types.index_of_block_19:
  movq $1, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rax
  negq %rax
  movq %rax, -536(%rbp)
  movq -536(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  jmp std.mime.types.index_of_epilogue
std.mime.types.index_of_epilogue:
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
.Lfunc_end_std.mime.types.index_of:

.globl std.mime.types.to_lower
std.mime.types.to_lower:
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
  subq $664, %rsp
  movq %rdi, -48(%rbp)
std.mime.types.to_lower_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.to_lower_block_0
std.mime.types.to_lower_block_0:
  leaq str_hdr_106(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_107(%rip), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_108(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.to_lower_block_5
std.mime.types.to_lower_block_5:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -344(%rbp)
  movq -344(%rbp), %rdi
  call lm_list_len
  mov -352(%rbp), rax
  movq -352(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rax
  cmpq -360(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -376(%rbp)
  movq -376(%rbp), %rax
  movq -104(%rbp), %rdx
  movl %eax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -384(%rbp)
  movq -384(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.to_lower_block_8
  jmp std.mime.types.to_lower_block_34
std.mime.types.to_lower_block_8:
  movq $1, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  addq -392(%rbp), %rax
  movq %rax, -408(%rbp)
  movq -408(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -416(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -416(%rbp), %rdi
  movq -424(%rbp), %rsi
  movq -432(%rbp), %rdx
  call _builtin_substring
  mov -440(%rbp), rax
  movq -440(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -456(%rbp), %rdi
  movq -464(%rbp), %rsi
  call std.mime.types.index_of
  mov -472(%rbp), rax
  movq -472(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -480(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rax
  negq %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  cmpq -504(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  movq -184(%rbp), %rdx
  movl %eax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.to_lower_block_19
  jmp std.mime.types.to_lower_block_26
std.mime.types.to_lower_block_19:
  movq $1, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  addq -536(%rbp), %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -560(%rbp), %rdi
  movq -568(%rbp), %rsi
  movq -576(%rbp), %rdx
  call _builtin_substring
  mov -584(%rbp), rax
  movq -584(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -592(%rbp), %rdi
  movq -600(%rbp), %rsi
  call lm_str_concat
  mov -608(%rbp), rax
  movq -608(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.to_lower_block_29
std.mime.types.to_lower_block_26:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -624(%rbp), %rdi
  movq -632(%rbp), %rsi
  call lm_str_concat
  mov -640(%rbp), rax
  movq -640(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.to_lower_block_29
std.mime.types.to_lower_block_29:
  movq $1, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  addq -656(%rbp), %rax
  movq %rax, -672(%rbp)
  movq -672(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.to_lower_block_5
std.mime.types.to_lower_block_34:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rax
  jmp std.mime.types.to_lower_epilogue
std.mime.types.to_lower_epilogue:
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
.Lfunc_end_std.mime.types.to_lower:

.globl std.mime.types.MIMEParams.to_string
std.mime.types.MIMEParams.to_string:
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
std.mime.types.MIMEParams.to_string_entry:
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
  jmp std.mime.types.MIMEParams.to_string_epilogue
std.mime.types.MIMEParams.to_string_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.to_string:

.globl std.mime.index.parse
std.mime.index.parse:
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
std.mime.index.parse_entry:
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
  jmp std.mime.index.parse_block_0
std.mime.index.parse_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -152(%rbp)
  movq -152(%rbp), %rdi
  call std.mime.types.parse
  mov -160(%rbp), rax
  movq -160(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rax
  jmp std.mime.index.parse_epilogue
std.mime.index.parse_epilogue:
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
.Lfunc_end_std.mime.index.parse:

.globl std.mime.types.MIMEType.is_image
std.mime.types.MIMEType.is_image:
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
std.mime.types.MIMEType.is_image_entry:
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
  jmp std.mime.types.MIMEType.is_image_epilogue
std.mime.types.MIMEType.is_image_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.is_image:

.globl std.mime.index.extension_to_mime
std.mime.index.extension_to_mime:
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
std.mime.index.extension_to_mime_entry:
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
  jmp std.mime.index.extension_to_mime_block_0
std.mime.index.extension_to_mime_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -152(%rbp)
  movq -152(%rbp), %rdi
  call std.mime.types.extension_to_mime
  mov -160(%rbp), rax
  movq -160(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rax
  jmp std.mime.index.extension_to_mime_epilogue
std.mime.index.extension_to_mime_epilogue:
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
.Lfunc_end_std.mime.index.extension_to_mime:

.globl std.mime.types.MIMEParams.init
std.mime.types.MIMEParams.init:
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
std.mime.types.MIMEParams.init_entry:
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
  jmp std.mime.types.MIMEParams.init_epilogue
std.mime.types.MIMEParams.init_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.init:

.globl std.mime.types.MIMEType.to_string
std.mime.types.MIMEType.to_string:
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
std.mime.types.MIMEType.to_string_entry:
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
  jmp std.mime.types.MIMEType.to_string_epilogue
std.mime.types.MIMEType.to_string_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.to_string:

.globl std.mime.index.MIMEParams
std.mime.index.MIMEParams:
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
std.mime.index.MIMEParams_entry:
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
  jmp std.mime.index.MIMEParams_block_0
std.mime.index.MIMEParams_block_0:
  # Bump Allocation: 16 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $16, %rax
  movq %rax, heap_ptr(%rip)
  movq -144(%rbp), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -152(%rbp)
  movq -152(%rbp), %rdi
  call std.mime.types.MIMEParams.init
  mov -160(%rbp), rax
  movq -160(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rax
  jmp std.mime.index.MIMEParams_epilogue
std.mime.index.MIMEParams_epilogue:
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
.Lfunc_end_std.mime.index.MIMEParams:

.globl test_parsing
test_parsing:
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
  subq $2456, %rsp
test_parsing_entry:
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
  jmp test_parsing_block_0
test_parsing_block_0:
  leaq str_hdr_109(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -840(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -848(%rbp)
  movq -848(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_pr_nil_0_9383
  jmp test_parsing_pr_str_0_9383
test_parsing_pr_nil_0_9383:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -856(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -856(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -864(%rbp)
  jmp test_parsing_pr_next_0_9383
test_parsing_pr_str_0_9383:
  movq -840(%rbp), %rax
  addq $8, %rax
  movq %rax, -872(%rbp)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -840(%rbp), %rax
  addq $24, %rax
  movq %rax, -888(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -888(%rbp), %rsi
  movq -880(%rbp), %rdx
  syscall
  movq %rax, -896(%rbp)
  jmp test_parsing_pr_next_0_9383
test_parsing_pr_next_0_9383:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -904(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -912(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_110(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -920(%rbp), %rdi
  call std.mime.index.parse
  mov -928(%rbp), rax
  movq -928(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -936(%rbp), %rax
  movq %rax, -944(%rbp)
  movq -944(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -952(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -960(%rbp)
  movq -960(%rbp), %rax
  addq $0, %rax
  movq %rax, -968(%rbp)
  movq -968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -976(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -984(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -992(%rbp), %rax
  cmpq -984(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1000(%rbp)
  movq -1000(%rbp), %rax
  movq -112(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_111(%rip), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1008(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1016(%rbp)
  movq -1008(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_112
  jmp test_parsing_assert_fail_112
test_parsing_assert_pass_112:
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -1024(%rbp), %rax
  addq $8, %rax
  movq %rax, -1032(%rbp)
  movq -1032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -1040(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_113(%rip), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1048(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1056(%rbp)
  movq -1048(%rbp), %rdi
  movq -1056(%rbp), %rsi
  call lm_key_eq
  mov -1064(%rbp), rax
  movq -1064(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_114(%rip), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1072(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1080(%rbp)
  movq -1072(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_115
  jmp test_parsing_assert_fail_115
test_parsing_assert_fail_112:
  movq -1016(%rbp), %rax
  addq $8, %rax
  movq %rax, -1088(%rbp)
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -1016(%rbp), %rax
  addq $24, %rax
  movq %rax, -1104(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1104(%rbp), %rsi
  movq -1096(%rbp), %rdx
  syscall
  movq %rax, -1112(%rbp)
  movq $50397203, %rax
  movq %rax, -1120(%rbp)
  jmp test_parsing_assert_pass_112
test_parsing_assert_pass_115:
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1128(%rbp)
  movq -1128(%rbp), %rax
  addq $24, %rax
  movq %rax, -1136(%rbp)
  movq -1136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1144(%rbp)
  movq -1144(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_116(%rip), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1152(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1160(%rbp)
  movq -1152(%rbp), %rdi
  movq -1160(%rbp), %rsi
  call lm_key_eq
  mov -1168(%rbp), rax
  movq -1168(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_117(%rip), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1176(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1184(%rbp)
  movq -1176(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_118
  jmp test_parsing_assert_fail_118
test_parsing_assert_fail_115:
  movq -1080(%rbp), %rax
  addq $8, %rax
  movq %rax, -1192(%rbp)
  movq -1192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1200(%rbp)
  movq -1080(%rbp), %rax
  addq $24, %rax
  movq %rax, -1208(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1208(%rbp), %rsi
  movq -1200(%rbp), %rdx
  syscall
  movq %rax, -1216(%rbp)
  movq $50397203, %rax
  movq %rax, -1224(%rbp)
  jmp test_parsing_assert_pass_115
test_parsing_assert_pass_118:
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1232(%rbp)
  movq -1232(%rbp), %rdi
  call std.mime.types.MIMEType.to_string
  mov -1240(%rbp), rax
  movq -1240(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_119(%rip), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1248(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1256(%rbp)
  movq -1248(%rbp), %rdi
  movq -1256(%rbp), %rsi
  call lm_key_eq
  mov -1264(%rbp), rax
  movq -1264(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_120(%rip), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1272(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1280(%rbp)
  movq -1272(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_121
  jmp test_parsing_assert_fail_121
test_parsing_assert_fail_118:
  movq -1184(%rbp), %rax
  addq $8, %rax
  movq %rax, -1288(%rbp)
  movq -1288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1296(%rbp)
  movq -1184(%rbp), %rax
  addq $24, %rax
  movq %rax, -1304(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1304(%rbp), %rsi
  movq -1296(%rbp), %rdx
  syscall
  movq %rax, -1312(%rbp)
  movq $50397203, %rax
  movq %rax, -1320(%rbp)
  jmp test_parsing_assert_pass_118
test_parsing_assert_pass_121:
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_122(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1328(%rbp)
  movq -1328(%rbp), %rdi
  call std.mime.index.parse
  mov -1336(%rbp), rax
  movq -1336(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1344(%rbp)
  movq -1344(%rbp), %rax
  movq %rax, -1352(%rbp)
  movq -1352(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1360(%rbp)
  movq -1360(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1368(%rbp)
  movq -1368(%rbp), %rax
  addq $0, %rax
  movq %rax, -1376(%rbp)
  movq -1376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1384(%rbp)
  movq -1384(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1392(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1400(%rbp)
  movq -1400(%rbp), %rax
  cmpq -1392(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1408(%rbp)
  movq -1408(%rbp), %rax
  movq -304(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_123(%rip), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1416(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1424(%rbp)
  movq -1416(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_124
  jmp test_parsing_assert_fail_124
test_parsing_assert_fail_121:
  movq -1280(%rbp), %rax
  addq $8, %rax
  movq %rax, -1432(%rbp)
  movq -1432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1440(%rbp)
  movq -1280(%rbp), %rax
  addq $24, %rax
  movq %rax, -1448(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1448(%rbp), %rsi
  movq -1440(%rbp), %rdx
  syscall
  movq %rax, -1456(%rbp)
  movq $50397203, %rax
  movq %rax, -1464(%rbp)
  jmp test_parsing_assert_pass_121
test_parsing_assert_pass_124:
  movq $0, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1472(%rbp)
  movq -1472(%rbp), %rax
  addq $8, %rax
  movq %rax, -1480(%rbp)
  movq -1480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1488(%rbp)
  movq -1488(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_125(%rip), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1496(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1504(%rbp)
  movq -1496(%rbp), %rdi
  movq -1504(%rbp), %rsi
  call lm_key_eq
  mov -1512(%rbp), rax
  movq -1512(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_126(%rip), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1520(%rbp)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1528(%rbp)
  movq -1520(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_127
  jmp test_parsing_assert_fail_127
test_parsing_assert_fail_124:
  movq -1424(%rbp), %rax
  addq $8, %rax
  movq %rax, -1536(%rbp)
  movq -1536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1544(%rbp)
  movq -1424(%rbp), %rax
  addq $24, %rax
  movq %rax, -1552(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1552(%rbp), %rsi
  movq -1544(%rbp), %rdx
  syscall
  movq %rax, -1560(%rbp)
  movq $50397203, %rax
  movq %rax, -1568(%rbp)
  jmp test_parsing_assert_pass_124
test_parsing_assert_pass_127:
  movq $0, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1576(%rbp)
  movq -1576(%rbp), %rax
  addq $24, %rax
  movq %rax, -1584(%rbp)
  movq -1584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1592(%rbp)
  movq -1592(%rbp), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_128(%rip), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1600(%rbp)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1608(%rbp)
  movq -1600(%rbp), %rdi
  movq -1608(%rbp), %rsi
  call lm_key_eq
  mov -1616(%rbp), rax
  movq -1616(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_129(%rip), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1624(%rbp)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1632(%rbp)
  movq -1624(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_130
  jmp test_parsing_assert_fail_130
test_parsing_assert_fail_127:
  movq -1528(%rbp), %rax
  addq $8, %rax
  movq %rax, -1640(%rbp)
  movq -1640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1648(%rbp)
  movq -1528(%rbp), %rax
  addq $24, %rax
  movq %rax, -1656(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1656(%rbp), %rsi
  movq -1648(%rbp), %rdx
  syscall
  movq %rax, -1664(%rbp)
  movq $50397203, %rax
  movq %rax, -1672(%rbp)
  jmp test_parsing_assert_pass_127
test_parsing_assert_pass_130:
  movq $0, %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1680(%rbp)
  movq -1680(%rbp), %rax
  addq $16, %rax
  movq %rax, -1688(%rbp)
  movq -1688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1696(%rbp)
  movq -1696(%rbp), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_131(%rip), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1704(%rbp)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1712(%rbp)
  movq -1704(%rbp), %rdi
  movq -1712(%rbp), %rsi
  call std.mime.types.MIMEParams.get
  mov -1720(%rbp), rax
  movq -1720(%rbp), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_132(%rip), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1728(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1736(%rbp)
  movq -1728(%rbp), %rdi
  movq -1736(%rbp), %rsi
  call lm_key_eq
  mov -1744(%rbp), rax
  movq -1744(%rbp), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_133(%rip), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1752(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1760(%rbp)
  movq -1752(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_134
  jmp test_parsing_assert_fail_134
test_parsing_assert_fail_130:
  movq -1632(%rbp), %rax
  addq $8, %rax
  movq %rax, -1768(%rbp)
  movq -1768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1776(%rbp)
  movq -1632(%rbp), %rax
  addq $24, %rax
  movq %rax, -1784(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1784(%rbp), %rsi
  movq -1776(%rbp), %rdx
  syscall
  movq %rax, -1792(%rbp)
  movq $50397203, %rax
  movq %rax, -1800(%rbp)
  jmp test_parsing_assert_pass_130
test_parsing_assert_pass_134:
  movq $0, %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1808(%rbp)
  movq -1808(%rbp), %rax
  addq $16, %rax
  movq %rax, -1816(%rbp)
  movq -1816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1824(%rbp)
  movq -1824(%rbp), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_135(%rip), %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1832(%rbp)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1840(%rbp)
  movq -1832(%rbp), %rdi
  movq -1840(%rbp), %rsi
  call std.mime.types.MIMEParams.get
  mov -1848(%rbp), rax
  movq -1848(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_136(%rip), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1856(%rbp)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1864(%rbp)
  movq -1856(%rbp), %rdi
  movq -1864(%rbp), %rsi
  call lm_key_eq
  mov -1872(%rbp), rax
  movq -1872(%rbp), %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_137(%rip), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1880(%rbp)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1888(%rbp)
  movq -1880(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_138
  jmp test_parsing_assert_fail_138
test_parsing_assert_fail_134:
  movq -1760(%rbp), %rax
  addq $8, %rax
  movq %rax, -1896(%rbp)
  movq -1896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1904(%rbp)
  movq -1760(%rbp), %rax
  addq $24, %rax
  movq %rax, -1912(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1912(%rbp), %rsi
  movq -1904(%rbp), %rdx
  syscall
  movq %rax, -1920(%rbp)
  movq $50397203, %rax
  movq %rax, -1928(%rbp)
  jmp test_parsing_assert_pass_134
test_parsing_assert_pass_138:
  movq $0, %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_139(%rip), %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1936(%rbp)
  movq -1936(%rbp), %rdi
  call std.mime.index.parse
  mov -1944(%rbp), rax
  movq -1944(%rbp), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1952(%rbp)
  movq -1952(%rbp), %rax
  movq %rax, -1960(%rbp)
  movq -1960(%rbp), %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1968(%rbp)
  movq -1968(%rbp), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1976(%rbp)
  movq -1976(%rbp), %rax
  addq $0, %rax
  movq %rax, -1984(%rbp)
  movq -1984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1992(%rbp)
  movq -1992(%rbp), %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2000(%rbp)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2008(%rbp)
  movq -2008(%rbp), %rax
  cmpq -2000(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2016(%rbp)
  movq -2016(%rbp), %rax
  movq -568(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_140(%rip), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2024(%rbp)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2032(%rbp)
  movq -2024(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_141
  jmp test_parsing_assert_fail_141
test_parsing_assert_fail_138:
  movq -1888(%rbp), %rax
  addq $8, %rax
  movq %rax, -2040(%rbp)
  movq -2040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2048(%rbp)
  movq -1888(%rbp), %rax
  addq $24, %rax
  movq %rax, -2056(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2056(%rbp), %rsi
  movq -2048(%rbp), %rdx
  syscall
  movq %rax, -2064(%rbp)
  movq $50397203, %rax
  movq %rax, -2072(%rbp)
  jmp test_parsing_assert_pass_138
test_parsing_assert_pass_141:
  movq $0, %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_142(%rip), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2080(%rbp)
  movq -2080(%rbp), %rdi
  call std.mime.index.parse
  mov -2088(%rbp), rax
  movq -2088(%rbp), %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2096(%rbp)
  movq -2096(%rbp), %rax
  movq %rax, -2104(%rbp)
  movq -2104(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2112(%rbp)
  movq -2112(%rbp), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2120(%rbp)
  movq -2120(%rbp), %rax
  addq $0, %rax
  movq %rax, -2128(%rbp)
  movq -2128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2136(%rbp)
  movq -2136(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2144(%rbp)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2152(%rbp)
  movq -2152(%rbp), %rax
  cmpq -2144(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2160(%rbp)
  movq -2160(%rbp), %rax
  movq -640(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_143(%rip), %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2168(%rbp)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2176(%rbp)
  movq -2168(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_144
  jmp test_parsing_assert_fail_144
test_parsing_assert_fail_141:
  movq -2032(%rbp), %rax
  addq $8, %rax
  movq %rax, -2184(%rbp)
  movq -2184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2192(%rbp)
  movq -2032(%rbp), %rax
  addq $24, %rax
  movq %rax, -2200(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2200(%rbp), %rsi
  movq -2192(%rbp), %rdx
  syscall
  movq %rax, -2208(%rbp)
  movq $50397203, %rax
  movq %rax, -2216(%rbp)
  jmp test_parsing_assert_pass_141
test_parsing_assert_pass_144:
  movq $0, %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_145(%rip), %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2224(%rbp)
  movq -2224(%rbp), %rdi
  call std.mime.index.parse
  mov -2232(%rbp), rax
  movq -2232(%rbp), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2240(%rbp)
  movq -2240(%rbp), %rax
  movq %rax, -2248(%rbp)
  movq -2248(%rbp), %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2256(%rbp)
  movq -2256(%rbp), %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2264(%rbp)
  movq -2264(%rbp), %rax
  addq $0, %rax
  movq %rax, -2272(%rbp)
  movq -2272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2280(%rbp)
  movq -2280(%rbp), %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2288(%rbp)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2296(%rbp)
  movq -2296(%rbp), %rax
  cmpq -2288(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2304(%rbp)
  movq -2304(%rbp), %rax
  movq -712(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_146(%rip), %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2312(%rbp)
  movq -720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2320(%rbp)
  movq -2312(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_147
  jmp test_parsing_assert_fail_147
test_parsing_assert_fail_144:
  movq -2176(%rbp), %rax
  addq $8, %rax
  movq %rax, -2328(%rbp)
  movq -2328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2336(%rbp)
  movq -2176(%rbp), %rax
  addq $24, %rax
  movq %rax, -2344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2344(%rbp), %rsi
  movq -2336(%rbp), %rdx
  syscall
  movq %rax, -2352(%rbp)
  movq $50397203, %rax
  movq %rax, -2360(%rbp)
  jmp test_parsing_assert_pass_144
test_parsing_assert_pass_147:
  movq $0, %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_148(%rip), %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2368(%rbp)
  movq -2368(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2376(%rbp)
  movq -2376(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_pr_nil_0_886
  jmp test_parsing_pr_str_0_886
test_parsing_assert_fail_147:
  movq -2320(%rbp), %rax
  addq $8, %rax
  movq %rax, -2384(%rbp)
  movq -2384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2392(%rbp)
  movq -2320(%rbp), %rax
  addq $24, %rax
  movq %rax, -2400(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2400(%rbp), %rsi
  movq -2392(%rbp), %rdx
  syscall
  movq %rax, -2408(%rbp)
  movq $50397203, %rax
  movq %rax, -2416(%rbp)
  jmp test_parsing_assert_pass_147
test_parsing_pr_nil_0_886:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2424(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2424(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2432(%rbp)
  jmp test_parsing_pr_next_0_886
test_parsing_pr_str_0_886:
  movq -2368(%rbp), %rax
  addq $8, %rax
  movq %rax, -2440(%rbp)
  movq -2440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2448(%rbp)
  movq -2368(%rbp), %rax
  addq $24, %rax
  movq %rax, -2456(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2456(%rbp), %rsi
  movq -2448(%rbp), %rdx
  syscall
  movq %rax, -2464(%rbp)
  jmp test_parsing_pr_next_0_886
test_parsing_pr_next_0_886:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2472(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2472(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2480(%rbp)
  movq $0, %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2488(%rbp)
  movq -2488(%rbp), %rax
  jmp test_parsing_epilogue
test_parsing_epilogue:
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
.Lfunc_end_test_parsing:

.globl test_parameters
test_parameters:
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
  subq $1272, %rsp
test_parameters_entry:
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
  jmp test_parameters_block_0
test_parameters_block_0:
  leaq str_hdr_149(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  testq %rax, %rax
  jne test_parameters_pr_nil_0_2777
  jmp test_parameters_pr_str_0_2777
test_parameters_pr_nil_0_2777:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -512(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -512(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -520(%rbp)
  jmp test_parameters_pr_next_0_2777
test_parameters_pr_str_0_2777:
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
  jmp test_parameters_pr_next_0_2777
test_parameters_pr_next_0_2777:
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
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  call std.mime.index.MIMEParams
  mov -576(%rbp), rax
  movq -576(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -584(%rbp), %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_150(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_151(%rip), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -608(%rbp), %rdi
  movq -616(%rbp), %rsi
  movq -624(%rbp), %rdx
  call std.mime.types.MIMEParams.set
  mov -632(%rbp), rax
  movq -632(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_152(%rip), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_153(%rip), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -640(%rbp), %rdi
  movq -648(%rbp), %rsi
  movq -656(%rbp), %rdx
  call std.mime.types.MIMEParams.set
  mov -664(%rbp), rax
  movq -664(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_154(%rip), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -672(%rbp), %rdi
  movq -680(%rbp), %rsi
  call std.mime.types.MIMEParams.get
  mov -688(%rbp), rax
  movq -688(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_155(%rip), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -696(%rbp), %rdi
  movq -704(%rbp), %rsi
  call lm_key_eq
  mov -712(%rbp), rax
  movq -712(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_156(%rip), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -720(%rbp), %rax
  testq %rax, %rax
  jne test_parameters_assert_pass_157
  jmp test_parameters_assert_fail_157
test_parameters_assert_pass_157:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_158(%rip), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -736(%rbp), %rdi
  movq -744(%rbp), %rsi
  call std.mime.types.MIMEParams.get
  mov -752(%rbp), rax
  movq -752(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_159(%rip), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -760(%rbp), %rdi
  movq -768(%rbp), %rsi
  call lm_key_eq
  mov -776(%rbp), rax
  movq -776(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_160(%rip), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -784(%rbp), %rax
  testq %rax, %rax
  jne test_parameters_assert_pass_161
  jmp test_parameters_assert_fail_161
test_parameters_assert_fail_157:
  movq -728(%rbp), %rax
  addq $8, %rax
  movq %rax, -800(%rbp)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -728(%rbp), %rax
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
  jmp test_parameters_assert_pass_157
test_parameters_assert_pass_161:
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_162(%rip), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -840(%rbp), %rdi
  movq -848(%rbp), %rsi
  call std.mime.types.MIMEParams.has
  mov -856(%rbp), rax
  movq -856(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -872(%rbp), %rax
  cmpq -864(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -880(%rbp)
  movq -880(%rbp), %rax
  movq -256(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_163(%rip), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -888(%rbp), %rax
  testq %rax, %rax
  jne test_parameters_assert_pass_164
  jmp test_parameters_assert_fail_164
test_parameters_assert_fail_161:
  movq -792(%rbp), %rax
  addq $8, %rax
  movq %rax, -904(%rbp)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -912(%rbp)
  movq -792(%rbp), %rax
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
  jmp test_parameters_assert_pass_161
test_parameters_assert_pass_164:
  movq $0, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_165(%rip), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -944(%rbp), %rdi
  movq -952(%rbp), %rsi
  call std.mime.types.MIMEParams.has
  mov -960(%rbp), rax
  movq -960(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -976(%rbp), %rax
  cmpq -968(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -984(%rbp)
  movq -984(%rbp), %rax
  movq -304(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_166(%rip), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -992(%rbp), %rax
  testq %rax, %rax
  jne test_parameters_assert_pass_167
  jmp test_parameters_assert_fail_167
test_parameters_assert_fail_164:
  movq -896(%rbp), %rax
  addq $8, %rax
  movq %rax, -1008(%rbp)
  movq -1008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1016(%rbp)
  movq -896(%rbp), %rax
  addq $24, %rax
  movq %rax, -1024(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1024(%rbp), %rsi
  movq -1016(%rbp), %rdx
  syscall
  movq %rax, -1032(%rbp)
  movq $50397203, %rax
  movq %rax, -1040(%rbp)
  jmp test_parameters_assert_pass_164
test_parameters_assert_pass_167:
  movq $0, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_168(%rip), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1048(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1056(%rbp)
  movq -1048(%rbp), %rdi
  movq -1056(%rbp), %rsi
  call std.mime.types.MIMEParams.remove
  mov -1064(%rbp), rax
  movq -1064(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_169(%rip), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1072(%rbp)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1080(%rbp)
  movq -1072(%rbp), %rdi
  movq -1080(%rbp), %rsi
  call std.mime.types.MIMEParams.has
  mov -1088(%rbp), rax
  movq -1088(%rbp), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1104(%rbp)
  movq -1104(%rbp), %rax
  cmpq -1096(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1112(%rbp)
  movq -1112(%rbp), %rax
  movq -368(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_170(%rip), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1120(%rbp)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1128(%rbp)
  movq -1120(%rbp), %rax
  testq %rax, %rax
  jne test_parameters_assert_pass_171
  jmp test_parameters_assert_fail_171
test_parameters_assert_fail_167:
  movq -1000(%rbp), %rax
  addq $8, %rax
  movq %rax, -1136(%rbp)
  movq -1136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1144(%rbp)
  movq -1000(%rbp), %rax
  addq $24, %rax
  movq %rax, -1152(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1152(%rbp), %rsi
  movq -1144(%rbp), %rdx
  syscall
  movq %rax, -1160(%rbp)
  movq $50397203, %rax
  movq %rax, -1168(%rbp)
  jmp test_parameters_assert_pass_167
test_parameters_assert_pass_171:
  movq $0, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_172(%rip), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1176(%rbp)
  movq -1176(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1184(%rbp)
  movq -1184(%rbp), %rax
  testq %rax, %rax
  jne test_parameters_pr_nil_0_6915
  jmp test_parameters_pr_str_0_6915
test_parameters_assert_fail_171:
  movq -1128(%rbp), %rax
  addq $8, %rax
  movq %rax, -1192(%rbp)
  movq -1192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1200(%rbp)
  movq -1128(%rbp), %rax
  addq $24, %rax
  movq %rax, -1208(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1208(%rbp), %rsi
  movq -1200(%rbp), %rdx
  syscall
  movq %rax, -1216(%rbp)
  movq $50397203, %rax
  movq %rax, -1224(%rbp)
  jmp test_parameters_assert_pass_171
test_parameters_pr_nil_0_6915:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1232(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1232(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1240(%rbp)
  jmp test_parameters_pr_next_0_6915
test_parameters_pr_str_0_6915:
  movq -1176(%rbp), %rax
  addq $8, %rax
  movq %rax, -1248(%rbp)
  movq -1248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1256(%rbp)
  movq -1176(%rbp), %rax
  addq $24, %rax
  movq %rax, -1264(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1264(%rbp), %rsi
  movq -1256(%rbp), %rdx
  syscall
  movq %rax, -1272(%rbp)
  jmp test_parameters_pr_next_0_6915
test_parameters_pr_next_0_6915:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1280(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1280(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1288(%rbp)
  movq $0, %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1296(%rbp)
  movq -1296(%rbp), %rax
  jmp test_parameters_epilogue
test_parameters_epilogue:
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
.Lfunc_end_test_parameters:

.globl std.mime.types.MIMEType.init
std.mime.types.MIMEType.init:
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
  movq %r8, -80(%rbp)
std.mime.types.MIMEType.init_entry:
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
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.mime.types.MIMEType.init_epilogue
std.mime.types.MIMEType.init_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.init:

.globl test_extension_mapping
test_extension_mapping:
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
  subq $1736, %rsp
test_extension_mapping_entry:
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
  jmp test_extension_mapping_block_0
test_extension_mapping_block_0:
  leaq str_hdr_173(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  testq %rax, %rax
  jne test_extension_mapping_pr_nil_0_7793
  jmp test_extension_mapping_pr_str_0_7793
test_extension_mapping_pr_nil_0_7793:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -664(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -664(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -672(%rbp)
  jmp test_extension_mapping_pr_next_0_7793
test_extension_mapping_pr_str_0_7793:
  movq -648(%rbp), %rax
  addq $8, %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -648(%rbp), %rax
  addq $24, %rax
  movq %rax, -696(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -696(%rbp), %rsi
  movq -688(%rbp), %rdx
  syscall
  movq %rax, -704(%rbp)
  jmp test_extension_mapping_pr_next_0_7793
test_extension_mapping_pr_next_0_7793:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -712(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -712(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -720(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_174(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -728(%rbp), %rdi
  call std.mime.index.extension_to_mime
  mov -736(%rbp), rax
  movq -736(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_175(%rip), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -744(%rbp), %rdi
  movq -752(%rbp), %rsi
  call lm_key_eq
  mov -760(%rbp), rax
  movq -760(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_176(%rip), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -768(%rbp), %rax
  testq %rax, %rax
  jne test_extension_mapping_assert_pass_177
  jmp test_extension_mapping_assert_fail_177
test_extension_mapping_assert_pass_177:
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_178(%rip), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -784(%rbp), %rdi
  call std.mime.index.extension_to_mime
  mov -792(%rbp), rax
  movq -792(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_179(%rip), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -800(%rbp), %rdi
  movq -808(%rbp), %rsi
  call lm_key_eq
  mov -816(%rbp), rax
  movq -816(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_180(%rip), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -832(%rbp)
  movq -824(%rbp), %rax
  testq %rax, %rax
  jne test_extension_mapping_assert_pass_181
  jmp test_extension_mapping_assert_fail_181
test_extension_mapping_assert_fail_177:
  movq -776(%rbp), %rax
  addq $8, %rax
  movq %rax, -840(%rbp)
  movq -840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -776(%rbp), %rax
  addq $24, %rax
  movq %rax, -856(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -856(%rbp), %rsi
  movq -848(%rbp), %rdx
  syscall
  movq %rax, -864(%rbp)
  movq $50397203, %rax
  movq %rax, -872(%rbp)
  jmp test_extension_mapping_assert_pass_177
test_extension_mapping_assert_pass_181:
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_182(%rip), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -880(%rbp), %rdi
  call std.mime.index.extension_to_mime
  mov -888(%rbp), rax
  movq -888(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_183(%rip), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -896(%rbp), %rdi
  movq -904(%rbp), %rsi
  call lm_key_eq
  mov -912(%rbp), rax
  movq -912(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_184(%rip), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -928(%rbp)
  movq -920(%rbp), %rax
  testq %rax, %rax
  jne test_extension_mapping_assert_pass_185
  jmp test_extension_mapping_assert_fail_185
test_extension_mapping_assert_fail_181:
  movq -832(%rbp), %rax
  addq $8, %rax
  movq %rax, -936(%rbp)
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -832(%rbp), %rax
  addq $24, %rax
  movq %rax, -952(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -952(%rbp), %rsi
  movq -944(%rbp), %rdx
  syscall
  movq %rax, -960(%rbp)
  movq $50397203, %rax
  movq %rax, -968(%rbp)
  jmp test_extension_mapping_assert_pass_181
test_extension_mapping_assert_pass_185:
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_186(%rip), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -976(%rbp), %rdi
  call std.mime.index.extension_to_mime
  mov -984(%rbp), rax
  movq -984(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_187(%rip), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -992(%rbp), %rdi
  movq -1000(%rbp), %rsi
  call lm_key_eq
  mov -1008(%rbp), rax
  movq -1008(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_188(%rip), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1016(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -1016(%rbp), %rax
  testq %rax, %rax
  jne test_extension_mapping_assert_pass_189
  jmp test_extension_mapping_assert_fail_189
test_extension_mapping_assert_fail_185:
  movq -928(%rbp), %rax
  addq $8, %rax
  movq %rax, -1032(%rbp)
  movq -1032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -928(%rbp), %rax
  addq $24, %rax
  movq %rax, -1048(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1048(%rbp), %rsi
  movq -1040(%rbp), %rdx
  syscall
  movq %rax, -1056(%rbp)
  movq $50397203, %rax
  movq %rax, -1064(%rbp)
  jmp test_extension_mapping_assert_pass_185
test_extension_mapping_assert_pass_189:
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_190(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1072(%rbp)
  movq -1072(%rbp), %rdi
  call std.mime.index.extension_to_mime
  mov -1080(%rbp), rax
  movq -1080(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_191(%rip), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1088(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -1088(%rbp), %rdi
  movq -1096(%rbp), %rsi
  call lm_key_eq
  mov -1104(%rbp), rax
  movq -1104(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_192(%rip), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1112(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1120(%rbp)
  movq -1112(%rbp), %rax
  testq %rax, %rax
  jne test_extension_mapping_assert_pass_193
  jmp test_extension_mapping_assert_fail_193
test_extension_mapping_assert_fail_189:
  movq -1024(%rbp), %rax
  addq $8, %rax
  movq %rax, -1128(%rbp)
  movq -1128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1136(%rbp)
  movq -1024(%rbp), %rax
  addq $24, %rax
  movq %rax, -1144(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1144(%rbp), %rsi
  movq -1136(%rbp), %rdx
  syscall
  movq %rax, -1152(%rbp)
  movq $50397203, %rax
  movq %rax, -1160(%rbp)
  jmp test_extension_mapping_assert_pass_189
test_extension_mapping_assert_pass_193:
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_194(%rip), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1168(%rbp)
  movq -1168(%rbp), %rdi
  call std.mime.index.mime_to_extension
  mov -1176(%rbp), rax
  movq -1176(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_195(%rip), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1184(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1192(%rbp)
  movq -1184(%rbp), %rdi
  movq -1192(%rbp), %rsi
  call lm_key_eq
  mov -1200(%rbp), rax
  movq -1200(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_196(%rip), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1208(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1216(%rbp)
  movq -1208(%rbp), %rax
  testq %rax, %rax
  jne test_extension_mapping_assert_pass_197
  jmp test_extension_mapping_assert_fail_197
test_extension_mapping_assert_fail_193:
  movq -1120(%rbp), %rax
  addq $8, %rax
  movq %rax, -1224(%rbp)
  movq -1224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1232(%rbp)
  movq -1120(%rbp), %rax
  addq $24, %rax
  movq %rax, -1240(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1240(%rbp), %rsi
  movq -1232(%rbp), %rdx
  syscall
  movq %rax, -1248(%rbp)
  movq $50397203, %rax
  movq %rax, -1256(%rbp)
  jmp test_extension_mapping_assert_pass_193
test_extension_mapping_assert_pass_197:
  movq $0, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_198(%rip), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1264(%rbp)
  movq -1264(%rbp), %rdi
  call std.mime.index.mime_to_extension
  mov -1272(%rbp), rax
  movq -1272(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_199(%rip), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1280(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -1280(%rbp), %rdi
  movq -1288(%rbp), %rsi
  call lm_key_eq
  mov -1296(%rbp), rax
  movq -1296(%rbp), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_200(%rip), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1304(%rbp)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1312(%rbp)
  movq -1304(%rbp), %rax
  testq %rax, %rax
  jne test_extension_mapping_assert_pass_201
  jmp test_extension_mapping_assert_fail_201
test_extension_mapping_assert_fail_197:
  movq -1216(%rbp), %rax
  addq $8, %rax
  movq %rax, -1320(%rbp)
  movq -1320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1328(%rbp)
  movq -1216(%rbp), %rax
  addq $24, %rax
  movq %rax, -1336(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1336(%rbp), %rsi
  movq -1328(%rbp), %rdx
  syscall
  movq %rax, -1344(%rbp)
  movq $50397203, %rax
  movq %rax, -1352(%rbp)
  jmp test_extension_mapping_assert_pass_197
test_extension_mapping_assert_pass_201:
  movq $0, %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_202(%rip), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1360(%rbp)
  movq -1360(%rbp), %rdi
  call std.mime.index.mime_to_extension
  mov -1368(%rbp), rax
  movq -1368(%rbp), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_203(%rip), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1376(%rbp)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1384(%rbp)
  movq -1376(%rbp), %rdi
  movq -1384(%rbp), %rsi
  call lm_key_eq
  mov -1392(%rbp), rax
  movq -1392(%rbp), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_204(%rip), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1400(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1408(%rbp)
  movq -1400(%rbp), %rax
  testq %rax, %rax
  jne test_extension_mapping_assert_pass_205
  jmp test_extension_mapping_assert_fail_205
test_extension_mapping_assert_fail_201:
  movq -1312(%rbp), %rax
  addq $8, %rax
  movq %rax, -1416(%rbp)
  movq -1416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1424(%rbp)
  movq -1312(%rbp), %rax
  addq $24, %rax
  movq %rax, -1432(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1432(%rbp), %rsi
  movq -1424(%rbp), %rdx
  syscall
  movq %rax, -1440(%rbp)
  movq $50397203, %rax
  movq %rax, -1448(%rbp)
  jmp test_extension_mapping_assert_pass_201
test_extension_mapping_assert_pass_205:
  movq $0, %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_206(%rip), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1456(%rbp)
  movq -1456(%rbp), %rdi
  call std.mime.index.mime_to_extension
  mov -1464(%rbp), rax
  movq -1464(%rbp), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_207(%rip), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1472(%rbp)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1480(%rbp)
  movq -1472(%rbp), %rdi
  movq -1480(%rbp), %rsi
  call lm_key_eq
  mov -1488(%rbp), rax
  movq -1488(%rbp), %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_208(%rip), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1496(%rbp)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1504(%rbp)
  movq -1496(%rbp), %rax
  testq %rax, %rax
  jne test_extension_mapping_assert_pass_209
  jmp test_extension_mapping_assert_fail_209
test_extension_mapping_assert_fail_205:
  movq -1408(%rbp), %rax
  addq $8, %rax
  movq %rax, -1512(%rbp)
  movq -1512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1520(%rbp)
  movq -1408(%rbp), %rax
  addq $24, %rax
  movq %rax, -1528(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1528(%rbp), %rsi
  movq -1520(%rbp), %rdx
  syscall
  movq %rax, -1536(%rbp)
  movq $50397203, %rax
  movq %rax, -1544(%rbp)
  jmp test_extension_mapping_assert_pass_205
test_extension_mapping_assert_pass_209:
  movq $0, %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_210(%rip), %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1552(%rbp)
  movq -1552(%rbp), %rdi
  call std.mime.index.mime_to_extension
  mov -1560(%rbp), rax
  movq -1560(%rbp), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_211(%rip), %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1568(%rbp)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1576(%rbp)
  movq -1568(%rbp), %rdi
  movq -1576(%rbp), %rsi
  call lm_key_eq
  mov -1584(%rbp), rax
  movq -1584(%rbp), %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_212(%rip), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1592(%rbp)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1600(%rbp)
  movq -1592(%rbp), %rax
  testq %rax, %rax
  jne test_extension_mapping_assert_pass_213
  jmp test_extension_mapping_assert_fail_213
test_extension_mapping_assert_fail_209:
  movq -1504(%rbp), %rax
  addq $8, %rax
  movq %rax, -1608(%rbp)
  movq -1608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1616(%rbp)
  movq -1504(%rbp), %rax
  addq $24, %rax
  movq %rax, -1624(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1624(%rbp), %rsi
  movq -1616(%rbp), %rdx
  syscall
  movq %rax, -1632(%rbp)
  movq $50397203, %rax
  movq %rax, -1640(%rbp)
  jmp test_extension_mapping_assert_pass_209
test_extension_mapping_assert_pass_213:
  movq $0, %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_214(%rip), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1648(%rbp)
  movq -1648(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1656(%rbp)
  movq -1656(%rbp), %rax
  testq %rax, %rax
  jne test_extension_mapping_pr_nil_0_8335
  jmp test_extension_mapping_pr_str_0_8335
test_extension_mapping_assert_fail_213:
  movq -1600(%rbp), %rax
  addq $8, %rax
  movq %rax, -1664(%rbp)
  movq -1664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1672(%rbp)
  movq -1600(%rbp), %rax
  addq $24, %rax
  movq %rax, -1680(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1680(%rbp), %rsi
  movq -1672(%rbp), %rdx
  syscall
  movq %rax, -1688(%rbp)
  movq $50397203, %rax
  movq %rax, -1696(%rbp)
  jmp test_extension_mapping_assert_pass_213
test_extension_mapping_pr_nil_0_8335:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1704(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1704(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1712(%rbp)
  jmp test_extension_mapping_pr_next_0_8335
test_extension_mapping_pr_str_0_8335:
  movq -1648(%rbp), %rax
  addq $8, %rax
  movq %rax, -1720(%rbp)
  movq -1720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1728(%rbp)
  movq -1648(%rbp), %rax
  addq $24, %rax
  movq %rax, -1736(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1736(%rbp), %rsi
  movq -1728(%rbp), %rdx
  syscall
  movq %rax, -1744(%rbp)
  jmp test_extension_mapping_pr_next_0_8335
test_extension_mapping_pr_next_0_8335:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1752(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1752(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1760(%rbp)
  movq $0, %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1768(%rbp)
  movq -1768(%rbp), %rax
  jmp test_extension_mapping_epilogue
test_extension_mapping_epilogue:
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
.Lfunc_end_test_extension_mapping:

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
  leaq str_hdr_215(%rip), %rax
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
  jne __user_main_pr_nil_0_5386
  jmp __user_main_pr_str_0_5386
__user_main_pr_nil_0_5386:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -344(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -352(%rbp)
  jmp __user_main_pr_next_0_5386
__user_main_pr_str_0_5386:
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
  jmp __user_main_pr_next_0_5386
__user_main_pr_next_0_5386:
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
  call test_parsing
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
  leaq str_hdr_216(%rip), %rax
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
  jne __user_main_assert_pass_217
  jmp __user_main_assert_fail_217
__user_main_assert_pass_217:
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  call test_classification
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
  leaq str_hdr_218(%rip), %rax
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
  jne __user_main_assert_pass_219
  jmp __user_main_assert_fail_219
__user_main_assert_fail_217:
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
  jmp __user_main_assert_pass_217
__user_main_assert_pass_219:
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  call test_parameters
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
  leaq str_hdr_220(%rip), %rax
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
  jne __user_main_assert_pass_221
  jmp __user_main_assert_fail_221
__user_main_assert_fail_219:
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
  jmp __user_main_assert_pass_219
__user_main_assert_pass_221:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  call test_extension_mapping
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
  leaq str_hdr_222(%rip), %rax
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
  jne __user_main_assert_pass_223
  jmp __user_main_assert_fail_223
__user_main_assert_fail_221:
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
  jmp __user_main_assert_pass_221
__user_main_assert_pass_223:
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_224(%rip), %rax
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
  jne __user_main_pr_nil_0_492
  jmp __user_main_pr_str_0_492
__user_main_assert_fail_223:
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
  jmp __user_main_assert_pass_223
__user_main_pr_nil_0_492:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -776(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -776(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -784(%rbp)
  jmp __user_main_pr_next_0_492
__user_main_pr_str_0_492:
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
  jmp __user_main_pr_next_0_492
__user_main_pr_next_0_492:
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

.globl std.mime.types.MIMEParams.get
std.mime.types.MIMEParams.get:
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
std.mime.types.MIMEParams.get_entry:
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
  jmp std.mime.types.MIMEParams.get_epilogue
std.mime.types.MIMEParams.get_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.get:

.globl std.mime.types.MIMEParams.set
std.mime.types.MIMEParams.set:
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
std.mime.types.MIMEParams.set_entry:
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
  jmp std.mime.types.MIMEParams.set_epilogue
std.mime.types.MIMEParams.set_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.set:

.globl std.mime.types.parse
std.mime.types.parse:
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
  subq $2712, %rsp
  movq %rdi, -48(%rbp)
std.mime.types.parse_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.parse_block_0
std.mime.types.parse_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1072(%rbp)
  movq -1072(%rbp), %rdi
  call std.mime.types.trim
  mov -1080(%rbp), rax
  movq -1080(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1088(%rbp)
  movq -1088(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_225(%rip), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1104(%rbp)
  movq -1096(%rbp), %rdi
  movq -1104(%rbp), %rsi
  call lm_key_eq
  mov -1112(%rbp), rax
  movq -1112(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1120(%rbp)
  movq -1120(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.parse_block_5
  jmp std.mime.types.parse_block_13
std.mime.types.parse_block_5:
  leaq str_hdr_226(%rip), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_227(%rip), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 16 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1128(%rbp)
  addq $16, %rax
  movq %rax, heap_ptr(%rip)
  movq -1128(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1136(%rbp)
  movq -1136(%rbp), %rdi
  call std.mime.types.MIMEParams.init
  mov -1144(%rbp), rax
  movq -1144(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 32 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1152(%rbp)
  addq $32, %rax
  movq %rax, heap_ptr(%rip)
  movq -1152(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1160(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1168(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1176(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1184(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1192(%rbp)
  movq -1160(%rbp), %rdi
  movq -1168(%rbp), %rsi
  movq -1176(%rbp), %rdx
  movq -1184(%rbp), %rcx
  movq -1192(%rbp), %r8
  call std.mime.types.MIMEType.init
  mov -1200(%rbp), rax
  movq -1200(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1208(%rbp)
  movq -1208(%rbp), %rax
  jmp std.mime.types.parse_epilogue
std.mime.types.parse_block_13:
  leaq str_hdr_228(%rip), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1216(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1224(%rbp)
  movq -1216(%rbp), %rdi
  movq -1224(%rbp), %rsi
  call std.mime.types.split_str
  mov -1232(%rbp), rax
  movq -1232(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1240(%rbp)
  movq -1240(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1248(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1256(%rbp)
  movq -1248(%rbp), %rdi
  movq -1256(%rbp), %rsi
  call lm_list_get
  mov -1264(%rbp), rax
  movq -1264(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1272(%rbp)
  movq -1272(%rbp), %rdi
  call std.mime.types.trim
  mov -1280(%rbp), rax
  movq -1280(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -1288(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_229(%rip), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1296(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1304(%rbp)
  movq -1296(%rbp), %rdi
  movq -1304(%rbp), %rsi
  call std.mime.types.index_of
  mov -1312(%rbp), rax
  movq -1312(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1320(%rbp)
  movq -1320(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1328(%rbp)
  movq -1328(%rbp), %rax
  negq %rax
  movq %rax, -1336(%rbp)
  movq -1336(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1344(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1352(%rbp)
  movq -1352(%rbp), %rax
  cmpq -1344(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1360(%rbp)
  movq -1360(%rbp), %rax
  movq -248(%rbp), %rdx
  movl %eax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1368(%rbp)
  movq -1368(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.parse_block_27
  jmp std.mime.types.parse_block_35
std.mime.types.parse_block_27:
  leaq str_hdr_230(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_231(%rip), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 16 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1376(%rbp)
  addq $16, %rax
  movq %rax, heap_ptr(%rip)
  movq -1376(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1384(%rbp)
  movq -1384(%rbp), %rdi
  call std.mime.types.MIMEParams.init
  mov -1392(%rbp), rax
  movq -1392(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 32 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1400(%rbp)
  addq $32, %rax
  movq %rax, heap_ptr(%rip)
  movq -1400(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1408(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1416(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1424(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1432(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1440(%rbp)
  movq -1408(%rbp), %rdi
  movq -1416(%rbp), %rsi
  movq -1424(%rbp), %rdx
  movq -1432(%rbp), %rcx
  movq -1440(%rbp), %r8
  call std.mime.types.MIMEType.init
  mov -1448(%rbp), rax
  movq -1448(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1456(%rbp)
  movq -1456(%rbp), %rax
  jmp std.mime.types.parse_epilogue
std.mime.types.parse_block_35:
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1464(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1472(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1480(%rbp)
  movq -1464(%rbp), %rdi
  movq -1472(%rbp), %rsi
  movq -1480(%rbp), %rdx
  call _builtin_substring
  mov -1488(%rbp), rax
  movq -1488(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1496(%rbp)
  movq -1496(%rbp), %rdi
  call std.mime.types.trim
  mov -1504(%rbp), rax
  movq -1504(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1512(%rbp)
  movq -1512(%rbp), %rdi
  call std.mime.types.to_lower
  mov -1520(%rbp), rax
  movq -1520(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1528(%rbp)
  movq -1528(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1536(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1544(%rbp)
  movq -1544(%rbp), %rax
  addq -1536(%rbp), %rax
  movq %rax, -1552(%rbp)
  movq -1552(%rbp), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1560(%rbp)
  movq -1560(%rbp), %rdi
  call lm_list_len
  mov -1568(%rbp), rax
  movq -1568(%rbp), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1576(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1584(%rbp)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1592(%rbp)
  movq -1576(%rbp), %rdi
  movq -1584(%rbp), %rsi
  movq -1592(%rbp), %rdx
  call _builtin_substring
  mov -1600(%rbp), rax
  movq -1600(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1608(%rbp)
  movq -1608(%rbp), %rdi
  call std.mime.types.trim
  mov -1616(%rbp), rax
  movq -1616(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1624(%rbp)
  movq -1624(%rbp), %rdi
  call std.mime.types.to_lower
  mov -1632(%rbp), rax
  movq -1632(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1640(%rbp)
  movq -1640(%rbp), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_232(%rip), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1648(%rbp)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1656(%rbp)
  movq -1648(%rbp), %rdi
  movq -1656(%rbp), %rsi
  call lm_key_eq
  mov -1664(%rbp), rax
  movq -1664(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1672(%rbp)
  movq -1672(%rbp), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1680(%rbp)
  movq -1680(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.parse_block_56
  jmp std.mime.types.parse_block_52
std.mime.types.parse_block_52:
  leaq str_hdr_233(%rip), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1688(%rbp)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1696(%rbp)
  movq -1688(%rbp), %rdi
  movq -1696(%rbp), %rsi
  call lm_key_eq
  mov -1704(%rbp), rax
  movq -1704(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1712(%rbp)
  movq -1712(%rbp), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.parse_block_56
std.mime.types.parse_block_56:
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1720(%rbp)
  movq -1720(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.parse_block_57
  jmp std.mime.types.parse_block_65
std.mime.types.parse_block_57:
  leaq str_hdr_234(%rip), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_235(%rip), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 16 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1728(%rbp)
  addq $16, %rax
  movq %rax, heap_ptr(%rip)
  movq -1728(%rbp), %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1736(%rbp)
  movq -1736(%rbp), %rdi
  call std.mime.types.MIMEParams.init
  mov -1744(%rbp), rax
  movq -1744(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 32 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1752(%rbp)
  addq $32, %rax
  movq %rax, heap_ptr(%rip)
  movq -1752(%rbp), %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1760(%rbp)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1768(%rbp)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1776(%rbp)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1784(%rbp)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1792(%rbp)
  movq -1760(%rbp), %rdi
  movq -1768(%rbp), %rsi
  movq -1776(%rbp), %rdx
  movq -1784(%rbp), %rcx
  movq -1792(%rbp), %r8
  call std.mime.types.MIMEType.init
  mov -1800(%rbp), rax
  movq -1800(%rbp), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1808(%rbp)
  movq -1808(%rbp), %rax
  jmp std.mime.types.parse_epilogue
std.mime.types.parse_block_65:
  # Bump Allocation: 16 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1816(%rbp)
  addq $16, %rax
  movq %rax, heap_ptr(%rip)
  movq -1816(%rbp), %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1824(%rbp)
  movq -1824(%rbp), %rdi
  call std.mime.types.MIMEParams.init
  mov -1832(%rbp), rax
  movq -1832(%rbp), %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1840(%rbp)
  movq -1840(%rbp), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.parse_block_70
std.mime.types.parse_block_70:
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1848(%rbp)
  movq -1848(%rbp), %rdi
  call lm_list_len
  mov -1856(%rbp), rax
  movq -1856(%rbp), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1864(%rbp)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1872(%rbp)
  movq -1872(%rbp), %rax
  cmpq -1864(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1880(%rbp)
  movq -1880(%rbp), %rax
  movq -552(%rbp), %rdx
  movl %eax, (%rdx)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1888(%rbp)
  movq -1888(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.parse_block_73
  jmp std.mime.types.parse_block_141
std.mime.types.parse_block_73:
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1896(%rbp)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1904(%rbp)
  movq -1896(%rbp), %rdi
  movq -1904(%rbp), %rsi
  call lm_list_get
  mov -1912(%rbp), rax
  movq -1912(%rbp), %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1920(%rbp)
  movq -1920(%rbp), %rdi
  call std.mime.types.trim
  mov -1928(%rbp), rax
  movq -1928(%rbp), %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1936(%rbp)
  movq -1936(%rbp), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_236(%rip), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1944(%rbp)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1952(%rbp)
  movq -1944(%rbp), %rdi
  movq -1952(%rbp), %rsi
  call lm_key_eq
  mov -1960(%rbp), rax
  movq -1960(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1968(%rbp)
  movq -1968(%rbp), %rax
  movq -592(%rbp), %rdx
  movl %eax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1976(%rbp)
  movq -1976(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.parse_block_79
  jmp std.mime.types.parse_block_136
std.mime.types.parse_block_79:
  leaq str_hdr_237(%rip), %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1984(%rbp)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1992(%rbp)
  movq -1984(%rbp), %rdi
  movq -1992(%rbp), %rsi
  call std.mime.types.index_of
  mov -2000(%rbp), rax
  movq -2000(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2008(%rbp)
  movq -2008(%rbp), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2016(%rbp)
  movq -2016(%rbp), %rax
  negq %rax
  movq %rax, -2024(%rbp)
  movq -2024(%rbp), %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2032(%rbp)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2040(%rbp)
  movq -2040(%rbp), %rax
  cmpq -2032(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -2048(%rbp)
  movq -2048(%rbp), %rax
  movq -640(%rbp), %rdx
  movl %eax, (%rdx)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2056(%rbp)
  movq -2056(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.parse_block_86
  jmp std.mime.types.parse_block_135
std.mime.types.parse_block_86:
  movq $0, %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2064(%rbp)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2072(%rbp)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2080(%rbp)
  movq -2064(%rbp), %rdi
  movq -2072(%rbp), %rsi
  movq -2080(%rbp), %rdx
  call _builtin_substring
  mov -2088(%rbp), rax
  movq -2088(%rbp), %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2096(%rbp)
  movq -2096(%rbp), %rdi
  call std.mime.types.trim
  mov -2104(%rbp), rax
  movq -2104(%rbp), %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2112(%rbp)
  movq -2112(%rbp), %rdi
  call std.mime.types.to_lower
  mov -2120(%rbp), rax
  movq -2120(%rbp), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2128(%rbp)
  movq -2128(%rbp), %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2136(%rbp)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2144(%rbp)
  movq -2144(%rbp), %rax
  addq -2136(%rbp), %rax
  movq %rax, -2152(%rbp)
  movq -2152(%rbp), %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2160(%rbp)
  movq -2160(%rbp), %rdi
  call lm_list_len
  mov -2168(%rbp), rax
  movq -2168(%rbp), %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2176(%rbp)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2184(%rbp)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2192(%rbp)
  movq -2176(%rbp), %rdi
  movq -2184(%rbp), %rsi
  movq -2192(%rbp), %rdx
  call _builtin_substring
  mov -2200(%rbp), rax
  movq -2200(%rbp), %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2208(%rbp)
  movq -2208(%rbp), %rdi
  call std.mime.types.trim
  mov -2216(%rbp), rax
  movq -2216(%rbp), %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2224(%rbp)
  movq -2224(%rbp), %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_238(%rip), %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2232(%rbp)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2240(%rbp)
  movq -2232(%rbp), %rdi
  movq -2240(%rbp), %rsi
  call lm_key_eq
  mov -2248(%rbp), rax
  movq -2248(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2256(%rbp)
  movq -2256(%rbp), %rax
  movq -752(%rbp), %rdx
  movl %eax, (%rdx)
  movq -752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2264(%rbp)
  movq -2264(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.parse_block_101
  jmp std.mime.types.parse_block_134
std.mime.types.parse_block_101:
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2272(%rbp)
  movq -2272(%rbp), %rdi
  call lm_list_len
  mov -2280(%rbp), rax
  movq -2280(%rbp), %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2288(%rbp)
  movq -776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2296(%rbp)
  movq -2296(%rbp), %rax
  cmpq -2288(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -2304(%rbp)
  movq -2304(%rbp), %rax
  movq -792(%rbp), %rdx
  movl %eax, (%rdx)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2312(%rbp)
  movq -2312(%rbp), %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2320(%rbp)
  movq -2320(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.parse_block_106
  jmp std.mime.types.parse_block_113
std.mime.types.parse_block_106:
  movq $0, %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2328(%rbp)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2336(%rbp)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2344(%rbp)
  movq -2328(%rbp), %rdi
  movq -2336(%rbp), %rsi
  movq -2344(%rbp), %rdx
  call _builtin_substring
  mov -2352(%rbp), rax
  movq -2352(%rbp), %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_239(%rip), %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2360(%rbp)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2368(%rbp)
  movq -2360(%rbp), %rdi
  movq -2368(%rbp), %rsi
  call lm_key_eq
  mov -2376(%rbp), rax
  movq -2376(%rbp), %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2384(%rbp)
  movq -2384(%rbp), %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.parse_block_113
std.mime.types.parse_block_113:
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2392(%rbp)
  movq -2392(%rbp), %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2400(%rbp)
  movq -2400(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.parse_block_115
  jmp std.mime.types.parse_block_124
std.mime.types.parse_block_115:
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2408(%rbp)
  movq -2408(%rbp), %rdi
  call lm_list_len
  mov -2416(%rbp), rax
  movq -2416(%rbp), %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2424(%rbp)
  movq -840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2432(%rbp)
  movq -2432(%rbp), %rax
  subq -2424(%rbp), %rax
  movq %rax, -2440(%rbp)
  movq -2440(%rbp), %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2448(%rbp)
  movq -2448(%rbp), %rdi
  call lm_list_len
  mov -2456(%rbp), rax
  movq -2456(%rbp), %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2464(%rbp)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2472(%rbp)
  movq -864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2480(%rbp)
  movq -2464(%rbp), %rdi
  movq -2472(%rbp), %rsi
  movq -2480(%rbp), %rdx
  call _builtin_substring
  mov -2488(%rbp), rax
  movq -2488(%rbp), %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_240(%rip), %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2496(%rbp)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2504(%rbp)
  movq -2496(%rbp), %rdi
  movq -2504(%rbp), %rsi
  call lm_key_eq
  mov -2512(%rbp), rax
  movq -2512(%rbp), %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  movq -888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2520(%rbp)
  movq -2520(%rbp), %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.parse_block_124
std.mime.types.parse_block_124:
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2528(%rbp)
  movq -2528(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.parse_block_125
  jmp std.mime.types.parse_block_132
std.mime.types.parse_block_125:
  movq $1, %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2536(%rbp)
  movq -2536(%rbp), %rdi
  call lm_list_len
  mov -2544(%rbp), rax
  movq -2544(%rbp), %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2552(%rbp)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2560(%rbp)
  movq -2560(%rbp), %rax
  subq -2552(%rbp), %rax
  movq %rax, -2568(%rbp)
  movq -2568(%rbp), %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2576(%rbp)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2584(%rbp)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2592(%rbp)
  movq -2576(%rbp), %rdi
  movq -2584(%rbp), %rsi
  movq -2592(%rbp), %rdx
  call _builtin_substring
  mov -2600(%rbp), rax
  movq -2600(%rbp), %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2608(%rbp)
  movq -2608(%rbp), %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.parse_block_132
std.mime.types.parse_block_132:
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2616(%rbp)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2624(%rbp)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2632(%rbp)
  movq -2616(%rbp), %rdi
  movq -2624(%rbp), %rsi
  movq -2632(%rbp), %rdx
  call std.mime.types.MIMEParams.add
  mov -2640(%rbp), rax
  movq -2640(%rbp), %rax
  movq -936(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.parse_block_134
std.mime.types.parse_block_134:
  jmp std.mime.types.parse_block_135
std.mime.types.parse_block_135:
  jmp std.mime.types.parse_block_136
std.mime.types.parse_block_136:
  movq $1, %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  movq -952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2648(%rbp)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2656(%rbp)
  movq -2656(%rbp), %rax
  addq -2648(%rbp), %rax
  movq %rax, -2664(%rbp)
  movq -2664(%rbp), %rax
  movq -960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2672(%rbp)
  movq -2672(%rbp), %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.parse_block_70
std.mime.types.parse_block_141:
  movq $1, %rax
  movq -968(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 32 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2680(%rbp)
  addq $32, %rax
  movq %rax, heap_ptr(%rip)
  movq -2680(%rbp), %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2688(%rbp)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2696(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2704(%rbp)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2712(%rbp)
  movq -968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2720(%rbp)
  movq -2688(%rbp), %rdi
  movq -2696(%rbp), %rsi
  movq -2704(%rbp), %rdx
  movq -2712(%rbp), %rcx
  movq -2720(%rbp), %r8
  call std.mime.types.MIMEType.init
  mov -2728(%rbp), rax
  movq -2728(%rbp), %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2736(%rbp)
  movq -2736(%rbp), %rax
  jmp std.mime.types.parse_epilogue
std.mime.types.parse_epilogue:
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
.Lfunc_end_std.mime.types.parse:

.globl std.mime.index.__init__
std.mime.index.__init__:
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
std.mime.index.__init___entry:
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
  jmp std.mime.index.__init___epilogue
std.mime.index.__init___epilogue:
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
.Lfunc_end_std.mime.index.__init__:

.globl std.mime.types.split_str
std.mime.types.split_str:
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
  subq $648, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.mime.types.split_str_entry:
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
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.split_str_block_0
std.mime.types.split_str_block_0:
  movq $0, %rdi
  call lm_list_new
  mov -344(%rbp), rax
  movq -344(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -352(%rbp)
  movq -352(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -360(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_241(%rip), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.split_str_block_6
std.mime.types.split_str_block_6:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rdi
  call lm_list_len
  mov -376(%rbp), rax
  movq -376(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -384(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rax
  cmpq -384(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  movq -128(%rbp), %rdx
  movl %eax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -408(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.split_str_block_9
  jmp std.mime.types.split_str_block_31
std.mime.types.split_str_block_9:
  movq $1, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -416(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  addq -416(%rbp), %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -440(%rbp), %rdi
  movq -448(%rbp), %rsi
  movq -456(%rbp), %rdx
  call _builtin_substring
  mov -464(%rbp), rax
  movq -464(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -472(%rbp), %rdi
  movq -480(%rbp), %rsi
  call lm_key_eq
  mov -488(%rbp), rax
  movq -488(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.split_str_block_15
  jmp std.mime.types.split_str_block_19
std.mime.types.split_str_block_15:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -504(%rbp), %rdi
  movq -512(%rbp), %rsi
  call lm_list_append
  mov -520(%rbp), rax
  leaq str_hdr_242(%rip), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.split_str_block_26
std.mime.types.split_str_block_19:
  movq $1, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  addq -536(%rbp), %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -560(%rbp), %rdi
  movq -568(%rbp), %rsi
  movq -576(%rbp), %rdx
  call _builtin_substring
  mov -584(%rbp), rax
  movq -584(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -592(%rbp), %rdi
  movq -600(%rbp), %rsi
  call lm_str_concat
  mov -608(%rbp), rax
  movq -608(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.split_str_block_26
std.mime.types.split_str_block_26:
  movq $1, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -632(%rbp), %rax
  addq -624(%rbp), %rax
  movq %rax, -640(%rbp)
  movq -640(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.split_str_block_6
std.mime.types.split_str_block_31:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -656(%rbp), %rdi
  movq -664(%rbp), %rsi
  call lm_list_append
  mov -672(%rbp), rax
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rax
  jmp std.mime.types.split_str_epilogue
std.mime.types.split_str_epilogue:
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
.Lfunc_end_std.mime.types.split_str:

.globl std.mime.types.MIMEParams.has
std.mime.types.MIMEParams.has:
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
std.mime.types.MIMEParams.has_entry:
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
  jmp std.mime.types.MIMEParams.has_epilogue
std.mime.types.MIMEParams.has_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.has:

.globl std.mime.types.trim
std.mime.types.trim:
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
  subq $1832, %rsp
  movq %rdi, -48(%rbp)
std.mime.types.trim_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.trim_block_0
std.mime.types.trim_block_0:
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.trim_block_2
std.mime.types.trim_block_2:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rdi
  call lm_list_len
  mov -752(%rbp), rax
  movq -752(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -768(%rbp), %rax
  cmpq -760(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -776(%rbp)
  movq -776(%rbp), %rax
  movq -88(%rbp), %rdx
  movl %eax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -784(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -792(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.trim_block_6
  jmp std.mime.types.trim_block_44
std.mime.types.trim_block_6:
  movq $1, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -808(%rbp), %rax
  addq -800(%rbp), %rax
  movq %rax, -816(%rbp)
  movq -816(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -832(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -824(%rbp), %rdi
  movq -832(%rbp), %rsi
  movq -840(%rbp), %rdx
  call _builtin_substring
  mov -848(%rbp), rax
  movq -848(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_243(%rip), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -856(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -856(%rbp), %rdi
  movq -864(%rbp), %rsi
  call lm_key_eq
  mov -872(%rbp), rax
  movq -872(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -880(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -888(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.trim_block_22
  jmp std.mime.types.trim_block_14
std.mime.types.trim_block_14:
  movq $1, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -904(%rbp), %rax
  addq -896(%rbp), %rax
  movq %rax, -912(%rbp)
  movq -912(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -928(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -920(%rbp), %rdi
  movq -928(%rbp), %rsi
  movq -936(%rbp), %rdx
  call _builtin_substring
  mov -944(%rbp), rax
  movq -944(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_244(%rip), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -960(%rbp)
  movq -952(%rbp), %rdi
  movq -960(%rbp), %rsi
  call lm_key_eq
  mov -968(%rbp), rax
  movq -968(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -976(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.trim_block_22
std.mime.types.trim_block_22:
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -984(%rbp)
  movq -984(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -992(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.trim_block_32
  jmp std.mime.types.trim_block_24
std.mime.types.trim_block_24:
  movq $1, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1008(%rbp)
  movq -1008(%rbp), %rax
  addq -1000(%rbp), %rax
  movq %rax, -1016(%rbp)
  movq -1016(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1032(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -1024(%rbp), %rdi
  movq -1032(%rbp), %rsi
  movq -1040(%rbp), %rdx
  call _builtin_substring
  mov -1048(%rbp), rax
  movq -1048(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_245(%rip), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1056(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1064(%rbp)
  movq -1056(%rbp), %rdi
  movq -1064(%rbp), %rsi
  call lm_key_eq
  mov -1072(%rbp), rax
  movq -1072(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1080(%rbp)
  movq -1080(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.trim_block_32
std.mime.types.trim_block_32:
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1088(%rbp)
  movq -1088(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -1096(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.trim_block_42
  jmp std.mime.types.trim_block_34
std.mime.types.trim_block_34:
  movq $1, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1104(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1112(%rbp)
  movq -1112(%rbp), %rax
  addq -1104(%rbp), %rax
  movq %rax, -1120(%rbp)
  movq -1120(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1128(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1136(%rbp)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1144(%rbp)
  movq -1128(%rbp), %rdi
  movq -1136(%rbp), %rsi
  movq -1144(%rbp), %rdx
  call _builtin_substring
  mov -1152(%rbp), rax
  movq -1152(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_246(%rip), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1160(%rbp)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1168(%rbp)
  movq -1160(%rbp), %rdi
  movq -1168(%rbp), %rsi
  call lm_key_eq
  mov -1176(%rbp), rax
  movq -1176(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1184(%rbp)
  movq -1184(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.trim_block_42
std.mime.types.trim_block_42:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1192(%rbp)
  movq -1192(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.trim_block_44
std.mime.types.trim_block_44:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1200(%rbp)
  movq -1200(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.trim_block_45
  jmp std.mime.types.trim_block_50
std.mime.types.trim_block_45:
  movq $1, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1208(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1216(%rbp)
  movq -1216(%rbp), %rax
  addq -1208(%rbp), %rax
  movq %rax, -1224(%rbp)
  movq -1224(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1232(%rbp)
  movq -1232(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.trim_block_2
std.mime.types.trim_block_50:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1240(%rbp)
  movq -1240(%rbp), %rdi
  call lm_list_len
  mov -1248(%rbp), rax
  movq -1248(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1256(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1264(%rbp)
  movq -1264(%rbp), %rax
  subq -1256(%rbp), %rax
  movq %rax, -1272(%rbp)
  movq -1272(%rbp), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1280(%rbp)
  movq -1280(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.trim_block_55
std.mime.types.trim_block_55:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1296(%rbp)
  movq -1296(%rbp), %rax
  cmpq -1288(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -1304(%rbp)
  movq -1304(%rbp), %rax
  movq -376(%rbp), %rdx
  movl %eax, (%rdx)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1312(%rbp)
  movq -1312(%rbp), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1320(%rbp)
  movq -1320(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.trim_block_58
  jmp std.mime.types.trim_block_96
std.mime.types.trim_block_58:
  movq $1, %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1328(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1336(%rbp)
  movq -1336(%rbp), %rax
  addq -1328(%rbp), %rax
  movq %rax, -1344(%rbp)
  movq -1344(%rbp), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1352(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1360(%rbp)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1368(%rbp)
  movq -1352(%rbp), %rdi
  movq -1360(%rbp), %rsi
  movq -1368(%rbp), %rdx
  call _builtin_substring
  mov -1376(%rbp), rax
  movq -1376(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_247(%rip), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1384(%rbp)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1392(%rbp)
  movq -1384(%rbp), %rdi
  movq -1392(%rbp), %rsi
  call lm_key_eq
  mov -1400(%rbp), rax
  movq -1400(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1408(%rbp)
  movq -1408(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1416(%rbp)
  movq -1416(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.trim_block_74
  jmp std.mime.types.trim_block_66
std.mime.types.trim_block_66:
  movq $1, %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1424(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1432(%rbp)
  movq -1432(%rbp), %rax
  addq -1424(%rbp), %rax
  movq %rax, -1440(%rbp)
  movq -1440(%rbp), %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1448(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1456(%rbp)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1464(%rbp)
  movq -1448(%rbp), %rdi
  movq -1456(%rbp), %rsi
  movq -1464(%rbp), %rdx
  call _builtin_substring
  mov -1472(%rbp), rax
  movq -1472(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_248(%rip), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1480(%rbp)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1488(%rbp)
  movq -1480(%rbp), %rdi
  movq -1488(%rbp), %rsi
  call lm_key_eq
  mov -1496(%rbp), rax
  movq -1496(%rbp), %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1504(%rbp)
  movq -1504(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.trim_block_74
std.mime.types.trim_block_74:
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1512(%rbp)
  movq -1512(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1520(%rbp)
  movq -1520(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.trim_block_84
  jmp std.mime.types.trim_block_76
std.mime.types.trim_block_76:
  movq $1, %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1528(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1536(%rbp)
  movq -1536(%rbp), %rax
  addq -1528(%rbp), %rax
  movq %rax, -1544(%rbp)
  movq -1544(%rbp), %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1552(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1560(%rbp)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1568(%rbp)
  movq -1552(%rbp), %rdi
  movq -1560(%rbp), %rsi
  movq -1568(%rbp), %rdx
  call _builtin_substring
  mov -1576(%rbp), rax
  movq -1576(%rbp), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_249(%rip), %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1584(%rbp)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1592(%rbp)
  movq -1584(%rbp), %rdi
  movq -1592(%rbp), %rsi
  call lm_key_eq
  mov -1600(%rbp), rax
  movq -1600(%rbp), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1608(%rbp)
  movq -1608(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.trim_block_84
std.mime.types.trim_block_84:
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1616(%rbp)
  movq -1616(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1624(%rbp)
  movq -1624(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.trim_block_94
  jmp std.mime.types.trim_block_86
std.mime.types.trim_block_86:
  movq $1, %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1632(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1640(%rbp)
  movq -1640(%rbp), %rax
  addq -1632(%rbp), %rax
  movq %rax, -1648(%rbp)
  movq -1648(%rbp), %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1656(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1664(%rbp)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1672(%rbp)
  movq -1656(%rbp), %rdi
  movq -1664(%rbp), %rsi
  movq -1672(%rbp), %rdx
  call _builtin_substring
  mov -1680(%rbp), rax
  movq -1680(%rbp), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_250(%rip), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1688(%rbp)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1696(%rbp)
  movq -1688(%rbp), %rdi
  movq -1696(%rbp), %rsi
  call lm_key_eq
  mov -1704(%rbp), rax
  movq -1704(%rbp), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1712(%rbp)
  movq -1712(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.trim_block_94
std.mime.types.trim_block_94:
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1720(%rbp)
  movq -1720(%rbp), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.trim_block_96
std.mime.types.trim_block_96:
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1728(%rbp)
  movq -1728(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.trim_block_97
  jmp std.mime.types.trim_block_101
std.mime.types.trim_block_97:
  movq $1, %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1736(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1744(%rbp)
  movq -1744(%rbp), %rax
  subq -1736(%rbp), %rax
  movq %rax, -1752(%rbp)
  movq -1752(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1760(%rbp)
  movq -1760(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.mime.types.trim_block_55
std.mime.types.trim_block_101:
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1768(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1776(%rbp)
  movq -1776(%rbp), %rax
  cmpq -1768(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -1784(%rbp)
  movq -1784(%rbp), %rax
  movq -616(%rbp), %rdx
  movl %eax, (%rdx)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1792(%rbp)
  movq -1792(%rbp), %rax
  testq %rax, %rax
  jne std.mime.types.trim_block_103
  jmp std.mime.types.trim_block_105
std.mime.types.trim_block_103:
  leaq str_hdr_251(%rip), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1800(%rbp)
  movq -1800(%rbp), %rax
  jmp std.mime.types.trim_epilogue
std.mime.types.trim_block_105:
  movq $1, %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1808(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1816(%rbp)
  movq -1816(%rbp), %rax
  addq -1808(%rbp), %rax
  movq %rax, -1824(%rbp)
  movq -1824(%rbp), %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1832(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1840(%rbp)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1848(%rbp)
  movq -1832(%rbp), %rdi
  movq -1840(%rbp), %rsi
  movq -1848(%rbp), %rdx
  call _builtin_substring
  mov -1856(%rbp), rax
  movq -1856(%rbp), %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1864(%rbp)
  movq -1864(%rbp), %rax
  jmp std.mime.types.trim_epilogue
std.mime.types.trim_epilogue:
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
.Lfunc_end_std.mime.types.trim:

.globl std.mime.types.MIMEParams.add
std.mime.types.MIMEParams.add:
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
std.mime.types.MIMEParams.add_entry:
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
  jmp std.mime.types.MIMEParams.add_epilogue
std.mime.types.MIMEParams.add_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.add:

.globl std.mime.types.MIMEType.is_text
std.mime.types.MIMEType.is_text:
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
std.mime.types.MIMEType.is_text_entry:
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
  jmp std.mime.types.MIMEType.is_text_epilogue
std.mime.types.MIMEType.is_text_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.is_text:

.globl std.mime.types.MIMEType.is_video
std.mime.types.MIMEType.is_video:
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
std.mime.types.MIMEType.is_video_entry:
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
  jmp std.mime.types.MIMEType.is_video_epilogue
std.mime.types.MIMEType.is_video_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.is_video:

.globl std.mime.types.MIMEType.is_application
std.mime.types.MIMEType.is_application:
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
std.mime.types.MIMEType.is_application_entry:
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
  jmp std.mime.types.MIMEType.is_application_epilogue
std.mime.types.MIMEType.is_application_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.is_application:

.globl std.mime.types.__init__
std.mime.types.__init__:
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
std.mime.types.__init___entry:
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
  jmp std.mime.types.__init___epilogue
std.mime.types.__init___epilogue:
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
.Lfunc_end_std.mime.types.__init__:

.globl test_classification
test_classification:
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
  subq $1480, %rsp
test_classification_entry:
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
  jmp test_classification_block_0
test_classification_block_0:
  leaq str_hdr_252(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -576(%rbp)
  movq -576(%rbp), %rax
  testq %rax, %rax
  jne test_classification_pr_nil_0_6649
  jmp test_classification_pr_str_0_6649
test_classification_pr_nil_0_6649:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -584(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -584(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -592(%rbp)
  jmp test_classification_pr_next_0_6649
test_classification_pr_str_0_6649:
  movq -568(%rbp), %rax
  addq $8, %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -568(%rbp), %rax
  addq $24, %rax
  movq %rax, -616(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -616(%rbp), %rsi
  movq -608(%rbp), %rdx
  syscall
  movq %rax, -624(%rbp)
  jmp test_classification_pr_next_0_6649
test_classification_pr_next_0_6649:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -632(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -632(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -640(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_253(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rdi
  call std.mime.index.parse
  mov -656(%rbp), rax
  movq -656(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  movq %rax, -672(%rbp)
  movq -672(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_254(%rip), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rdi
  call std.mime.index.parse
  mov -696(%rbp), rax
  movq -696(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -704(%rbp), %rax
  movq %rax, -712(%rbp)
  movq -712(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -720(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_255(%rip), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -728(%rbp), %rdi
  call std.mime.index.parse
  mov -736(%rbp), rax
  movq -736(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -760(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_256(%rip), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -768(%rbp), %rdi
  call std.mime.index.parse
  mov -776(%rbp), rax
  movq -776(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -784(%rbp), %rax
  movq %rax, -792(%rbp)
  movq -792(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -800(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_257(%rip), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -808(%rbp), %rdi
  call std.mime.index.parse
  mov -816(%rbp), rax
  movq -816(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -824(%rbp), %rax
  movq %rax, -832(%rbp)
  movq -832(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -840(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -848(%rbp), %rdi
  call std.mime.types.MIMEType.is_text
  mov -856(%rbp), rax
  movq -856(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -872(%rbp), %rax
  cmpq -864(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -880(%rbp)
  movq -880(%rbp), %rax
  movq -240(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_258(%rip), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -888(%rbp), %rax
  testq %rax, %rax
  jne test_classification_assert_pass_259
  jmp test_classification_assert_fail_259
test_classification_assert_pass_259:
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -904(%rbp), %rdi
  call std.mime.types.MIMEType.is_image
  mov -912(%rbp), rax
  movq -912(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -928(%rbp)
  movq -928(%rbp), %rax
  cmpq -920(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -936(%rbp)
  movq -936(%rbp), %rax
  movq -280(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_260(%rip), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -944(%rbp), %rax
  testq %rax, %rax
  jne test_classification_assert_pass_261
  jmp test_classification_assert_fail_261
test_classification_assert_fail_259:
  movq -896(%rbp), %rax
  addq $8, %rax
  movq %rax, -960(%rbp)
  movq -960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -896(%rbp), %rax
  addq $24, %rax
  movq %rax, -976(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -976(%rbp), %rsi
  movq -968(%rbp), %rdx
  syscall
  movq %rax, -984(%rbp)
  movq $50397203, %rax
  movq %rax, -992(%rbp)
  jmp test_classification_assert_pass_259
test_classification_assert_pass_261:
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -1000(%rbp), %rdi
  call std.mime.types.MIMEType.is_image
  mov -1008(%rbp), rax
  movq -1008(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1016(%rbp)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -1024(%rbp), %rax
  cmpq -1016(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1032(%rbp)
  movq -1032(%rbp), %rax
  movq -320(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_262(%rip), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1048(%rbp)
  movq -1040(%rbp), %rax
  testq %rax, %rax
  jne test_classification_assert_pass_263
  jmp test_classification_assert_fail_263
test_classification_assert_fail_261:
  movq -952(%rbp), %rax
  addq $8, %rax
  movq %rax, -1056(%rbp)
  movq -1056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1064(%rbp)
  movq -952(%rbp), %rax
  addq $24, %rax
  movq %rax, -1072(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1072(%rbp), %rsi
  movq -1064(%rbp), %rdx
  syscall
  movq %rax, -1080(%rbp)
  movq $50397203, %rax
  movq %rax, -1088(%rbp)
  jmp test_classification_assert_pass_261
test_classification_assert_pass_263:
  movq $0, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -1096(%rbp), %rdi
  call std.mime.types.MIMEType.is_audio
  mov -1104(%rbp), rax
  movq -1104(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1112(%rbp)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1120(%rbp)
  movq -1120(%rbp), %rax
  cmpq -1112(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1128(%rbp)
  movq -1128(%rbp), %rax
  movq -360(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_264(%rip), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1136(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1144(%rbp)
  movq -1136(%rbp), %rax
  testq %rax, %rax
  jne test_classification_assert_pass_265
  jmp test_classification_assert_fail_265
test_classification_assert_fail_263:
  movq -1048(%rbp), %rax
  addq $8, %rax
  movq %rax, -1152(%rbp)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1160(%rbp)
  movq -1048(%rbp), %rax
  addq $24, %rax
  movq %rax, -1168(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1168(%rbp), %rsi
  movq -1160(%rbp), %rdx
  syscall
  movq %rax, -1176(%rbp)
  movq $50397203, %rax
  movq %rax, -1184(%rbp)
  jmp test_classification_assert_pass_263
test_classification_assert_pass_265:
  movq $0, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1192(%rbp)
  movq -1192(%rbp), %rdi
  call std.mime.types.MIMEType.is_video
  mov -1200(%rbp), rax
  movq -1200(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1208(%rbp)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1216(%rbp)
  movq -1216(%rbp), %rax
  cmpq -1208(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1224(%rbp)
  movq -1224(%rbp), %rax
  movq -400(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_266(%rip), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1232(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1240(%rbp)
  movq -1232(%rbp), %rax
  testq %rax, %rax
  jne test_classification_assert_pass_267
  jmp test_classification_assert_fail_267
test_classification_assert_fail_265:
  movq -1144(%rbp), %rax
  addq $8, %rax
  movq %rax, -1248(%rbp)
  movq -1248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1256(%rbp)
  movq -1144(%rbp), %rax
  addq $24, %rax
  movq %rax, -1264(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1264(%rbp), %rsi
  movq -1256(%rbp), %rdx
  syscall
  movq %rax, -1272(%rbp)
  movq $50397203, %rax
  movq %rax, -1280(%rbp)
  jmp test_classification_assert_pass_265
test_classification_assert_pass_267:
  movq $0, %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -1288(%rbp), %rdi
  call std.mime.types.MIMEType.is_application
  mov -1296(%rbp), rax
  movq -1296(%rbp), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1304(%rbp)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1312(%rbp)
  movq -1312(%rbp), %rax
  cmpq -1304(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1320(%rbp)
  movq -1320(%rbp), %rax
  movq -440(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_268(%rip), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1328(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1336(%rbp)
  movq -1328(%rbp), %rax
  testq %rax, %rax
  jne test_classification_assert_pass_269
  jmp test_classification_assert_fail_269
test_classification_assert_fail_267:
  movq -1240(%rbp), %rax
  addq $8, %rax
  movq %rax, -1344(%rbp)
  movq -1344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1352(%rbp)
  movq -1240(%rbp), %rax
  addq $24, %rax
  movq %rax, -1360(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1360(%rbp), %rsi
  movq -1352(%rbp), %rdx
  syscall
  movq %rax, -1368(%rbp)
  movq $50397203, %rax
  movq %rax, -1376(%rbp)
  jmp test_classification_assert_pass_267
test_classification_assert_pass_269:
  movq $0, %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_270(%rip), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1384(%rbp)
  movq -1384(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1392(%rbp)
  movq -1392(%rbp), %rax
  testq %rax, %rax
  jne test_classification_pr_nil_0_1421
  jmp test_classification_pr_str_0_1421
test_classification_assert_fail_269:
  movq -1336(%rbp), %rax
  addq $8, %rax
  movq %rax, -1400(%rbp)
  movq -1400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1408(%rbp)
  movq -1336(%rbp), %rax
  addq $24, %rax
  movq %rax, -1416(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1416(%rbp), %rsi
  movq -1408(%rbp), %rdx
  syscall
  movq %rax, -1424(%rbp)
  movq $50397203, %rax
  movq %rax, -1432(%rbp)
  jmp test_classification_assert_pass_269
test_classification_pr_nil_0_1421:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1440(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1440(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1448(%rbp)
  jmp test_classification_pr_next_0_1421
test_classification_pr_str_0_1421:
  movq -1384(%rbp), %rax
  addq $8, %rax
  movq %rax, -1456(%rbp)
  movq -1456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1464(%rbp)
  movq -1384(%rbp), %rax
  addq $24, %rax
  movq %rax, -1472(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1472(%rbp), %rsi
  movq -1464(%rbp), %rdx
  syscall
  movq %rax, -1480(%rbp)
  jmp test_classification_pr_next_0_1421
test_classification_pr_next_0_1421:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1488(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1488(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1496(%rbp)
  movq $0, %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1504(%rbp)
  movq -1504(%rbp), %rax
  jmp test_classification_epilogue
test_classification_epilogue:
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
.Lfunc_end_test_classification:

.globl std.mime.index.MIMEType
std.mime.index.MIMEType:
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
  subq $264, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
  movq %rdx, -64(%rbp)
  movq %rcx, -72(%rbp)
std.mime.index.MIMEType_entry:
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
  jmp std.mime.index.MIMEType_block_0
std.mime.index.MIMEType_block_0:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -216(%rbp)
  movq -216(%rbp), %rax
  movq %rax, -224(%rbp)
  movq -224(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 32 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $32, %rax
  movq %rax, heap_ptr(%rip)
  movq -232(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -240(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -248(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -256(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -264(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -272(%rbp)
  movq -240(%rbp), %rdi
  movq -248(%rbp), %rsi
  movq -256(%rbp), %rdx
  movq -264(%rbp), %rcx
  movq -272(%rbp), %r8
  call std.mime.types.MIMEType.init
  mov -280(%rbp), rax
  movq -280(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rax
  jmp std.mime.index.MIMEType_epilogue
std.mime.index.MIMEType_epilogue:
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
.Lfunc_end_std.mime.index.MIMEType:

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

.globl _builtin_substring
_builtin_substring:
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
  movq %rdx, -64(%rbp)
_builtin_substring_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -64(%rbp), %rax
  subq -56(%rbp), %rax
  movq %rax, -80(%rbp)
  movq -80(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -88(%rbp)
  movq -88(%rbp), %rax
  testq %rax, %rax
  jne _builtin_substring_sub_neg_len
  jmp _builtin_substring_sub_pos_len
_builtin_substring_sub_neg_len:
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp _builtin_substring_sub_alloc
_builtin_substring_sub_pos_len:
  movq -80(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp _builtin_substring_sub_alloc
_builtin_substring_sub_alloc:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -96(%rbp)
  movq -96(%rbp), %rdi
  call lm_str_alloc
  mov -104(%rbp), rax
  movq -48(%rbp), %rax
  addq $24, %rax
  movq %rax, -112(%rbp)
  movq -104(%rbp), %rax
  addq $24, %rax
  movq %rax, -120(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  jmp _builtin_substring_sub_loop
_builtin_substring_sub_loop:
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -136(%rbp)
  movq -136(%rbp), %rax
  cmpq -96(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -144(%rbp)
  movq -144(%rbp), %rax
  testq %rax, %rax
  jne _builtin_substring_sub_body
  jmp _builtin_substring_sub_done
_builtin_substring_sub_body:
  movq -56(%rbp), %rax
  addq -136(%rbp), %rax
  movq %rax, -152(%rbp)
  movq -112(%rbp), %rax
  addq -152(%rbp), %rax
  movq %rax, -160(%rbp)
  movq -160(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -120(%rbp), %rax
  addq -136(%rbp), %rax
  movq %rax, -176(%rbp)
  movq -168(%rbp), %rax
  movq -176(%rbp), %rdx
  movb %al, (%rdx)
  movq -136(%rbp), %rax
  addq $1, %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  jmp _builtin_substring_sub_loop
_builtin_substring_sub_done:
  movq -120(%rbp), %rax
  addq -96(%rbp), %rax
  movq %rax, -192(%rbp)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movb %al, (%rdx)
  movq -104(%rbp), %rax
  addq $8, %rax
  movq %rax, -200(%rbp)
  movq -96(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  jmp _builtin_substring_epilogue
_builtin_substring_epilogue:
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
.Lfunc_end__builtin_substring:

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

.globl substring
substring:
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
  movq %rdx, -64(%rbp)
substring_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -64(%rbp), %rax
  subq -56(%rbp), %rax
  movq %rax, -80(%rbp)
  movq -80(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -88(%rbp)
  movq -88(%rbp), %rax
  testq %rax, %rax
  jne substring_sub_neg_len
  jmp substring_sub_pos_len
substring_sub_neg_len:
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp substring_sub_alloc
substring_sub_pos_len:
  movq -80(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp substring_sub_alloc
substring_sub_alloc:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -96(%rbp)
  movq -96(%rbp), %rdi
  call lm_str_alloc
  mov -104(%rbp), rax
  movq -48(%rbp), %rax
  addq $24, %rax
  movq %rax, -112(%rbp)
  movq -104(%rbp), %rax
  addq $24, %rax
  movq %rax, -120(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  jmp substring_sub_loop
substring_sub_loop:
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -136(%rbp)
  movq -136(%rbp), %rax
  cmpq -96(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -144(%rbp)
  movq -144(%rbp), %rax
  testq %rax, %rax
  jne substring_sub_body
  jmp substring_sub_done
substring_sub_body:
  movq -56(%rbp), %rax
  addq -136(%rbp), %rax
  movq %rax, -152(%rbp)
  movq -112(%rbp), %rax
  addq -152(%rbp), %rax
  movq %rax, -160(%rbp)
  movq -160(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -120(%rbp), %rax
  addq -136(%rbp), %rax
  movq %rax, -176(%rbp)
  movq -168(%rbp), %rax
  movq -176(%rbp), %rdx
  movb %al, (%rdx)
  movq -136(%rbp), %rax
  addq $1, %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  jmp substring_sub_loop
substring_sub_done:
  movq -120(%rbp), %rax
  addq -96(%rbp), %rax
  movq %rax, -192(%rbp)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movb %al, (%rdx)
  movq -104(%rbp), %rax
  addq $8, %rax
  movq %rax, -200(%rbp)
  movq -96(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  jmp substring_epilogue
substring_epilogue:
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
.Lfunc_end_substring:

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
  jne lm_list_to_str_i2s_neg_1
  jmp lm_list_to_str_i2s_pos_1
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
lm_list_to_str_i2s_neg_1:
  movq $1, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  negq %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_i2s_loop_1
lm_list_to_str_i2s_pos_1:
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_i2s_loop_1
lm_list_to_str_i2s_loop_1:
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
  jne lm_list_to_str_i2s_loop_1
  jmp lm_list_to_str_i2s_sign_1
lm_list_to_str_i2s_sign_1:
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
  jne lm_list_to_str_i2s_minus_1
  jmp lm_list_to_str_i2s_done_1
lm_list_to_str_i2s_minus_1:
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
  jmp lm_list_to_str_i2s_done_1
lm_list_to_str_i2s_done_1:
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
  jne lm_enum_to_str_i2s_neg_2
  jmp lm_enum_to_str_i2s_pos_2
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
lm_enum_to_str_i2s_neg_2:
  movq $1, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  negq %rax
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_2
lm_enum_to_str_i2s_pos_2:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_2
lm_enum_to_str_i2s_loop_2:
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
  jne lm_enum_to_str_i2s_loop_2
  jmp lm_enum_to_str_i2s_sign_2
lm_enum_to_str_i2s_sign_2:
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
  jne lm_enum_to_str_i2s_minus_2
  jmp lm_enum_to_str_i2s_done_2
lm_enum_to_str_i2s_minus_2:
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
  jmp lm_enum_to_str_i2s_done_2
lm_enum_to_str_i2s_done_2:
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
  jne lm_enum_to_str_i2s_neg_3
  jmp lm_enum_to_str_i2s_pos_3
lm_enum_to_str_i2s_neg_3:
  movq $1, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  negq %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_3
lm_enum_to_str_i2s_pos_3:
  movq $0, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_3
lm_enum_to_str_i2s_loop_3:
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
  jne lm_enum_to_str_i2s_loop_3
  jmp lm_enum_to_str_i2s_sign_3
lm_enum_to_str_i2s_sign_3:
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
  jne lm_enum_to_str_i2s_minus_3
  jmp lm_enum_to_str_i2s_done_3
lm_enum_to_str_i2s_minus_3:
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
  jmp lm_enum_to_str_i2s_done_3
lm_enum_to_str_i2s_done_3:
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

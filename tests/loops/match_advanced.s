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
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 65
  .byte 100
  .byte 118
  .byte 97
  .byte 110
  .byte 99
  .byte 101
  .byte 100
  .byte 32
  .byte 77
  .byte 97
  .byte 116
  .byte 99
  .byte 104
  .byte 32
  .byte 83
  .byte 116
  .byte 97
  .byte 116
  .byte 101
  .byte 109
  .byte 101
  .byte 110
  .byte 116
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
  .byte 82
  .byte 101
  .byte 99
  .byte 111
  .byte 114
  .byte 100
  .byte 32
  .byte 68
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 40
  .byte 68
  .byte 105
  .byte 99
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 97
  .byte 114
  .byte 105
  .byte 101
  .byte 115
  .byte 41
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 74
  .byte 111
  .byte 104
  .byte 110
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 110
  .byte 97
  .byte 109
  .byte 101
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
  .byte 74
  .byte 111
  .byte 97
  .byte 110
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 99
  .byte 105
  .byte 116
  .byte 121
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
  .byte 78
  .byte 101
  .byte 119
  .byte 32
  .byte 89
  .byte 111
  .byte 114
  .byte 107
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
  .byte 78
  .byte 97
  .byte 109
  .byte 101
  .byte 58
  .byte 32
  .byte 74
  .byte 111
  .byte 104
  .byte 110
  .byte 44
  .byte 32
  .byte 65
  .byte 103
  .byte 101
  .byte 58
  .byte 32
  .byte 51
  .byte 48
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
  .byte 82
  .byte 101
  .byte 99
  .byte 111
  .byte 114
  .byte 100
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 50
  .byte 32
  .byte 102
  .byte 105
  .byte 101
  .byte 108
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
str_hdr_13:
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
  .byte 78
  .byte 97
  .byte 109
  .byte 101
  .byte 58
  .byte 32
  .byte 74
  .byte 111
  .byte 97
  .byte 110
  .byte 44
  .byte 32
  .byte 65
  .byte 103
  .byte 101
  .byte 58
  .byte 32
  .byte 50
  .byte 54
  .byte 44
  .byte 32
  .byte 67
  .byte 105
  .byte 116
  .byte 121
  .byte 58
  .byte 32
  .byte 78
  .byte 101
  .byte 119
  .byte 32
  .byte 89
  .byte 111
  .byte 114
  .byte 107
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
  .byte 82
  .byte 101
  .byte 99
  .byte 111
  .byte 114
  .byte 100
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 51
  .byte 32
  .byte 102
  .byte 105
  .byte 101
  .byte 108
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
str_hdr_16:
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
  .byte 82
  .byte 101
  .byte 115
  .byte 117
  .byte 108
  .byte 116
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 82
  .byte 101
  .byte 115
  .byte 117
  .byte 108
  .byte 116
  .byte 32
  .byte 50
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 76
  .byte 105
  .byte 115
  .byte 116
  .byte 32
  .byte 68
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 69
  .byte 109
  .byte 112
  .byte 116
  .byte 121
  .byte 32
  .byte 108
  .byte 105
  .byte 115
  .byte 116
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
  .byte 109
  .byte 112
  .byte 116
  .byte 121
  .byte 32
  .byte 108
  .byte 105
  .byte 115
  .byte 116
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
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
str_hdr_22:
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
  .byte 79
  .byte 110
  .byte 101
  .byte 32
  .byte 101
  .byte 108
  .byte 101
  .byte 109
  .byte 101
  .byte 110
  .byte 116
  .byte 58
  .byte 32
  .byte 49
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
  .byte 83
  .byte 105
  .byte 110
  .byte 103
  .byte 108
  .byte 101
  .byte 32
  .byte 101
  .byte 108
  .byte 101
  .byte 109
  .byte 101
  .byte 110
  .byte 116
  .byte 32
  .byte 108
  .byte 105
  .byte 115
  .byte 116
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
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
str_hdr_25:
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
  .byte 84
  .byte 119
  .byte 111
  .byte 32
  .byte 101
  .byte 108
  .byte 101
  .byte 109
  .byte 101
  .byte 110
  .byte 116
  .byte 115
  .byte 58
  .byte 32
  .byte 49
  .byte 44
  .byte 32
  .byte 50
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
  .byte 84
  .byte 119
  .byte 111
  .byte 32
  .byte 101
  .byte 108
  .byte 101
  .byte 109
  .byte 101
  .byte 110
  .byte 116
  .byte 32
  .byte 108
  .byte 105
  .byte 115
  .byte 116
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
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
str_hdr_28:
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
  .byte 72
  .byte 101
  .byte 97
  .byte 100
  .byte 58
  .byte 32
  .byte 49
  .byte 44
  .byte 32
  .byte 84
  .byte 97
  .byte 105
  .byte 108
  .byte 58
  .byte 32
  .byte 91
  .byte 50
  .byte 44
  .byte 32
  .byte 51
  .byte 44
  .byte 32
  .byte 52
  .byte 44
  .byte 32
  .byte 53
  .byte 93
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
  .byte 76
  .byte 105
  .byte 115
  .byte 116
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 115
  .byte 112
  .byte 114
  .byte 101
  .byte 97
  .byte 100
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
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
str_hdr_31:
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
  .byte 69
  .byte 109
  .byte 112
  .byte 116
  .byte 121
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
  .byte 79
  .byte 110
  .byte 101
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 84
  .byte 119
  .byte 111
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 77
  .byte 97
  .byte 110
  .byte 121
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 84
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 32
  .byte 68
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 58
  .byte 32
  .byte 40
  .byte 49
  .byte 48
  .byte 44
  .byte 32
  .byte 50
  .byte 48
  .byte 41
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
  .byte 50
  .byte 45
  .byte 116
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
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
str_hdr_39:
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
  .byte 51
  .byte 45
  .byte 116
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 58
  .byte 32
  .byte 40
  .byte 49
  .byte 44
  .byte 32
  .byte 50
  .byte 44
  .byte 32
  .byte 51
  .byte 41
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
  .byte 51
  .byte 45
  .byte 116
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
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
str_hdr_42:
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
  .byte 50
  .byte 45
  .byte 116
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 51
  .byte 45
  .byte 116
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 52
  .byte 58
  .byte 32
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 68
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 65
  .byte 108
  .byte 105
  .byte 99
  .byte 101
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
  .byte 115
  .byte 99
  .byte 111
  .byte 114
  .byte 101
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 58
  .byte 32
  .byte 120
  .byte 61
  .byte 49
  .byte 48
  .byte 48
  .byte 44
  .byte 32
  .byte 97
  .byte 61
  .byte 49
  .byte 48
  .byte 44
  .byte 32
  .byte 98
  .byte 61
  .byte 50
  .byte 48
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
  .byte 84
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 43
  .byte 76
  .byte 105
  .byte 115
  .byte 116
  .byte 32
  .byte 110
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
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
str_hdr_51:
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
  .byte 82
  .byte 101
  .byte 99
  .byte 111
  .byte 114
  .byte 100
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 108
  .byte 105
  .byte 115
  .byte 116
  .byte 58
  .byte 32
  .byte 65
  .byte 108
  .byte 105
  .byte 99
  .byte 101
  .byte 44
  .byte 32
  .byte 115
  .byte 99
  .byte 111
  .byte 114
  .byte 101
  .byte 115
  .byte 58
  .byte 32
  .byte 57
  .byte 53
  .byte 44
  .byte 32
  .byte 56
  .byte 55
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
  .byte 82
  .byte 101
  .byte 99
  .byte 111
  .byte 114
  .byte 100
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 108
  .byte 105
  .byte 115
  .byte 116
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
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
str_hdr_54:
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 50
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 77
  .byte 105
  .byte 120
  .byte 101
  .byte 100
  .byte 32
  .byte 80
  .byte 97
  .byte 116
  .byte 116
  .byte 101
  .byte 114
  .byte 110
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
vname_Circle:
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
  .byte 67
  .byte 105
  .byte 114
  .byte 99
  .byte 108
  .byte 101
  .byte 0
.align 8
vname_Rectangle:
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
  .byte 82
  .byte 101
  .byte 99
  .byte 116
  .byte 97
  .byte 110
  .byte 103
  .byte 108
  .byte 101
  .byte 0
.align 8
vname_Point:
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
  .byte 80
  .byte 111
  .byte 105
  .byte 110
  .byte 116
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
  .byte 67
  .byte 105
  .byte 114
  .byte 99
  .byte 108
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 114
  .byte 97
  .byte 100
  .byte 105
  .byte 117
  .byte 115
  .byte 32
  .byte 53
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
  .byte 67
  .byte 105
  .byte 114
  .byte 99
  .byte 108
  .byte 101
  .byte 32
  .byte 115
  .byte 104
  .byte 97
  .byte 112
  .byte 101
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 99
  .byte 114
  .byte 105
  .byte 112
  .byte 116
  .byte 105
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
str_hdr_60:
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
  .byte 82
  .byte 101
  .byte 99
  .byte 116
  .byte 97
  .byte 110
  .byte 103
  .byte 108
  .byte 101
  .byte 32
  .byte 49
  .byte 48
  .byte 120
  .byte 50
  .byte 48
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
  .byte 101
  .byte 99
  .byte 116
  .byte 97
  .byte 110
  .byte 103
  .byte 108
  .byte 101
  .byte 32
  .byte 115
  .byte 104
  .byte 97
  .byte 112
  .byte 101
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 99
  .byte 114
  .byte 105
  .byte 112
  .byte 116
  .byte 105
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
str_hdr_63:
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
  .byte 80
  .byte 111
  .byte 105
  .byte 110
  .byte 116
  .byte 32
  .byte 97
  .byte 116
  .byte 32
  .byte 40
  .byte 51
  .byte 44
  .byte 32
  .byte 52
  .byte 41
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
  .byte 80
  .byte 111
  .byte 105
  .byte 110
  .byte 116
  .byte 32
  .byte 115
  .byte 104
  .byte 97
  .byte 112
  .byte 101
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 99
  .byte 114
  .byte 105
  .byte 112
  .byte 116
  .byte 105
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
str_hdr_66:
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
  .byte 67
  .byte 105
  .byte 114
  .byte 99
  .byte 108
  .byte 101
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 82
  .byte 101
  .byte 99
  .byte 116
  .byte 97
  .byte 110
  .byte 103
  .byte 108
  .byte 101
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 80
  .byte 111
  .byte 105
  .byte 110
  .byte 116
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 42
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 42
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
  .byte 68
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 71
  .byte 117
  .byte 97
  .byte 114
  .byte 100
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 65
  .byte 108
  .byte 105
  .byte 99
  .byte 101
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 66
  .byte 111
  .byte 98
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 65
  .byte 108
  .byte 105
  .byte 99
  .byte 101
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 97
  .byte 110
  .byte 32
  .byte 97
  .byte 100
  .byte 117
  .byte 108
  .byte 116
  .byte 32
  .byte 40
  .byte 50
  .byte 53
  .byte 41
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
  .byte 65
  .byte 100
  .byte 117
  .byte 108
  .byte 116
  .byte 32
  .byte 103
  .byte 117
  .byte 97
  .byte 114
  .byte 100
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
str_hdr_79:
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
  .byte 66
  .byte 111
  .byte 98
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 97
  .byte 32
  .byte 109
  .byte 105
  .byte 110
  .byte 111
  .byte 114
  .byte 32
  .byte 40
  .byte 49
  .byte 54
  .byte 41
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
  .byte 77
  .byte 105
  .byte 110
  .byte 111
  .byte 114
  .byte 32
  .byte 103
  .byte 117
  .byte 97
  .byte 114
  .byte 100
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
str_hdr_82:
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
  .byte 65
  .byte 100
  .byte 117
  .byte 108
  .byte 116
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 77
  .byte 105
  .byte 110
  .byte 111
  .byte 114
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 47
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 47
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
  .byte 55
  .byte 58
  .byte 32
  .byte 76
  .byte 105
  .byte 115
  .byte 116
  .byte 32
  .byte 68
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 83
  .byte 112
  .byte 114
  .byte 101
  .byte 97
  .byte 100
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 70
  .byte 105
  .byte 114
  .byte 115
  .byte 116
  .byte 58
  .byte 32
  .byte 49
  .byte 44
  .byte 32
  .byte 82
  .byte 101
  .byte 115
  .byte 116
  .byte 58
  .byte 32
  .byte 91
  .byte 50
  .byte 44
  .byte 32
  .byte 51
  .byte 44
  .byte 32
  .byte 52
  .byte 44
  .byte 32
  .byte 53
  .byte 93
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
  .byte 50
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 50
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 83
  .byte 112
  .byte 114
  .byte 101
  .byte 97
  .byte 100
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 109
  .byte 117
  .byte 108
  .byte 116
  .byte 105
  .byte 112
  .byte 108
  .byte 101
  .byte 32
  .byte 101
  .byte 108
  .byte 101
  .byte 109
  .byte 101
  .byte 110
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
str_hdr_88:
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
  .byte 70
  .byte 105
  .byte 114
  .byte 115
  .byte 116
  .byte 58
  .byte 32
  .byte 49
  .byte 48
  .byte 48
  .byte 44
  .byte 32
  .byte 82
  .byte 101
  .byte 115
  .byte 116
  .byte 58
  .byte 32
  .byte 91
  .byte 93
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
  .byte 47
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 47
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 83
  .byte 112
  .byte 114
  .byte 101
  .byte 97
  .byte 100
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 115
  .byte 105
  .byte 110
  .byte 103
  .byte 108
  .byte 101
  .byte 32
  .byte 101
  .byte 108
  .byte 101
  .byte 109
  .byte 101
  .byte 110
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
str_hdr_91:
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
  .byte 83
  .byte 112
  .byte 114
  .byte 101
  .byte 97
  .byte 100
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 83
  .byte 112
  .byte 114
  .byte 101
  .byte 97
  .byte 100
  .byte 32
  .byte 50
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 56
  .byte 58
  .byte 32
  .byte 84
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 76
  .byte 105
  .byte 115
  .byte 116
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 43
  .byte 76
  .byte 105
  .byte 115
  .byte 116
  .byte 58
  .byte 32
  .byte 120
  .byte 61
  .byte 57
  .byte 57
  .byte 44
  .byte 32
  .byte 91
  .byte 97
  .byte 44
  .byte 98
  .byte 44
  .byte 99
  .byte 93
  .byte 61
  .byte 91
  .byte 49
  .byte 44
  .byte 50
  .byte 44
  .byte 51
  .byte 93
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 116
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 43
  .byte 108
  .byte 105
  .byte 115
  .byte 116
  .byte 32
  .byte 100
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
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
str_hdr_97:
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 57
  .byte 58
  .byte 32
  .byte 82
  .byte 101
  .byte 99
  .byte 111
  .byte 114
  .byte 100
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 79
  .byte 112
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 97
  .byte 108
  .byte 32
  .byte 70
  .byte 105
  .byte 101
  .byte 108
  .byte 100
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 74
  .byte 111
  .byte 104
  .byte 110
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 99
  .byte 105
  .byte 116
  .byte 121
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
  .byte 78
  .byte 89
  .byte 67
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 74
  .byte 97
  .byte 110
  .byte 101
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 74
  .byte 111
  .byte 104
  .byte 110
  .byte 44
  .byte 32
  .byte 51
  .byte 48
  .byte 44
  .byte 32
  .byte 78
  .byte 89
  .byte 67
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
  .byte 82
  .byte 101
  .byte 99
  .byte 111
  .byte 114
  .byte 100
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 99
  .byte 105
  .byte 116
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
str_hdr_110:
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
  .byte 74
  .byte 97
  .byte 110
  .byte 101
  .byte 44
  .byte 32
  .byte 50
  .byte 53
  .byte 32
  .byte 40
  .byte 110
  .byte 111
  .byte 32
  .byte 99
  .byte 105
  .byte 116
  .byte 121
  .byte 41
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
  .byte 82
  .byte 101
  .byte 99
  .byte 111
  .byte 114
  .byte 100
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 111
  .byte 117
  .byte 116
  .byte 32
  .byte 99
  .byte 105
  .byte 116
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
str_hdr_113:
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
  .byte 87
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 99
  .byte 105
  .byte 116
  .byte 121
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 87
  .byte 105
  .byte 116
  .byte 104
  .byte 111
  .byte 117
  .byte 116
  .byte 32
  .byte 99
  .byte 105
  .byte 116
  .byte 121
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 0
.align 8
str_hdr_115:
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
  .byte 49
  .byte 48
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 80
  .byte 97
  .byte 116
  .byte 116
  .byte 101
  .byte 114
  .byte 110
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 110
  .byte 97
  .byte 109
  .byte 101
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
  .byte 115
  .byte 116
  .byte 0
.align 8
str_hdr_118:
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
  .byte 118
  .byte 97
  .byte 108
  .byte 117
  .byte 101
  .byte 115
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
  .byte 67
  .byte 111
  .byte 109
  .byte 112
  .byte 108
  .byte 101
  .byte 120
  .byte 58
  .byte 32
  .byte 120
  .byte 61
  .byte 52
  .byte 50
  .byte 44
  .byte 32
  .byte 110
  .byte 97
  .byte 109
  .byte 101
  .byte 61
  .byte 116
  .byte 101
  .byte 115
  .byte 116
  .byte 44
  .byte 32
  .byte 118
  .byte 97
  .byte 108
  .byte 117
  .byte 101
  .byte 115
  .byte 61
  .byte 91
  .byte 49
  .byte 48
  .byte 44
  .byte 50
  .byte 48
  .byte 93
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
  .byte 67
  .byte 111
  .byte 109
  .byte 112
  .byte 108
  .byte 101
  .byte 120
  .byte 32
  .byte 110
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 112
  .byte 97
  .byte 116
  .byte 116
  .byte 101
  .byte 114
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
str_hdr_122:
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
  .byte 67
  .byte 111
  .byte 109
  .byte 112
  .byte 108
  .byte 101
  .byte 120
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 45
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 45
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
  .byte 49
  .byte 58
  .byte 32
  .byte 69
  .byte 110
  .byte 117
  .byte 109
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 77
  .byte 117
  .byte 108
  .byte 116
  .byte 105
  .byte 112
  .byte 108
  .byte 101
  .byte 32
  .byte 80
  .byte 97
  .byte 121
  .byte 108
  .byte 111
  .byte 97
  .byte 100
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
  .byte 0
.align 8
vname_Move:
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
  .byte 77
  .byte 111
  .byte 118
  .byte 101
  .byte 0
.align 8
vname_Resize:
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
  .byte 82
  .byte 101
  .byte 115
  .byte 105
  .byte 122
  .byte 101
  .byte 0
.align 8
vname_Color:
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
  .byte 67
  .byte 111
  .byte 108
  .byte 111
  .byte 114
  .byte 0
.align 8
str_hdr_124:
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
  .byte 77
  .byte 111
  .byte 118
  .byte 101
  .byte 32
  .byte 116
  .byte 111
  .byte 32
  .byte 40
  .byte 49
  .byte 48
  .byte 44
  .byte 32
  .byte 50
  .byte 48
  .byte 41
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
  .byte 77
  .byte 111
  .byte 118
  .byte 101
  .byte 32
  .byte 99
  .byte 111
  .byte 109
  .byte 109
  .byte 97
  .byte 110
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
str_hdr_127:
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
  .byte 82
  .byte 101
  .byte 115
  .byte 105
  .byte 122
  .byte 101
  .byte 32
  .byte 116
  .byte 111
  .byte 32
  .byte 49
  .byte 48
  .byte 48
  .byte 120
  .byte 50
  .byte 48
  .byte 48
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
  .byte 82
  .byte 101
  .byte 115
  .byte 105
  .byte 122
  .byte 101
  .byte 32
  .byte 99
  .byte 111
  .byte 109
  .byte 109
  .byte 97
  .byte 110
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
str_hdr_130:
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
  .byte 67
  .byte 111
  .byte 108
  .byte 111
  .byte 114
  .byte 32
  .byte 82
  .byte 71
  .byte 66
  .byte 40
  .byte 50
  .byte 53
  .byte 53
  .byte 44
  .byte 32
  .byte 49
  .byte 50
  .byte 56
  .byte 44
  .byte 32
  .byte 54
  .byte 52
  .byte 41
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
  .byte 67
  .byte 111
  .byte 108
  .byte 111
  .byte 114
  .byte 32
  .byte 99
  .byte 111
  .byte 109
  .byte 109
  .byte 97
  .byte 110
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
str_hdr_133:
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
  .byte 77
  .byte 111
  .byte 118
  .byte 101
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 0
.align 8
str_hdr_134:
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
  .byte 82
  .byte 101
  .byte 115
  .byte 105
  .byte 122
  .byte 101
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 67
  .byte 111
  .byte 108
  .byte 111
  .byte 114
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 47
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 47
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
  .byte 50
  .byte 58
  .byte 32
  .byte 68
  .byte 101
  .byte 115
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 105
  .byte 110
  .byte 32
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 77
  .byte 97
  .byte 116
  .byte 99
  .byte 104
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 58
  .byte 32
  .byte 120
  .byte 61
  .byte 49
  .byte 48
  .byte 48
  .byte 44
  .byte 32
  .byte 97
  .byte 61
  .byte 49
  .byte 44
  .byte 32
  .byte 98
  .byte 61
  .byte 50
  .byte 48
  .byte 0
.align 8
str_hdr_138:
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 109
  .byte 97
  .byte 116
  .byte 99
  .byte 104
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 97
  .byte 61
  .byte 49
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 58
  .byte 32
  .byte 120
  .byte 61
  .byte 50
  .byte 48
  .byte 48
  .byte 44
  .byte 32
  .byte 97
  .byte 61
  .byte 50
  .byte 44
  .byte 32
  .byte 98
  .byte 61
  .byte 51
  .byte 48
  .byte 0
.align 8
str_hdr_141:
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 109
  .byte 97
  .byte 116
  .byte 99
  .byte 104
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 97
  .byte 61
  .byte 50
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 58
  .byte 32
  .byte 120
  .byte 61
  .byte 51
  .byte 48
  .byte 48
  .byte 44
  .byte 32
  .byte 97
  .byte 61
  .byte 53
  .byte 44
  .byte 32
  .byte 98
  .byte 61
  .byte 52
  .byte 48
  .byte 0
.align 8
str_hdr_144:
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 109
  .byte 97
  .byte 116
  .byte 99
  .byte 104
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 97
  .byte 61
  .byte 53
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 0
.align 8
str_hdr_147:
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 50
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 51
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 48
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 48
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 10
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 65
  .byte 100
  .byte 118
  .byte 97
  .byte 110
  .byte 99
  .byte 101
  .byte 100
  .byte 32
  .byte 77
  .byte 97
  .byte 116
  .byte 99
  .byte 104
  .byte 32
  .byte 83
  .byte 116
  .byte 97
  .byte 116
  .byte 101
  .byte 109
  .byte 101
  .byte 110
  .byte 116
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
  .byte 67
  .byte 111
  .byte 108
  .byte 111
  .byte 114
  .byte 32
  .byte 82
  .byte 71
  .byte 66
  .byte 40
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 37
  .byte 115
  .byte 41
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
  .byte 82
  .byte 101
  .byte 115
  .byte 105
  .byte 122
  .byte 101
  .byte 32
  .byte 116
  .byte 111
  .byte 32
  .byte 37
  .byte 115
  .byte 120
  .byte 37
  .byte 115
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
  .byte 77
  .byte 111
  .byte 118
  .byte 101
  .byte 32
  .byte 116
  .byte 111
  .byte 32
  .byte 40
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 37
  .byte 115
  .byte 41
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 118
  .byte 97
  .byte 108
  .byte 117
  .byte 101
  .byte 115
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 118
  .byte 97
  .byte 108
  .byte 117
  .byte 101
  .byte 115
  .byte 0
.align 8
str_hdr_157:
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
  .byte 67
  .byte 111
  .byte 109
  .byte 112
  .byte 108
  .byte 101
  .byte 120
  .byte 58
  .byte 32
  .byte 120
  .byte 61
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 110
  .byte 97
  .byte 109
  .byte 101
  .byte 61
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 118
  .byte 97
  .byte 108
  .byte 117
  .byte 101
  .byte 115
  .byte 61
  .byte 91
  .byte 37
  .byte 115
  .byte 44
  .byte 37
  .byte 115
  .byte 93
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 99
  .byte 105
  .byte 116
  .byte 121
  .byte 0
.align 8
str_hdr_161:
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 97
  .byte 109
  .byte 101
  .byte 0
.align 8
str_hdr_164:
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 37
  .byte 115
  .byte 32
  .byte 40
  .byte 110
  .byte 111
  .byte 32
  .byte 99
  .byte 105
  .byte 116
  .byte 121
  .byte 41
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
  .byte 97
  .byte 109
  .byte 101
  .byte 0
.align 8
str_hdr_167:
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 99
  .byte 105
  .byte 116
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
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 37
  .byte 115
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
  .byte 80
  .byte 111
  .byte 105
  .byte 110
  .byte 116
  .byte 32
  .byte 97
  .byte 116
  .byte 32
  .byte 40
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 37
  .byte 115
  .byte 41
  .byte 0
.align 8
str_hdr_171:
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
  .byte 82
  .byte 101
  .byte 99
  .byte 116
  .byte 97
  .byte 110
  .byte 103
  .byte 108
  .byte 101
  .byte 32
  .byte 37
  .byte 115
  .byte 120
  .byte 37
  .byte 115
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
  .byte 67
  .byte 105
  .byte 114
  .byte 99
  .byte 108
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 114
  .byte 97
  .byte 100
  .byte 105
  .byte 117
  .byte 115
  .byte 32
  .byte 37
  .byte 115
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
  .byte 72
  .byte 101
  .byte 97
  .byte 100
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 84
  .byte 97
  .byte 105
  .byte 108
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 119
  .byte 111
  .byte 32
  .byte 101
  .byte 108
  .byte 101
  .byte 109
  .byte 101
  .byte 110
  .byte 116
  .byte 115
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 37
  .byte 115
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
  .byte 79
  .byte 110
  .byte 101
  .byte 32
  .byte 101
  .byte 108
  .byte 101
  .byte 109
  .byte 101
  .byte 110
  .byte 116
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 69
  .byte 109
  .byte 112
  .byte 116
  .byte 121
  .byte 32
  .byte 108
  .byte 105
  .byte 115
  .byte 116
  .byte 0
.align 8
str_hdr_177:
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 97
  .byte 103
  .byte 101
  .byte 0
.align 8
str_hdr_181:
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
  .byte 99
  .byte 105
  .byte 116
  .byte 121
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
  .byte 110
  .byte 97
  .byte 109
  .byte 101
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 99
  .byte 105
  .byte 116
  .byte 121
  .byte 0
.align 8
str_hdr_185:
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
  .byte 78
  .byte 97
  .byte 109
  .byte 101
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 65
  .byte 103
  .byte 101
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 67
  .byte 105
  .byte 116
  .byte 121
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 78
  .byte 97
  .byte 109
  .byte 101
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 65
  .byte 103
  .byte 101
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 0
.align 8
str_hdr_189:
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
  .byte 69
  .byte 109
  .byte 112
  .byte 116
  .byte 121
  .byte 32
  .byte 108
  .byte 105
  .byte 115
  .byte 116
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
  .byte 70
  .byte 105
  .byte 114
  .byte 115
  .byte 116
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 82
  .byte 101
  .byte 115
  .byte 116
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 115
  .byte 99
  .byte 111
  .byte 114
  .byte 101
  .byte 115
  .byte 0
.align 8
str_hdr_193:
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 115
  .byte 99
  .byte 111
  .byte 114
  .byte 101
  .byte 115
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
  .byte 101
  .byte 99
  .byte 111
  .byte 114
  .byte 100
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 108
  .byte 105
  .byte 115
  .byte 116
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 115
  .byte 99
  .byte 111
  .byte 114
  .byte 101
  .byte 115
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 37
  .byte 115
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 58
  .byte 32
  .byte 120
  .byte 61
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 97
  .byte 61
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 98
  .byte 61
  .byte 37
  .byte 115
  .byte 0
.align 8
str_hdr_197:
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
  .byte 84
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 43
  .byte 76
  .byte 105
  .byte 115
  .byte 116
  .byte 58
  .byte 32
  .byte 120
  .byte 61
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 91
  .byte 97
  .byte 44
  .byte 98
  .byte 44
  .byte 99
  .byte 93
  .byte 61
  .byte 91
  .byte 37
  .byte 115
  .byte 44
  .byte 37
  .byte 115
  .byte 44
  .byte 37
  .byte 115
  .byte 93
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 58
  .byte 32
  .byte 120
  .byte 61
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 97
  .byte 61
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 98
  .byte 61
  .byte 37
  .byte 115
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 58
  .byte 32
  .byte 120
  .byte 61
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 97
  .byte 61
  .byte 50
  .byte 44
  .byte 32
  .byte 98
  .byte 61
  .byte 37
  .byte 115
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 58
  .byte 32
  .byte 120
  .byte 61
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 97
  .byte 61
  .byte 49
  .byte 44
  .byte 32
  .byte 98
  .byte 61
  .byte 37
  .byte 115
  .byte 0
.align 8
str_hdr_201:
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 110
  .byte 97
  .byte 109
  .byte 101
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
  .byte 97
  .byte 103
  .byte 101
  .byte 0
.align 8
str_hdr_205:
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
  .byte 37
  .byte 115
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 97
  .byte 110
  .byte 32
  .byte 97
  .byte 100
  .byte 117
  .byte 108
  .byte 116
  .byte 32
  .byte 40
  .byte 37
  .byte 115
  .byte 41
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
  .byte 97
  .byte 109
  .byte 101
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 97
  .byte 109
  .byte 101
  .byte 0
.align 8
str_hdr_209:
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
  .byte 97
  .byte 103
  .byte 101
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
  .byte 37
  .byte 115
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 97
  .byte 32
  .byte 109
  .byte 105
  .byte 110
  .byte 111
  .byte 114
  .byte 32
  .byte 40
  .byte 37
  .byte 115
  .byte 41
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
  .byte 51
  .byte 45
  .byte 116
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 58
  .byte 32
  .byte 40
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 37
  .byte 115
  .byte 41
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
  .byte 117
  .byte 112
  .byte 108
  .byte 101
  .byte 58
  .byte 32
  .byte 40
  .byte 37
  .byte 115
  .byte 44
  .byte 32
  .byte 37
  .byte 115
  .byte 41
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
  subq $13016, %rsp
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
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1272(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1280(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1280(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1288(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1288(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1296(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1304(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1304(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1312(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1312(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1320(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1320(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1328(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1328(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1336(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1336(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1344(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1344(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1352(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1352(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1360(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1360(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1368(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1368(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1376(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1376(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1384(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1384(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1392(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1392(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1400(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1400(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1408(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1408(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1416(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1416(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1424(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1424(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1432(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1432(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1440(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1440(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1448(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1448(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1456(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1456(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1464(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1464(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1472(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1472(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1480(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1480(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1488(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1488(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1496(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1496(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1504(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1504(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1512(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1512(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1520(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1520(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1528(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1528(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1536(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1536(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1544(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1544(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1552(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1552(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1560(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1560(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1568(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1568(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1576(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1576(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1584(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1584(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1592(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1592(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1600(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1600(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1608(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1608(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1616(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1616(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1624(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1624(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1632(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1632(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1640(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1640(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1648(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1648(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1656(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1656(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1664(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1664(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1672(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1672(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1680(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1680(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1688(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1688(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1696(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1696(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1704(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1704(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1712(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1712(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1720(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1720(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1728(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1728(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1736(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1736(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1744(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1744(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1752(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1752(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1760(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1760(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1768(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1768(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1776(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1776(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1784(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1784(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1792(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1792(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1800(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1800(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1808(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1808(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1816(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1816(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1824(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1824(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1832(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1832(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1840(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1840(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1848(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1848(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1856(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1856(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1864(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1864(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1872(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1872(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1880(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1880(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1888(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1888(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1896(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1896(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1904(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1904(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1912(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1912(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1920(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1920(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1928(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1928(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1936(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1936(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1944(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1944(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1952(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1952(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1960(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1960(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1968(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1968(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1976(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1976(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1984(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1984(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1992(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1992(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2000(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2000(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2008(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2008(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2016(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2016(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2024(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2024(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2032(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2032(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2040(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2040(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2048(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2048(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2056(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2056(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2064(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2064(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2072(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2072(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2080(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2080(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2088(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2088(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2096(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2096(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2272(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2280(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2280(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2288(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2288(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2296(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2304(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2304(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2312(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2312(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2320(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2320(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2328(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2328(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2336(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2336(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2344(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2344(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2352(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2352(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2360(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2360(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2368(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2368(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2376(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2376(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2384(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2384(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2392(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2392(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2400(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2400(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2408(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2408(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2416(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2416(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2424(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2424(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2432(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2432(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2440(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2440(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2448(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2448(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2456(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2456(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2464(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2464(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2472(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2472(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2480(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2480(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2488(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2488(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2496(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2496(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2504(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2504(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2512(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2512(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2520(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2520(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2528(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2528(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2536(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2536(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2544(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2544(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2552(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2552(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2560(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2560(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2568(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2568(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2576(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2576(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2584(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2584(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2592(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2592(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2600(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2600(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2608(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2608(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2616(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2616(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2624(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2624(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2632(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2632(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2640(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2640(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2648(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2648(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2656(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2656(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2664(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2664(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2672(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2672(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2680(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2680(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2688(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2688(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2696(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2696(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2704(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2704(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2712(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2712(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2720(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2720(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2728(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2728(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2736(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2736(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2744(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2744(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2752(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2752(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2760(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2760(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2768(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2768(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2776(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2776(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2784(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2784(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2792(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2792(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2800(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2800(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2808(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2808(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2816(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2816(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2824(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2824(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2832(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2832(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2840(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2840(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2848(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2848(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2856(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2856(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2864(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2864(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2872(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2872(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2880(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2880(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2888(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2888(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2896(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2896(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2904(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2904(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2912(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2912(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2920(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2920(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2928(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2928(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2936(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2936(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2944(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2944(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2952(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2952(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2960(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2960(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2968(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2968(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2976(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2976(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2984(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2984(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2992(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2992(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3000(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3000(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3008(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3008(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3016(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3016(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3024(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3024(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3032(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3032(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3040(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3040(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3048(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3048(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3056(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3056(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3064(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3064(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3072(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3072(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3080(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3080(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3088(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3088(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3096(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3096(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3272(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3280(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3280(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3288(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3288(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3296(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3304(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3304(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3312(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3312(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3320(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3320(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3328(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3328(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3336(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3336(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3344(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3344(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3352(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3352(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3360(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3360(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3368(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3368(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3376(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3376(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3384(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3384(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3392(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3392(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3400(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3400(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3408(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3408(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3416(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3416(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3424(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3424(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3432(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3432(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3440(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3440(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3448(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3448(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3456(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3456(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3464(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3464(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3472(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3472(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3480(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3480(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3488(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3488(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3496(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3496(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3504(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3504(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3512(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3512(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3520(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3520(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3528(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3528(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3536(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3536(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3544(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3544(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3552(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3552(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3560(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3560(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3568(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3568(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3576(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3576(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3584(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3584(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3592(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3592(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3600(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3600(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3608(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3608(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3616(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3616(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3624(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3624(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3632(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3632(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3640(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3640(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3648(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3648(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3656(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3656(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3664(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3664(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3672(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3672(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3680(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3680(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3688(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3688(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3696(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3696(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3704(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3704(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3712(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3712(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3720(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3720(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3728(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3728(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3736(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3736(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3744(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3744(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3752(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3752(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3760(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3760(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3768(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3768(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_0
main_block_0:
  leaq str_hdr_0(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3776(%rbp)
  movq -3776(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3784(%rbp)
  movq -3784(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9383
  jmp main_pr_str_0_9383
main_pr_nil_0_9383:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3792(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3792(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3800(%rbp)
  jmp main_pr_next_0_9383
main_pr_str_0_9383:
  movq -3776(%rbp), %rax
  addq $8, %rax
  movq %rax, -3808(%rbp)
  movq -3808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3816(%rbp)
  movq -3776(%rbp), %rax
  addq $24, %rax
  movq %rax, -3824(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3824(%rbp), %rsi
  movq -3816(%rbp), %rdx
  syscall
  movq %rax, -3832(%rbp)
  jmp main_pr_next_0_9383
main_pr_next_0_9383:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3840(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3840(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3848(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_1(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3856(%rbp)
  movq -3856(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3864(%rbp)
  movq -3864(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_886
  jmp main_pr_str_0_886
main_pr_nil_0_886:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3872(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3872(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3880(%rbp)
  jmp main_pr_next_0_886
main_pr_str_0_886:
  movq -3856(%rbp), %rax
  addq $8, %rax
  movq %rax, -3888(%rbp)
  movq -3888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3896(%rbp)
  movq -3856(%rbp), %rax
  addq $24, %rax
  movq %rax, -3904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3904(%rbp), %rsi
  movq -3896(%rbp), %rdx
  syscall
  movq %rax, -3912(%rbp)
  jmp main_pr_next_0_886
main_pr_next_0_886:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3920(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3920(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3928(%rbp)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  call lm_dict_new
  mov -3936(%rbp), rax
  movq -3936(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_2(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_3(%rip), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3944(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3952(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3960(%rbp)
  movq -3944(%rbp), %rdi
  movq -3952(%rbp), %rsi
  movq -3960(%rbp), %rdx
  call lm_dict_set
  mov -3968(%rbp), rax
  leaq str_hdr_4(%rip), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq $30, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3976(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3984(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3992(%rbp)
  movq -3976(%rbp), %rdi
  movq -3984(%rbp), %rsi
  movq -3992(%rbp), %rdx
  call lm_dict_set
  mov -4000(%rbp), rax
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4008(%rbp)
  movq -4008(%rbp), %rdi
  call testRecordDestructuring
  mov -4016(%rbp), rax
  movq -4016(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4024(%rbp)
  movq -4024(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  call lm_dict_new
  mov -4032(%rbp), rax
  movq -4032(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_5(%rip), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_6(%rip), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4040(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4048(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4056(%rbp)
  movq -4040(%rbp), %rdi
  movq -4048(%rbp), %rsi
  movq -4056(%rbp), %rdx
  call lm_dict_set
  mov -4064(%rbp), rax
  leaq str_hdr_7(%rip), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq $26, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4072(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4080(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4088(%rbp)
  movq -4072(%rbp), %rdi
  movq -4080(%rbp), %rsi
  movq -4088(%rbp), %rdx
  call lm_dict_set
  mov -4096(%rbp), rax
  leaq str_hdr_8(%rip), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_9(%rip), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4104(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4112(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4120(%rbp)
  movq -4104(%rbp), %rdi
  movq -4112(%rbp), %rsi
  movq -4120(%rbp), %rdx
  call lm_dict_set
  mov -4128(%rbp), rax
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4136(%rbp)
  movq -4136(%rbp), %rdi
  call testRecordDestructuring
  mov -4144(%rbp), rax
  movq -4144(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4152(%rbp)
  movq -4152(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_10(%rip), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4160(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4168(%rbp)
  movq -4160(%rbp), %rdi
  movq -4168(%rbp), %rsi
  call lm_key_eq
  mov -4176(%rbp), rax
  movq -4176(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_11(%rip), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4184(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4192(%rbp)
  movq -4184(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_12
  jmp main_assert_fail_12
main_assert_pass_12:
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_13(%rip), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4200(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4208(%rbp)
  movq -4200(%rbp), %rdi
  movq -4208(%rbp), %rsi
  call lm_key_eq
  mov -4216(%rbp), rax
  movq -4216(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_14(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4224(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4232(%rbp)
  movq -4224(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_15
  jmp main_assert_fail_15
main_assert_fail_12:
  movq -4192(%rbp), %rax
  addq $8, %rax
  movq %rax, -4240(%rbp)
  movq -4240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4248(%rbp)
  movq -4192(%rbp), %rax
  addq $24, %rax
  movq %rax, -4256(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4256(%rbp), %rsi
  movq -4248(%rbp), %rdx
  syscall
  movq %rax, -4264(%rbp)
  movq $50397203, %rax
  movq %rax, -4272(%rbp)
  jmp main_assert_pass_12
main_assert_pass_15:
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_16(%rip), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4280(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4288(%rbp)
  movq -4280(%rbp), %rdi
  movq -4288(%rbp), %rsi
  call lm_rt_str_format
  mov -4296(%rbp), rax
  movq -4296(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4304(%rbp)
  movq -4304(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4312(%rbp)
  movq -4312(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2777
  jmp main_pr_str_0_2777
main_assert_fail_15:
  movq -4232(%rbp), %rax
  addq $8, %rax
  movq %rax, -4320(%rbp)
  movq -4320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4328(%rbp)
  movq -4232(%rbp), %rax
  addq $24, %rax
  movq %rax, -4336(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4336(%rbp), %rsi
  movq -4328(%rbp), %rdx
  syscall
  movq %rax, -4344(%rbp)
  movq $50397203, %rax
  movq %rax, -4352(%rbp)
  jmp main_assert_pass_15
main_pr_nil_0_2777:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4360(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4360(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4368(%rbp)
  jmp main_pr_next_0_2777
main_pr_str_0_2777:
  movq -4304(%rbp), %rax
  addq $8, %rax
  movq %rax, -4376(%rbp)
  movq -4376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4384(%rbp)
  movq -4304(%rbp), %rax
  addq $24, %rax
  movq %rax, -4392(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4392(%rbp), %rsi
  movq -4384(%rbp), %rdx
  syscall
  movq %rax, -4400(%rbp)
  jmp main_pr_next_0_2777
main_pr_next_0_2777:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4408(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4408(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4416(%rbp)
  movq $0, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_17(%rip), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4424(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4432(%rbp)
  movq -4424(%rbp), %rdi
  movq -4432(%rbp), %rsi
  call lm_rt_str_format
  mov -4440(%rbp), rax
  movq -4440(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4448(%rbp)
  movq -4448(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4456(%rbp)
  movq -4456(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6915
  jmp main_pr_str_0_6915
main_pr_nil_0_6915:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4464(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4464(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4472(%rbp)
  jmp main_pr_next_0_6915
main_pr_str_0_6915:
  movq -4448(%rbp), %rax
  addq $8, %rax
  movq %rax, -4480(%rbp)
  movq -4480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4488(%rbp)
  movq -4448(%rbp), %rax
  addq $24, %rax
  movq %rax, -4496(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4496(%rbp), %rsi
  movq -4488(%rbp), %rdx
  syscall
  movq %rax, -4504(%rbp)
  jmp main_pr_next_0_6915
main_pr_next_0_6915:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4512(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4512(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4520(%rbp)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_18(%rip), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4528(%rbp)
  movq -4528(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4536(%rbp)
  movq -4536(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7793
  jmp main_pr_str_0_7793
main_pr_nil_0_7793:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4544(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4552(%rbp)
  jmp main_pr_next_0_7793
main_pr_str_0_7793:
  movq -4528(%rbp), %rax
  addq $8, %rax
  movq %rax, -4560(%rbp)
  movq -4560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4568(%rbp)
  movq -4528(%rbp), %rax
  addq $24, %rax
  movq %rax, -4576(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4576(%rbp), %rsi
  movq -4568(%rbp), %rdx
  syscall
  movq %rax, -4584(%rbp)
  jmp main_pr_next_0_7793
main_pr_next_0_7793:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4592(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4592(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4600(%rbp)
  movq $0, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -4608(%rbp), rax
  movq -4608(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4616(%rbp)
  movq -4616(%rbp), %rdi
  call testListDestructuring
  mov -4624(%rbp), rax
  movq -4624(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4632(%rbp)
  movq -4632(%rbp), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -4640(%rbp), rax
  movq -4640(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4648(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4656(%rbp)
  movq -4648(%rbp), %rdi
  movq -4656(%rbp), %rsi
  call lm_list_append
  mov -4664(%rbp), rax
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4672(%rbp)
  movq -4672(%rbp), %rdi
  call testListDestructuring
  mov -4680(%rbp), rax
  movq -4680(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4688(%rbp)
  movq -4688(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -4696(%rbp), rax
  movq -4696(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4704(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4712(%rbp)
  movq -4704(%rbp), %rdi
  movq -4712(%rbp), %rsi
  call lm_list_append
  mov -4720(%rbp), rax
  movq $2, %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4728(%rbp)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4736(%rbp)
  movq -4728(%rbp), %rdi
  movq -4736(%rbp), %rsi
  call lm_list_append
  mov -4744(%rbp), rax
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4752(%rbp)
  movq -4752(%rbp), %rdi
  call testListDestructuring
  mov -4760(%rbp), rax
  movq -4760(%rbp), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4768(%rbp)
  movq -4768(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -4776(%rbp), rax
  movq -4776(%rbp), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4784(%rbp)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4792(%rbp)
  movq -4784(%rbp), %rdi
  movq -4792(%rbp), %rsi
  call lm_list_append
  mov -4800(%rbp), rax
  movq $2, %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4808(%rbp)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4816(%rbp)
  movq -4808(%rbp), %rdi
  movq -4816(%rbp), %rsi
  call lm_list_append
  mov -4824(%rbp), rax
  movq $3, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4832(%rbp)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4840(%rbp)
  movq -4832(%rbp), %rdi
  movq -4840(%rbp), %rsi
  call lm_list_append
  mov -4848(%rbp), rax
  movq $4, %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4856(%rbp)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4864(%rbp)
  movq -4856(%rbp), %rdi
  movq -4864(%rbp), %rsi
  call lm_list_append
  mov -4872(%rbp), rax
  movq $5, %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4880(%rbp)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4888(%rbp)
  movq -4880(%rbp), %rdi
  movq -4888(%rbp), %rsi
  call lm_list_append
  mov -4896(%rbp), rax
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4904(%rbp)
  movq -4904(%rbp), %rdi
  call testListDestructuring
  mov -4912(%rbp), rax
  movq -4912(%rbp), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4920(%rbp)
  movq -4920(%rbp), %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_19(%rip), %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4928(%rbp)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4936(%rbp)
  movq -4928(%rbp), %rdi
  movq -4936(%rbp), %rsi
  call lm_key_eq
  mov -4944(%rbp), rax
  movq -4944(%rbp), %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_20(%rip), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4952(%rbp)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4960(%rbp)
  movq -4952(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_21
  jmp main_assert_fail_21
main_assert_pass_21:
  movq $0, %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_22(%rip), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4968(%rbp)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4976(%rbp)
  movq -4968(%rbp), %rdi
  movq -4976(%rbp), %rsi
  call lm_key_eq
  mov -4984(%rbp), rax
  movq -4984(%rbp), %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_23(%rip), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4992(%rbp)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5000(%rbp)
  movq -4992(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_24
  jmp main_assert_fail_24
main_assert_fail_21:
  movq -4960(%rbp), %rax
  addq $8, %rax
  movq %rax, -5008(%rbp)
  movq -5008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5016(%rbp)
  movq -4960(%rbp), %rax
  addq $24, %rax
  movq %rax, -5024(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5024(%rbp), %rsi
  movq -5016(%rbp), %rdx
  syscall
  movq %rax, -5032(%rbp)
  movq $50397203, %rax
  movq %rax, -5040(%rbp)
  jmp main_assert_pass_21
main_assert_pass_24:
  movq $0, %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_25(%rip), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5048(%rbp)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5056(%rbp)
  movq -5048(%rbp), %rdi
  movq -5056(%rbp), %rsi
  call lm_key_eq
  mov -5064(%rbp), rax
  movq -5064(%rbp), %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_26(%rip), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5072(%rbp)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5080(%rbp)
  movq -5072(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_27
  jmp main_assert_fail_27
main_assert_fail_24:
  movq -5000(%rbp), %rax
  addq $8, %rax
  movq %rax, -5088(%rbp)
  movq -5088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5096(%rbp)
  movq -5000(%rbp), %rax
  addq $24, %rax
  movq %rax, -5104(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5104(%rbp), %rsi
  movq -5096(%rbp), %rdx
  syscall
  movq %rax, -5112(%rbp)
  movq $50397203, %rax
  movq %rax, -5120(%rbp)
  jmp main_assert_pass_24
main_assert_pass_27:
  movq $0, %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_28(%rip), %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5128(%rbp)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5136(%rbp)
  movq -5128(%rbp), %rdi
  movq -5136(%rbp), %rsi
  call lm_key_eq
  mov -5144(%rbp), rax
  movq -5144(%rbp), %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_29(%rip), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5152(%rbp)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5160(%rbp)
  movq -5152(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_30
  jmp main_assert_fail_30
main_assert_fail_27:
  movq -5080(%rbp), %rax
  addq $8, %rax
  movq %rax, -5168(%rbp)
  movq -5168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5176(%rbp)
  movq -5080(%rbp), %rax
  addq $24, %rax
  movq %rax, -5184(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5184(%rbp), %rsi
  movq -5176(%rbp), %rdx
  syscall
  movq %rax, -5192(%rbp)
  movq $50397203, %rax
  movq %rax, -5200(%rbp)
  jmp main_assert_pass_27
main_assert_pass_30:
  movq $0, %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_31(%rip), %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5208(%rbp)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5216(%rbp)
  movq -5208(%rbp), %rdi
  movq -5216(%rbp), %rsi
  call lm_rt_str_format
  mov -5224(%rbp), rax
  movq -5224(%rbp), %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5232(%rbp)
  movq -5232(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5240(%rbp)
  movq -5240(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8335
  jmp main_pr_str_0_8335
main_assert_fail_30:
  movq -5160(%rbp), %rax
  addq $8, %rax
  movq %rax, -5248(%rbp)
  movq -5248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5256(%rbp)
  movq -5160(%rbp), %rax
  addq $24, %rax
  movq %rax, -5264(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5264(%rbp), %rsi
  movq -5256(%rbp), %rdx
  syscall
  movq %rax, -5272(%rbp)
  movq $50397203, %rax
  movq %rax, -5280(%rbp)
  jmp main_assert_pass_30
main_pr_nil_0_8335:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5288(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5288(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5296(%rbp)
  jmp main_pr_next_0_8335
main_pr_str_0_8335:
  movq -5232(%rbp), %rax
  addq $8, %rax
  movq %rax, -5304(%rbp)
  movq -5304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5312(%rbp)
  movq -5232(%rbp), %rax
  addq $24, %rax
  movq %rax, -5320(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5320(%rbp), %rsi
  movq -5312(%rbp), %rdx
  syscall
  movq %rax, -5328(%rbp)
  jmp main_pr_next_0_8335
main_pr_next_0_8335:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5336(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5336(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5344(%rbp)
  movq $0, %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_32(%rip), %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5352(%rbp)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5360(%rbp)
  movq -5352(%rbp), %rdi
  movq -5360(%rbp), %rsi
  call lm_rt_str_format
  mov -5368(%rbp), rax
  movq -5368(%rbp), %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5376(%rbp)
  movq -5376(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5384(%rbp)
  movq -5384(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5386
  jmp main_pr_str_0_5386
main_pr_nil_0_5386:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5392(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5392(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5400(%rbp)
  jmp main_pr_next_0_5386
main_pr_str_0_5386:
  movq -5376(%rbp), %rax
  addq $8, %rax
  movq %rax, -5408(%rbp)
  movq -5408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5416(%rbp)
  movq -5376(%rbp), %rax
  addq $24, %rax
  movq %rax, -5424(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5424(%rbp), %rsi
  movq -5416(%rbp), %rdx
  syscall
  movq %rax, -5432(%rbp)
  jmp main_pr_next_0_5386
main_pr_next_0_5386:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5440(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5440(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5448(%rbp)
  movq $0, %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_33(%rip), %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5456(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5464(%rbp)
  movq -5456(%rbp), %rdi
  movq -5464(%rbp), %rsi
  call lm_rt_str_format
  mov -5472(%rbp), rax
  movq -5472(%rbp), %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5480(%rbp)
  movq -5480(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5488(%rbp)
  movq -5488(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_492
  jmp main_pr_str_0_492
main_pr_nil_0_492:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5496(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5496(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5504(%rbp)
  jmp main_pr_next_0_492
main_pr_str_0_492:
  movq -5480(%rbp), %rax
  addq $8, %rax
  movq %rax, -5512(%rbp)
  movq -5512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5520(%rbp)
  movq -5480(%rbp), %rax
  addq $24, %rax
  movq %rax, -5528(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5528(%rbp), %rsi
  movq -5520(%rbp), %rdx
  syscall
  movq %rax, -5536(%rbp)
  jmp main_pr_next_0_492
main_pr_next_0_492:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5544(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5552(%rbp)
  movq $0, %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_34(%rip), %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5560(%rbp)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5568(%rbp)
  movq -5560(%rbp), %rdi
  movq -5568(%rbp), %rsi
  call lm_rt_str_format
  mov -5576(%rbp), rax
  movq -5576(%rbp), %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5584(%rbp)
  movq -5584(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5592(%rbp)
  movq -5592(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6649
  jmp main_pr_str_0_6649
main_pr_nil_0_6649:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5600(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5600(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5608(%rbp)
  jmp main_pr_next_0_6649
main_pr_str_0_6649:
  movq -5584(%rbp), %rax
  addq $8, %rax
  movq %rax, -5616(%rbp)
  movq -5616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5624(%rbp)
  movq -5584(%rbp), %rax
  addq $24, %rax
  movq %rax, -5632(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5632(%rbp), %rsi
  movq -5624(%rbp), %rdx
  syscall
  movq %rax, -5640(%rbp)
  jmp main_pr_next_0_6649
main_pr_next_0_6649:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5648(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5648(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5656(%rbp)
  movq $0, %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_35(%rip), %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5664(%rbp)
  movq -5664(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5672(%rbp)
  movq -5672(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1421
  jmp main_pr_str_0_1421
main_pr_nil_0_1421:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5680(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5680(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5688(%rbp)
  jmp main_pr_next_0_1421
main_pr_str_0_1421:
  movq -5664(%rbp), %rax
  addq $8, %rax
  movq %rax, -5696(%rbp)
  movq -5696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5704(%rbp)
  movq -5664(%rbp), %rax
  addq $24, %rax
  movq %rax, -5712(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5712(%rbp), %rsi
  movq -5704(%rbp), %rdx
  syscall
  movq %rax, -5720(%rbp)
  jmp main_pr_next_0_1421
main_pr_next_0_1421:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5728(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5728(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5736(%rbp)
  movq $0, %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  call lm_tuple_new
  mov -5744(%rbp), rax
  movq -5744(%rbp), %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5752(%rbp)
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5760(%rbp)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5768(%rbp)
  movq -5752(%rbp), %rdi
  movq -5760(%rbp), %rsi
  movq -5768(%rbp), %rdx
  call lm_tuple_set
  mov -5776(%rbp), rax
  movq $20, %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5784(%rbp)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5792(%rbp)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5800(%rbp)
  movq -5784(%rbp), %rdi
  movq -5792(%rbp), %rsi
  movq -5800(%rbp), %rdx
  call lm_tuple_set
  mov -5808(%rbp), rax
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5816(%rbp)
  movq -5816(%rbp), %rdi
  call testTupleDestructuring
  mov -5824(%rbp), rax
  movq -5824(%rbp), %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5832(%rbp)
  movq -5832(%rbp), %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rdi
  call lm_tuple_new
  mov -5840(%rbp), rax
  movq -5840(%rbp), %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5848(%rbp)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5856(%rbp)
  movq -864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5864(%rbp)
  movq -5848(%rbp), %rdi
  movq -5856(%rbp), %rsi
  movq -5864(%rbp), %rdx
  call lm_tuple_set
  mov -5872(%rbp), rax
  movq $2, %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5880(%rbp)
  movq -888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5888(%rbp)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5896(%rbp)
  movq -5880(%rbp), %rdi
  movq -5888(%rbp), %rsi
  movq -5896(%rbp), %rdx
  call lm_tuple_set
  mov -5904(%rbp), rax
  movq $3, %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5912(%rbp)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5920(%rbp)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5928(%rbp)
  movq -5912(%rbp), %rdi
  movq -5920(%rbp), %rsi
  movq -5928(%rbp), %rdx
  call lm_tuple_set
  mov -5936(%rbp), rax
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5944(%rbp)
  movq -5944(%rbp), %rdi
  call testTupleDestructuring
  mov -5952(%rbp), rax
  movq -5952(%rbp), %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5960(%rbp)
  movq -5960(%rbp), %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_36(%rip), %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5968(%rbp)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5976(%rbp)
  movq -5968(%rbp), %rdi
  movq -5976(%rbp), %rsi
  call lm_key_eq
  mov -5984(%rbp), rax
  movq -5984(%rbp), %rax
  movq -936(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_37(%rip), %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5992(%rbp)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6000(%rbp)
  movq -5992(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_38
  jmp main_assert_fail_38
main_assert_pass_38:
  movq $0, %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_39(%rip), %rax
  movq -960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6008(%rbp)
  movq -960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6016(%rbp)
  movq -6008(%rbp), %rdi
  movq -6016(%rbp), %rsi
  call lm_key_eq
  mov -6024(%rbp), rax
  movq -6024(%rbp), %rax
  movq -968(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_40(%rip), %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6032(%rbp)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6040(%rbp)
  movq -6032(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_41
  jmp main_assert_fail_41
main_assert_fail_38:
  movq -6000(%rbp), %rax
  addq $8, %rax
  movq %rax, -6048(%rbp)
  movq -6048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6056(%rbp)
  movq -6000(%rbp), %rax
  addq $24, %rax
  movq %rax, -6064(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6064(%rbp), %rsi
  movq -6056(%rbp), %rdx
  syscall
  movq %rax, -6072(%rbp)
  movq $50397203, %rax
  movq %rax, -6080(%rbp)
  jmp main_assert_pass_38
main_assert_pass_41:
  movq $0, %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_42(%rip), %rax
  movq -1000(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6088(%rbp)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6096(%rbp)
  movq -6088(%rbp), %rdi
  movq -6096(%rbp), %rsi
  call lm_rt_str_format
  mov -6104(%rbp), rax
  movq -6104(%rbp), %rax
  movq -992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6112(%rbp)
  movq -6112(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6120(%rbp)
  movq -6120(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2362
  jmp main_pr_str_0_2362
main_assert_fail_41:
  movq -6040(%rbp), %rax
  addq $8, %rax
  movq %rax, -6128(%rbp)
  movq -6128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6136(%rbp)
  movq -6040(%rbp), %rax
  addq $24, %rax
  movq %rax, -6144(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6144(%rbp), %rsi
  movq -6136(%rbp), %rdx
  syscall
  movq %rax, -6152(%rbp)
  movq $50397203, %rax
  movq %rax, -6160(%rbp)
  jmp main_assert_pass_41
main_pr_nil_0_2362:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6168(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6168(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6176(%rbp)
  jmp main_pr_next_0_2362
main_pr_str_0_2362:
  movq -6112(%rbp), %rax
  addq $8, %rax
  movq %rax, -6184(%rbp)
  movq -6184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6192(%rbp)
  movq -6112(%rbp), %rax
  addq $24, %rax
  movq %rax, -6200(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6200(%rbp), %rsi
  movq -6192(%rbp), %rdx
  syscall
  movq %rax, -6208(%rbp)
  jmp main_pr_next_0_2362
main_pr_next_0_2362:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6216(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6216(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6224(%rbp)
  movq $0, %rax
  movq -1008(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_43(%rip), %rax
  movq -1024(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6232(%rbp)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6240(%rbp)
  movq -6232(%rbp), %rdi
  movq -6240(%rbp), %rsi
  call lm_rt_str_format
  mov -6248(%rbp), rax
  movq -6248(%rbp), %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6256(%rbp)
  movq -6256(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6264(%rbp)
  movq -6264(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_27
  jmp main_pr_str_0_27
main_pr_nil_0_27:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6272(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6272(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6280(%rbp)
  jmp main_pr_next_0_27
main_pr_str_0_27:
  movq -6256(%rbp), %rax
  addq $8, %rax
  movq %rax, -6288(%rbp)
  movq -6288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6296(%rbp)
  movq -6256(%rbp), %rax
  addq $24, %rax
  movq %rax, -6304(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6304(%rbp), %rsi
  movq -6296(%rbp), %rdx
  syscall
  movq %rax, -6312(%rbp)
  jmp main_pr_next_0_27
main_pr_next_0_27:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6320(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6320(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6328(%rbp)
  movq $0, %rax
  movq -1032(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_44(%rip), %rax
  movq -1040(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6336(%rbp)
  movq -6336(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6344(%rbp)
  movq -6344(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8690
  jmp main_pr_str_0_8690
main_pr_nil_0_8690:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6352(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6352(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6360(%rbp)
  jmp main_pr_next_0_8690
main_pr_str_0_8690:
  movq -6336(%rbp), %rax
  addq $8, %rax
  movq %rax, -6368(%rbp)
  movq -6368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6376(%rbp)
  movq -6336(%rbp), %rax
  addq $24, %rax
  movq %rax, -6384(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6384(%rbp), %rsi
  movq -6376(%rbp), %rdx
  syscall
  movq %rax, -6392(%rbp)
  jmp main_pr_next_0_8690
main_pr_next_0_8690:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6400(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6400(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6408(%rbp)
  movq $0, %rax
  movq -1048(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  call lm_tuple_new
  mov -6416(%rbp), rax
  movq -6416(%rbp), %rax
  movq -1056(%rbp), %rdx
  movq %rax, (%rdx)
  movq $100, %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1072(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6424(%rbp)
  movq -1072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6432(%rbp)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6440(%rbp)
  movq -6424(%rbp), %rdi
  movq -6432(%rbp), %rsi
  movq -6440(%rbp), %rdx
  call lm_tuple_set
  mov -6448(%rbp), rax
  movq $0, %rdi
  call lm_list_new
  mov -6456(%rbp), rax
  movq -6456(%rbp), %rax
  movq -1080(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -1088(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6464(%rbp)
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6472(%rbp)
  movq -6464(%rbp), %rdi
  movq -6472(%rbp), %rsi
  call lm_list_append
  mov -6480(%rbp), rax
  movq $20, %rax
  movq -1104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6488(%rbp)
  movq -1104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6496(%rbp)
  movq -6488(%rbp), %rdi
  movq -6496(%rbp), %rsi
  call lm_list_append
  mov -6504(%rbp), rax
  movq $1, %rax
  movq -1120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6512(%rbp)
  movq -1120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6520(%rbp)
  movq -1080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6528(%rbp)
  movq -6512(%rbp), %rdi
  movq -6520(%rbp), %rsi
  movq -6528(%rbp), %rdx
  call lm_tuple_set
  mov -6536(%rbp), rax
  movq -1056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6544(%rbp)
  movq -6544(%rbp), %rdi
  call testNestedDestructuring
  mov -6552(%rbp), rax
  movq -6552(%rbp), %rax
  movq -1128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6560(%rbp)
  movq -6560(%rbp), %rax
  movq -1136(%rbp), %rdx
  movq %rax, (%rdx)
  call lm_dict_new
  mov -6568(%rbp), rax
  movq -6568(%rbp), %rax
  movq -1144(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_45(%rip), %rax
  movq -1152(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_46(%rip), %rax
  movq -1160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6576(%rbp)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6584(%rbp)
  movq -1160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6592(%rbp)
  movq -6576(%rbp), %rdi
  movq -6584(%rbp), %rsi
  movq -6592(%rbp), %rdx
  call lm_dict_set
  mov -6600(%rbp), rax
  leaq str_hdr_47(%rip), %rax
  movq -1168(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -6608(%rbp), rax
  movq -6608(%rbp), %rax
  movq -1176(%rbp), %rdx
  movq %rax, (%rdx)
  movq $95, %rax
  movq -1184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6616(%rbp)
  movq -1184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6624(%rbp)
  movq -6616(%rbp), %rdi
  movq -6624(%rbp), %rsi
  call lm_list_append
  mov -6632(%rbp), rax
  movq $87, %rax
  movq -1200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6640(%rbp)
  movq -1200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6648(%rbp)
  movq -6640(%rbp), %rdi
  movq -6648(%rbp), %rsi
  call lm_list_append
  mov -6656(%rbp), rax
  movq -1144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6664(%rbp)
  movq -1168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6672(%rbp)
  movq -1176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6680(%rbp)
  movq -6664(%rbp), %rdi
  movq -6672(%rbp), %rsi
  movq -6680(%rbp), %rdx
  call lm_dict_set
  mov -6688(%rbp), rax
  movq -1144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6696(%rbp)
  movq -6696(%rbp), %rdi
  call testNestedDestructuring
  mov -6704(%rbp), rax
  movq -6704(%rbp), %rax
  movq -1216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6712(%rbp)
  movq -6712(%rbp), %rax
  movq -1224(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_48(%rip), %rax
  movq -1232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6720(%rbp)
  movq -1232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6728(%rbp)
  movq -6720(%rbp), %rdi
  movq -6728(%rbp), %rsi
  call lm_key_eq
  mov -6736(%rbp), rax
  movq -6736(%rbp), %rax
  movq -1240(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_49(%rip), %rax
  movq -1248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6744(%rbp)
  movq -1248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6752(%rbp)
  movq -6744(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_50
  jmp main_assert_fail_50
main_assert_pass_50:
  movq $0, %rax
  movq -1256(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_51(%rip), %rax
  movq -1264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6760(%rbp)
  movq -1264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6768(%rbp)
  movq -6760(%rbp), %rdi
  movq -6768(%rbp), %rsi
  call lm_key_eq
  mov -6776(%rbp), rax
  movq -6776(%rbp), %rax
  movq -1272(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_52(%rip), %rax
  movq -1280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6784(%rbp)
  movq -1280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6792(%rbp)
  movq -6784(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_53
  jmp main_assert_fail_53
main_assert_fail_50:
  movq -6752(%rbp), %rax
  addq $8, %rax
  movq %rax, -6800(%rbp)
  movq -6800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6808(%rbp)
  movq -6752(%rbp), %rax
  addq $24, %rax
  movq %rax, -6816(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6816(%rbp), %rsi
  movq -6808(%rbp), %rdx
  syscall
  movq %rax, -6824(%rbp)
  movq $50397203, %rax
  movq %rax, -6832(%rbp)
  jmp main_assert_pass_50
main_assert_pass_53:
  movq $0, %rax
  movq -1288(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_54(%rip), %rax
  movq -1304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6840(%rbp)
  movq -1136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6848(%rbp)
  movq -6840(%rbp), %rdi
  movq -6848(%rbp), %rsi
  call lm_rt_str_format
  mov -6856(%rbp), rax
  movq -6856(%rbp), %rax
  movq -1296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6864(%rbp)
  movq -6864(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6872(%rbp)
  movq -6872(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_59
  jmp main_pr_str_0_59
main_assert_fail_53:
  movq -6792(%rbp), %rax
  addq $8, %rax
  movq %rax, -6880(%rbp)
  movq -6880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6888(%rbp)
  movq -6792(%rbp), %rax
  addq $24, %rax
  movq %rax, -6896(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6896(%rbp), %rsi
  movq -6888(%rbp), %rdx
  syscall
  movq %rax, -6904(%rbp)
  movq $50397203, %rax
  movq %rax, -6912(%rbp)
  jmp main_assert_pass_53
main_pr_nil_0_59:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6920(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6920(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6928(%rbp)
  jmp main_pr_next_0_59
main_pr_str_0_59:
  movq -6864(%rbp), %rax
  addq $8, %rax
  movq %rax, -6936(%rbp)
  movq -6936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6944(%rbp)
  movq -6864(%rbp), %rax
  addq $24, %rax
  movq %rax, -6952(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6952(%rbp), %rsi
  movq -6944(%rbp), %rdx
  syscall
  movq %rax, -6960(%rbp)
  jmp main_pr_next_0_59
main_pr_next_0_59:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6968(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6968(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6976(%rbp)
  movq $0, %rax
  movq -1312(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_55(%rip), %rax
  movq -1328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6984(%rbp)
  movq -1224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6992(%rbp)
  movq -6984(%rbp), %rdi
  movq -6992(%rbp), %rsi
  call lm_rt_str_format
  mov -7000(%rbp), rax
  movq -7000(%rbp), %rax
  movq -1320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7008(%rbp)
  movq -7008(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7016(%rbp)
  movq -7016(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7763
  jmp main_pr_str_0_7763
main_pr_nil_0_7763:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7024(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7024(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7032(%rbp)
  jmp main_pr_next_0_7763
main_pr_str_0_7763:
  movq -7008(%rbp), %rax
  addq $8, %rax
  movq %rax, -7040(%rbp)
  movq -7040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7048(%rbp)
  movq -7008(%rbp), %rax
  addq $24, %rax
  movq %rax, -7056(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7056(%rbp), %rsi
  movq -7048(%rbp), %rdx
  syscall
  movq %rax, -7064(%rbp)
  jmp main_pr_next_0_7763
main_pr_next_0_7763:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7072(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7072(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7080(%rbp)
  movq $0, %rax
  movq -1336(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_56(%rip), %rax
  movq -1344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7088(%rbp)
  movq -7088(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7096(%rbp)
  movq -7096(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3926
  jmp main_pr_str_0_3926
main_pr_nil_0_3926:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7104(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7104(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7112(%rbp)
  jmp main_pr_next_0_3926
main_pr_str_0_3926:
  movq -7088(%rbp), %rax
  addq $8, %rax
  movq %rax, -7120(%rbp)
  movq -7120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7128(%rbp)
  movq -7088(%rbp), %rax
  addq $24, %rax
  movq %rax, -7136(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7136(%rbp), %rsi
  movq -7128(%rbp), %rdx
  syscall
  movq %rax, -7144(%rbp)
  jmp main_pr_next_0_3926
main_pr_next_0_3926:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7152(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7152(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7160(%rbp)
  movq $0, %rax
  movq -1352(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4617315517961601024, %rax
  movq -1360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7168(%rbp)
  movq $0, %rdi
  movq -7168(%rbp), %rsi
  leaq vname_Circle(%rip), %rdx
  call lm_enum_new
  mov -7176(%rbp), rax
  movq -7176(%rbp), %rax
  movq -1368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7184(%rbp)
  movq -7184(%rbp), %rdi
  call describeShape
  mov -7192(%rbp), rax
  movq -7192(%rbp), %rax
  movq -1384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7200(%rbp)
  movq -7200(%rbp), %rax
  movq -1392(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -1400(%rbp), %rdx
  movq %rax, (%rdx)
  movq $20, %rax
  movq -1408(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  call lm_tuple_new
  mov -7208(%rbp), rax
  movq -7208(%rbp), %rax
  movq -1424(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7216(%rbp)
  movq -1432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7224(%rbp)
  movq -1400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7232(%rbp)
  movq -7216(%rbp), %rdi
  movq -7224(%rbp), %rsi
  movq -7232(%rbp), %rdx
  call lm_tuple_set
  mov -7240(%rbp), rax
  movq $1, %rax
  movq -1440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7248(%rbp)
  movq -1440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7256(%rbp)
  movq -1408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7264(%rbp)
  movq -7248(%rbp), %rdi
  movq -7256(%rbp), %rsi
  movq -7264(%rbp), %rdx
  call lm_tuple_set
  mov -7272(%rbp), rax
  movq -1424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7280(%rbp)
  movq $1, %rdi
  movq -7280(%rbp), %rsi
  leaq vname_Rectangle(%rip), %rdx
  call lm_enum_new
  mov -7288(%rbp), rax
  movq -7288(%rbp), %rax
  movq -1416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7296(%rbp)
  movq -7296(%rbp), %rdi
  call describeShape
  mov -7304(%rbp), rax
  movq -7304(%rbp), %rax
  movq -1448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7312(%rbp)
  movq -7312(%rbp), %rax
  movq -1456(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -1464(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4, %rax
  movq -1472(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  call lm_tuple_new
  mov -7320(%rbp), rax
  movq -7320(%rbp), %rax
  movq -1488(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7328(%rbp)
  movq -1496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7336(%rbp)
  movq -1464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7344(%rbp)
  movq -7328(%rbp), %rdi
  movq -7336(%rbp), %rsi
  movq -7344(%rbp), %rdx
  call lm_tuple_set
  mov -7352(%rbp), rax
  movq $1, %rax
  movq -1504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7360(%rbp)
  movq -1504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7368(%rbp)
  movq -1472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7376(%rbp)
  movq -7360(%rbp), %rdi
  movq -7368(%rbp), %rsi
  movq -7376(%rbp), %rdx
  call lm_tuple_set
  mov -7384(%rbp), rax
  movq -1488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7392(%rbp)
  movq $2, %rdi
  movq -7392(%rbp), %rsi
  leaq vname_Point(%rip), %rdx
  call lm_enum_new
  mov -7400(%rbp), rax
  movq -7400(%rbp), %rax
  movq -1480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7408(%rbp)
  movq -7408(%rbp), %rdi
  call describeShape
  mov -7416(%rbp), rax
  movq -7416(%rbp), %rax
  movq -1512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7424(%rbp)
  movq -7424(%rbp), %rax
  movq -1520(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_57(%rip), %rax
  movq -1528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7432(%rbp)
  movq -1528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7440(%rbp)
  movq -7432(%rbp), %rdi
  movq -7440(%rbp), %rsi
  call lm_key_eq
  mov -7448(%rbp), rax
  movq -7448(%rbp), %rax
  movq -1536(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_58(%rip), %rax
  movq -1544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7456(%rbp)
  movq -1544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7464(%rbp)
  movq -7456(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_59
  jmp main_assert_fail_59
main_assert_pass_59:
  movq $0, %rax
  movq -1552(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_60(%rip), %rax
  movq -1560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7472(%rbp)
  movq -1560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7480(%rbp)
  movq -7472(%rbp), %rdi
  movq -7480(%rbp), %rsi
  call lm_key_eq
  mov -7488(%rbp), rax
  movq -7488(%rbp), %rax
  movq -1568(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_61(%rip), %rax
  movq -1576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7496(%rbp)
  movq -1576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7504(%rbp)
  movq -7496(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_62
  jmp main_assert_fail_62
main_assert_fail_59:
  movq -7464(%rbp), %rax
  addq $8, %rax
  movq %rax, -7512(%rbp)
  movq -7512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7520(%rbp)
  movq -7464(%rbp), %rax
  addq $24, %rax
  movq %rax, -7528(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7528(%rbp), %rsi
  movq -7520(%rbp), %rdx
  syscall
  movq %rax, -7536(%rbp)
  movq $50397203, %rax
  movq %rax, -7544(%rbp)
  jmp main_assert_pass_59
main_assert_pass_62:
  movq $0, %rax
  movq -1584(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_63(%rip), %rax
  movq -1592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7552(%rbp)
  movq -1592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7560(%rbp)
  movq -7552(%rbp), %rdi
  movq -7560(%rbp), %rsi
  call lm_key_eq
  mov -7568(%rbp), rax
  movq -7568(%rbp), %rax
  movq -1600(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_64(%rip), %rax
  movq -1608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7576(%rbp)
  movq -1608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7584(%rbp)
  movq -7576(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_65
  jmp main_assert_fail_65
main_assert_fail_62:
  movq -7504(%rbp), %rax
  addq $8, %rax
  movq %rax, -7592(%rbp)
  movq -7592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7600(%rbp)
  movq -7504(%rbp), %rax
  addq $24, %rax
  movq %rax, -7608(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7608(%rbp), %rsi
  movq -7600(%rbp), %rdx
  syscall
  movq %rax, -7616(%rbp)
  movq $50397203, %rax
  movq %rax, -7624(%rbp)
  jmp main_assert_pass_62
main_assert_pass_65:
  movq $0, %rax
  movq -1616(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_66(%rip), %rax
  movq -1632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7632(%rbp)
  movq -1392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7640(%rbp)
  movq -7632(%rbp), %rdi
  movq -7640(%rbp), %rsi
  call lm_rt_str_format
  mov -7648(%rbp), rax
  movq -7648(%rbp), %rax
  movq -1624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7656(%rbp)
  movq -7656(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7664(%rbp)
  movq -7664(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_540
  jmp main_pr_str_0_540
main_assert_fail_65:
  movq -7584(%rbp), %rax
  addq $8, %rax
  movq %rax, -7672(%rbp)
  movq -7672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7680(%rbp)
  movq -7584(%rbp), %rax
  addq $24, %rax
  movq %rax, -7688(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7688(%rbp), %rsi
  movq -7680(%rbp), %rdx
  syscall
  movq %rax, -7696(%rbp)
  movq $50397203, %rax
  movq %rax, -7704(%rbp)
  jmp main_assert_pass_65
main_pr_nil_0_540:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7712(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7712(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7720(%rbp)
  jmp main_pr_next_0_540
main_pr_str_0_540:
  movq -7656(%rbp), %rax
  addq $8, %rax
  movq %rax, -7728(%rbp)
  movq -7728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7736(%rbp)
  movq -7656(%rbp), %rax
  addq $24, %rax
  movq %rax, -7744(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7744(%rbp), %rsi
  movq -7736(%rbp), %rdx
  syscall
  movq %rax, -7752(%rbp)
  jmp main_pr_next_0_540
main_pr_next_0_540:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7760(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7760(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7768(%rbp)
  movq $0, %rax
  movq -1640(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_67(%rip), %rax
  movq -1656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7776(%rbp)
  movq -1456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7784(%rbp)
  movq -7776(%rbp), %rdi
  movq -7784(%rbp), %rsi
  call lm_rt_str_format
  mov -7792(%rbp), rax
  movq -7792(%rbp), %rax
  movq -1648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7800(%rbp)
  movq -7800(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7808(%rbp)
  movq -7808(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3426
  jmp main_pr_str_0_3426
main_pr_nil_0_3426:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7816(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7816(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7824(%rbp)
  jmp main_pr_next_0_3426
main_pr_str_0_3426:
  movq -7800(%rbp), %rax
  addq $8, %rax
  movq %rax, -7832(%rbp)
  movq -7832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7840(%rbp)
  movq -7800(%rbp), %rax
  addq $24, %rax
  movq %rax, -7848(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7848(%rbp), %rsi
  movq -7840(%rbp), %rdx
  syscall
  movq %rax, -7856(%rbp)
  jmp main_pr_next_0_3426
main_pr_next_0_3426:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7864(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7864(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7872(%rbp)
  movq $0, %rax
  movq -1664(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_68(%rip), %rax
  movq -1680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7880(%rbp)
  movq -1520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7888(%rbp)
  movq -7880(%rbp), %rdi
  movq -7888(%rbp), %rsi
  call lm_rt_str_format
  mov -7896(%rbp), rax
  movq -7896(%rbp), %rax
  movq -1672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7904(%rbp)
  movq -7904(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7912(%rbp)
  movq -7912(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9172
  jmp main_pr_str_0_9172
main_pr_nil_0_9172:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7920(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7920(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7928(%rbp)
  jmp main_pr_next_0_9172
main_pr_str_0_9172:
  movq -7904(%rbp), %rax
  addq $8, %rax
  movq %rax, -7936(%rbp)
  movq -7936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7944(%rbp)
  movq -7904(%rbp), %rax
  addq $24, %rax
  movq %rax, -7952(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7952(%rbp), %rsi
  movq -7944(%rbp), %rdx
  syscall
  movq %rax, -7960(%rbp)
  jmp main_pr_next_0_9172
main_pr_next_0_9172:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7968(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7968(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7976(%rbp)
  movq $0, %rax
  movq -1688(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_69(%rip), %rax
  movq -1696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7984(%rbp)
  movq -7984(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7992(%rbp)
  movq -7992(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5736
  jmp main_pr_str_0_5736
main_pr_nil_0_5736:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8000(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8000(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8008(%rbp)
  jmp main_pr_next_0_5736
main_pr_str_0_5736:
  movq -7984(%rbp), %rax
  addq $8, %rax
  movq %rax, -8016(%rbp)
  movq -8016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8024(%rbp)
  movq -7984(%rbp), %rax
  addq $24, %rax
  movq %rax, -8032(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8032(%rbp), %rsi
  movq -8024(%rbp), %rdx
  syscall
  movq %rax, -8040(%rbp)
  jmp main_pr_next_0_5736
main_pr_next_0_5736:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8048(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8048(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8056(%rbp)
  movq $0, %rax
  movq -1704(%rbp), %rdx
  movq %rax, (%rdx)
  call lm_dict_new
  mov -8064(%rbp), rax
  movq -8064(%rbp), %rax
  movq -1712(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_70(%rip), %rax
  movq -1720(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_71(%rip), %rax
  movq -1728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8072(%rbp)
  movq -1720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8080(%rbp)
  movq -1728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8088(%rbp)
  movq -8072(%rbp), %rdi
  movq -8080(%rbp), %rsi
  movq -8088(%rbp), %rdx
  call lm_dict_set
  mov -8096(%rbp), rax
  leaq str_hdr_72(%rip), %rax
  movq -1736(%rbp), %rdx
  movq %rax, (%rdx)
  movq $25, %rax
  movq -1744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8104(%rbp)
  movq -1736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8112(%rbp)
  movq -1744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8120(%rbp)
  movq -8104(%rbp), %rdi
  movq -8112(%rbp), %rsi
  movq -8120(%rbp), %rdx
  call lm_dict_set
  mov -8128(%rbp), rax
  movq -1712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8136(%rbp)
  movq -8136(%rbp), %rdi
  call testDestructuringWithGuards
  mov -8144(%rbp), rax
  movq -8144(%rbp), %rax
  movq -1752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8152(%rbp)
  movq -8152(%rbp), %rax
  movq -1760(%rbp), %rdx
  movq %rax, (%rdx)
  call lm_dict_new
  mov -8160(%rbp), rax
  movq -8160(%rbp), %rax
  movq -1768(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_73(%rip), %rax
  movq -1776(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_74(%rip), %rax
  movq -1784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8168(%rbp)
  movq -1776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8176(%rbp)
  movq -1784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8184(%rbp)
  movq -8168(%rbp), %rdi
  movq -8176(%rbp), %rsi
  movq -8184(%rbp), %rdx
  call lm_dict_set
  mov -8192(%rbp), rax
  leaq str_hdr_75(%rip), %rax
  movq -1792(%rbp), %rdx
  movq %rax, (%rdx)
  movq $16, %rax
  movq -1800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8200(%rbp)
  movq -1792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8208(%rbp)
  movq -1800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8216(%rbp)
  movq -8200(%rbp), %rdi
  movq -8208(%rbp), %rsi
  movq -8216(%rbp), %rdx
  call lm_dict_set
  mov -8224(%rbp), rax
  movq -1768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8232(%rbp)
  movq -8232(%rbp), %rdi
  call testDestructuringWithGuards
  mov -8240(%rbp), rax
  movq -8240(%rbp), %rax
  movq -1808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8248(%rbp)
  movq -8248(%rbp), %rax
  movq -1816(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_76(%rip), %rax
  movq -1824(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8256(%rbp)
  movq -1824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8264(%rbp)
  movq -8256(%rbp), %rdi
  movq -8264(%rbp), %rsi
  call lm_key_eq
  mov -8272(%rbp), rax
  movq -8272(%rbp), %rax
  movq -1832(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_77(%rip), %rax
  movq -1840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8280(%rbp)
  movq -1840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8288(%rbp)
  movq -8280(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_78
  jmp main_assert_fail_78
main_assert_pass_78:
  movq $0, %rax
  movq -1848(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_79(%rip), %rax
  movq -1856(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8296(%rbp)
  movq -1856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8304(%rbp)
  movq -8296(%rbp), %rdi
  movq -8304(%rbp), %rsi
  call lm_key_eq
  mov -8312(%rbp), rax
  movq -8312(%rbp), %rax
  movq -1864(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_80(%rip), %rax
  movq -1872(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8320(%rbp)
  movq -1872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8328(%rbp)
  movq -8320(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_81
  jmp main_assert_fail_81
main_assert_fail_78:
  movq -8288(%rbp), %rax
  addq $8, %rax
  movq %rax, -8336(%rbp)
  movq -8336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8344(%rbp)
  movq -8288(%rbp), %rax
  addq $24, %rax
  movq %rax, -8352(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8352(%rbp), %rsi
  movq -8344(%rbp), %rdx
  syscall
  movq %rax, -8360(%rbp)
  movq $50397203, %rax
  movq %rax, -8368(%rbp)
  jmp main_assert_pass_78
main_assert_pass_81:
  movq $0, %rax
  movq -1880(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_82(%rip), %rax
  movq -1896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8376(%rbp)
  movq -1760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8384(%rbp)
  movq -8376(%rbp), %rdi
  movq -8384(%rbp), %rsi
  call lm_rt_str_format
  mov -8392(%rbp), rax
  movq -8392(%rbp), %rax
  movq -1888(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8400(%rbp)
  movq -8400(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8408(%rbp)
  movq -8408(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5211
  jmp main_pr_str_0_5211
main_assert_fail_81:
  movq -8328(%rbp), %rax
  addq $8, %rax
  movq %rax, -8416(%rbp)
  movq -8416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8424(%rbp)
  movq -8328(%rbp), %rax
  addq $24, %rax
  movq %rax, -8432(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8432(%rbp), %rsi
  movq -8424(%rbp), %rdx
  syscall
  movq %rax, -8440(%rbp)
  movq $50397203, %rax
  movq %rax, -8448(%rbp)
  jmp main_assert_pass_81
main_pr_nil_0_5211:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8456(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8456(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8464(%rbp)
  jmp main_pr_next_0_5211
main_pr_str_0_5211:
  movq -8400(%rbp), %rax
  addq $8, %rax
  movq %rax, -8472(%rbp)
  movq -8472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8480(%rbp)
  movq -8400(%rbp), %rax
  addq $24, %rax
  movq %rax, -8488(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8488(%rbp), %rsi
  movq -8480(%rbp), %rdx
  syscall
  movq %rax, -8496(%rbp)
  jmp main_pr_next_0_5211
main_pr_next_0_5211:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8504(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8504(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8512(%rbp)
  movq $0, %rax
  movq -1904(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_83(%rip), %rax
  movq -1920(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8520(%rbp)
  movq -1816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8528(%rbp)
  movq -8520(%rbp), %rdi
  movq -8528(%rbp), %rsi
  call lm_rt_str_format
  mov -8536(%rbp), rax
  movq -8536(%rbp), %rax
  movq -1912(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8544(%rbp)
  movq -8544(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8552(%rbp)
  movq -8552(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5368
  jmp main_pr_str_0_5368
main_pr_nil_0_5368:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8560(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8560(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8568(%rbp)
  jmp main_pr_next_0_5368
main_pr_str_0_5368:
  movq -8544(%rbp), %rax
  addq $8, %rax
  movq %rax, -8576(%rbp)
  movq -8576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8584(%rbp)
  movq -8544(%rbp), %rax
  addq $24, %rax
  movq %rax, -8592(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8592(%rbp), %rsi
  movq -8584(%rbp), %rdx
  syscall
  movq %rax, -8600(%rbp)
  jmp main_pr_next_0_5368
main_pr_next_0_5368:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8608(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8608(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8616(%rbp)
  movq $0, %rax
  movq -1928(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_84(%rip), %rax
  movq -1936(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8624(%rbp)
  movq -8624(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8632(%rbp)
  movq -8632(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2567
  jmp main_pr_str_0_2567
main_pr_nil_0_2567:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8640(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8640(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8648(%rbp)
  jmp main_pr_next_0_2567
main_pr_str_0_2567:
  movq -8624(%rbp), %rax
  addq $8, %rax
  movq %rax, -8656(%rbp)
  movq -8656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8664(%rbp)
  movq -8624(%rbp), %rax
  addq $24, %rax
  movq %rax, -8672(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8672(%rbp), %rsi
  movq -8664(%rbp), %rdx
  syscall
  movq %rax, -8680(%rbp)
  jmp main_pr_next_0_2567
main_pr_next_0_2567:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8688(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8688(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8696(%rbp)
  movq $0, %rax
  movq -1944(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -8704(%rbp), rax
  movq -8704(%rbp), %rax
  movq -1952(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8712(%rbp)
  movq -1960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8720(%rbp)
  movq -8712(%rbp), %rdi
  movq -8720(%rbp), %rsi
  call lm_list_append
  mov -8728(%rbp), rax
  movq $2, %rax
  movq -1976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8736(%rbp)
  movq -1976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8744(%rbp)
  movq -8736(%rbp), %rdi
  movq -8744(%rbp), %rsi
  call lm_list_append
  mov -8752(%rbp), rax
  movq $3, %rax
  movq -1992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8760(%rbp)
  movq -1992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8768(%rbp)
  movq -8760(%rbp), %rdi
  movq -8768(%rbp), %rsi
  call lm_list_append
  mov -8776(%rbp), rax
  movq $4, %rax
  movq -2008(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8784(%rbp)
  movq -2008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8792(%rbp)
  movq -8784(%rbp), %rdi
  movq -8792(%rbp), %rsi
  call lm_list_append
  mov -8800(%rbp), rax
  movq $5, %rax
  movq -2024(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8808(%rbp)
  movq -2024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8816(%rbp)
  movq -8808(%rbp), %rdi
  movq -8816(%rbp), %rsi
  call lm_list_append
  mov -8824(%rbp), rax
  movq -1952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8832(%rbp)
  movq -8832(%rbp), %rdi
  call testSpreadDestructuring
  mov -8840(%rbp), rax
  movq -8840(%rbp), %rax
  movq -2040(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8848(%rbp)
  movq -8848(%rbp), %rax
  movq -2048(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -8856(%rbp), rax
  movq -8856(%rbp), %rax
  movq -2056(%rbp), %rdx
  movq %rax, (%rdx)
  movq $100, %rax
  movq -2064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8864(%rbp)
  movq -2064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8872(%rbp)
  movq -8864(%rbp), %rdi
  movq -8872(%rbp), %rsi
  call lm_list_append
  mov -8880(%rbp), rax
  movq -2056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8888(%rbp)
  movq -8888(%rbp), %rdi
  call testSpreadDestructuring
  mov -8896(%rbp), rax
  movq -8896(%rbp), %rax
  movq -2080(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8904(%rbp)
  movq -8904(%rbp), %rax
  movq -2088(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_85(%rip), %rax
  movq -2096(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8912(%rbp)
  movq -2096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8920(%rbp)
  movq -8912(%rbp), %rdi
  movq -8920(%rbp), %rsi
  call lm_key_eq
  mov -8928(%rbp), rax
  movq -8928(%rbp), %rax
  movq -2104(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_86(%rip), %rax
  movq -2112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8936(%rbp)
  movq -2112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8944(%rbp)
  movq -8936(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_87
  jmp main_assert_fail_87
main_assert_pass_87:
  movq $0, %rax
  movq -2120(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_88(%rip), %rax
  movq -2128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8952(%rbp)
  movq -2128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8960(%rbp)
  movq -8952(%rbp), %rdi
  movq -8960(%rbp), %rsi
  call lm_key_eq
  mov -8968(%rbp), rax
  movq -8968(%rbp), %rax
  movq -2136(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_89(%rip), %rax
  movq -2144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8976(%rbp)
  movq -2144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8984(%rbp)
  movq -8976(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_90
  jmp main_assert_fail_90
main_assert_fail_87:
  movq -8944(%rbp), %rax
  addq $8, %rax
  movq %rax, -8992(%rbp)
  movq -8992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9000(%rbp)
  movq -8944(%rbp), %rax
  addq $24, %rax
  movq %rax, -9008(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9008(%rbp), %rsi
  movq -9000(%rbp), %rdx
  syscall
  movq %rax, -9016(%rbp)
  movq $50397203, %rax
  movq %rax, -9024(%rbp)
  jmp main_assert_pass_87
main_assert_pass_90:
  movq $0, %rax
  movq -2152(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_91(%rip), %rax
  movq -2168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9032(%rbp)
  movq -2048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9040(%rbp)
  movq -9032(%rbp), %rdi
  movq -9040(%rbp), %rsi
  call lm_rt_str_format
  mov -9048(%rbp), rax
  movq -9048(%rbp), %rax
  movq -2160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9056(%rbp)
  movq -9056(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9064(%rbp)
  movq -9064(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6429
  jmp main_pr_str_0_6429
main_assert_fail_90:
  movq -8984(%rbp), %rax
  addq $8, %rax
  movq %rax, -9072(%rbp)
  movq -9072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9080(%rbp)
  movq -8984(%rbp), %rax
  addq $24, %rax
  movq %rax, -9088(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9088(%rbp), %rsi
  movq -9080(%rbp), %rdx
  syscall
  movq %rax, -9096(%rbp)
  movq $50397203, %rax
  movq %rax, -9104(%rbp)
  jmp main_assert_pass_90
main_pr_nil_0_6429:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9112(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9112(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9120(%rbp)
  jmp main_pr_next_0_6429
main_pr_str_0_6429:
  movq -9056(%rbp), %rax
  addq $8, %rax
  movq %rax, -9128(%rbp)
  movq -9128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9136(%rbp)
  movq -9056(%rbp), %rax
  addq $24, %rax
  movq %rax, -9144(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9144(%rbp), %rsi
  movq -9136(%rbp), %rdx
  syscall
  movq %rax, -9152(%rbp)
  jmp main_pr_next_0_6429
main_pr_next_0_6429:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9160(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9168(%rbp)
  movq $0, %rax
  movq -2176(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_92(%rip), %rax
  movq -2192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9176(%rbp)
  movq -2088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9184(%rbp)
  movq -9176(%rbp), %rdi
  movq -9184(%rbp), %rsi
  call lm_rt_str_format
  mov -9192(%rbp), rax
  movq -9192(%rbp), %rax
  movq -2184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9200(%rbp)
  movq -9200(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9208(%rbp)
  movq -9208(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5782
  jmp main_pr_str_0_5782
main_pr_nil_0_5782:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9216(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9216(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9224(%rbp)
  jmp main_pr_next_0_5782
main_pr_str_0_5782:
  movq -9200(%rbp), %rax
  addq $8, %rax
  movq %rax, -9232(%rbp)
  movq -9232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9240(%rbp)
  movq -9200(%rbp), %rax
  addq $24, %rax
  movq %rax, -9248(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9248(%rbp), %rsi
  movq -9240(%rbp), %rdx
  syscall
  movq %rax, -9256(%rbp)
  jmp main_pr_next_0_5782
main_pr_next_0_5782:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9264(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9264(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9272(%rbp)
  movq $0, %rax
  movq -2200(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_93(%rip), %rax
  movq -2208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9280(%rbp)
  movq -9280(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9288(%rbp)
  movq -9288(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1530
  jmp main_pr_str_0_1530
main_pr_nil_0_1530:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9296(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9296(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9304(%rbp)
  jmp main_pr_next_0_1530
main_pr_str_0_1530:
  movq -9280(%rbp), %rax
  addq $8, %rax
  movq %rax, -9312(%rbp)
  movq -9312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9320(%rbp)
  movq -9280(%rbp), %rax
  addq $24, %rax
  movq %rax, -9328(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9328(%rbp), %rsi
  movq -9320(%rbp), %rdx
  syscall
  movq %rax, -9336(%rbp)
  jmp main_pr_next_0_1530
main_pr_next_0_1530:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9344(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9352(%rbp)
  movq $0, %rax
  movq -2216(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  call lm_tuple_new
  mov -9360(%rbp), rax
  movq -9360(%rbp), %rax
  movq -2224(%rbp), %rdx
  movq %rax, (%rdx)
  movq $99, %rax
  movq -2232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -2240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9368(%rbp)
  movq -2240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9376(%rbp)
  movq -2232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9384(%rbp)
  movq -9368(%rbp), %rdi
  movq -9376(%rbp), %rsi
  movq -9384(%rbp), %rdx
  call lm_tuple_set
  mov -9392(%rbp), rax
  movq $0, %rdi
  call lm_list_new
  mov -9400(%rbp), rax
  movq -9400(%rbp), %rax
  movq -2248(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -2256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9408(%rbp)
  movq -2256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9416(%rbp)
  movq -9408(%rbp), %rdi
  movq -9416(%rbp), %rsi
  call lm_list_append
  mov -9424(%rbp), rax
  movq $2, %rax
  movq -2272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9432(%rbp)
  movq -2272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9440(%rbp)
  movq -9432(%rbp), %rdi
  movq -9440(%rbp), %rsi
  call lm_list_append
  mov -9448(%rbp), rax
  movq $3, %rax
  movq -2288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9456(%rbp)
  movq -2288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9464(%rbp)
  movq -9456(%rbp), %rdi
  movq -9464(%rbp), %rsi
  call lm_list_append
  mov -9472(%rbp), rax
  movq $1, %rax
  movq -2304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9480(%rbp)
  movq -2304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9488(%rbp)
  movq -2248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9496(%rbp)
  movq -9480(%rbp), %rdi
  movq -9488(%rbp), %rsi
  movq -9496(%rbp), %rdx
  call lm_tuple_set
  mov -9504(%rbp), rax
  movq -2224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9512(%rbp)
  movq -9512(%rbp), %rdi
  call testNestedTupleList
  mov -9520(%rbp), rax
  movq -9520(%rbp), %rax
  movq -2312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9528(%rbp)
  movq -9528(%rbp), %rax
  movq -2320(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_94(%rip), %rax
  movq -2328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9536(%rbp)
  movq -2328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9544(%rbp)
  movq -9536(%rbp), %rdi
  movq -9544(%rbp), %rsi
  call lm_key_eq
  mov -9552(%rbp), rax
  movq -9552(%rbp), %rax
  movq -2336(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_95(%rip), %rax
  movq -2344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9560(%rbp)
  movq -2344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9568(%rbp)
  movq -9560(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_96
  jmp main_assert_fail_96
main_assert_pass_96:
  movq $0, %rax
  movq -2352(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_97(%rip), %rax
  movq -2368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9576(%rbp)
  movq -2320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9584(%rbp)
  movq -9576(%rbp), %rdi
  movq -9584(%rbp), %rsi
  call lm_rt_str_format
  mov -9592(%rbp), rax
  movq -9592(%rbp), %rax
  movq -2360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9600(%rbp)
  movq -9600(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9608(%rbp)
  movq -9608(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2862
  jmp main_pr_str_0_2862
main_assert_fail_96:
  movq -9568(%rbp), %rax
  addq $8, %rax
  movq %rax, -9616(%rbp)
  movq -9616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9624(%rbp)
  movq -9568(%rbp), %rax
  addq $24, %rax
  movq %rax, -9632(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9632(%rbp), %rsi
  movq -9624(%rbp), %rdx
  syscall
  movq %rax, -9640(%rbp)
  movq $50397203, %rax
  movq %rax, -9648(%rbp)
  jmp main_assert_pass_96
main_pr_nil_0_2862:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9656(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9656(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9664(%rbp)
  jmp main_pr_next_0_2862
main_pr_str_0_2862:
  movq -9600(%rbp), %rax
  addq $8, %rax
  movq %rax, -9672(%rbp)
  movq -9672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9680(%rbp)
  movq -9600(%rbp), %rax
  addq $24, %rax
  movq %rax, -9688(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9688(%rbp), %rsi
  movq -9680(%rbp), %rdx
  syscall
  movq %rax, -9696(%rbp)
  jmp main_pr_next_0_2862
main_pr_next_0_2862:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9704(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9704(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9712(%rbp)
  movq $0, %rax
  movq -2376(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_98(%rip), %rax
  movq -2384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9720(%rbp)
  movq -9720(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9728(%rbp)
  movq -9728(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5123
  jmp main_pr_str_0_5123
main_pr_nil_0_5123:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9736(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9736(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9744(%rbp)
  jmp main_pr_next_0_5123
main_pr_str_0_5123:
  movq -9720(%rbp), %rax
  addq $8, %rax
  movq %rax, -9752(%rbp)
  movq -9752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9760(%rbp)
  movq -9720(%rbp), %rax
  addq $24, %rax
  movq %rax, -9768(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9768(%rbp), %rsi
  movq -9760(%rbp), %rdx
  syscall
  movq %rax, -9776(%rbp)
  jmp main_pr_next_0_5123
main_pr_next_0_5123:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9784(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9784(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9792(%rbp)
  movq $0, %rax
  movq -2392(%rbp), %rdx
  movq %rax, (%rdx)
  call lm_dict_new
  mov -9800(%rbp), rax
  movq -9800(%rbp), %rax
  movq -2400(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_99(%rip), %rax
  movq -2408(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_100(%rip), %rax
  movq -2416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9808(%rbp)
  movq -2408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9816(%rbp)
  movq -2416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9824(%rbp)
  movq -9808(%rbp), %rdi
  movq -9816(%rbp), %rsi
  movq -9824(%rbp), %rdx
  call lm_dict_set
  mov -9832(%rbp), rax
  leaq str_hdr_101(%rip), %rax
  movq -2424(%rbp), %rdx
  movq %rax, (%rdx)
  movq $30, %rax
  movq -2432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9840(%rbp)
  movq -2424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9848(%rbp)
  movq -2432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9856(%rbp)
  movq -9840(%rbp), %rdi
  movq -9848(%rbp), %rsi
  movq -9856(%rbp), %rdx
  call lm_dict_set
  mov -9864(%rbp), rax
  leaq str_hdr_102(%rip), %rax
  movq -2440(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_103(%rip), %rax
  movq -2448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9872(%rbp)
  movq -2440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9880(%rbp)
  movq -2448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9888(%rbp)
  movq -9872(%rbp), %rdi
  movq -9880(%rbp), %rsi
  movq -9888(%rbp), %rdx
  call lm_dict_set
  mov -9896(%rbp), rax
  movq -2400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9904(%rbp)
  movq -9904(%rbp), %rdi
  call testOptionalFields
  mov -9912(%rbp), rax
  movq -9912(%rbp), %rax
  movq -2456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9920(%rbp)
  movq -9920(%rbp), %rax
  movq -2464(%rbp), %rdx
  movq %rax, (%rdx)
  call lm_dict_new
  mov -9928(%rbp), rax
  movq -9928(%rbp), %rax
  movq -2472(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_104(%rip), %rax
  movq -2480(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_105(%rip), %rax
  movq -2488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9936(%rbp)
  movq -2480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9944(%rbp)
  movq -2488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9952(%rbp)
  movq -9936(%rbp), %rdi
  movq -9944(%rbp), %rsi
  movq -9952(%rbp), %rdx
  call lm_dict_set
  mov -9960(%rbp), rax
  leaq str_hdr_106(%rip), %rax
  movq -2496(%rbp), %rdx
  movq %rax, (%rdx)
  movq $25, %rax
  movq -2504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9968(%rbp)
  movq -2496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9976(%rbp)
  movq -2504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9984(%rbp)
  movq -9968(%rbp), %rdi
  movq -9976(%rbp), %rsi
  movq -9984(%rbp), %rdx
  call lm_dict_set
  mov -9992(%rbp), rax
  movq -2472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10000(%rbp)
  movq -10000(%rbp), %rdi
  call testOptionalFields
  mov -10008(%rbp), rax
  movq -10008(%rbp), %rax
  movq -2512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10016(%rbp)
  movq -10016(%rbp), %rax
  movq -2520(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_107(%rip), %rax
  movq -2528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10024(%rbp)
  movq -2528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10032(%rbp)
  movq -10024(%rbp), %rdi
  movq -10032(%rbp), %rsi
  call lm_key_eq
  mov -10040(%rbp), rax
  movq -10040(%rbp), %rax
  movq -2536(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_108(%rip), %rax
  movq -2544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10048(%rbp)
  movq -2544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10056(%rbp)
  movq -10048(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_109
  jmp main_assert_fail_109
main_assert_pass_109:
  movq $0, %rax
  movq -2552(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_110(%rip), %rax
  movq -2560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10064(%rbp)
  movq -2560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10072(%rbp)
  movq -10064(%rbp), %rdi
  movq -10072(%rbp), %rsi
  call lm_key_eq
  mov -10080(%rbp), rax
  movq -10080(%rbp), %rax
  movq -2568(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_111(%rip), %rax
  movq -2576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10088(%rbp)
  movq -2576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10096(%rbp)
  movq -10088(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_112
  jmp main_assert_fail_112
main_assert_fail_109:
  movq -10056(%rbp), %rax
  addq $8, %rax
  movq %rax, -10104(%rbp)
  movq -10104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10112(%rbp)
  movq -10056(%rbp), %rax
  addq $24, %rax
  movq %rax, -10120(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10120(%rbp), %rsi
  movq -10112(%rbp), %rdx
  syscall
  movq %rax, -10128(%rbp)
  movq $50397203, %rax
  movq %rax, -10136(%rbp)
  jmp main_assert_pass_109
main_assert_pass_112:
  movq $0, %rax
  movq -2584(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_113(%rip), %rax
  movq -2600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10144(%rbp)
  movq -2464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10152(%rbp)
  movq -10144(%rbp), %rdi
  movq -10152(%rbp), %rsi
  call lm_rt_str_format
  mov -10160(%rbp), rax
  movq -10160(%rbp), %rax
  movq -2592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10168(%rbp)
  movq -10168(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10176(%rbp)
  movq -10176(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_4067
  jmp main_pr_str_0_4067
main_assert_fail_112:
  movq -10096(%rbp), %rax
  addq $8, %rax
  movq %rax, -10184(%rbp)
  movq -10184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10192(%rbp)
  movq -10096(%rbp), %rax
  addq $24, %rax
  movq %rax, -10200(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10200(%rbp), %rsi
  movq -10192(%rbp), %rdx
  syscall
  movq %rax, -10208(%rbp)
  movq $50397203, %rax
  movq %rax, -10216(%rbp)
  jmp main_assert_pass_112
main_pr_nil_0_4067:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10224(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10224(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10232(%rbp)
  jmp main_pr_next_0_4067
main_pr_str_0_4067:
  movq -10168(%rbp), %rax
  addq $8, %rax
  movq %rax, -10240(%rbp)
  movq -10240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10248(%rbp)
  movq -10168(%rbp), %rax
  addq $24, %rax
  movq %rax, -10256(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10256(%rbp), %rsi
  movq -10248(%rbp), %rdx
  syscall
  movq %rax, -10264(%rbp)
  jmp main_pr_next_0_4067
main_pr_next_0_4067:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10272(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10272(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10280(%rbp)
  movq $0, %rax
  movq -2608(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_114(%rip), %rax
  movq -2624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10288(%rbp)
  movq -2520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10296(%rbp)
  movq -10288(%rbp), %rdi
  movq -10296(%rbp), %rsi
  call lm_rt_str_format
  mov -10304(%rbp), rax
  movq -10304(%rbp), %rax
  movq -2616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10312(%rbp)
  movq -10312(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10320(%rbp)
  movq -10320(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3135
  jmp main_pr_str_0_3135
main_pr_nil_0_3135:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10328(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10328(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10336(%rbp)
  jmp main_pr_next_0_3135
main_pr_str_0_3135:
  movq -10312(%rbp), %rax
  addq $8, %rax
  movq %rax, -10344(%rbp)
  movq -10344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10352(%rbp)
  movq -10312(%rbp), %rax
  addq $24, %rax
  movq %rax, -10360(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10360(%rbp), %rsi
  movq -10352(%rbp), %rdx
  syscall
  movq %rax, -10368(%rbp)
  jmp main_pr_next_0_3135
main_pr_next_0_3135:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10376(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10376(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10384(%rbp)
  movq $0, %rax
  movq -2632(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_115(%rip), %rax
  movq -2640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10392(%rbp)
  movq -10392(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10400(%rbp)
  movq -10400(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3929
  jmp main_pr_str_0_3929
main_pr_nil_0_3929:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10408(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10408(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10416(%rbp)
  jmp main_pr_next_0_3929
main_pr_str_0_3929:
  movq -10392(%rbp), %rax
  addq $8, %rax
  movq %rax, -10424(%rbp)
  movq -10424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10432(%rbp)
  movq -10392(%rbp), %rax
  addq $24, %rax
  movq %rax, -10440(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10440(%rbp), %rsi
  movq -10432(%rbp), %rdx
  syscall
  movq %rax, -10448(%rbp)
  jmp main_pr_next_0_3929
main_pr_next_0_3929:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10456(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10456(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10464(%rbp)
  movq $0, %rax
  movq -2648(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  call lm_tuple_new
  mov -10472(%rbp), rax
  movq -10472(%rbp), %rax
  movq -2656(%rbp), %rdx
  movq %rax, (%rdx)
  movq $42, %rax
  movq -2664(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -2672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10480(%rbp)
  movq -2672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10488(%rbp)
  movq -2664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10496(%rbp)
  movq -10480(%rbp), %rdi
  movq -10488(%rbp), %rsi
  movq -10496(%rbp), %rdx
  call lm_tuple_set
  mov -10504(%rbp), rax
  call lm_dict_new
  mov -10512(%rbp), rax
  movq -10512(%rbp), %rax
  movq -2680(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_116(%rip), %rax
  movq -2688(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_117(%rip), %rax
  movq -2696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10520(%rbp)
  movq -2688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10528(%rbp)
  movq -2696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10536(%rbp)
  movq -10520(%rbp), %rdi
  movq -10528(%rbp), %rsi
  movq -10536(%rbp), %rdx
  call lm_dict_set
  mov -10544(%rbp), rax
  leaq str_hdr_118(%rip), %rax
  movq -2704(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -10552(%rbp), rax
  movq -10552(%rbp), %rax
  movq -2712(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -2720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10560(%rbp)
  movq -2720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10568(%rbp)
  movq -10560(%rbp), %rdi
  movq -10568(%rbp), %rsi
  call lm_list_append
  mov -10576(%rbp), rax
  movq $20, %rax
  movq -2736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10584(%rbp)
  movq -2736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10592(%rbp)
  movq -10584(%rbp), %rdi
  movq -10592(%rbp), %rsi
  call lm_list_append
  mov -10600(%rbp), rax
  movq -2680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10608(%rbp)
  movq -2704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10616(%rbp)
  movq -2712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10624(%rbp)
  movq -10608(%rbp), %rdi
  movq -10616(%rbp), %rsi
  movq -10624(%rbp), %rdx
  call lm_dict_set
  mov -10632(%rbp), rax
  movq $1, %rax
  movq -2752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10640(%rbp)
  movq -2752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10648(%rbp)
  movq -2680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10656(%rbp)
  movq -10640(%rbp), %rdi
  movq -10648(%rbp), %rsi
  movq -10656(%rbp), %rdx
  call lm_tuple_set
  mov -10664(%rbp), rax
  movq -2656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10672(%rbp)
  movq -10672(%rbp), %rdi
  call testComplexNested
  mov -10680(%rbp), rax
  movq -10680(%rbp), %rax
  movq -2760(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10688(%rbp)
  movq -10688(%rbp), %rax
  movq -2768(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_119(%rip), %rax
  movq -2776(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10696(%rbp)
  movq -2776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10704(%rbp)
  movq -10696(%rbp), %rdi
  movq -10704(%rbp), %rsi
  call lm_key_eq
  mov -10712(%rbp), rax
  movq -10712(%rbp), %rax
  movq -2784(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_120(%rip), %rax
  movq -2792(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10720(%rbp)
  movq -2792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10728(%rbp)
  movq -10720(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_121
  jmp main_assert_fail_121
main_assert_pass_121:
  movq $0, %rax
  movq -2800(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_122(%rip), %rax
  movq -2816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10736(%rbp)
  movq -2768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10744(%rbp)
  movq -10736(%rbp), %rdi
  movq -10744(%rbp), %rsi
  call lm_rt_str_format
  mov -10752(%rbp), rax
  movq -10752(%rbp), %rax
  movq -2808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10760(%rbp)
  movq -10760(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10768(%rbp)
  movq -10768(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9802
  jmp main_pr_str_0_9802
main_assert_fail_121:
  movq -10728(%rbp), %rax
  addq $8, %rax
  movq %rax, -10776(%rbp)
  movq -10776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10784(%rbp)
  movq -10728(%rbp), %rax
  addq $24, %rax
  movq %rax, -10792(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10792(%rbp), %rsi
  movq -10784(%rbp), %rdx
  syscall
  movq %rax, -10800(%rbp)
  movq $50397203, %rax
  movq %rax, -10808(%rbp)
  jmp main_assert_pass_121
main_pr_nil_0_9802:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10816(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10816(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10824(%rbp)
  jmp main_pr_next_0_9802
main_pr_str_0_9802:
  movq -10760(%rbp), %rax
  addq $8, %rax
  movq %rax, -10832(%rbp)
  movq -10832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10840(%rbp)
  movq -10760(%rbp), %rax
  addq $24, %rax
  movq %rax, -10848(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10848(%rbp), %rsi
  movq -10840(%rbp), %rdx
  syscall
  movq %rax, -10856(%rbp)
  jmp main_pr_next_0_9802
main_pr_next_0_9802:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10864(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10864(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10872(%rbp)
  movq $0, %rax
  movq -2824(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_123(%rip), %rax
  movq -2832(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10880(%rbp)
  movq -10880(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10888(%rbp)
  movq -10888(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_4022
  jmp main_pr_str_0_4022
main_pr_nil_0_4022:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10896(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10896(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10904(%rbp)
  jmp main_pr_next_0_4022
main_pr_str_0_4022:
  movq -10880(%rbp), %rax
  addq $8, %rax
  movq %rax, -10912(%rbp)
  movq -10912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10920(%rbp)
  movq -10880(%rbp), %rax
  addq $24, %rax
  movq %rax, -10928(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10928(%rbp), %rsi
  movq -10920(%rbp), %rdx
  syscall
  movq %rax, -10936(%rbp)
  jmp main_pr_next_0_4022
main_pr_next_0_4022:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10944(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10944(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10952(%rbp)
  movq $0, %rax
  movq -2840(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -2848(%rbp), %rdx
  movq %rax, (%rdx)
  movq $20, %rax
  movq -2856(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  call lm_tuple_new
  mov -10960(%rbp), rax
  movq -10960(%rbp), %rax
  movq -2872(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -2880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10968(%rbp)
  movq -2880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10976(%rbp)
  movq -2848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10984(%rbp)
  movq -10968(%rbp), %rdi
  movq -10976(%rbp), %rsi
  movq -10984(%rbp), %rdx
  call lm_tuple_set
  mov -10992(%rbp), rax
  movq $1, %rax
  movq -2888(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11000(%rbp)
  movq -2888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11008(%rbp)
  movq -2856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11016(%rbp)
  movq -11000(%rbp), %rdi
  movq -11008(%rbp), %rsi
  movq -11016(%rbp), %rdx
  call lm_tuple_set
  mov -11024(%rbp), rax
  movq -2872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11032(%rbp)
  movq $0, %rdi
  movq -11032(%rbp), %rsi
  leaq vname_Move(%rip), %rdx
  call lm_enum_new
  mov -11040(%rbp), rax
  movq -11040(%rbp), %rax
  movq -2864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11048(%rbp)
  movq -11048(%rbp), %rdi
  call processCommand
  mov -11056(%rbp), rax
  movq -11056(%rbp), %rax
  movq -2896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11064(%rbp)
  movq -11064(%rbp), %rax
  movq -2904(%rbp), %rdx
  movq %rax, (%rdx)
  movq $100, %rax
  movq -2912(%rbp), %rdx
  movq %rax, (%rdx)
  movq $200, %rax
  movq -2920(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  call lm_tuple_new
  mov -11072(%rbp), rax
  movq -11072(%rbp), %rax
  movq -2936(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -2944(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11080(%rbp)
  movq -2944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11088(%rbp)
  movq -2912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11096(%rbp)
  movq -11080(%rbp), %rdi
  movq -11088(%rbp), %rsi
  movq -11096(%rbp), %rdx
  call lm_tuple_set
  mov -11104(%rbp), rax
  movq $1, %rax
  movq -2952(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11112(%rbp)
  movq -2952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11120(%rbp)
  movq -2920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11128(%rbp)
  movq -11112(%rbp), %rdi
  movq -11120(%rbp), %rsi
  movq -11128(%rbp), %rdx
  call lm_tuple_set
  mov -11136(%rbp), rax
  movq -2936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11144(%rbp)
  movq $1, %rdi
  movq -11144(%rbp), %rsi
  leaq vname_Resize(%rip), %rdx
  call lm_enum_new
  mov -11152(%rbp), rax
  movq -11152(%rbp), %rax
  movq -2928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11160(%rbp)
  movq -11160(%rbp), %rdi
  call processCommand
  mov -11168(%rbp), rax
  movq -11168(%rbp), %rax
  movq -2960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11176(%rbp)
  movq -11176(%rbp), %rax
  movq -2968(%rbp), %rdx
  movq %rax, (%rdx)
  movq $255, %rax
  movq -2976(%rbp), %rdx
  movq %rax, (%rdx)
  movq $128, %rax
  movq -2984(%rbp), %rdx
  movq %rax, (%rdx)
  movq $64, %rax
  movq -2992(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rdi
  call lm_tuple_new
  mov -11184(%rbp), rax
  movq -11184(%rbp), %rax
  movq -3008(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -3016(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11192(%rbp)
  movq -3016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11200(%rbp)
  movq -2976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11208(%rbp)
  movq -11192(%rbp), %rdi
  movq -11200(%rbp), %rsi
  movq -11208(%rbp), %rdx
  call lm_tuple_set
  mov -11216(%rbp), rax
  movq $1, %rax
  movq -3024(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11224(%rbp)
  movq -3024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11232(%rbp)
  movq -2984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11240(%rbp)
  movq -11224(%rbp), %rdi
  movq -11232(%rbp), %rsi
  movq -11240(%rbp), %rdx
  call lm_tuple_set
  mov -11248(%rbp), rax
  movq $2, %rax
  movq -3032(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11256(%rbp)
  movq -3032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11264(%rbp)
  movq -2992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11272(%rbp)
  movq -11256(%rbp), %rdi
  movq -11264(%rbp), %rsi
  movq -11272(%rbp), %rdx
  call lm_tuple_set
  mov -11280(%rbp), rax
  movq -3008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11288(%rbp)
  movq $2, %rdi
  movq -11288(%rbp), %rsi
  leaq vname_Color(%rip), %rdx
  call lm_enum_new
  mov -11296(%rbp), rax
  movq -11296(%rbp), %rax
  movq -3000(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11304(%rbp)
  movq -11304(%rbp), %rdi
  call processCommand
  mov -11312(%rbp), rax
  movq -11312(%rbp), %rax
  movq -3040(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11320(%rbp)
  movq -11320(%rbp), %rax
  movq -3048(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_124(%rip), %rax
  movq -3056(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11328(%rbp)
  movq -3056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11336(%rbp)
  movq -11328(%rbp), %rdi
  movq -11336(%rbp), %rsi
  call lm_key_eq
  mov -11344(%rbp), rax
  movq -11344(%rbp), %rax
  movq -3064(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_125(%rip), %rax
  movq -3072(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11352(%rbp)
  movq -3072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11360(%rbp)
  movq -11352(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_126
  jmp main_assert_fail_126
main_assert_pass_126:
  movq $0, %rax
  movq -3080(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_127(%rip), %rax
  movq -3088(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11368(%rbp)
  movq -3088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11376(%rbp)
  movq -11368(%rbp), %rdi
  movq -11376(%rbp), %rsi
  call lm_key_eq
  mov -11384(%rbp), rax
  movq -11384(%rbp), %rax
  movq -3096(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_128(%rip), %rax
  movq -3104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11392(%rbp)
  movq -3104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11400(%rbp)
  movq -11392(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_129
  jmp main_assert_fail_129
main_assert_fail_126:
  movq -11360(%rbp), %rax
  addq $8, %rax
  movq %rax, -11408(%rbp)
  movq -11408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11416(%rbp)
  movq -11360(%rbp), %rax
  addq $24, %rax
  movq %rax, -11424(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11424(%rbp), %rsi
  movq -11416(%rbp), %rdx
  syscall
  movq %rax, -11432(%rbp)
  movq $50397203, %rax
  movq %rax, -11440(%rbp)
  jmp main_assert_pass_126
main_assert_pass_129:
  movq $0, %rax
  movq -3112(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_130(%rip), %rax
  movq -3120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11448(%rbp)
  movq -3120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11456(%rbp)
  movq -11448(%rbp), %rdi
  movq -11456(%rbp), %rsi
  call lm_key_eq
  mov -11464(%rbp), rax
  movq -11464(%rbp), %rax
  movq -3128(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_131(%rip), %rax
  movq -3136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11472(%rbp)
  movq -3136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11480(%rbp)
  movq -11472(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_132
  jmp main_assert_fail_132
main_assert_fail_129:
  movq -11400(%rbp), %rax
  addq $8, %rax
  movq %rax, -11488(%rbp)
  movq -11488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11496(%rbp)
  movq -11400(%rbp), %rax
  addq $24, %rax
  movq %rax, -11504(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11504(%rbp), %rsi
  movq -11496(%rbp), %rdx
  syscall
  movq %rax, -11512(%rbp)
  movq $50397203, %rax
  movq %rax, -11520(%rbp)
  jmp main_assert_pass_129
main_assert_pass_132:
  movq $0, %rax
  movq -3144(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_133(%rip), %rax
  movq -3160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11528(%rbp)
  movq -2904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11536(%rbp)
  movq -11528(%rbp), %rdi
  movq -11536(%rbp), %rsi
  call lm_rt_str_format
  mov -11544(%rbp), rax
  movq -11544(%rbp), %rax
  movq -3152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11552(%rbp)
  movq -11552(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11560(%rbp)
  movq -11560(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3058
  jmp main_pr_str_0_3058
main_assert_fail_132:
  movq -11480(%rbp), %rax
  addq $8, %rax
  movq %rax, -11568(%rbp)
  movq -11568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11576(%rbp)
  movq -11480(%rbp), %rax
  addq $24, %rax
  movq %rax, -11584(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11584(%rbp), %rsi
  movq -11576(%rbp), %rdx
  syscall
  movq %rax, -11592(%rbp)
  movq $50397203, %rax
  movq %rax, -11600(%rbp)
  jmp main_assert_pass_132
main_pr_nil_0_3058:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -11608(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11608(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -11616(%rbp)
  jmp main_pr_next_0_3058
main_pr_str_0_3058:
  movq -11552(%rbp), %rax
  addq $8, %rax
  movq %rax, -11624(%rbp)
  movq -11624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11632(%rbp)
  movq -11552(%rbp), %rax
  addq $24, %rax
  movq %rax, -11640(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11640(%rbp), %rsi
  movq -11632(%rbp), %rdx
  syscall
  movq %rax, -11648(%rbp)
  jmp main_pr_next_0_3058
main_pr_next_0_3058:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -11656(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11656(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -11664(%rbp)
  movq $0, %rax
  movq -3168(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_134(%rip), %rax
  movq -3184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11672(%rbp)
  movq -2968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11680(%rbp)
  movq -11672(%rbp), %rdi
  movq -11680(%rbp), %rsi
  call lm_rt_str_format
  mov -11688(%rbp), rax
  movq -11688(%rbp), %rax
  movq -3176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11696(%rbp)
  movq -11696(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11704(%rbp)
  movq -11704(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3069
  jmp main_pr_str_0_3069
main_pr_nil_0_3069:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -11712(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11712(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -11720(%rbp)
  jmp main_pr_next_0_3069
main_pr_str_0_3069:
  movq -11696(%rbp), %rax
  addq $8, %rax
  movq %rax, -11728(%rbp)
  movq -11728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11736(%rbp)
  movq -11696(%rbp), %rax
  addq $24, %rax
  movq %rax, -11744(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11744(%rbp), %rsi
  movq -11736(%rbp), %rdx
  syscall
  movq %rax, -11752(%rbp)
  jmp main_pr_next_0_3069
main_pr_next_0_3069:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -11760(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11760(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -11768(%rbp)
  movq $0, %rax
  movq -3192(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_135(%rip), %rax
  movq -3208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11776(%rbp)
  movq -3048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11784(%rbp)
  movq -11776(%rbp), %rdi
  movq -11784(%rbp), %rsi
  call lm_rt_str_format
  mov -11792(%rbp), rax
  movq -11792(%rbp), %rax
  movq -3200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11800(%rbp)
  movq -11800(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11808(%rbp)
  movq -11808(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8167
  jmp main_pr_str_0_8167
main_pr_nil_0_8167:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -11816(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11816(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -11824(%rbp)
  jmp main_pr_next_0_8167
main_pr_str_0_8167:
  movq -11800(%rbp), %rax
  addq $8, %rax
  movq %rax, -11832(%rbp)
  movq -11832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11840(%rbp)
  movq -11800(%rbp), %rax
  addq $24, %rax
  movq %rax, -11848(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11848(%rbp), %rsi
  movq -11840(%rbp), %rdx
  syscall
  movq %rax, -11856(%rbp)
  jmp main_pr_next_0_8167
main_pr_next_0_8167:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -11864(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11864(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -11872(%rbp)
  movq $0, %rax
  movq -3216(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_136(%rip), %rax
  movq -3224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11880(%rbp)
  movq -11880(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11888(%rbp)
  movq -11888(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1393
  jmp main_pr_str_0_1393
main_pr_nil_0_1393:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -11896(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11896(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -11904(%rbp)
  jmp main_pr_next_0_1393
main_pr_str_0_1393:
  movq -11880(%rbp), %rax
  addq $8, %rax
  movq %rax, -11912(%rbp)
  movq -11912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11920(%rbp)
  movq -11880(%rbp), %rax
  addq $24, %rax
  movq %rax, -11928(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11928(%rbp), %rsi
  movq -11920(%rbp), %rdx
  syscall
  movq %rax, -11936(%rbp)
  jmp main_pr_next_0_1393
main_pr_next_0_1393:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -11944(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11944(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -11952(%rbp)
  movq $0, %rax
  movq -3232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  call lm_tuple_new
  mov -11960(%rbp), rax
  movq -11960(%rbp), %rax
  movq -3240(%rbp), %rdx
  movq %rax, (%rdx)
  movq $100, %rax
  movq -3248(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -3256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11968(%rbp)
  movq -3256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11976(%rbp)
  movq -3248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11984(%rbp)
  movq -11968(%rbp), %rdi
  movq -11976(%rbp), %rsi
  movq -11984(%rbp), %rdx
  call lm_tuple_set
  mov -11992(%rbp), rax
  movq $0, %rdi
  call lm_list_new
  mov -12000(%rbp), rax
  movq -12000(%rbp), %rax
  movq -3264(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -3272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12008(%rbp)
  movq -3272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12016(%rbp)
  movq -12008(%rbp), %rdi
  movq -12016(%rbp), %rsi
  call lm_list_append
  mov -12024(%rbp), rax
  movq $20, %rax
  movq -3288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12032(%rbp)
  movq -3288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12040(%rbp)
  movq -12032(%rbp), %rdi
  movq -12040(%rbp), %rsi
  call lm_list_append
  mov -12048(%rbp), rax
  movq $1, %rax
  movq -3304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12056(%rbp)
  movq -3304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12064(%rbp)
  movq -3264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12072(%rbp)
  movq -12056(%rbp), %rdi
  movq -12064(%rbp), %rsi
  movq -12072(%rbp), %rdx
  call lm_tuple_set
  mov -12080(%rbp), rax
  movq -3240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12088(%rbp)
  movq -12088(%rbp), %rdi
  call testNestedDestructure
  mov -12096(%rbp), rax
  movq -12096(%rbp), %rax
  movq -3312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12104(%rbp)
  movq -12104(%rbp), %rax
  movq -3320(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  call lm_tuple_new
  mov -12112(%rbp), rax
  movq -12112(%rbp), %rax
  movq -3328(%rbp), %rdx
  movq %rax, (%rdx)
  movq $200, %rax
  movq -3336(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -3344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12120(%rbp)
  movq -3344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12128(%rbp)
  movq -3336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12136(%rbp)
  movq -12120(%rbp), %rdi
  movq -12128(%rbp), %rsi
  movq -12136(%rbp), %rdx
  call lm_tuple_set
  mov -12144(%rbp), rax
  movq $0, %rdi
  call lm_list_new
  mov -12152(%rbp), rax
  movq -12152(%rbp), %rax
  movq -3352(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -3360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12160(%rbp)
  movq -3360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12168(%rbp)
  movq -12160(%rbp), %rdi
  movq -12168(%rbp), %rsi
  call lm_list_append
  mov -12176(%rbp), rax
  movq $30, %rax
  movq -3376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12184(%rbp)
  movq -3376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12192(%rbp)
  movq -12184(%rbp), %rdi
  movq -12192(%rbp), %rsi
  call lm_list_append
  mov -12200(%rbp), rax
  movq $1, %rax
  movq -3392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12208(%rbp)
  movq -3392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12216(%rbp)
  movq -3352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12224(%rbp)
  movq -12208(%rbp), %rdi
  movq -12216(%rbp), %rsi
  movq -12224(%rbp), %rdx
  call lm_tuple_set
  mov -12232(%rbp), rax
  movq -3328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12240(%rbp)
  movq -12240(%rbp), %rdi
  call testNestedDestructure
  mov -12248(%rbp), rax
  movq -12248(%rbp), %rax
  movq -3400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12256(%rbp)
  movq -12256(%rbp), %rax
  movq -3408(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  call lm_tuple_new
  mov -12264(%rbp), rax
  movq -12264(%rbp), %rax
  movq -3416(%rbp), %rdx
  movq %rax, (%rdx)
  movq $300, %rax
  movq -3424(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -3432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12272(%rbp)
  movq -3432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12280(%rbp)
  movq -3424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12288(%rbp)
  movq -12272(%rbp), %rdi
  movq -12280(%rbp), %rsi
  movq -12288(%rbp), %rdx
  call lm_tuple_set
  mov -12296(%rbp), rax
  movq $0, %rdi
  call lm_list_new
  mov -12304(%rbp), rax
  movq -12304(%rbp), %rax
  movq -3440(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -3448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12312(%rbp)
  movq -3448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12320(%rbp)
  movq -12312(%rbp), %rdi
  movq -12320(%rbp), %rsi
  call lm_list_append
  mov -12328(%rbp), rax
  movq $40, %rax
  movq -3464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12336(%rbp)
  movq -3464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12344(%rbp)
  movq -12336(%rbp), %rdi
  movq -12344(%rbp), %rsi
  call lm_list_append
  mov -12352(%rbp), rax
  movq $1, %rax
  movq -3480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12360(%rbp)
  movq -3480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12368(%rbp)
  movq -3440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12376(%rbp)
  movq -12360(%rbp), %rdi
  movq -12368(%rbp), %rsi
  movq -12376(%rbp), %rdx
  call lm_tuple_set
  mov -12384(%rbp), rax
  movq -3416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12392(%rbp)
  movq -12392(%rbp), %rdi
  call testNestedDestructure
  mov -12400(%rbp), rax
  movq -12400(%rbp), %rax
  movq -3488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12408(%rbp)
  movq -12408(%rbp), %rax
  movq -3496(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_137(%rip), %rax
  movq -3504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12416(%rbp)
  movq -3504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12424(%rbp)
  movq -12416(%rbp), %rdi
  movq -12424(%rbp), %rsi
  call lm_key_eq
  mov -12432(%rbp), rax
  movq -12432(%rbp), %rax
  movq -3512(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_138(%rip), %rax
  movq -3520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12440(%rbp)
  movq -3520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12448(%rbp)
  movq -12440(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_139
  jmp main_assert_fail_139
main_assert_pass_139:
  movq $0, %rax
  movq -3528(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_140(%rip), %rax
  movq -3536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12456(%rbp)
  movq -3536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12464(%rbp)
  movq -12456(%rbp), %rdi
  movq -12464(%rbp), %rsi
  call lm_key_eq
  mov -12472(%rbp), rax
  movq -12472(%rbp), %rax
  movq -3544(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_141(%rip), %rax
  movq -3552(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12480(%rbp)
  movq -3552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12488(%rbp)
  movq -12480(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_142
  jmp main_assert_fail_142
main_assert_fail_139:
  movq -12448(%rbp), %rax
  addq $8, %rax
  movq %rax, -12496(%rbp)
  movq -12496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12504(%rbp)
  movq -12448(%rbp), %rax
  addq $24, %rax
  movq %rax, -12512(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12512(%rbp), %rsi
  movq -12504(%rbp), %rdx
  syscall
  movq %rax, -12520(%rbp)
  movq $50397203, %rax
  movq %rax, -12528(%rbp)
  jmp main_assert_pass_139
main_assert_pass_142:
  movq $0, %rax
  movq -3560(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_143(%rip), %rax
  movq -3568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12536(%rbp)
  movq -3568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12544(%rbp)
  movq -12536(%rbp), %rdi
  movq -12544(%rbp), %rsi
  call lm_key_eq
  mov -12552(%rbp), rax
  movq -12552(%rbp), %rax
  movq -3576(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_144(%rip), %rax
  movq -3584(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12560(%rbp)
  movq -3584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12568(%rbp)
  movq -12560(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_145
  jmp main_assert_fail_145
main_assert_fail_142:
  movq -12488(%rbp), %rax
  addq $8, %rax
  movq %rax, -12576(%rbp)
  movq -12576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12584(%rbp)
  movq -12488(%rbp), %rax
  addq $24, %rax
  movq %rax, -12592(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12592(%rbp), %rsi
  movq -12584(%rbp), %rdx
  syscall
  movq %rax, -12600(%rbp)
  movq $50397203, %rax
  movq %rax, -12608(%rbp)
  jmp main_assert_pass_142
main_assert_pass_145:
  movq $0, %rax
  movq -3592(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_146(%rip), %rax
  movq -3608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12616(%rbp)
  movq -3320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12624(%rbp)
  movq -12616(%rbp), %rdi
  movq -12624(%rbp), %rsi
  call lm_rt_str_format
  mov -12632(%rbp), rax
  movq -12632(%rbp), %rax
  movq -3600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12640(%rbp)
  movq -12640(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -12648(%rbp)
  movq -12648(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8456
  jmp main_pr_str_0_8456
main_assert_fail_145:
  movq -12568(%rbp), %rax
  addq $8, %rax
  movq %rax, -12656(%rbp)
  movq -12656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12664(%rbp)
  movq -12568(%rbp), %rax
  addq $24, %rax
  movq %rax, -12672(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12672(%rbp), %rsi
  movq -12664(%rbp), %rdx
  syscall
  movq %rax, -12680(%rbp)
  movq $50397203, %rax
  movq %rax, -12688(%rbp)
  jmp main_assert_pass_145
main_pr_nil_0_8456:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -12696(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12696(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -12704(%rbp)
  jmp main_pr_next_0_8456
main_pr_str_0_8456:
  movq -12640(%rbp), %rax
  addq $8, %rax
  movq %rax, -12712(%rbp)
  movq -12712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12720(%rbp)
  movq -12640(%rbp), %rax
  addq $24, %rax
  movq %rax, -12728(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12728(%rbp), %rsi
  movq -12720(%rbp), %rdx
  syscall
  movq %rax, -12736(%rbp)
  jmp main_pr_next_0_8456
main_pr_next_0_8456:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -12744(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12744(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -12752(%rbp)
  movq $0, %rax
  movq -3616(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_147(%rip), %rax
  movq -3632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12760(%rbp)
  movq -3408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12768(%rbp)
  movq -12760(%rbp), %rdi
  movq -12768(%rbp), %rsi
  call lm_rt_str_format
  mov -12776(%rbp), rax
  movq -12776(%rbp), %rax
  movq -3624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12784(%rbp)
  movq -12784(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -12792(%rbp)
  movq -12792(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5011
  jmp main_pr_str_0_5011
main_pr_nil_0_5011:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -12800(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12800(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -12808(%rbp)
  jmp main_pr_next_0_5011
main_pr_str_0_5011:
  movq -12784(%rbp), %rax
  addq $8, %rax
  movq %rax, -12816(%rbp)
  movq -12816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12824(%rbp)
  movq -12784(%rbp), %rax
  addq $24, %rax
  movq %rax, -12832(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12832(%rbp), %rsi
  movq -12824(%rbp), %rdx
  syscall
  movq %rax, -12840(%rbp)
  jmp main_pr_next_0_5011
main_pr_next_0_5011:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -12848(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12848(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -12856(%rbp)
  movq $0, %rax
  movq -3640(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_148(%rip), %rax
  movq -3656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12864(%rbp)
  movq -3496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12872(%rbp)
  movq -12864(%rbp), %rdi
  movq -12872(%rbp), %rsi
  call lm_rt_str_format
  mov -12880(%rbp), rax
  movq -12880(%rbp), %rax
  movq -3648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12888(%rbp)
  movq -12888(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -12896(%rbp)
  movq -12896(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8042
  jmp main_pr_str_0_8042
main_pr_nil_0_8042:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -12904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12904(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -12912(%rbp)
  jmp main_pr_next_0_8042
main_pr_str_0_8042:
  movq -12888(%rbp), %rax
  addq $8, %rax
  movq %rax, -12920(%rbp)
  movq -12920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12928(%rbp)
  movq -12888(%rbp), %rax
  addq $24, %rax
  movq %rax, -12936(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12936(%rbp), %rsi
  movq -12928(%rbp), %rdx
  syscall
  movq %rax, -12944(%rbp)
  jmp main_pr_next_0_8042
main_pr_next_0_8042:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -12952(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12952(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -12960(%rbp)
  movq $0, %rax
  movq -3664(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_149(%rip), %rax
  movq -3672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12968(%rbp)
  movq -12968(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -12976(%rbp)
  movq -12976(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6229
  jmp main_pr_str_0_6229
main_pr_nil_0_6229:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -12984(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12984(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -12992(%rbp)
  jmp main_pr_next_0_6229
main_pr_str_0_6229:
  movq -12968(%rbp), %rax
  addq $8, %rax
  movq %rax, -13000(%rbp)
  movq -13000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -13008(%rbp)
  movq -12968(%rbp), %rax
  addq $24, %rax
  movq %rax, -13016(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -13016(%rbp), %rsi
  movq -13008(%rbp), %rdx
  syscall
  movq %rax, -13024(%rbp)
  jmp main_pr_next_0_6229
main_pr_next_0_6229:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -13032(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -13032(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -13040(%rbp)
  movq $0, %rax
  movq -3680(%rbp), %rdx
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

.globl processCommand
processCommand:
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
  subq $1336, %rsp
  movq %rdi, -48(%rbp)
processCommand_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp processCommand_block_0
processCommand_block_0:
  jmp processCommand_block_1
processCommand_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rdi
  call lm_enum_tag
  mov -576(%rbp), rax
  movq -576(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  cmpq -584(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  testq %rax, %rax
  jne processCommand_block_5
  jmp processCommand_block_11
processCommand_block_5:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rdi
  call lm_enum_payload
  mov -624(%rbp), rax
  movq -624(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -632(%rbp), %rdi
  movq -640(%rbp), %rsi
  call lm_tuple_get
  mov -648(%rbp), rax
  movq -648(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -656(%rbp), %rdi
  movq -664(%rbp), %rsi
  call lm_tuple_get
  mov -672(%rbp), rax
  movq -672(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  jmp processCommand_block_57
processCommand_block_11:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rdi
  call lm_enum_tag
  mov -688(%rbp), rax
  movq -688(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -704(%rbp), %rax
  cmpq -696(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -712(%rbp)
  movq -712(%rbp), %rax
  movq -208(%rbp), %rdx
  movl %eax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -720(%rbp), %rax
  testq %rax, %rax
  jne processCommand_block_15
  jmp processCommand_block_21
processCommand_block_15:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -728(%rbp), %rdi
  call lm_enum_payload
  mov -736(%rbp), rax
  movq -736(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -744(%rbp), %rdi
  movq -752(%rbp), %rsi
  call lm_tuple_get
  mov -760(%rbp), rax
  movq -760(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -768(%rbp), %rdi
  movq -776(%rbp), %rsi
  call lm_tuple_get
  mov -784(%rbp), rax
  movq -784(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  jmp processCommand_block_47
processCommand_block_21:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -792(%rbp), %rdi
  call lm_enum_tag
  mov -800(%rbp), rax
  movq -800(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -816(%rbp), %rax
  cmpq -808(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -824(%rbp)
  movq -824(%rbp), %rax
  movq -336(%rbp), %rdx
  movl %eax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -832(%rbp)
  movq -832(%rbp), %rax
  testq %rax, %rax
  jne processCommand_block_25
  jmp processCommand_block_33
processCommand_block_25:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -840(%rbp), %rdi
  call lm_enum_payload
  mov -848(%rbp), rax
  movq -848(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -856(%rbp)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -856(%rbp), %rdi
  movq -864(%rbp), %rsi
  call lm_tuple_get
  mov -872(%rbp), rax
  movq -872(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -880(%rbp), %rdi
  movq -888(%rbp), %rsi
  call lm_tuple_get
  mov -896(%rbp), rax
  movq -896(%rbp), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -912(%rbp)
  movq -904(%rbp), %rdi
  movq -912(%rbp), %rsi
  call lm_tuple_get
  mov -920(%rbp), rax
  movq -920(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  jmp processCommand_block_34
processCommand_block_33:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -928(%rbp)
  movq -928(%rbp), %rax
  jmp processCommand_epilogue
processCommand_block_34:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -936(%rbp), %rdi
  call lm_enum_payload
  mov -944(%rbp), rax
  movq -944(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -960(%rbp)
  movq -952(%rbp), %rdi
  movq -960(%rbp), %rsi
  call lm_tuple_get
  mov -968(%rbp), rax
  movq -968(%rbp), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -984(%rbp)
  movq -976(%rbp), %rdi
  movq -984(%rbp), %rsi
  call lm_tuple_get
  mov -992(%rbp), rax
  movq -992(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1008(%rbp)
  movq -1000(%rbp), %rdi
  movq -1008(%rbp), %rsi
  call lm_tuple_get
  mov -1016(%rbp), rax
  movq -1016(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_150(%rip), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1032(%rbp)
  movq -1024(%rbp), %rdi
  movq -1032(%rbp), %rsi
  call lm_rt_str_format
  mov -1040(%rbp), rax
  movq -1040(%rbp), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1048(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1056(%rbp)
  movq -1048(%rbp), %rdi
  movq -1056(%rbp), %rsi
  call lm_rt_str_format
  mov -1064(%rbp), rax
  movq -1064(%rbp), %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1072(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1080(%rbp)
  movq -1072(%rbp), %rdi
  movq -1080(%rbp), %rsi
  call lm_rt_str_format
  mov -1088(%rbp), rax
  movq -1088(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -1096(%rbp), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1104(%rbp)
  movq -1104(%rbp), %rax
  jmp processCommand_epilogue
processCommand_block_47:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1112(%rbp)
  movq -1112(%rbp), %rdi
  call lm_enum_payload
  mov -1120(%rbp), rax
  movq -1120(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1128(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1136(%rbp)
  movq -1128(%rbp), %rdi
  movq -1136(%rbp), %rsi
  call lm_tuple_get
  mov -1144(%rbp), rax
  movq -1144(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1152(%rbp)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1160(%rbp)
  movq -1152(%rbp), %rdi
  movq -1160(%rbp), %rsi
  call lm_tuple_get
  mov -1168(%rbp), rax
  movq -1168(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_151(%rip), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1176(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1184(%rbp)
  movq -1176(%rbp), %rdi
  movq -1184(%rbp), %rsi
  call lm_rt_str_format
  mov -1192(%rbp), rax
  movq -1192(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1200(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1208(%rbp)
  movq -1200(%rbp), %rdi
  movq -1208(%rbp), %rsi
  call lm_rt_str_format
  mov -1216(%rbp), rax
  movq -1216(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1224(%rbp)
  movq -1224(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1232(%rbp)
  movq -1232(%rbp), %rax
  jmp processCommand_epilogue
processCommand_block_57:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1240(%rbp)
  movq -1240(%rbp), %rdi
  call lm_enum_payload
  mov -1248(%rbp), rax
  movq -1248(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1256(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1264(%rbp)
  movq -1256(%rbp), %rdi
  movq -1264(%rbp), %rsi
  call lm_tuple_get
  mov -1272(%rbp), rax
  movq -1272(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1280(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -1280(%rbp), %rdi
  movq -1288(%rbp), %rsi
  call lm_tuple_get
  mov -1296(%rbp), rax
  movq -1296(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_152(%rip), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1304(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1312(%rbp)
  movq -1304(%rbp), %rdi
  movq -1312(%rbp), %rsi
  call lm_rt_str_format
  mov -1320(%rbp), rax
  movq -1320(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1328(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1336(%rbp)
  movq -1328(%rbp), %rdi
  movq -1336(%rbp), %rsi
  call lm_rt_str_format
  mov -1344(%rbp), rax
  movq -1344(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1352(%rbp)
  movq -1352(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1360(%rbp)
  movq -1360(%rbp), %rax
  jmp processCommand_epilogue
processCommand_epilogue:
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
.Lfunc_end_processCommand:

.globl testComplexNested
testComplexNested:
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
  subq $1048, %rsp
  movq %rdi, -48(%rbp)
testComplexNested_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testComplexNested_block_0
testComplexNested_block_0:
  jmp testComplexNested_block_1
testComplexNested_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rax
  cmpq -480(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  testq %rax, %rax
  jne testComplexNested_block_5
  jmp testComplexNested_block_30
testComplexNested_block_5:
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -512(%rbp), %rdi
  movq -520(%rbp), %rsi
  call lm_tuple_get
  mov -528(%rbp), rax
  movq -528(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -536(%rbp), %rdi
  movq -544(%rbp), %rsi
  call lm_tuple_get
  mov -552(%rbp), rax
  movq -552(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -584(%rbp), %rax
  cmpq -576(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  movq -136(%rbp), %rdx
  movl %eax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  testq %rax, %rax
  jne testComplexNested_block_13
  jmp testComplexNested_block_30
testComplexNested_block_13:
  leaq str_hdr_153(%rip), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -608(%rbp), %rdi
  movq -616(%rbp), %rsi
  call lm_dict_has
  mov -624(%rbp), rax
  movq -624(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -632(%rbp), %rax
  testq %rax, %rax
  jne testComplexNested_block_16
  jmp testComplexNested_block_30
testComplexNested_block_16:
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -640(%rbp), %rdi
  movq -648(%rbp), %rsi
  call lm_dict_get
  mov -656(%rbp), rax
  movq -656(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_154(%rip), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -664(%rbp), %rdi
  movq -672(%rbp), %rsi
  call lm_dict_has
  mov -680(%rbp), rax
  movq -680(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rax
  testq %rax, %rax
  jne testComplexNested_block_20
  jmp testComplexNested_block_30
testComplexNested_block_20:
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -696(%rbp), %rdi
  movq -704(%rbp), %rsi
  call lm_dict_get
  mov -712(%rbp), rax
  movq -712(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -720(%rbp), %rdi
  call lm_list_len
  mov -728(%rbp), rax
  movq -728(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rax
  cmpq -736(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rax
  movq -208(%rbp), %rdx
  movl %eax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -760(%rbp), %rax
  testq %rax, %rax
  jne testComplexNested_block_25
  jmp testComplexNested_block_30
testComplexNested_block_25:
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -768(%rbp), %rdi
  movq -776(%rbp), %rsi
  call lm_list_get
  mov -784(%rbp), rax
  movq -784(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -792(%rbp), %rdi
  movq -800(%rbp), %rsi
  call lm_list_get
  mov -808(%rbp), rax
  movq -808(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testComplexNested_block_31
testComplexNested_block_30:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -816(%rbp), %rax
  jmp testComplexNested_epilogue
testComplexNested_block_31:
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -832(%rbp)
  movq -824(%rbp), %rdi
  movq -832(%rbp), %rsi
  call lm_tuple_get
  mov -840(%rbp), rax
  movq -840(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -856(%rbp)
  movq -848(%rbp), %rdi
  movq -856(%rbp), %rsi
  call lm_tuple_get
  mov -864(%rbp), rax
  movq -864(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_155(%rip), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -872(%rbp), %rdi
  movq -880(%rbp), %rsi
  call lm_dict_get
  mov -888(%rbp), rax
  movq -888(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_156(%rip), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -896(%rbp), %rdi
  movq -904(%rbp), %rsi
  call lm_dict_get
  mov -912(%rbp), rax
  movq -912(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -928(%rbp)
  movq -920(%rbp), %rdi
  movq -928(%rbp), %rsi
  call lm_list_get
  mov -936(%rbp), rax
  movq -936(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -944(%rbp), %rdi
  movq -952(%rbp), %rsi
  call lm_list_get
  mov -960(%rbp), rax
  movq -960(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_157(%rip), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -968(%rbp), %rdi
  movq -976(%rbp), %rsi
  call lm_rt_str_format
  mov -984(%rbp), rax
  movq -984(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -992(%rbp), %rdi
  movq -1000(%rbp), %rsi
  call lm_rt_str_format
  mov -1008(%rbp), rax
  movq -1008(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1016(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -1016(%rbp), %rdi
  movq -1024(%rbp), %rsi
  call lm_rt_str_format
  mov -1032(%rbp), rax
  movq -1032(%rbp), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1048(%rbp)
  movq -1040(%rbp), %rdi
  movq -1048(%rbp), %rsi
  call lm_rt_str_format
  mov -1056(%rbp), rax
  movq -1056(%rbp), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1064(%rbp)
  movq -1064(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1072(%rbp)
  movq -1072(%rbp), %rax
  jmp testComplexNested_epilogue
testComplexNested_epilogue:
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
.Lfunc_end_testComplexNested:

.globl testOptionalFields
testOptionalFields:
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
  subq $1064, %rsp
  movq %rdi, -48(%rbp)
testOptionalFields_entry:
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
  jmp testOptionalFields_block_0
testOptionalFields_block_0:
  jmp testOptionalFields_block_1
testOptionalFields_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  cmpq -464(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -480(%rbp)
  movq -480(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rax
  testq %rax, %rax
  jne testOptionalFields_block_5
  jmp testOptionalFields_block_18
testOptionalFields_block_5:
  leaq str_hdr_158(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -496(%rbp), %rdi
  movq -504(%rbp), %rsi
  call lm_dict_has
  mov -512(%rbp), rax
  movq -512(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  testq %rax, %rax
  jne testOptionalFields_block_8
  jmp testOptionalFields_block_18
testOptionalFields_block_8:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -528(%rbp), %rdi
  movq -536(%rbp), %rsi
  call lm_dict_get
  mov -544(%rbp), rax
  movq -544(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_159(%rip), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -552(%rbp), %rdi
  movq -560(%rbp), %rsi
  call lm_dict_has
  mov -568(%rbp), rax
  movq -568(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -576(%rbp), %rax
  testq %rax, %rax
  jne testOptionalFields_block_12
  jmp testOptionalFields_block_18
testOptionalFields_block_12:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -584(%rbp), %rdi
  movq -592(%rbp), %rsi
  call lm_dict_get
  mov -600(%rbp), rax
  movq -600(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_160(%rip), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -608(%rbp), %rdi
  movq -616(%rbp), %rsi
  call lm_dict_has
  mov -624(%rbp), rax
  movq -624(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -632(%rbp), %rax
  testq %rax, %rax
  jne testOptionalFields_block_16
  jmp testOptionalFields_block_18
testOptionalFields_block_16:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -640(%rbp), %rdi
  movq -648(%rbp), %rsi
  call lm_dict_get
  mov -656(%rbp), rax
  movq -656(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testOptionalFields_block_41
testOptionalFields_block_18:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -672(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rax
  cmpq -680(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -696(%rbp)
  movq -696(%rbp), %rax
  movq -256(%rbp), %rdx
  movl %eax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -704(%rbp), %rax
  testq %rax, %rax
  jne testOptionalFields_block_22
  jmp testOptionalFields_block_31
testOptionalFields_block_22:
  leaq str_hdr_161(%rip), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -712(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -712(%rbp), %rdi
  movq -720(%rbp), %rsi
  call lm_dict_has
  mov -728(%rbp), rax
  movq -728(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -736(%rbp), %rax
  testq %rax, %rax
  jne testOptionalFields_block_25
  jmp testOptionalFields_block_31
testOptionalFields_block_25:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -744(%rbp), %rdi
  movq -752(%rbp), %rsi
  call lm_dict_get
  mov -760(%rbp), rax
  movq -760(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_162(%rip), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -768(%rbp), %rdi
  movq -776(%rbp), %rsi
  call lm_dict_has
  mov -784(%rbp), rax
  movq -784(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -792(%rbp), %rax
  testq %rax, %rax
  jne testOptionalFields_block_29
  jmp testOptionalFields_block_31
testOptionalFields_block_29:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -800(%rbp), %rdi
  movq -808(%rbp), %rsi
  call lm_dict_get
  mov -816(%rbp), rax
  movq -816(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testOptionalFields_block_32
testOptionalFields_block_31:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -824(%rbp), %rax
  jmp testOptionalFields_epilogue
testOptionalFields_block_32:
  leaq str_hdr_163(%rip), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -832(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -832(%rbp), %rdi
  movq -840(%rbp), %rsi
  call lm_dict_get
  mov -848(%rbp), rax
  movq -848(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_164(%rip), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -856(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -856(%rbp), %rdi
  movq -864(%rbp), %rsi
  call lm_dict_get
  mov -872(%rbp), rax
  movq -872(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_165(%rip), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -880(%rbp), %rdi
  movq -888(%rbp), %rsi
  call lm_rt_str_format
  mov -896(%rbp), rax
  movq -896(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -912(%rbp)
  movq -904(%rbp), %rdi
  movq -912(%rbp), %rsi
  call lm_rt_str_format
  mov -920(%rbp), rax
  movq -920(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -928(%rbp)
  movq -928(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -936(%rbp), %rax
  jmp testOptionalFields_epilogue
testOptionalFields_block_41:
  leaq str_hdr_166(%rip), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -944(%rbp), %rdi
  movq -952(%rbp), %rsi
  call lm_dict_get
  mov -960(%rbp), rax
  movq -960(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_167(%rip), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -968(%rbp), %rdi
  movq -976(%rbp), %rsi
  call lm_dict_get
  mov -984(%rbp), rax
  movq -984(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_168(%rip), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -992(%rbp), %rdi
  movq -1000(%rbp), %rsi
  call lm_dict_get
  mov -1008(%rbp), rax
  movq -1008(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_169(%rip), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1016(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -1016(%rbp), %rdi
  movq -1024(%rbp), %rsi
  call lm_rt_str_format
  mov -1032(%rbp), rax
  movq -1032(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1048(%rbp)
  movq -1040(%rbp), %rdi
  movq -1048(%rbp), %rsi
  call lm_rt_str_format
  mov -1056(%rbp), rax
  movq -1056(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1064(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1072(%rbp)
  movq -1064(%rbp), %rdi
  movq -1072(%rbp), %rsi
  call lm_rt_str_format
  mov -1080(%rbp), rax
  movq -1080(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1088(%rbp)
  movq -1088(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -1096(%rbp), %rax
  jmp testOptionalFields_epilogue
testOptionalFields_epilogue:
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
.Lfunc_end_testOptionalFields:

.globl describeShape
describeShape:
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
  subq $1016, %rsp
  movq %rdi, -48(%rbp)
describeShape_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp describeShape_block_0
describeShape_block_0:
  jmp describeShape_block_1
describeShape_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rdi
  call lm_enum_tag
  mov -464(%rbp), rax
  movq -464(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -480(%rbp), %rax
  cmpq -472(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  testq %rax, %rax
  jne describeShape_block_5
  jmp describeShape_block_7
describeShape_block_5:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rdi
  call lm_enum_payload
  mov -512(%rbp), rax
  movq -512(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp describeShape_block_48
describeShape_block_7:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rdi
  call lm_enum_tag
  mov -528(%rbp), rax
  movq -528(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  cmpq -536(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rax
  movq -136(%rbp), %rdx
  movl %eax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rax
  testq %rax, %rax
  jne describeShape_block_11
  jmp describeShape_block_17
describeShape_block_11:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rdi
  call lm_enum_payload
  mov -576(%rbp), rax
  movq -576(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -584(%rbp), %rdi
  movq -592(%rbp), %rsi
  call lm_tuple_get
  mov -600(%rbp), rax
  movq -600(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -608(%rbp), %rdi
  movq -616(%rbp), %rsi
  call lm_tuple_get
  mov -624(%rbp), rax
  movq -624(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  jmp describeShape_block_38
describeShape_block_17:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -632(%rbp), %rdi
  call lm_enum_tag
  mov -640(%rbp), rax
  movq -640(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  cmpq -648(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  movq -264(%rbp), %rdx
  movl %eax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -672(%rbp), %rax
  testq %rax, %rax
  jne describeShape_block_21
  jmp describeShape_block_27
describeShape_block_21:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rdi
  call lm_enum_payload
  mov -688(%rbp), rax
  movq -688(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -696(%rbp), %rdi
  movq -704(%rbp), %rsi
  call lm_tuple_get
  mov -712(%rbp), rax
  movq -712(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -720(%rbp), %rdi
  movq -728(%rbp), %rsi
  call lm_tuple_get
  mov -736(%rbp), rax
  movq -736(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  jmp describeShape_block_28
describeShape_block_27:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rax
  jmp describeShape_epilogue
describeShape_block_28:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rdi
  call lm_enum_payload
  mov -760(%rbp), rax
  movq -760(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -768(%rbp), %rdi
  movq -776(%rbp), %rsi
  call lm_tuple_get
  mov -784(%rbp), rax
  movq -784(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -792(%rbp), %rdi
  movq -800(%rbp), %rsi
  call lm_tuple_get
  mov -808(%rbp), rax
  movq -808(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_170(%rip), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -816(%rbp), %rdi
  movq -824(%rbp), %rsi
  call lm_rt_str_format
  mov -832(%rbp), rax
  movq -832(%rbp), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -840(%rbp), %rdi
  movq -848(%rbp), %rsi
  call lm_rt_str_format
  mov -856(%rbp), rax
  movq -856(%rbp), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -864(%rbp), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -872(%rbp), %rax
  jmp describeShape_epilogue
describeShape_block_38:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -880(%rbp), %rdi
  call lm_enum_payload
  mov -888(%rbp), rax
  movq -888(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -896(%rbp), %rdi
  movq -904(%rbp), %rsi
  call lm_tuple_get
  mov -912(%rbp), rax
  movq -912(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -928(%rbp)
  movq -920(%rbp), %rdi
  movq -928(%rbp), %rsi
  call lm_tuple_get
  mov -936(%rbp), rax
  movq -936(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_171(%rip), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -944(%rbp), %rdi
  movq -952(%rbp), %rsi
  call lm_rt_str_format
  mov -960(%rbp), rax
  movq -960(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -968(%rbp), %rdi
  movq -976(%rbp), %rsi
  call lm_rt_str_format
  mov -984(%rbp), rax
  movq -984(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -992(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -1000(%rbp), %rax
  jmp describeShape_epilogue
describeShape_block_48:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1008(%rbp)
  movq -1008(%rbp), %rdi
  call lm_enum_payload
  mov -1016(%rbp), rax
  movq -1016(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_172(%rip), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1032(%rbp)
  movq -1024(%rbp), %rdi
  movq -1032(%rbp), %rsi
  call lm_rt_str_format
  mov -1040(%rbp), rax
  movq -1040(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1048(%rbp)
  movq -1048(%rbp), %rax
  jmp describeShape_epilogue
describeShape_epilogue:
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
.Lfunc_end_describeShape:

.globl testListDestructuring
testListDestructuring:
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
  subq $1160, %rsp
  movq %rdi, -48(%rbp)
testListDestructuring_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testListDestructuring_block_0
testListDestructuring_block_0:
  jmp testListDestructuring_block_1
testListDestructuring_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rdi
  call lm_list_len
  mov -512(%rbp), rax
  movq -512(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rax
  cmpq -520(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -536(%rbp)
  movq -536(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  testq %rax, %rax
  jne testListDestructuring_block_5
  jmp testListDestructuring_block_6
testListDestructuring_block_5:
  jmp testListDestructuring_block_63
testListDestructuring_block_6:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rdi
  call lm_list_len
  mov -560(%rbp), rax
  movq -560(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -576(%rbp), %rax
  cmpq -568(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -584(%rbp)
  movq -584(%rbp), %rax
  movq -112(%rbp), %rdx
  movl %eax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  testq %rax, %rax
  jne testListDestructuring_block_10
  jmp testListDestructuring_block_13
testListDestructuring_block_10:
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -600(%rbp), %rdi
  movq -608(%rbp), %rsi
  call lm_list_get
  mov -616(%rbp), rax
  movq -616(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testListDestructuring_block_58
testListDestructuring_block_13:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -624(%rbp), %rdi
  call lm_list_len
  mov -632(%rbp), rax
  movq -632(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  cmpq -640(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  movq -184(%rbp), %rdx
  movl %eax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  testq %rax, %rax
  jne testListDestructuring_block_17
  jmp testListDestructuring_block_22
testListDestructuring_block_17:
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -672(%rbp), %rdi
  movq -680(%rbp), %rsi
  call lm_list_get
  mov -688(%rbp), rax
  movq -688(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -696(%rbp), %rdi
  movq -704(%rbp), %rsi
  call lm_list_get
  mov -712(%rbp), rax
  movq -712(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testListDestructuring_block_49
testListDestructuring_block_22:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -720(%rbp), %rdi
  call lm_list_len
  mov -728(%rbp), rax
  movq -728(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rax
  cmpq -736(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rax
  movq -296(%rbp), %rdx
  movl %eax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -760(%rbp), %rax
  testq %rax, %rax
  jne testListDestructuring_block_26
  jmp testListDestructuring_block_29
testListDestructuring_block_26:
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -768(%rbp), %rdi
  movq -776(%rbp), %rsi
  call lm_list_get
  mov -784(%rbp), rax
  movq -784(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testListDestructuring_block_30
testListDestructuring_block_29:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -792(%rbp), %rax
  jmp testListDestructuring_epilogue
testListDestructuring_block_30:
  movq $0, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -800(%rbp), %rdi
  movq -808(%rbp), %rsi
  call lm_list_get
  mov -816(%rbp), rax
  movq -816(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -824(%rbp), rax
  movq -824(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -832(%rbp)
  movq -832(%rbp), %rdi
  call lm_list_len
  mov -840(%rbp), rax
  movq -840(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testListDestructuring_block_36
testListDestructuring_block_36:
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -856(%rbp)
  movq -856(%rbp), %rax
  cmpq -848(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -864(%rbp)
  movq -864(%rbp), %rax
  movq -360(%rbp), %rdx
  movl %eax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -872(%rbp), %rax
  testq %rax, %rax
  jne testListDestructuring_block_38
  jmp testListDestructuring_block_44
testListDestructuring_block_38:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -880(%rbp), %rdi
  movq -888(%rbp), %rsi
  call lm_list_get
  mov -896(%rbp), rax
  movq -896(%rbp), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -912(%rbp)
  movq -904(%rbp), %rdi
  movq -912(%rbp), %rsi
  call lm_list_append
  mov -920(%rbp), rax
  movq $1, %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -928(%rbp)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -936(%rbp), %rax
  addq -928(%rbp), %rax
  movq %rax, -944(%rbp)
  movq -944(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -952(%rbp), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testListDestructuring_block_36
testListDestructuring_block_44:
  leaq str_hdr_173(%rip), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -960(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -960(%rbp), %rdi
  movq -968(%rbp), %rsi
  call lm_rt_str_format
  mov -976(%rbp), rax
  movq -976(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -984(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -984(%rbp), %rdi
  movq -992(%rbp), %rsi
  call lm_rt_str_format
  mov -1000(%rbp), rax
  movq -1000(%rbp), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1008(%rbp)
  movq -1008(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1016(%rbp)
  movq -1016(%rbp), %rax
  jmp testListDestructuring_epilogue
testListDestructuring_block_49:
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1032(%rbp)
  movq -1024(%rbp), %rdi
  movq -1032(%rbp), %rsi
  call lm_list_get
  mov -1040(%rbp), rax
  movq -1040(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1048(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1056(%rbp)
  movq -1048(%rbp), %rdi
  movq -1056(%rbp), %rsi
  call lm_list_get
  mov -1064(%rbp), rax
  movq -1064(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_174(%rip), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1072(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1080(%rbp)
  movq -1072(%rbp), %rdi
  movq -1080(%rbp), %rsi
  call lm_rt_str_format
  mov -1088(%rbp), rax
  movq -1088(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1104(%rbp)
  movq -1096(%rbp), %rdi
  movq -1104(%rbp), %rsi
  call lm_rt_str_format
  mov -1112(%rbp), rax
  movq -1112(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1120(%rbp)
  movq -1120(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1128(%rbp)
  movq -1128(%rbp), %rax
  jmp testListDestructuring_epilogue
testListDestructuring_block_58:
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1136(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1144(%rbp)
  movq -1136(%rbp), %rdi
  movq -1144(%rbp), %rsi
  call lm_list_get
  mov -1152(%rbp), rax
  movq -1152(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_175(%rip), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1160(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1168(%rbp)
  movq -1160(%rbp), %rdi
  movq -1168(%rbp), %rsi
  call lm_rt_str_format
  mov -1176(%rbp), rax
  movq -1176(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1184(%rbp)
  movq -1184(%rbp), %rax
  jmp testListDestructuring_epilogue
testListDestructuring_block_63:
  leaq str_hdr_176(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1192(%rbp)
  movq -1192(%rbp), %rax
  jmp testListDestructuring_epilogue
testListDestructuring_epilogue:
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
.Lfunc_end_testListDestructuring:

.globl testRecordDestructuring
testRecordDestructuring:
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
  subq $1064, %rsp
  movq %rdi, -48(%rbp)
testRecordDestructuring_entry:
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
  jmp testRecordDestructuring_block_0
testRecordDestructuring_block_0:
  jmp testRecordDestructuring_block_1
testRecordDestructuring_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  cmpq -464(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -480(%rbp)
  movq -480(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rax
  testq %rax, %rax
  jne testRecordDestructuring_block_5
  jmp testRecordDestructuring_block_14
testRecordDestructuring_block_5:
  leaq str_hdr_177(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -496(%rbp), %rdi
  movq -504(%rbp), %rsi
  call lm_dict_has
  mov -512(%rbp), rax
  movq -512(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  testq %rax, %rax
  jne testRecordDestructuring_block_8
  jmp testRecordDestructuring_block_14
testRecordDestructuring_block_8:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -528(%rbp), %rdi
  movq -536(%rbp), %rsi
  call lm_dict_get
  mov -544(%rbp), rax
  movq -544(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_178(%rip), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -552(%rbp), %rdi
  movq -560(%rbp), %rsi
  call lm_dict_has
  mov -568(%rbp), rax
  movq -568(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -576(%rbp), %rax
  testq %rax, %rax
  jne testRecordDestructuring_block_12
  jmp testRecordDestructuring_block_14
testRecordDestructuring_block_12:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -584(%rbp), %rdi
  movq -592(%rbp), %rsi
  call lm_dict_get
  mov -600(%rbp), rax
  movq -600(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testRecordDestructuring_block_44
testRecordDestructuring_block_14:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -632(%rbp), %rax
  cmpq -624(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -640(%rbp)
  movq -640(%rbp), %rax
  movq -208(%rbp), %rdx
  movl %eax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  testq %rax, %rax
  jne testRecordDestructuring_block_18
  jmp testRecordDestructuring_block_31
testRecordDestructuring_block_18:
  leaq str_hdr_179(%rip), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -656(%rbp), %rdi
  movq -664(%rbp), %rsi
  call lm_dict_has
  mov -672(%rbp), rax
  movq -672(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rax
  testq %rax, %rax
  jne testRecordDestructuring_block_21
  jmp testRecordDestructuring_block_31
testRecordDestructuring_block_21:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -688(%rbp), %rdi
  movq -696(%rbp), %rsi
  call lm_dict_get
  mov -704(%rbp), rax
  movq -704(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_180(%rip), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -712(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -712(%rbp), %rdi
  movq -720(%rbp), %rsi
  call lm_dict_has
  mov -728(%rbp), rax
  movq -728(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -736(%rbp), %rax
  testq %rax, %rax
  jne testRecordDestructuring_block_25
  jmp testRecordDestructuring_block_31
testRecordDestructuring_block_25:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -744(%rbp), %rdi
  movq -752(%rbp), %rsi
  call lm_dict_get
  mov -760(%rbp), rax
  movq -760(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_181(%rip), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -768(%rbp), %rdi
  movq -776(%rbp), %rsi
  call lm_dict_has
  mov -784(%rbp), rax
  movq -784(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -792(%rbp), %rax
  testq %rax, %rax
  jne testRecordDestructuring_block_29
  jmp testRecordDestructuring_block_31
testRecordDestructuring_block_29:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -800(%rbp), %rdi
  movq -808(%rbp), %rsi
  call lm_dict_get
  mov -816(%rbp), rax
  movq -816(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testRecordDestructuring_block_32
testRecordDestructuring_block_31:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -824(%rbp), %rax
  jmp testRecordDestructuring_epilogue
testRecordDestructuring_block_32:
  leaq str_hdr_182(%rip), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -832(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -832(%rbp), %rdi
  movq -840(%rbp), %rsi
  call lm_dict_get
  mov -848(%rbp), rax
  movq -848(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_183(%rip), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -856(%rbp)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -856(%rbp), %rdi
  movq -864(%rbp), %rsi
  call lm_dict_get
  mov -872(%rbp), rax
  movq -872(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_184(%rip), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -880(%rbp), %rdi
  movq -888(%rbp), %rsi
  call lm_dict_get
  mov -896(%rbp), rax
  movq -896(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_185(%rip), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -912(%rbp)
  movq -904(%rbp), %rdi
  movq -912(%rbp), %rsi
  call lm_rt_str_format
  mov -920(%rbp), rax
  movq -920(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -928(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -928(%rbp), %rdi
  movq -936(%rbp), %rsi
  call lm_rt_str_format
  mov -944(%rbp), rax
  movq -944(%rbp), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -960(%rbp)
  movq -952(%rbp), %rdi
  movq -960(%rbp), %rsi
  call lm_rt_str_format
  mov -968(%rbp), rax
  movq -968(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -976(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -984(%rbp)
  movq -984(%rbp), %rax
  jmp testRecordDestructuring_epilogue
testRecordDestructuring_block_44:
  leaq str_hdr_186(%rip), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -992(%rbp), %rdi
  movq -1000(%rbp), %rsi
  call lm_dict_get
  mov -1008(%rbp), rax
  movq -1008(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_187(%rip), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1016(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -1016(%rbp), %rdi
  movq -1024(%rbp), %rsi
  call lm_dict_get
  mov -1032(%rbp), rax
  movq -1032(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_188(%rip), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1048(%rbp)
  movq -1040(%rbp), %rdi
  movq -1048(%rbp), %rsi
  call lm_rt_str_format
  mov -1056(%rbp), rax
  movq -1056(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1064(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1072(%rbp)
  movq -1064(%rbp), %rdi
  movq -1072(%rbp), %rsi
  call lm_rt_str_format
  mov -1080(%rbp), rax
  movq -1080(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1088(%rbp)
  movq -1088(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -1096(%rbp), %rax
  jmp testRecordDestructuring_epilogue
testRecordDestructuring_epilogue:
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
.Lfunc_end_testRecordDestructuring:

.globl testSpreadDestructuring
testSpreadDestructuring:
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
testSpreadDestructuring_entry:
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
  jmp testSpreadDestructuring_block_0
testSpreadDestructuring_block_0:
  jmp testSpreadDestructuring_block_1
testSpreadDestructuring_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rdi
  call lm_list_len
  mov -328(%rbp), rax
  movq -328(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -344(%rbp)
  movq -344(%rbp), %rax
  cmpq -336(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -352(%rbp)
  movq -352(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -360(%rbp), %rax
  testq %rax, %rax
  jne testSpreadDestructuring_block_5
  jmp testSpreadDestructuring_block_8
testSpreadDestructuring_block_5:
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -376(%rbp)
  movq -368(%rbp), %rdi
  movq -376(%rbp), %rsi
  call lm_list_get
  mov -384(%rbp), rax
  movq -384(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testSpreadDestructuring_block_16
testSpreadDestructuring_block_8:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rdi
  call lm_list_len
  mov -400(%rbp), rax
  movq -400(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -416(%rbp)
  movq -416(%rbp), %rax
  cmpq -408(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  movq -224(%rbp), %rdx
  movl %eax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  testq %rax, %rax
  jne testSpreadDestructuring_block_12
  jmp testSpreadDestructuring_block_13
testSpreadDestructuring_block_12:
  jmp testSpreadDestructuring_block_14
testSpreadDestructuring_block_13:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -440(%rbp), %rax
  jmp testSpreadDestructuring_epilogue
testSpreadDestructuring_block_14:
  leaq str_hdr_189(%rip), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  jmp testSpreadDestructuring_epilogue
testSpreadDestructuring_block_16:
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -456(%rbp), %rdi
  movq -464(%rbp), %rsi
  call lm_list_get
  mov -472(%rbp), rax
  movq -472(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -480(%rbp), rax
  movq -480(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rdi
  call lm_list_len
  mov -496(%rbp), rax
  movq -496(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testSpreadDestructuring_block_22
testSpreadDestructuring_block_22:
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  cmpq -504(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  movq -144(%rbp), %rdx
  movl %eax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rax
  testq %rax, %rax
  jne testSpreadDestructuring_block_24
  jmp testSpreadDestructuring_block_30
testSpreadDestructuring_block_24:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -536(%rbp), %rdi
  movq -544(%rbp), %rsi
  call lm_list_get
  mov -552(%rbp), rax
  movq -552(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -560(%rbp), %rdi
  movq -568(%rbp), %rsi
  call lm_list_append
  mov -576(%rbp), rax
  movq $1, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  addq -584(%rbp), %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testSpreadDestructuring_block_22
testSpreadDestructuring_block_30:
  leaq str_hdr_190(%rip), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -616(%rbp), %rdi
  movq -624(%rbp), %rsi
  call lm_rt_str_format
  mov -632(%rbp), rax
  movq -632(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -640(%rbp), %rdi
  movq -648(%rbp), %rsi
  call lm_rt_str_format
  mov -656(%rbp), rax
  movq -656(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -672(%rbp), %rax
  jmp testSpreadDestructuring_epilogue
testSpreadDestructuring_epilogue:
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
.Lfunc_end_testSpreadDestructuring:

.globl testNestedDestructuring
testNestedDestructuring:
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
  subq $1368, %rsp
  movq %rdi, -48(%rbp)
testNestedDestructuring_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testNestedDestructuring_block_0
testNestedDestructuring_block_0:
  jmp testNestedDestructuring_block_1
testNestedDestructuring_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -584(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  cmpq -592(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rax
  testq %rax, %rax
  jne testNestedDestructuring_block_5
  jmp testNestedDestructuring_block_18
testNestedDestructuring_block_5:
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -624(%rbp), %rdi
  movq -632(%rbp), %rsi
  call lm_tuple_get
  mov -640(%rbp), rax
  movq -640(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -648(%rbp), %rdi
  movq -656(%rbp), %rsi
  call lm_tuple_get
  mov -664(%rbp), rax
  movq -664(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -672(%rbp), %rdi
  call lm_list_len
  mov -680(%rbp), rax
  movq -680(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -696(%rbp), %rax
  cmpq -688(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -704(%rbp)
  movq -704(%rbp), %rax
  movq -136(%rbp), %rdx
  movl %eax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -712(%rbp)
  movq -712(%rbp), %rax
  testq %rax, %rax
  jne testNestedDestructuring_block_13
  jmp testNestedDestructuring_block_18
testNestedDestructuring_block_13:
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -720(%rbp), %rdi
  movq -728(%rbp), %rsi
  call lm_list_get
  mov -736(%rbp), rax
  movq -736(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -744(%rbp), %rdi
  movq -752(%rbp), %rsi
  call lm_list_get
  mov -760(%rbp), rax
  movq -760(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testNestedDestructuring_block_54
testNestedDestructuring_block_18:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -776(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -792(%rbp), %rax
  cmpq -784(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -800(%rbp)
  movq -800(%rbp), %rax
  movq -288(%rbp), %rdx
  movl %eax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -808(%rbp), %rax
  testq %rax, %rax
  jne testNestedDestructuring_block_22
  jmp testNestedDestructuring_block_39
testNestedDestructuring_block_22:
  leaq str_hdr_191(%rip), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -816(%rbp), %rdi
  movq -824(%rbp), %rsi
  call lm_dict_has
  mov -832(%rbp), rax
  movq -832(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -840(%rbp), %rax
  testq %rax, %rax
  jne testNestedDestructuring_block_25
  jmp testNestedDestructuring_block_39
testNestedDestructuring_block_25:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -856(%rbp)
  movq -848(%rbp), %rdi
  movq -856(%rbp), %rsi
  call lm_dict_get
  mov -864(%rbp), rax
  movq -864(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_192(%rip), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -872(%rbp), %rdi
  movq -880(%rbp), %rsi
  call lm_dict_has
  mov -888(%rbp), rax
  movq -888(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -896(%rbp), %rax
  testq %rax, %rax
  jne testNestedDestructuring_block_29
  jmp testNestedDestructuring_block_39
testNestedDestructuring_block_29:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -912(%rbp)
  movq -904(%rbp), %rdi
  movq -912(%rbp), %rsi
  call lm_dict_get
  mov -920(%rbp), rax
  movq -920(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -928(%rbp)
  movq -928(%rbp), %rdi
  call lm_list_len
  mov -936(%rbp), rax
  movq -936(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -952(%rbp), %rax
  cmpq -944(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -960(%rbp)
  movq -960(%rbp), %rax
  movq -360(%rbp), %rdx
  movl %eax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -968(%rbp), %rax
  testq %rax, %rax
  jne testNestedDestructuring_block_34
  jmp testNestedDestructuring_block_39
testNestedDestructuring_block_34:
  movq $0, %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -984(%rbp)
  movq -976(%rbp), %rdi
  movq -984(%rbp), %rsi
  call lm_list_get
  mov -992(%rbp), rax
  movq -992(%rbp), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1008(%rbp)
  movq -1000(%rbp), %rdi
  movq -1008(%rbp), %rsi
  call lm_list_get
  mov -1016(%rbp), rax
  movq -1016(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testNestedDestructuring_block_40
testNestedDestructuring_block_39:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -1024(%rbp), %rax
  jmp testNestedDestructuring_epilogue
testNestedDestructuring_block_40:
  leaq str_hdr_193(%rip), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1032(%rbp)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -1032(%rbp), %rdi
  movq -1040(%rbp), %rsi
  call lm_dict_get
  mov -1048(%rbp), rax
  movq -1048(%rbp), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_194(%rip), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1056(%rbp)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1064(%rbp)
  movq -1056(%rbp), %rdi
  movq -1064(%rbp), %rsi
  call lm_dict_get
  mov -1072(%rbp), rax
  movq -1072(%rbp), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1080(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1088(%rbp)
  movq -1080(%rbp), %rdi
  movq -1088(%rbp), %rsi
  call lm_list_get
  mov -1096(%rbp), rax
  movq -1096(%rbp), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1104(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1112(%rbp)
  movq -1104(%rbp), %rdi
  movq -1112(%rbp), %rsi
  call lm_list_get
  mov -1120(%rbp), rax
  movq -1120(%rbp), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_195(%rip), %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1128(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1136(%rbp)
  movq -1128(%rbp), %rdi
  movq -1136(%rbp), %rsi
  call lm_rt_str_format
  mov -1144(%rbp), rax
  movq -1144(%rbp), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1152(%rbp)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1160(%rbp)
  movq -1152(%rbp), %rdi
  movq -1160(%rbp), %rsi
  call lm_rt_str_format
  mov -1168(%rbp), rax
  movq -1168(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1176(%rbp)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1184(%rbp)
  movq -1176(%rbp), %rdi
  movq -1184(%rbp), %rsi
  call lm_rt_str_format
  mov -1192(%rbp), rax
  movq -1192(%rbp), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1200(%rbp)
  movq -1200(%rbp), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1208(%rbp)
  movq -1208(%rbp), %rax
  jmp testNestedDestructuring_epilogue
testNestedDestructuring_block_54:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1216(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1224(%rbp)
  movq -1216(%rbp), %rdi
  movq -1224(%rbp), %rsi
  call lm_tuple_get
  mov -1232(%rbp), rax
  movq -1232(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1240(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1248(%rbp)
  movq -1240(%rbp), %rdi
  movq -1248(%rbp), %rsi
  call lm_tuple_get
  mov -1256(%rbp), rax
  movq -1256(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1264(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1272(%rbp)
  movq -1264(%rbp), %rdi
  movq -1272(%rbp), %rsi
  call lm_list_get
  mov -1280(%rbp), rax
  movq -1280(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1296(%rbp)
  movq -1288(%rbp), %rdi
  movq -1296(%rbp), %rsi
  call lm_list_get
  mov -1304(%rbp), rax
  movq -1304(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_196(%rip), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1312(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1320(%rbp)
  movq -1312(%rbp), %rdi
  movq -1320(%rbp), %rsi
  call lm_rt_str_format
  mov -1328(%rbp), rax
  movq -1328(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1336(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1344(%rbp)
  movq -1336(%rbp), %rdi
  movq -1344(%rbp), %rsi
  call lm_rt_str_format
  mov -1352(%rbp), rax
  movq -1352(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1360(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1368(%rbp)
  movq -1360(%rbp), %rdi
  movq -1368(%rbp), %rsi
  call lm_rt_str_format
  mov -1376(%rbp), rax
  movq -1376(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1384(%rbp)
  movq -1384(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1392(%rbp)
  movq -1392(%rbp), %rax
  jmp testNestedDestructuring_epilogue
testNestedDestructuring_epilogue:
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
.Lfunc_end_testNestedDestructuring:

.globl testNestedTupleList
testNestedTupleList:
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
testNestedTupleList_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testNestedTupleList_block_0
testNestedTupleList_block_0:
  jmp testNestedTupleList_block_1
testNestedTupleList_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -416(%rbp)
  movq -416(%rbp), %rax
  cmpq -408(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  testq %rax, %rax
  jne testNestedTupleList_block_5
  jmp testNestedTupleList_block_20
testNestedTupleList_block_5:
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -440(%rbp), %rdi
  movq -448(%rbp), %rsi
  call lm_tuple_get
  mov -456(%rbp), rax
  movq -456(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -464(%rbp), %rdi
  movq -472(%rbp), %rsi
  call lm_tuple_get
  mov -480(%rbp), rax
  movq -480(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rdi
  call lm_list_len
  mov -496(%rbp), rax
  movq -496(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  cmpq -504(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  movq -136(%rbp), %rdx
  movl %eax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rax
  testq %rax, %rax
  jne testNestedTupleList_block_13
  jmp testNestedTupleList_block_20
testNestedTupleList_block_13:
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -536(%rbp), %rdi
  movq -544(%rbp), %rsi
  call lm_list_get
  mov -552(%rbp), rax
  movq -552(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -560(%rbp), %rdi
  movq -568(%rbp), %rsi
  call lm_list_get
  mov -576(%rbp), rax
  movq -576(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -584(%rbp), %rdi
  movq -592(%rbp), %rsi
  call lm_list_get
  mov -600(%rbp), rax
  movq -600(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testNestedTupleList_block_21
testNestedTupleList_block_20:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  jmp testNestedTupleList_epilogue
testNestedTupleList_block_21:
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -616(%rbp), %rdi
  movq -624(%rbp), %rsi
  call lm_tuple_get
  mov -632(%rbp), rax
  movq -632(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -640(%rbp), %rdi
  movq -648(%rbp), %rsi
  call lm_tuple_get
  mov -656(%rbp), rax
  movq -656(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -664(%rbp), %rdi
  movq -672(%rbp), %rsi
  call lm_list_get
  mov -680(%rbp), rax
  movq -680(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -688(%rbp), %rdi
  movq -696(%rbp), %rsi
  call lm_list_get
  mov -704(%rbp), rax
  movq -704(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -712(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -712(%rbp), %rdi
  movq -720(%rbp), %rsi
  call lm_list_get
  mov -728(%rbp), rax
  movq -728(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_197(%rip), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -736(%rbp), %rdi
  movq -744(%rbp), %rsi
  call lm_rt_str_format
  mov -752(%rbp), rax
  movq -752(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -760(%rbp), %rdi
  movq -768(%rbp), %rsi
  call lm_rt_str_format
  mov -776(%rbp), rax
  movq -776(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -784(%rbp), %rdi
  movq -792(%rbp), %rsi
  call lm_rt_str_format
  mov -800(%rbp), rax
  movq -800(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -808(%rbp), %rdi
  movq -816(%rbp), %rsi
  call lm_rt_str_format
  mov -824(%rbp), rax
  movq -824(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -832(%rbp)
  movq -832(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -840(%rbp), %rax
  jmp testNestedTupleList_epilogue
testNestedTupleList_epilogue:
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
.Lfunc_end_testNestedTupleList:

.globl testNestedDestructure
testNestedDestructure:
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
testNestedDestructure_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testNestedDestructure_block_0
testNestedDestructure_block_0:
  jmp testNestedDestructure_block_1
testNestedDestructure_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -440(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  cmpq -448(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  testq %rax, %rax
  jne testNestedDestructure_block_5
  jmp testNestedDestructure_block_18
testNestedDestructure_block_5:
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -480(%rbp), %rdi
  movq -488(%rbp), %rsi
  call lm_tuple_get
  mov -496(%rbp), rax
  movq -496(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -504(%rbp), %rdi
  movq -512(%rbp), %rsi
  call lm_tuple_get
  mov -520(%rbp), rax
  movq -520(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rdi
  call lm_list_len
  mov -536(%rbp), rax
  movq -536(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rax
  cmpq -544(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rax
  movq -136(%rbp), %rdx
  movl %eax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rax
  testq %rax, %rax
  jne testNestedDestructure_block_13
  jmp testNestedDestructure_block_18
testNestedDestructure_block_13:
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -576(%rbp), %rdi
  movq -584(%rbp), %rsi
  call lm_list_get
  mov -592(%rbp), rax
  movq -592(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -600(%rbp), %rdi
  movq -608(%rbp), %rsi
  call lm_list_get
  mov -616(%rbp), rax
  movq -616(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testNestedDestructure_block_19
testNestedDestructure_block_18:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -624(%rbp), %rax
  jmp testNestedDestructure_epilogue
testNestedDestructure_block_19:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -632(%rbp), %rdi
  movq -640(%rbp), %rsi
  call lm_tuple_get
  mov -648(%rbp), rax
  movq -648(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -656(%rbp), %rdi
  movq -664(%rbp), %rsi
  call lm_tuple_get
  mov -672(%rbp), rax
  movq -672(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -680(%rbp), %rdi
  movq -688(%rbp), %rsi
  call lm_list_get
  mov -696(%rbp), rax
  movq -696(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -712(%rbp)
  movq -704(%rbp), %rdi
  movq -712(%rbp), %rsi
  call lm_list_get
  mov -720(%rbp), rax
  movq -720(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testNestedDestructure_block_28
testNestedDestructure_block_28:
  movq $1, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -728(%rbp), %rdi
  movq -736(%rbp), %rsi
  call lm_key_eq
  mov -744(%rbp), rax
  movq -744(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rax
  testq %rax, %rax
  jne testNestedDestructure_block_31
  jmp testNestedDestructure_block_32
testNestedDestructure_block_31:
  jmp testNestedDestructure_block_48
testNestedDestructure_block_32:
  movq $2, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -760(%rbp), %rdi
  movq -768(%rbp), %rsi
  call lm_key_eq
  mov -776(%rbp), rax
  movq -776(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -784(%rbp), %rax
  testq %rax, %rax
  jne testNestedDestructure_block_35
  jmp testNestedDestructure_block_36
testNestedDestructure_block_35:
  jmp testNestedDestructure_block_43
testNestedDestructure_block_36:
  jmp testNestedDestructure_block_37
testNestedDestructure_block_37:
  leaq str_hdr_198(%rip), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -792(%rbp), %rdi
  movq -800(%rbp), %rsi
  call lm_rt_str_format
  mov -808(%rbp), rax
  movq -808(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -816(%rbp), %rdi
  movq -824(%rbp), %rsi
  call lm_rt_str_format
  mov -832(%rbp), rax
  movq -832(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -840(%rbp), %rdi
  movq -848(%rbp), %rsi
  call lm_rt_str_format
  mov -856(%rbp), rax
  movq -856(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -864(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -872(%rbp), %rax
  jmp testNestedDestructure_epilogue
testNestedDestructure_block_43:
  leaq str_hdr_199(%rip), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -880(%rbp), %rdi
  movq -888(%rbp), %rsi
  call lm_rt_str_format
  mov -896(%rbp), rax
  movq -896(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -912(%rbp)
  movq -904(%rbp), %rdi
  movq -912(%rbp), %rsi
  call lm_rt_str_format
  mov -920(%rbp), rax
  movq -920(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -928(%rbp)
  movq -928(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -936(%rbp), %rax
  jmp testNestedDestructure_epilogue
testNestedDestructure_block_48:
  leaq str_hdr_200(%rip), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -944(%rbp), %rdi
  movq -952(%rbp), %rsi
  call lm_rt_str_format
  mov -960(%rbp), rax
  movq -960(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -968(%rbp), %rdi
  movq -976(%rbp), %rsi
  call lm_rt_str_format
  mov -984(%rbp), rax
  movq -984(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -992(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -1000(%rbp), %rax
  jmp testNestedDestructure_epilogue
testNestedDestructure_epilogue:
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
.Lfunc_end_testNestedDestructure:

.globl testDestructuringWithGuards
testDestructuringWithGuards:
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
  subq $1016, %rsp
  movq %rdi, -48(%rbp)
testDestructuringWithGuards_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testDestructuringWithGuards_block_0
testDestructuringWithGuards_block_0:
  jmp testDestructuringWithGuards_block_1
testDestructuringWithGuards_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -440(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  cmpq -448(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  testq %rax, %rax
  jne testDestructuringWithGuards_block_5
  jmp testDestructuringWithGuards_block_25
testDestructuringWithGuards_block_5:
  leaq str_hdr_201(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -480(%rbp), %rdi
  movq -488(%rbp), %rsi
  call lm_dict_has
  mov -496(%rbp), rax
  movq -496(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  testq %rax, %rax
  jne testDestructuringWithGuards_block_8
  jmp testDestructuringWithGuards_block_25
testDestructuringWithGuards_block_8:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -512(%rbp), %rdi
  movq -520(%rbp), %rsi
  call lm_dict_get
  mov -528(%rbp), rax
  movq -528(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_202(%rip), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -536(%rbp), %rdi
  movq -544(%rbp), %rsi
  call lm_dict_has
  mov -552(%rbp), rax
  movq -552(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rax
  testq %rax, %rax
  jne testDestructuringWithGuards_block_12
  jmp testDestructuringWithGuards_block_25
testDestructuringWithGuards_block_12:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -568(%rbp), %rdi
  movq -576(%rbp), %rsi
  call lm_dict_get
  mov -584(%rbp), rax
  movq -584(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $18, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  cmpq -592(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  movq -144(%rbp), %rdx
  movl %eax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rax
  testq %rax, %rax
  jne testDestructuringWithGuards_block_16
  jmp testDestructuringWithGuards_block_25
testDestructuringWithGuards_block_16:
  leaq str_hdr_203(%rip), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -624(%rbp), %rdi
  movq -632(%rbp), %rsi
  call lm_dict_get
  mov -640(%rbp), rax
  movq -640(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_204(%rip), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -648(%rbp), %rdi
  movq -656(%rbp), %rsi
  call lm_dict_get
  mov -664(%rbp), rax
  movq -664(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_205(%rip), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -672(%rbp), %rdi
  movq -680(%rbp), %rsi
  call lm_rt_str_format
  mov -688(%rbp), rax
  movq -688(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -696(%rbp), %rdi
  movq -704(%rbp), %rsi
  call lm_rt_str_format
  mov -712(%rbp), rax
  movq -712(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -720(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -728(%rbp), %rax
  jmp testDestructuringWithGuards_epilogue
testDestructuringWithGuards_block_25:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -760(%rbp), %rax
  cmpq -752(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -768(%rbp)
  movq -768(%rbp), %rax
  movq -224(%rbp), %rdx
  movl %eax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -776(%rbp), %rax
  testq %rax, %rax
  jne testDestructuringWithGuards_block_29
  jmp testDestructuringWithGuards_block_49
testDestructuringWithGuards_block_29:
  leaq str_hdr_206(%rip), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -784(%rbp), %rdi
  movq -792(%rbp), %rsi
  call lm_dict_has
  mov -800(%rbp), rax
  movq -800(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -808(%rbp), %rax
  testq %rax, %rax
  jne testDestructuringWithGuards_block_32
  jmp testDestructuringWithGuards_block_49
testDestructuringWithGuards_block_32:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -816(%rbp), %rdi
  movq -824(%rbp), %rsi
  call lm_dict_get
  mov -832(%rbp), rax
  movq -832(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_207(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -840(%rbp), %rdi
  movq -848(%rbp), %rsi
  call lm_dict_has
  mov -856(%rbp), rax
  movq -856(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -864(%rbp), %rax
  testq %rax, %rax
  jne testDestructuringWithGuards_block_36
  jmp testDestructuringWithGuards_block_49
testDestructuringWithGuards_block_36:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -872(%rbp), %rdi
  movq -880(%rbp), %rsi
  call lm_dict_get
  mov -888(%rbp), rax
  movq -888(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq $18, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -904(%rbp), %rax
  cmpq -896(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -912(%rbp)
  movq -912(%rbp), %rax
  movq -288(%rbp), %rdx
  movl %eax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -920(%rbp), %rax
  testq %rax, %rax
  jne testDestructuringWithGuards_block_40
  jmp testDestructuringWithGuards_block_49
testDestructuringWithGuards_block_40:
  leaq str_hdr_208(%rip), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -928(%rbp)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -928(%rbp), %rdi
  movq -936(%rbp), %rsi
  call lm_dict_get
  mov -944(%rbp), rax
  movq -944(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_209(%rip), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -960(%rbp)
  movq -952(%rbp), %rdi
  movq -960(%rbp), %rsi
  call lm_dict_get
  mov -968(%rbp), rax
  movq -968(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_210(%rip), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -984(%rbp)
  movq -976(%rbp), %rdi
  movq -984(%rbp), %rsi
  call lm_rt_str_format
  mov -992(%rbp), rax
  movq -992(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1008(%rbp)
  movq -1000(%rbp), %rdi
  movq -1008(%rbp), %rsi
  call lm_rt_str_format
  mov -1016(%rbp), rax
  movq -1016(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -1024(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1032(%rbp)
  movq -1032(%rbp), %rax
  jmp testDestructuringWithGuards_epilogue
testDestructuringWithGuards_block_49:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -1040(%rbp), %rax
  jmp testDestructuringWithGuards_epilogue
testDestructuringWithGuards_epilogue:
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
.Lfunc_end_testDestructuringWithGuards:

.globl testTupleDestructuring
testTupleDestructuring:
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
  subq $872, %rsp
  movq %rdi, -48(%rbp)
testTupleDestructuring_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testTupleDestructuring_block_0
testTupleDestructuring_block_0:
  jmp testTupleDestructuring_block_1
testTupleDestructuring_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -416(%rbp)
  movq -416(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  cmpq -424(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -440(%rbp)
  movq -440(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  testq %rax, %rax
  jne testTupleDestructuring_block_5
  jmp testTupleDestructuring_block_10
testTupleDestructuring_block_5:
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -456(%rbp), %rdi
  movq -464(%rbp), %rsi
  call lm_tuple_get
  mov -472(%rbp), rax
  movq -472(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -480(%rbp), %rdi
  movq -488(%rbp), %rsi
  call lm_tuple_get
  mov -496(%rbp), rax
  movq -496(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testTupleDestructuring_block_34
testTupleDestructuring_block_10:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rax
  cmpq -520(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -536(%rbp)
  movq -536(%rbp), %rax
  movq -192(%rbp), %rdx
  movl %eax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  testq %rax, %rax
  jne testTupleDestructuring_block_14
  jmp testTupleDestructuring_block_21
testTupleDestructuring_block_14:
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -552(%rbp), %rdi
  movq -560(%rbp), %rsi
  call lm_tuple_get
  mov -568(%rbp), rax
  movq -568(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -576(%rbp), %rdi
  movq -584(%rbp), %rsi
  call lm_tuple_get
  mov -592(%rbp), rax
  movq -592(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -600(%rbp), %rdi
  movq -608(%rbp), %rsi
  call lm_tuple_get
  mov -616(%rbp), rax
  movq -616(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  jmp testTupleDestructuring_block_22
testTupleDestructuring_block_21:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -624(%rbp), %rax
  jmp testTupleDestructuring_epilogue
testTupleDestructuring_block_22:
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -632(%rbp), %rdi
  movq -640(%rbp), %rsi
  call lm_tuple_get
  mov -648(%rbp), rax
  movq -648(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -656(%rbp), %rdi
  movq -664(%rbp), %rsi
  call lm_tuple_get
  mov -672(%rbp), rax
  movq -672(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -680(%rbp), %rdi
  movq -688(%rbp), %rsi
  call lm_tuple_get
  mov -696(%rbp), rax
  movq -696(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_211(%rip), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -712(%rbp)
  movq -704(%rbp), %rdi
  movq -712(%rbp), %rsi
  call lm_rt_str_format
  mov -720(%rbp), rax
  movq -720(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -728(%rbp), %rdi
  movq -736(%rbp), %rsi
  call lm_rt_str_format
  mov -744(%rbp), rax
  movq -744(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -752(%rbp), %rdi
  movq -760(%rbp), %rsi
  call lm_rt_str_format
  mov -768(%rbp), rax
  movq -768(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -776(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -784(%rbp), %rax
  jmp testTupleDestructuring_epilogue
testTupleDestructuring_block_34:
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -792(%rbp), %rdi
  movq -800(%rbp), %rsi
  call lm_tuple_get
  mov -808(%rbp), rax
  movq -808(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -816(%rbp), %rdi
  movq -824(%rbp), %rsi
  call lm_tuple_get
  mov -832(%rbp), rax
  movq -832(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_212(%rip), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -840(%rbp), %rdi
  movq -848(%rbp), %rsi
  call lm_rt_str_format
  mov -856(%rbp), rax
  movq -856(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -864(%rbp), %rdi
  movq -872(%rbp), %rsi
  call lm_rt_str_format
  mov -880(%rbp), rax
  movq -880(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -888(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -896(%rbp), %rax
  jmp testTupleDestructuring_epilogue
testTupleDestructuring_epilogue:
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
.Lfunc_end_testTupleDestructuring:

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

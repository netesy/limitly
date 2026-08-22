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
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
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
str_hdr_1:
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
str_hdr_2:
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
str_hdr_3:
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
str_hdr_4:
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
str_hdr_5:
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
  .byte 48
  .byte 49
  .byte 50
  .byte 51
  .byte 52
  .byte 53
  .byte 54
  .byte 55
  .byte 56
  .byte 57
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
  .byte 45
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
str_hdr_8:
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
  .byte 43
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
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
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
str_hdr_10:
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
  .byte 48
  .byte 49
  .byte 50
  .byte 51
  .byte 52
  .byte 53
  .byte 54
  .byte 55
  .byte 56
  .byte 57
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
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
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
str_hdr_12:
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
str_hdr_13:
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
str_hdr_14:
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
str_hdr_15:
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
str_hdr_16:
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
  .byte 49
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
  .byte 50
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
  .byte 52
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
  .byte 53
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
  .byte 54
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
  .byte 55
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
  .byte 56
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
  .byte 57
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
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
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
str_hdr_26:
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
  .byte 43
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
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
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
str_hdr_28:
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
  .byte 45
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
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
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
str_hdr_30:
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
str_hdr_31:
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
str_hdr_32:
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
str_hdr_33:
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
str_hdr_34:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 63
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 63
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
  .byte 48
  .byte 49
  .byte 50
  .byte 51
  .byte 52
  .byte 53
  .byte 54
  .byte 55
  .byte 56
  .byte 57
  .byte 45
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
  .byte 83
  .byte 101
  .byte 109
  .byte 86
  .byte 101
  .byte 114
  .byte 32
  .byte 102
  .byte 111
  .byte 114
  .byte 109
  .byte 97
  .byte 116
  .byte 116
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
str_hdr_36:
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 45
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 49
  .byte 43
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
  .byte 46
  .byte 49
  .byte 50
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 45
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 49
  .byte 43
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
  .byte 46
  .byte 49
  .byte 50
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
  .byte 116
  .byte 111
  .byte 95
  .byte 115
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 109
  .byte 97
  .byte 116
  .byte 99
  .byte 104
  .byte 101
  .byte 115
  .byte 32
  .byte 105
  .byte 110
  .byte 112
  .byte 117
  .byte 116
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
  .byte 50
  .byte 46
  .byte 48
  .byte 46
  .byte 49
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
  .byte 50
  .byte 46
  .byte 48
  .byte 46
  .byte 49
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
  .byte 116
  .byte 111
  .byte 95
  .byte 115
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 109
  .byte 97
  .byte 116
  .byte 99
  .byte 104
  .byte 101
  .byte 115
  .byte 32
  .byte 105
  .byte 110
  .byte 112
  .byte 117
  .byte 116
  .byte 32
  .byte 40
  .byte 115
  .byte 105
  .byte 109
  .byte 112
  .byte 108
  .byte 101
  .byte 41
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
  .byte 70
  .byte 111
  .byte 114
  .byte 109
  .byte 97
  .byte 116
  .byte 116
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
str_hdr_45:
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
  .byte 117
  .byte 110
  .byte 110
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 83
  .byte 101
  .byte 109
  .byte 86
  .byte 101
  .byte 114
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
  .byte 46
  .byte 46
  .byte 46
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 49
  .byte 46
  .byte 53
  .byte 46
  .byte 48
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
  .byte 50
  .byte 46
  .byte 48
  .byte 46
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
  .byte 49
  .byte 46
  .byte 49
  .byte 46
  .byte 48
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
  .byte 49
  .byte 46
  .byte 53
  .byte 46
  .byte 48
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
  .byte 99
  .byte 111
  .byte 109
  .byte 112
  .byte 97
  .byte 116
  .byte 105
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 50
  .byte 46
  .byte 48
  .byte 46
  .byte 48
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
  .byte 99
  .byte 111
  .byte 109
  .byte 112
  .byte 97
  .byte 116
  .byte 105
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 49
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 49
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 49
  .byte 46
  .byte 49
  .byte 46
  .byte 48
  .byte 32
  .byte 40
  .byte 111
  .byte 108
  .byte 100
  .byte 101
  .byte 114
  .byte 41
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
  .byte 99
  .byte 111
  .byte 109
  .byte 112
  .byte 97
  .byte 116
  .byte 105
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 48
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 48
  .byte 46
  .byte 50
  .byte 46
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
  .byte 48
  .byte 46
  .byte 51
  .byte 46
  .byte 48
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
  .byte 48
  .byte 46
  .byte 50
  .byte 46
  .byte 53
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 99
  .byte 111
  .byte 109
  .byte 112
  .byte 97
  .byte 116
  .byte 105
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 48
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 48
  .byte 46
  .byte 51
  .byte 46
  .byte 48
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 110
  .byte 111
  .byte 116
  .byte 32
  .byte 99
  .byte 111
  .byte 109
  .byte 112
  .byte 97
  .byte 116
  .byte 105
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 48
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 48
  .byte 46
  .byte 48
  .byte 46
  .byte 53
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
  .byte 48
  .byte 46
  .byte 48
  .byte 46
  .byte 53
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
  .byte 48
  .byte 46
  .byte 48
  .byte 46
  .byte 54
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
  .byte 48
  .byte 46
  .byte 48
  .byte 46
  .byte 53
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 99
  .byte 111
  .byte 109
  .byte 112
  .byte 97
  .byte 116
  .byte 105
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 48
  .byte 46
  .byte 48
  .byte 46
  .byte 53
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
  .byte 48
  .byte 46
  .byte 48
  .byte 46
  .byte 54
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 110
  .byte 111
  .byte 116
  .byte 32
  .byte 99
  .byte 111
  .byte 109
  .byte 112
  .byte 97
  .byte 116
  .byte 105
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 48
  .byte 46
  .byte 48
  .byte 46
  .byte 53
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
str_hdr_71:
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
  .byte 83
  .byte 101
  .byte 109
  .byte 86
  .byte 101
  .byte 114
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
str_hdr_72:
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 50
  .byte 46
  .byte 48
  .byte 46
  .byte 48
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
  .byte 49
  .byte 46
  .byte 51
  .byte 46
  .byte 48
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 52
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 32
  .byte 60
  .byte 32
  .byte 50
  .byte 46
  .byte 48
  .byte 46
  .byte 48
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
  .byte 50
  .byte 46
  .byte 48
  .byte 46
  .byte 48
  .byte 32
  .byte 62
  .byte 32
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 32
  .byte 60
  .byte 32
  .byte 49
  .byte 46
  .byte 51
  .byte 46
  .byte 48
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
  .byte 49
  .byte 46
  .byte 51
  .byte 46
  .byte 48
  .byte 32
  .byte 62
  .byte 32
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 32
  .byte 60
  .byte 32
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 52
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 32
  .byte 61
  .byte 61
  .byte 32
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 49
  .byte 46
  .byte 48
  .byte 46
  .byte 48
  .byte 45
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
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
  .byte 49
  .byte 46
  .byte 48
  .byte 46
  .byte 48
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
  .byte 49
  .byte 46
  .byte 48
  .byte 46
  .byte 48
  .byte 45
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 32
  .byte 60
  .byte 32
  .byte 49
  .byte 46
  .byte 48
  .byte 46
  .byte 48
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
  .byte 49
  .byte 46
  .byte 48
  .byte 46
  .byte 48
  .byte 32
  .byte 62
  .byte 32
  .byte 49
  .byte 46
  .byte 48
  .byte 46
  .byte 48
  .byte 45
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
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
  .byte 49
  .byte 46
  .byte 48
  .byte 46
  .byte 48
  .byte 45
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
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
  .byte 49
  .byte 46
  .byte 48
  .byte 46
  .byte 48
  .byte 45
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 49
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
  .byte 49
  .byte 46
  .byte 48
  .byte 46
  .byte 48
  .byte 45
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 98
  .byte 101
  .byte 116
  .byte 97
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
  .byte 49
  .byte 46
  .byte 48
  .byte 46
  .byte 48
  .byte 45
  .byte 98
  .byte 101
  .byte 116
  .byte 97
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
  .byte 49
  .byte 46
  .byte 48
  .byte 46
  .byte 48
  .byte 45
  .byte 98
  .byte 101
  .byte 116
  .byte 97
  .byte 46
  .byte 50
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
  .byte 49
  .byte 46
  .byte 48
  .byte 46
  .byte 48
  .byte 45
  .byte 98
  .byte 101
  .byte 116
  .byte 97
  .byte 46
  .byte 49
  .byte 49
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
  .byte 49
  .byte 46
  .byte 48
  .byte 46
  .byte 48
  .byte 45
  .byte 114
  .byte 99
  .byte 46
  .byte 49
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
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 32
  .byte 60
  .byte 32
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 49
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
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 49
  .byte 32
  .byte 60
  .byte 32
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 98
  .byte 101
  .byte 116
  .byte 97
  .byte 32
  .byte 40
  .byte 110
  .byte 117
  .byte 109
  .byte 101
  .byte 114
  .byte 105
  .byte 99
  .byte 32
  .byte 60
  .byte 32
  .byte 110
  .byte 111
  .byte 110
  .byte 45
  .byte 110
  .byte 117
  .byte 109
  .byte 101
  .byte 114
  .byte 105
  .byte 99
  .byte 41
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
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 98
  .byte 101
  .byte 116
  .byte 97
  .byte 32
  .byte 60
  .byte 32
  .byte 98
  .byte 101
  .byte 116
  .byte 97
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
  .byte 98
  .byte 101
  .byte 116
  .byte 97
  .byte 32
  .byte 60
  .byte 32
  .byte 98
  .byte 101
  .byte 116
  .byte 97
  .byte 46
  .byte 50
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
  .byte 98
  .byte 101
  .byte 116
  .byte 97
  .byte 46
  .byte 50
  .byte 32
  .byte 60
  .byte 32
  .byte 98
  .byte 101
  .byte 116
  .byte 97
  .byte 46
  .byte 49
  .byte 49
  .byte 32
  .byte 40
  .byte 110
  .byte 117
  .byte 109
  .byte 101
  .byte 114
  .byte 105
  .byte 99
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
  .byte 32
  .byte 50
  .byte 32
  .byte 60
  .byte 32
  .byte 49
  .byte 49
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
  .byte 98
  .byte 101
  .byte 116
  .byte 97
  .byte 46
  .byte 49
  .byte 49
  .byte 32
  .byte 60
  .byte 32
  .byte 114
  .byte 99
  .byte 46
  .byte 49
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 43
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
  .byte 46
  .byte 49
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 43
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
  .byte 46
  .byte 50
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 43
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
  .byte 46
  .byte 49
  .byte 32
  .byte 61
  .byte 61
  .byte 32
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 43
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
  .byte 46
  .byte 50
  .byte 32
  .byte 105
  .byte 110
  .byte 32
  .byte 112
  .byte 114
  .byte 101
  .byte 99
  .byte 101
  .byte 100
  .byte 101
  .byte 110
  .byte 99
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
  .byte 118
  .byte 98
  .byte 49
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 101
  .byte 113
  .byte 117
  .byte 97
  .byte 108
  .byte 32
  .byte 118
  .byte 98
  .byte 50
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
  .byte 67
  .byte 111
  .byte 109
  .byte 112
  .byte 97
  .byte 114
  .byte 105
  .byte 115
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
str_hdr_120:
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
  .byte 82
  .byte 117
  .byte 110
  .byte 110
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 83
  .byte 101
  .byte 109
  .byte 86
  .byte 101
  .byte 114
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
str_hdr_121:
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 70
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 32
  .byte 116
  .byte 111
  .byte 32
  .byte 112
  .byte 97
  .byte 114
  .byte 115
  .byte 101
  .byte 32
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 118
  .byte 49
  .byte 46
  .byte 109
  .byte 97
  .byte 106
  .byte 111
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
  .byte 49
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
  .byte 118
  .byte 49
  .byte 46
  .byte 109
  .byte 105
  .byte 110
  .byte 111
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
  .byte 50
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
  .byte 118
  .byte 49
  .byte 46
  .byte 112
  .byte 97
  .byte 116
  .byte 99
  .byte 104
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
  .byte 51
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
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
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
str_hdr_131:
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
  .byte 118
  .byte 49
  .byte 46
  .byte 112
  .byte 114
  .byte 101
  .byte 114
  .byte 101
  .byte 108
  .byte 101
  .byte 97
  .byte 115
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
  .byte 101
  .byte 109
  .byte 112
  .byte 116
  .byte 121
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
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
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
str_hdr_134:
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
  .byte 118
  .byte 49
  .byte 46
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
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
str_hdr_136:
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
  .byte 48
  .byte 46
  .byte 48
  .byte 46
  .byte 48
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
  .byte 70
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 32
  .byte 116
  .byte 111
  .byte 32
  .byte 112
  .byte 97
  .byte 114
  .byte 115
  .byte 101
  .byte 32
  .byte 48
  .byte 46
  .byte 48
  .byte 46
  .byte 48
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
  .byte 118
  .byte 50
  .byte 46
  .byte 109
  .byte 97
  .byte 106
  .byte 111
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
  .byte 118
  .byte 50
  .byte 46
  .byte 109
  .byte 105
  .byte 110
  .byte 111
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
  .byte 48
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
  .byte 118
  .byte 50
  .byte 46
  .byte 112
  .byte 97
  .byte 116
  .byte 99
  .byte 104
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
  .byte 48
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 45
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 49
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
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 32
  .byte 116
  .byte 111
  .byte 32
  .byte 112
  .byte 97
  .byte 114
  .byte 115
  .byte 101
  .byte 32
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 45
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 49
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
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 49
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
  .byte 118
  .byte 51
  .byte 46
  .byte 112
  .byte 114
  .byte 101
  .byte 114
  .byte 101
  .byte 108
  .byte 101
  .byte 97
  .byte 115
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
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 49
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
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
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
str_hdr_152:
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
  .byte 118
  .byte 51
  .byte 46
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
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
str_hdr_154:
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 43
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
  .byte 46
  .byte 49
  .byte 50
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
  .byte 70
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 32
  .byte 116
  .byte 111
  .byte 32
  .byte 112
  .byte 97
  .byte 114
  .byte 115
  .byte 101
  .byte 32
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 43
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
  .byte 46
  .byte 49
  .byte 50
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
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
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
str_hdr_158:
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
  .byte 118
  .byte 52
  .byte 46
  .byte 112
  .byte 114
  .byte 101
  .byte 114
  .byte 101
  .byte 108
  .byte 101
  .byte 97
  .byte 115
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
  .byte 101
  .byte 109
  .byte 112
  .byte 116
  .byte 121
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
  .byte 117
  .byte 105
  .byte 108
  .byte 100
  .byte 46
  .byte 49
  .byte 50
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
  .byte 118
  .byte 52
  .byte 46
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
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
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
  .byte 46
  .byte 49
  .byte 50
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 45
  .byte 98
  .byte 101
  .byte 116
  .byte 97
  .byte 46
  .byte 50
  .byte 43
  .byte 50
  .byte 48
  .byte 49
  .byte 52
  .byte 49
  .byte 50
  .byte 50
  .byte 51
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
  .byte 70
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 32
  .byte 116
  .byte 111
  .byte 32
  .byte 112
  .byte 97
  .byte 114
  .byte 115
  .byte 101
  .byte 32
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 45
  .byte 98
  .byte 101
  .byte 116
  .byte 97
  .byte 46
  .byte 50
  .byte 43
  .byte 50
  .byte 48
  .byte 49
  .byte 52
  .byte 49
  .byte 50
  .byte 50
  .byte 51
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
  .byte 98
  .byte 101
  .byte 116
  .byte 97
  .byte 46
  .byte 50
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
  .byte 118
  .byte 53
  .byte 46
  .byte 112
  .byte 114
  .byte 101
  .byte 114
  .byte 101
  .byte 108
  .byte 101
  .byte 97
  .byte 115
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
  .byte 98
  .byte 101
  .byte 116
  .byte 97
  .byte 46
  .byte 50
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
  .byte 50
  .byte 48
  .byte 49
  .byte 52
  .byte 49
  .byte 50
  .byte 50
  .byte 51
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
  .byte 118
  .byte 53
  .byte 46
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
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
  .byte 50
  .byte 48
  .byte 49
  .byte 52
  .byte 49
  .byte 50
  .byte 50
  .byte 51
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
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
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
str_hdr_173:
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
  .byte 102
  .byte 97
  .byte 105
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
  .byte 49
  .byte 46
  .byte 50
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
  .byte 77
  .byte 105
  .byte 115
  .byte 115
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 112
  .byte 97
  .byte 116
  .byte 99
  .byte 104
  .byte 32
  .byte 118
  .byte 101
  .byte 114
  .byte 115
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
  .byte 102
  .byte 97
  .byte 105
  .byte 108
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 46
  .byte 52
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
  .byte 70
  .byte 111
  .byte 117
  .byte 114
  .byte 32
  .byte 112
  .byte 97
  .byte 114
  .byte 116
  .byte 115
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
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
  .byte 48
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
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
  .byte 76
  .byte 101
  .byte 97
  .byte 100
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 122
  .byte 101
  .byte 114
  .byte 111
  .byte 101
  .byte 115
  .byte 32
  .byte 105
  .byte 110
  .byte 32
  .byte 99
  .byte 111
  .byte 114
  .byte 101
  .byte 32
  .byte 118
  .byte 101
  .byte 114
  .byte 115
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
  .byte 102
  .byte 97
  .byte 105
  .byte 108
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 45
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 48
  .byte 49
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
  .byte 49
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 49
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 76
  .byte 101
  .byte 97
  .byte 100
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 122
  .byte 101
  .byte 114
  .byte 111
  .byte 101
  .byte 115
  .byte 32
  .byte 105
  .byte 110
  .byte 32
  .byte 110
  .byte 117
  .byte 109
  .byte 101
  .byte 114
  .byte 105
  .byte 99
  .byte 32
  .byte 112
  .byte 114
  .byte 101
  .byte 45
  .byte 114
  .byte 101
  .byte 108
  .byte 101
  .byte 97
  .byte 115
  .byte 101
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 45
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 46
  .byte 46
  .byte 49
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
  .byte 69
  .byte 109
  .byte 112
  .byte 116
  .byte 121
  .byte 32
  .byte 112
  .byte 114
  .byte 101
  .byte 45
  .byte 114
  .byte 101
  .byte 108
  .byte 101
  .byte 97
  .byte 115
  .byte 101
  .byte 32
  .byte 105
  .byte 100
  .byte 101
  .byte 110
  .byte 116
  .byte 105
  .byte 102
  .byte 105
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
  .byte 102
  .byte 97
  .byte 105
  .byte 108
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 43
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
  .byte 46
  .byte 46
  .byte 49
  .byte 50
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
  .byte 69
  .byte 109
  .byte 112
  .byte 116
  .byte 121
  .byte 32
  .byte 98
  .byte 117
  .byte 105
  .byte 108
  .byte 100
  .byte 32
  .byte 105
  .byte 100
  .byte 101
  .byte 110
  .byte 116
  .byte 105
  .byte 102
  .byte 105
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
  .byte 102
  .byte 97
  .byte 105
  .byte 108
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
  .byte 49
  .byte 46
  .byte 50
  .byte 46
  .byte 51
  .byte 45
  .byte 97
  .byte 108
  .byte 112
  .byte 104
  .byte 97
  .byte 95
  .byte 49
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
  .byte 73
  .byte 110
  .byte 118
  .byte 97
  .byte 108
  .byte 105
  .byte 100
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
  .byte 105
  .byte 110
  .byte 32
  .byte 112
  .byte 114
  .byte 101
  .byte 45
  .byte 114
  .byte 101
  .byte 108
  .byte 101
  .byte 97
  .byte 115
  .byte 101
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 102
  .byte 97
  .byte 105
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
str_hdr_197:
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
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 83
  .byte 101
  .byte 109
  .byte 86
  .byte 101
  .byte 114
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
str_hdr_198:
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
  .byte 67
  .byte 111
  .byte 109
  .byte 112
  .byte 97
  .byte 114
  .byte 105
  .byte 115
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
str_hdr_202:
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
str_hdr_204:
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
  .byte 70
  .byte 111
  .byte 114
  .byte 109
  .byte 97
  .byte 116
  .byte 116
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
str_hdr_206:
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
  .byte 65
  .byte 108
  .byte 108
  .byte 32
  .byte 83
  .byte 101
  .byte 109
  .byte 86
  .byte 101
  .byte 114
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
  subq $136, %rsp
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
  jmp main_block_0
main_block_0:
  call std.semver.__init__
  mov -160(%rbp), rax
  movq -160(%rbp), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  call __user_main
  mov -168(%rbp), rax
  movq -168(%rbp), %rax
  movq -64(%rbp), %rdx
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

.globl std.semver.is_valid_build_id
std.semver.is_valid_build_id:
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
  subq $488, %rsp
  movq %rdi, -48(%rbp)
std.semver.is_valid_build_id_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.is_valid_build_id_block_0
std.semver.is_valid_build_id_block_0:
  leaq str_hdr_0(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -288(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -296(%rbp)
  movq -288(%rbp), %rdi
  movq -296(%rbp), %rsi
  call lm_key_eq
  mov -304(%rbp), rax
  movq -304(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -312(%rbp)
  movq -312(%rbp), %rax
  testq %rax, %rax
  jne std.semver.is_valid_build_id_block_3
  jmp std.semver.is_valid_build_id_block_5
std.semver.is_valid_build_id_block_3:
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rax
  jmp std.semver.is_valid_build_id_epilogue
std.semver.is_valid_build_id_block_5:
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.is_valid_build_id_block_7
std.semver.is_valid_build_id_block_7:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rdi
  call lm_list_len
  mov -336(%rbp), rax
  movq -336(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -344(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -352(%rbp)
  movq -352(%rbp), %rax
  cmpq -344(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -360(%rbp)
  movq -360(%rbp), %rax
  movq -104(%rbp), %rdx
  movl %eax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rax
  testq %rax, %rax
  jne std.semver.is_valid_build_id_block_10
  jmp std.semver.is_valid_build_id_block_25
std.semver.is_valid_build_id_block_10:
  movq $1, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -376(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -384(%rbp)
  movq -384(%rbp), %rax
  addq -376(%rbp), %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -416(%rbp)
  movq -400(%rbp), %rdi
  movq -408(%rbp), %rsi
  movq -416(%rbp), %rdx
  call substring
  mov -424(%rbp), rax
  movq -424(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rdi
  call std.semver.is_valid_char
  mov -440(%rbp), rax
  movq -440(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  cmpq -448(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  movq -152(%rbp), %rdx
  movl %eax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  testq %rax, %rax
  jne std.semver.is_valid_build_id_block_18
  jmp std.semver.is_valid_build_id_block_20
std.semver.is_valid_build_id_block_18:
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -480(%rbp), %rax
  jmp std.semver.is_valid_build_id_epilogue
std.semver.is_valid_build_id_block_20:
  movq $1, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  addq -488(%rbp), %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.is_valid_build_id_block_7
std.semver.is_valid_build_id_block_25:
  movq $1, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  jmp std.semver.is_valid_build_id_epilogue
std.semver.is_valid_build_id_epilogue:
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
.Lfunc_end_std.semver.is_valid_build_id:

.globl std.semver.is_valid_prerelease_id
std.semver.is_valid_prerelease_id:
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
  subq $712, %rsp
  movq %rdi, -48(%rbp)
std.semver.is_valid_prerelease_id_entry:
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
  jmp std.semver.is_valid_prerelease_id_block_0
std.semver.is_valid_prerelease_id_block_0:
  leaq str_hdr_1(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -376(%rbp)
  movq -368(%rbp), %rdi
  movq -376(%rbp), %rsi
  call lm_key_eq
  mov -384(%rbp), rax
  movq -384(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rax
  testq %rax, %rax
  jne std.semver.is_valid_prerelease_id_block_3
  jmp std.semver.is_valid_prerelease_id_block_5
std.semver.is_valid_prerelease_id_block_3:
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  jmp std.semver.is_valid_prerelease_id_epilogue
std.semver.is_valid_prerelease_id_block_5:
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.is_valid_prerelease_id_block_7
std.semver.is_valid_prerelease_id_block_7:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -408(%rbp), %rdi
  call lm_list_len
  mov -416(%rbp), rax
  movq -416(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  cmpq -424(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -440(%rbp)
  movq -440(%rbp), %rax
  movq -104(%rbp), %rdx
  movl %eax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  testq %rax, %rax
  jne std.semver.is_valid_prerelease_id_block_10
  jmp std.semver.is_valid_prerelease_id_block_25
std.semver.is_valid_prerelease_id_block_10:
  movq $1, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  addq -456(%rbp), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -480(%rbp), %rdi
  movq -488(%rbp), %rsi
  movq -496(%rbp), %rdx
  call substring
  mov -504(%rbp), rax
  movq -504(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rdi
  call std.semver.is_valid_char
  mov -520(%rbp), rax
  movq -520(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -536(%rbp), %rax
  cmpq -528(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  movq -152(%rbp), %rdx
  movl %eax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rax
  testq %rax, %rax
  jne std.semver.is_valid_prerelease_id_block_18
  jmp std.semver.is_valid_prerelease_id_block_20
std.semver.is_valid_prerelease_id_block_18:
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rax
  jmp std.semver.is_valid_prerelease_id_epilogue
std.semver.is_valid_prerelease_id_block_20:
  movq $1, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -576(%rbp), %rax
  addq -568(%rbp), %rax
  movq %rax, -584(%rbp)
  movq -584(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.is_valid_prerelease_id_block_7
std.semver.is_valid_prerelease_id_block_25:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rdi
  call std.semver.is_numeric
  mov -608(%rbp), rax
  movq -608(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rax
  testq %rax, %rax
  jne std.semver.is_valid_prerelease_id_block_27
  jmp std.semver.is_valid_prerelease_id_block_41
std.semver.is_valid_prerelease_id_block_27:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -624(%rbp), %rdi
  call lm_list_len
  mov -632(%rbp), rax
  movq -632(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  cmpq -640(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  movq -224(%rbp), %rdx
  movl %eax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  testq %rax, %rax
  jne std.semver.is_valid_prerelease_id_block_31
  jmp std.semver.is_valid_prerelease_id_block_40
std.semver.is_valid_prerelease_id_block_31:
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -672(%rbp), %rdi
  movq -680(%rbp), %rsi
  movq -688(%rbp), %rdx
  call substring
  mov -696(%rbp), rax
  movq -696(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_2(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -712(%rbp)
  movq -704(%rbp), %rdi
  movq -712(%rbp), %rsi
  call lm_key_eq
  mov -720(%rbp), rax
  movq -720(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -728(%rbp), %rax
  testq %rax, %rax
  jne std.semver.is_valid_prerelease_id_block_37
  jmp std.semver.is_valid_prerelease_id_block_39
std.semver.is_valid_prerelease_id_block_37:
  movq $0, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -736(%rbp), %rax
  jmp std.semver.is_valid_prerelease_id_epilogue
std.semver.is_valid_prerelease_id_block_39:
  jmp std.semver.is_valid_prerelease_id_block_40
std.semver.is_valid_prerelease_id_block_40:
  jmp std.semver.is_valid_prerelease_id_block_41
std.semver.is_valid_prerelease_id_block_41:
  movq $1, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rax
  jmp std.semver.is_valid_prerelease_id_epilogue
std.semver.is_valid_prerelease_id_epilogue:
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
.Lfunc_end_std.semver.is_valid_prerelease_id:

.globl std.semver.byte_ord
std.semver.byte_ord:
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
  subq $1288, %rsp
  movq %rdi, -48(%rbp)
std.semver.byte_ord_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.byte_ord_block_0
std.semver.byte_ord_block_0:
  leaq str_hdr_3(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.byte_ord_block_3
std.semver.byte_ord_block_3:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -584(%rbp), %rdi
  call lm_list_len
  mov -592(%rbp), rax
  movq -592(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  cmpq -600(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rax
  movq -88(%rbp), %rdx
  movl %eax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -624(%rbp), %rax
  testq %rax, %rax
  jne std.semver.byte_ord_block_6
  jmp std.semver.byte_ord_block_21
std.semver.byte_ord_block_6:
  movq $1, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -640(%rbp), %rax
  addq -632(%rbp), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -656(%rbp), %rdi
  movq -664(%rbp), %rsi
  movq -672(%rbp), %rdx
  call substring
  mov -680(%rbp), rax
  movq -680(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -688(%rbp), %rdi
  movq -696(%rbp), %rsi
  call lm_key_eq
  mov -704(%rbp), rax
  movq -704(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -712(%rbp)
  movq -712(%rbp), %rax
  testq %rax, %rax
  jne std.semver.byte_ord_block_12
  jmp std.semver.byte_ord_block_16
std.semver.byte_ord_block_12:
  movq $97, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq $97, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -728(%rbp), %rax
  addq -720(%rbp), %rax
  movq %rax, -736(%rbp)
  movq -736(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_block_16:
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -760(%rbp), %rax
  addq -752(%rbp), %rax
  movq %rax, -768(%rbp)
  movq -768(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -776(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.byte_ord_block_3
std.semver.byte_ord_block_21:
  leaq str_hdr_4(%rip), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -784(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.byte_ord_block_25
std.semver.byte_ord_block_25:
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -792(%rbp), %rdi
  call lm_list_len
  mov -800(%rbp), rax
  movq -800(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -816(%rbp), %rax
  cmpq -808(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -824(%rbp)
  movq -824(%rbp), %rax
  movq -208(%rbp), %rdx
  movl %eax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -832(%rbp)
  movq -832(%rbp), %rax
  testq %rax, %rax
  jne std.semver.byte_ord_block_28
  jmp std.semver.byte_ord_block_43
std.semver.byte_ord_block_28:
  movq $1, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -848(%rbp), %rax
  addq -840(%rbp), %rax
  movq %rax, -856(%rbp)
  movq -856(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -864(%rbp), %rdi
  movq -872(%rbp), %rsi
  movq -880(%rbp), %rdx
  call substring
  mov -888(%rbp), rax
  movq -888(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -896(%rbp), %rdi
  movq -904(%rbp), %rsi
  call lm_key_eq
  mov -912(%rbp), rax
  movq -912(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -920(%rbp), %rax
  testq %rax, %rax
  jne std.semver.byte_ord_block_34
  jmp std.semver.byte_ord_block_38
std.semver.byte_ord_block_34:
  movq $65, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq $65, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -928(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -936(%rbp), %rax
  addq -928(%rbp), %rax
  movq %rax, -944(%rbp)
  movq -944(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -952(%rbp), %rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_block_38:
  movq $1, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -960(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -968(%rbp), %rax
  addq -960(%rbp), %rax
  movq %rax, -976(%rbp)
  movq -976(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -984(%rbp)
  movq -984(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.byte_ord_block_25
std.semver.byte_ord_block_43:
  leaq str_hdr_5(%rip), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -992(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.byte_ord_block_47
std.semver.byte_ord_block_47:
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -1000(%rbp), %rdi
  call lm_list_len
  mov -1008(%rbp), rax
  movq -1008(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1016(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -1024(%rbp), %rax
  cmpq -1016(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1032(%rbp)
  movq -1032(%rbp), %rax
  movq -328(%rbp), %rdx
  movl %eax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -1040(%rbp), %rax
  testq %rax, %rax
  jne std.semver.byte_ord_block_50
  jmp std.semver.byte_ord_block_65
std.semver.byte_ord_block_50:
  movq $1, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1048(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1056(%rbp)
  movq -1056(%rbp), %rax
  addq -1048(%rbp), %rax
  movq %rax, -1064(%rbp)
  movq -1064(%rbp), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1072(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1080(%rbp)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1088(%rbp)
  movq -1072(%rbp), %rdi
  movq -1080(%rbp), %rsi
  movq -1088(%rbp), %rdx
  call substring
  mov -1096(%rbp), rax
  movq -1096(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1104(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1112(%rbp)
  movq -1104(%rbp), %rdi
  movq -1112(%rbp), %rsi
  call lm_key_eq
  mov -1120(%rbp), rax
  movq -1120(%rbp), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1128(%rbp)
  movq -1128(%rbp), %rax
  testq %rax, %rax
  jne std.semver.byte_ord_block_56
  jmp std.semver.byte_ord_block_60
std.semver.byte_ord_block_56:
  movq $48, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq $48, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1136(%rbp)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1144(%rbp)
  movq -1144(%rbp), %rax
  addq -1136(%rbp), %rax
  movq %rax, -1152(%rbp)
  movq -1152(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1160(%rbp)
  movq -1160(%rbp), %rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_block_60:
  movq $1, %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1168(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1176(%rbp)
  movq -1176(%rbp), %rax
  addq -1168(%rbp), %rax
  movq %rax, -1184(%rbp)
  movq -1184(%rbp), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1192(%rbp)
  movq -1192(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.byte_ord_block_47
std.semver.byte_ord_block_65:
  leaq str_hdr_6(%rip), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1200(%rbp)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1208(%rbp)
  movq -1200(%rbp), %rdi
  movq -1208(%rbp), %rsi
  call lm_key_eq
  mov -1216(%rbp), rax
  movq -1216(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1224(%rbp)
  movq -1224(%rbp), %rax
  testq %rax, %rax
  jne std.semver.byte_ord_block_68
  jmp std.semver.byte_ord_block_70
std.semver.byte_ord_block_68:
  movq $45, %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1232(%rbp)
  movq -1232(%rbp), %rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_block_70:
  leaq str_hdr_7(%rip), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1240(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1248(%rbp)
  movq -1240(%rbp), %rdi
  movq -1248(%rbp), %rsi
  call lm_key_eq
  mov -1256(%rbp), rax
  movq -1256(%rbp), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1264(%rbp)
  movq -1264(%rbp), %rax
  testq %rax, %rax
  jne std.semver.byte_ord_block_73
  jmp std.semver.byte_ord_block_75
std.semver.byte_ord_block_73:
  movq $46, %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1272(%rbp)
  movq -1272(%rbp), %rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_block_75:
  leaq str_hdr_8(%rip), %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1280(%rbp)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -1280(%rbp), %rdi
  movq -1288(%rbp), %rsi
  call lm_key_eq
  mov -1296(%rbp), rax
  movq -1296(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1304(%rbp)
  movq -1304(%rbp), %rax
  testq %rax, %rax
  jne std.semver.byte_ord_block_78
  jmp std.semver.byte_ord_block_80
std.semver.byte_ord_block_78:
  movq $43, %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1312(%rbp)
  movq -1312(%rbp), %rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_block_80:
  movq $0, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1320(%rbp)
  movq -1320(%rbp), %rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_epilogue:
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
.Lfunc_end_std.semver.byte_ord:

.globl std.semver.is_numeric
std.semver.is_numeric:
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
std.semver.is_numeric_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.is_numeric_block_0
std.semver.is_numeric_block_0:
  leaq str_hdr_9(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -304(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -312(%rbp)
  movq -304(%rbp), %rdi
  movq -312(%rbp), %rsi
  call lm_key_eq
  mov -320(%rbp), rax
  movq -320(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  testq %rax, %rax
  jne std.semver.is_numeric_block_3
  jmp std.semver.is_numeric_block_5
std.semver.is_numeric_block_3:
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rax
  jmp std.semver.is_numeric_epilogue
std.semver.is_numeric_block_5:
  leaq str_hdr_10(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.is_numeric_block_8
std.semver.is_numeric_block_8:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -344(%rbp)
  movq -344(%rbp), %rdi
  call lm_list_len
  mov -352(%rbp), rax
  movq -352(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rax
  cmpq -360(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -376(%rbp)
  movq -376(%rbp), %rax
  movq -112(%rbp), %rdx
  movl %eax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -384(%rbp)
  movq -384(%rbp), %rax
  testq %rax, %rax
  jne std.semver.is_numeric_block_11
  jmp std.semver.is_numeric_block_27
std.semver.is_numeric_block_11:
  movq $1, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  addq -392(%rbp), %rax
  movq %rax, -408(%rbp)
  movq -408(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -416(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -416(%rbp), %rdi
  movq -424(%rbp), %rsi
  movq -432(%rbp), %rdx
  call substring
  mov -440(%rbp), rax
  movq -440(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -448(%rbp), %rdi
  movq -456(%rbp), %rsi
  call std.semver.index_of
  mov -464(%rbp), rax
  movq -464(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  negq %rax
  movq %rax, -480(%rbp)
  movq -480(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  cmpq -488(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  movq -176(%rbp), %rdx
  movl %eax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  testq %rax, %rax
  jne std.semver.is_numeric_block_20
  jmp std.semver.is_numeric_block_22
std.semver.is_numeric_block_20:
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  jmp std.semver.is_numeric_epilogue
std.semver.is_numeric_block_22:
  movq $1, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -536(%rbp), %rax
  addq -528(%rbp), %rax
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.is_numeric_block_8
std.semver.is_numeric_block_27:
  movq $1, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rax
  jmp std.semver.is_numeric_epilogue
std.semver.is_numeric_epilogue:
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
.Lfunc_end_std.semver.is_numeric:

.globl std.semver.split_by_dot
std.semver.split_by_dot:
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
std.semver.split_by_dot_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.split_by_dot_block_0
std.semver.split_by_dot_block_0:
  movq $0, %rdi
  call lm_list_new
  mov -304(%rbp), rax
  movq -304(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -312(%rbp)
  movq -312(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_11(%rip), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.split_by_dot_block_5
std.semver.split_by_dot_block_5:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rdi
  call lm_list_len
  mov -328(%rbp), rax
  movq -328(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -344(%rbp)
  movq -344(%rbp), %rax
  cmpq -336(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -352(%rbp)
  movq -352(%rbp), %rax
  movq -104(%rbp), %rdx
  movl %eax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -360(%rbp), %rax
  testq %rax, %rax
  jne std.semver.split_by_dot_block_8
  jmp std.semver.split_by_dot_block_28
std.semver.split_by_dot_block_8:
  movq $1, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -376(%rbp)
  movq -376(%rbp), %rax
  addq -368(%rbp), %rax
  movq %rax, -384(%rbp)
  movq -384(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -392(%rbp), %rdi
  movq -400(%rbp), %rsi
  movq -408(%rbp), %rdx
  call substring
  mov -416(%rbp), rax
  movq -416(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_12(%rip), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -432(%rbp), %rdi
  movq -440(%rbp), %rsi
  call lm_key_eq
  mov -448(%rbp), rax
  movq -448(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  testq %rax, %rax
  jne std.semver.split_by_dot_block_16
  jmp std.semver.split_by_dot_block_20
std.semver.split_by_dot_block_16:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -464(%rbp), %rdi
  movq -472(%rbp), %rsi
  call lm_list_append
  mov -480(%rbp), rax
  leaq str_hdr_13(%rip), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.split_by_dot_block_23
std.semver.split_by_dot_block_20:
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -496(%rbp), %rdi
  movq -504(%rbp), %rsi
  call lm_str_concat
  mov -512(%rbp), rax
  movq -512(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.split_by_dot_block_23
std.semver.split_by_dot_block_23:
  movq $1, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -536(%rbp), %rax
  addq -528(%rbp), %rax
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.split_by_dot_block_5
std.semver.split_by_dot_block_28:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -560(%rbp), %rdi
  movq -568(%rbp), %rsi
  call lm_list_append
  mov -576(%rbp), rax
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -584(%rbp), %rax
  jmp std.semver.split_by_dot_epilogue
std.semver.split_by_dot_epilogue:
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
.Lfunc_end_std.semver.split_by_dot:

.globl std.semver.to_int
std.semver.to_int:
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
  subq $2328, %rsp
  movq %rdi, -48(%rbp)
std.semver.to_int_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.to_int_block_0
std.semver.to_int_block_0:
  leaq str_hdr_14(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1008(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1016(%rbp)
  movq -1008(%rbp), %rdi
  movq -1016(%rbp), %rsi
  call lm_key_eq
  mov -1024(%rbp), rax
  movq -1024(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1032(%rbp)
  movq -1032(%rbp), %rax
  testq %rax, %rax
  jne std.semver.to_int_block_3
  jmp std.semver.to_int_block_6
std.semver.to_int_block_3:
  movq $1, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -1040(%rbp), %rax
  negq %rax
  movq %rax, -1048(%rbp)
  movq -1048(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1056(%rbp)
  movq -1056(%rbp), %rax
  jmp std.semver.to_int_epilogue
std.semver.to_int_block_6:
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.to_int_block_9
std.semver.to_int_block_9:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1064(%rbp)
  movq -1064(%rbp), %rdi
  call lm_list_len
  mov -1072(%rbp), rax
  movq -1072(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1080(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1088(%rbp)
  movq -1088(%rbp), %rax
  cmpq -1080(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1096(%rbp)
  movq -1096(%rbp), %rax
  movq -120(%rbp), %rdx
  movl %eax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1104(%rbp)
  movq -1104(%rbp), %rax
  testq %rax, %rax
  jne std.semver.to_int_block_12
  jmp std.semver.to_int_block_154
std.semver.to_int_block_12:
  movq $1, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1112(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1120(%rbp)
  movq -1120(%rbp), %rax
  addq -1112(%rbp), %rax
  movq %rax, -1128(%rbp)
  movq -1128(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1136(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1144(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1152(%rbp)
  movq -1136(%rbp), %rdi
  movq -1144(%rbp), %rsi
  movq -1152(%rbp), %rdx
  call substring
  mov -1160(%rbp), rax
  movq -1160(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1168(%rbp)
  movq -1168(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_15(%rip), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1176(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1184(%rbp)
  movq -1176(%rbp), %rdi
  movq -1184(%rbp), %rsi
  call lm_key_eq
  mov -1192(%rbp), rax
  movq -1192(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1200(%rbp)
  movq -1200(%rbp), %rax
  testq %rax, %rax
  jne std.semver.to_int_block_20
  jmp std.semver.to_int_block_29
std.semver.to_int_block_20:
  movq $10, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1208(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1216(%rbp)
  movq -1216(%rbp), %rax
  imulq -1208(%rbp), %rax
  movq %rax, -1224(%rbp)
  movq -1224(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1232(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1240(%rbp)
  movq -1240(%rbp), %rax
  imulq -1232(%rbp), %rax
  movq %rax, -1248(%rbp)
  movq -1248(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1256(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1264(%rbp)
  movq -1264(%rbp), %rax
  addq -1256(%rbp), %rax
  movq %rax, -1272(%rbp)
  movq -1272(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1280(%rbp)
  movq -1280(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.to_int_block_146
std.semver.to_int_block_29:
  leaq str_hdr_16(%rip), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1296(%rbp)
  movq -1288(%rbp), %rdi
  movq -1296(%rbp), %rsi
  call lm_key_eq
  mov -1304(%rbp), rax
  movq -1304(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1312(%rbp)
  movq -1312(%rbp), %rax
  testq %rax, %rax
  jne std.semver.to_int_block_32
  jmp std.semver.to_int_block_41
std.semver.to_int_block_32:
  movq $10, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1320(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1328(%rbp)
  movq -1328(%rbp), %rax
  imulq -1320(%rbp), %rax
  movq %rax, -1336(%rbp)
  movq -1336(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1344(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1352(%rbp)
  movq -1352(%rbp), %rax
  imulq -1344(%rbp), %rax
  movq %rax, -1360(%rbp)
  movq -1360(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1368(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1376(%rbp)
  movq -1376(%rbp), %rax
  addq -1368(%rbp), %rax
  movq %rax, -1384(%rbp)
  movq -1384(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1392(%rbp)
  movq -1392(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.to_int_block_145
std.semver.to_int_block_41:
  leaq str_hdr_17(%rip), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1400(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1408(%rbp)
  movq -1400(%rbp), %rdi
  movq -1408(%rbp), %rsi
  call lm_key_eq
  mov -1416(%rbp), rax
  movq -1416(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1424(%rbp)
  movq -1424(%rbp), %rax
  testq %rax, %rax
  jne std.semver.to_int_block_44
  jmp std.semver.to_int_block_53
std.semver.to_int_block_44:
  movq $10, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1432(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1440(%rbp)
  movq -1440(%rbp), %rax
  imulq -1432(%rbp), %rax
  movq %rax, -1448(%rbp)
  movq -1448(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1456(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1464(%rbp)
  movq -1464(%rbp), %rax
  imulq -1456(%rbp), %rax
  movq %rax, -1472(%rbp)
  movq -1472(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1480(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1488(%rbp)
  movq -1488(%rbp), %rax
  addq -1480(%rbp), %rax
  movq %rax, -1496(%rbp)
  movq -1496(%rbp), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1504(%rbp)
  movq -1504(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.to_int_block_144
std.semver.to_int_block_53:
  leaq str_hdr_18(%rip), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1512(%rbp)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1520(%rbp)
  movq -1512(%rbp), %rdi
  movq -1520(%rbp), %rsi
  call lm_key_eq
  mov -1528(%rbp), rax
  movq -1528(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1536(%rbp)
  movq -1536(%rbp), %rax
  testq %rax, %rax
  jne std.semver.to_int_block_56
  jmp std.semver.to_int_block_65
std.semver.to_int_block_56:
  movq $10, %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1544(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1552(%rbp)
  movq -1552(%rbp), %rax
  imulq -1544(%rbp), %rax
  movq %rax, -1560(%rbp)
  movq -1560(%rbp), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1568(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1576(%rbp)
  movq -1576(%rbp), %rax
  imulq -1568(%rbp), %rax
  movq %rax, -1584(%rbp)
  movq -1584(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1592(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1600(%rbp)
  movq -1600(%rbp), %rax
  addq -1592(%rbp), %rax
  movq %rax, -1608(%rbp)
  movq -1608(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1616(%rbp)
  movq -1616(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.to_int_block_143
std.semver.to_int_block_65:
  leaq str_hdr_19(%rip), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1624(%rbp)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1632(%rbp)
  movq -1624(%rbp), %rdi
  movq -1632(%rbp), %rsi
  call lm_key_eq
  mov -1640(%rbp), rax
  movq -1640(%rbp), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1648(%rbp)
  movq -1648(%rbp), %rax
  testq %rax, %rax
  jne std.semver.to_int_block_68
  jmp std.semver.to_int_block_77
std.semver.to_int_block_68:
  movq $10, %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1656(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1664(%rbp)
  movq -1664(%rbp), %rax
  imulq -1656(%rbp), %rax
  movq %rax, -1672(%rbp)
  movq -1672(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4, %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1680(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1688(%rbp)
  movq -1688(%rbp), %rax
  imulq -1680(%rbp), %rax
  movq %rax, -1696(%rbp)
  movq -1696(%rbp), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4, %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1704(%rbp)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1712(%rbp)
  movq -1712(%rbp), %rax
  addq -1704(%rbp), %rax
  movq %rax, -1720(%rbp)
  movq -1720(%rbp), %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1728(%rbp)
  movq -1728(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.to_int_block_142
std.semver.to_int_block_77:
  leaq str_hdr_20(%rip), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1736(%rbp)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1744(%rbp)
  movq -1736(%rbp), %rdi
  movq -1744(%rbp), %rsi
  call lm_key_eq
  mov -1752(%rbp), rax
  movq -1752(%rbp), %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1760(%rbp)
  movq -1760(%rbp), %rax
  testq %rax, %rax
  jne std.semver.to_int_block_80
  jmp std.semver.to_int_block_89
std.semver.to_int_block_80:
  movq $10, %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1768(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1776(%rbp)
  movq -1776(%rbp), %rax
  imulq -1768(%rbp), %rax
  movq %rax, -1784(%rbp)
  movq -1784(%rbp), %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1792(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1800(%rbp)
  movq -1800(%rbp), %rax
  imulq -1792(%rbp), %rax
  movq %rax, -1808(%rbp)
  movq -1808(%rbp), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1816(%rbp)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1824(%rbp)
  movq -1824(%rbp), %rax
  addq -1816(%rbp), %rax
  movq %rax, -1832(%rbp)
  movq -1832(%rbp), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1840(%rbp)
  movq -1840(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.to_int_block_141
std.semver.to_int_block_89:
  leaq str_hdr_21(%rip), %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1848(%rbp)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1856(%rbp)
  movq -1848(%rbp), %rdi
  movq -1856(%rbp), %rsi
  call lm_key_eq
  mov -1864(%rbp), rax
  movq -1864(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1872(%rbp)
  movq -1872(%rbp), %rax
  testq %rax, %rax
  jne std.semver.to_int_block_92
  jmp std.semver.to_int_block_101
std.semver.to_int_block_92:
  movq $10, %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1880(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1888(%rbp)
  movq -1888(%rbp), %rax
  imulq -1880(%rbp), %rax
  movq %rax, -1896(%rbp)
  movq -1896(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq $6, %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1904(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1912(%rbp)
  movq -1912(%rbp), %rax
  imulq -1904(%rbp), %rax
  movq %rax, -1920(%rbp)
  movq -1920(%rbp), %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  movq $6, %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1928(%rbp)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1936(%rbp)
  movq -1936(%rbp), %rax
  addq -1928(%rbp), %rax
  movq %rax, -1944(%rbp)
  movq -1944(%rbp), %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1952(%rbp)
  movq -1952(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.to_int_block_140
std.semver.to_int_block_101:
  leaq str_hdr_22(%rip), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1960(%rbp)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1968(%rbp)
  movq -1960(%rbp), %rdi
  movq -1968(%rbp), %rsi
  call lm_key_eq
  mov -1976(%rbp), rax
  movq -1976(%rbp), %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1984(%rbp)
  movq -1984(%rbp), %rax
  testq %rax, %rax
  jne std.semver.to_int_block_104
  jmp std.semver.to_int_block_113
std.semver.to_int_block_104:
  movq $10, %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1992(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2000(%rbp)
  movq -2000(%rbp), %rax
  imulq -1992(%rbp), %rax
  movq %rax, -2008(%rbp)
  movq -2008(%rbp), %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq $7, %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2016(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2024(%rbp)
  movq -2024(%rbp), %rax
  imulq -2016(%rbp), %rax
  movq %rax, -2032(%rbp)
  movq -2032(%rbp), %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  movq $7, %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2040(%rbp)
  movq -720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2048(%rbp)
  movq -2048(%rbp), %rax
  addq -2040(%rbp), %rax
  movq %rax, -2056(%rbp)
  movq -2056(%rbp), %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2064(%rbp)
  movq -2064(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.to_int_block_139
std.semver.to_int_block_113:
  leaq str_hdr_23(%rip), %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2072(%rbp)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2080(%rbp)
  movq -2072(%rbp), %rdi
  movq -2080(%rbp), %rsi
  call lm_key_eq
  mov -2088(%rbp), rax
  movq -2088(%rbp), %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2096(%rbp)
  movq -2096(%rbp), %rax
  testq %rax, %rax
  jne std.semver.to_int_block_116
  jmp std.semver.to_int_block_125
std.semver.to_int_block_116:
  movq $10, %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2104(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2112(%rbp)
  movq -2112(%rbp), %rax
  imulq -2104(%rbp), %rax
  movq %rax, -2120(%rbp)
  movq -2120(%rbp), %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  movq $8, %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2128(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2136(%rbp)
  movq -2136(%rbp), %rax
  imulq -2128(%rbp), %rax
  movq %rax, -2144(%rbp)
  movq -2144(%rbp), %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  movq $8, %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2152(%rbp)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2160(%rbp)
  movq -2160(%rbp), %rax
  addq -2152(%rbp), %rax
  movq %rax, -2168(%rbp)
  movq -2168(%rbp), %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2176(%rbp)
  movq -2176(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.to_int_block_138
std.semver.to_int_block_125:
  leaq str_hdr_24(%rip), %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2184(%rbp)
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2192(%rbp)
  movq -2184(%rbp), %rdi
  movq -2192(%rbp), %rsi
  call lm_key_eq
  mov -2200(%rbp), rax
  movq -2200(%rbp), %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2208(%rbp)
  movq -2208(%rbp), %rax
  testq %rax, %rax
  jne std.semver.to_int_block_128
  jmp std.semver.to_int_block_151
std.semver.to_int_block_128:
  movq $10, %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2216(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2224(%rbp)
  movq -2224(%rbp), %rax
  imulq -2216(%rbp), %rax
  movq %rax, -2232(%rbp)
  movq -2232(%rbp), %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq $9, %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2240(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2248(%rbp)
  movq -2248(%rbp), %rax
  imulq -2240(%rbp), %rax
  movq %rax, -2256(%rbp)
  movq -2256(%rbp), %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  movq $9, %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2264(%rbp)
  movq -864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2272(%rbp)
  movq -2272(%rbp), %rax
  addq -2264(%rbp), %rax
  movq %rax, -2280(%rbp)
  movq -2280(%rbp), %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2288(%rbp)
  movq -2288(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.to_int_block_137
std.semver.to_int_block_137:
  jmp std.semver.to_int_block_138
std.semver.to_int_block_138:
  jmp std.semver.to_int_block_139
std.semver.to_int_block_139:
  jmp std.semver.to_int_block_140
std.semver.to_int_block_140:
  jmp std.semver.to_int_block_141
std.semver.to_int_block_141:
  jmp std.semver.to_int_block_142
std.semver.to_int_block_142:
  jmp std.semver.to_int_block_143
std.semver.to_int_block_143:
  jmp std.semver.to_int_block_144
std.semver.to_int_block_144:
  jmp std.semver.to_int_block_145
std.semver.to_int_block_145:
  jmp std.semver.to_int_block_146
std.semver.to_int_block_146:
  movq $1, %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2296(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2304(%rbp)
  movq -2304(%rbp), %rax
  addq -2296(%rbp), %rax
  movq %rax, -2312(%rbp)
  movq -2312(%rbp), %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2320(%rbp)
  movq -2320(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.to_int_block_9
std.semver.to_int_block_151:
  movq $1, %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  movq -888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2328(%rbp)
  movq -2328(%rbp), %rax
  negq %rax
  movq %rax, -2336(%rbp)
  movq -2336(%rbp), %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2344(%rbp)
  movq -2344(%rbp), %rax
  jmp std.semver.to_int_epilogue
std.semver.to_int_block_154:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2352(%rbp)
  movq -2352(%rbp), %rax
  jmp std.semver.to_int_epilogue
std.semver.to_int_epilogue:
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
.Lfunc_end_std.semver.to_int:

.globl std.semver.compare
std.semver.compare:
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
std.semver.compare_entry:
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
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.compare_block_0
std.semver.compare_block_0:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -176(%rbp)
  movq -168(%rbp), %rdi
  movq -176(%rbp), %rsi
  call std.semver.Version.compare
  mov -184(%rbp), rax
  movq -184(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -192(%rbp)
  movq -192(%rbp), %rax
  jmp std.semver.compare_epilogue
std.semver.compare_epilogue:
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
.Lfunc_end_std.semver.compare:

.globl std.semver.parse
std.semver.parse:
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
  subq $3016, %rsp
  movq %rdi, -48(%rbp)
std.semver.parse_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.parse_block_0
std.semver.parse_block_0:
  leaq str_hdr_25(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1136(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1144(%rbp)
  movq -1136(%rbp), %rdi
  movq -1144(%rbp), %rsi
  call lm_key_eq
  mov -1152(%rbp), rax
  movq -1152(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1160(%rbp)
  movq -1160(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_3
  jmp std.semver.parse_block_5
std.semver.parse_block_3:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1168(%rbp)
  movq -1168(%rbp), %rdi
  call lm_error_new
  mov -1176(%rbp), rax
  movq -1176(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1184(%rbp)
  movq -1184(%rbp), %rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_5:
  leaq str_hdr_26(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1192(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1200(%rbp)
  movq -1192(%rbp), %rdi
  movq -1200(%rbp), %rsi
  call std.semver.index_of
  mov -1208(%rbp), rax
  movq -1208(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1216(%rbp)
  movq -1216(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1224(%rbp)
  movq -1224(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_27(%rip), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1232(%rbp)
  movq -1232(%rbp), %rax
  negq %rax
  movq %rax, -1240(%rbp)
  movq -1240(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1248(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1256(%rbp)
  movq -1256(%rbp), %rax
  cmpq -1248(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -1264(%rbp)
  movq -1264(%rbp), %rax
  movq -144(%rbp), %rdx
  movl %eax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1272(%rbp)
  movq -1272(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_14
  jmp std.semver.parse_block_43
std.semver.parse_block_14:
  movq $1, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1280(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -1288(%rbp), %rax
  addq -1280(%rbp), %rax
  movq %rax, -1296(%rbp)
  movq -1296(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1304(%rbp)
  movq -1304(%rbp), %rdi
  call lm_list_len
  mov -1312(%rbp), rax
  movq -1312(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1320(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1328(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1336(%rbp)
  movq -1320(%rbp), %rdi
  movq -1328(%rbp), %rsi
  movq -1336(%rbp), %rdx
  call substring
  mov -1344(%rbp), rax
  movq -1344(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1352(%rbp)
  movq -1352(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1360(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1368(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1376(%rbp)
  movq -1360(%rbp), %rdi
  movq -1368(%rbp), %rsi
  movq -1376(%rbp), %rdx
  call substring
  mov -1384(%rbp), rax
  movq -1384(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1392(%rbp)
  movq -1392(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1400(%rbp)
  movq -1400(%rbp), %rdi
  call std.semver.split_by_dot
  mov -1408(%rbp), rax
  movq -1408(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1416(%rbp)
  movq -1416(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.parse_block_27
std.semver.parse_block_27:
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1424(%rbp)
  movq -1424(%rbp), %rdi
  call lm_list_len
  mov -1432(%rbp), rax
  movq -1432(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1440(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1448(%rbp)
  movq -1448(%rbp), %rax
  cmpq -1440(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1456(%rbp)
  movq -1456(%rbp), %rax
  movq -240(%rbp), %rdx
  movl %eax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1464(%rbp)
  movq -1464(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_30
  jmp std.semver.parse_block_42
std.semver.parse_block_30:
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1472(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1480(%rbp)
  movq -1472(%rbp), %rdi
  movq -1480(%rbp), %rsi
  call lm_list_get
  mov -1488(%rbp), rax
  movq -1488(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1496(%rbp)
  movq -1496(%rbp), %rdi
  call std.semver.is_valid_build_id
  mov -1504(%rbp), rax
  movq -1504(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1512(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1520(%rbp)
  movq -1520(%rbp), %rax
  cmpq -1512(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -1528(%rbp)
  movq -1528(%rbp), %rax
  movq -264(%rbp), %rdx
  movl %eax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1536(%rbp)
  movq -1536(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_35
  jmp std.semver.parse_block_37
std.semver.parse_block_35:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1544(%rbp)
  movq -1544(%rbp), %rdi
  call lm_error_new
  mov -1552(%rbp), rax
  movq -1552(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1560(%rbp)
  movq -1560(%rbp), %rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_37:
  movq $1, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1568(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1576(%rbp)
  movq -1576(%rbp), %rax
  addq -1568(%rbp), %rax
  movq %rax, -1584(%rbp)
  movq -1584(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1592(%rbp)
  movq -1592(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.parse_block_27
std.semver.parse_block_42:
  jmp std.semver.parse_block_43
std.semver.parse_block_43:
  leaq str_hdr_28(%rip), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1600(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1608(%rbp)
  movq -1600(%rbp), %rdi
  movq -1608(%rbp), %rsi
  call std.semver.index_of
  mov -1616(%rbp), rax
  movq -1616(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1624(%rbp)
  movq -1624(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1632(%rbp)
  movq -1632(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_29(%rip), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1640(%rbp)
  movq -1640(%rbp), %rax
  negq %rax
  movq %rax, -1648(%rbp)
  movq -1648(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1656(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1664(%rbp)
  movq -1664(%rbp), %rax
  cmpq -1656(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -1672(%rbp)
  movq -1672(%rbp), %rax
  movq -368(%rbp), %rdx
  movl %eax, (%rdx)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1680(%rbp)
  movq -1680(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_52
  jmp std.semver.parse_block_81
std.semver.parse_block_52:
  movq $1, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1688(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1696(%rbp)
  movq -1696(%rbp), %rax
  addq -1688(%rbp), %rax
  movq %rax, -1704(%rbp)
  movq -1704(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1712(%rbp)
  movq -1712(%rbp), %rdi
  call lm_list_len
  mov -1720(%rbp), rax
  movq -1720(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1728(%rbp)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1736(%rbp)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1744(%rbp)
  movq -1728(%rbp), %rdi
  movq -1736(%rbp), %rsi
  movq -1744(%rbp), %rdx
  call substring
  mov -1752(%rbp), rax
  movq -1752(%rbp), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1760(%rbp)
  movq -1760(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1768(%rbp)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1776(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1784(%rbp)
  movq -1768(%rbp), %rdi
  movq -1776(%rbp), %rsi
  movq -1784(%rbp), %rdx
  call substring
  mov -1792(%rbp), rax
  movq -1792(%rbp), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1800(%rbp)
  movq -1800(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1808(%rbp)
  movq -1808(%rbp), %rdi
  call std.semver.split_by_dot
  mov -1816(%rbp), rax
  movq -1816(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1824(%rbp)
  movq -1824(%rbp), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.parse_block_65
std.semver.parse_block_65:
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1832(%rbp)
  movq -1832(%rbp), %rdi
  call lm_list_len
  mov -1840(%rbp), rax
  movq -1840(%rbp), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1848(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1856(%rbp)
  movq -1856(%rbp), %rax
  cmpq -1848(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1864(%rbp)
  movq -1864(%rbp), %rax
  movq -464(%rbp), %rdx
  movl %eax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1872(%rbp)
  movq -1872(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_68
  jmp std.semver.parse_block_80
std.semver.parse_block_68:
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1880(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1888(%rbp)
  movq -1880(%rbp), %rdi
  movq -1888(%rbp), %rsi
  call lm_list_get
  mov -1896(%rbp), rax
  movq -1896(%rbp), %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1904(%rbp)
  movq -1904(%rbp), %rdi
  call std.semver.is_valid_prerelease_id
  mov -1912(%rbp), rax
  movq -1912(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1920(%rbp)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1928(%rbp)
  movq -1928(%rbp), %rax
  cmpq -1920(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -1936(%rbp)
  movq -1936(%rbp), %rax
  movq -488(%rbp), %rdx
  movl %eax, (%rdx)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1944(%rbp)
  movq -1944(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_73
  jmp std.semver.parse_block_75
std.semver.parse_block_73:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1952(%rbp)
  movq -1952(%rbp), %rdi
  call lm_error_new
  mov -1960(%rbp), rax
  movq -1960(%rbp), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1968(%rbp)
  movq -1968(%rbp), %rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_75:
  movq $1, %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1976(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1984(%rbp)
  movq -1984(%rbp), %rax
  addq -1976(%rbp), %rax
  movq %rax, -1992(%rbp)
  movq -1992(%rbp), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2000(%rbp)
  movq -2000(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.parse_block_65
std.semver.parse_block_80:
  jmp std.semver.parse_block_81
std.semver.parse_block_81:
  leaq str_hdr_30(%rip), %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2008(%rbp)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2016(%rbp)
  movq -2008(%rbp), %rdi
  movq -2016(%rbp), %rsi
  call std.semver.index_of
  mov -2024(%rbp), rax
  movq -2024(%rbp), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2032(%rbp)
  movq -2032(%rbp), %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2040(%rbp)
  movq -2040(%rbp), %rax
  negq %rax
  movq %rax, -2048(%rbp)
  movq -2048(%rbp), %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2056(%rbp)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2064(%rbp)
  movq -2064(%rbp), %rax
  cmpq -2056(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2072(%rbp)
  movq -2072(%rbp), %rax
  movq -576(%rbp), %rdx
  movl %eax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2080(%rbp)
  movq -2080(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_88
  jmp std.semver.parse_block_90
std.semver.parse_block_88:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2088(%rbp)
  movq -2088(%rbp), %rdi
  call lm_error_new
  mov -2096(%rbp), rax
  movq -2096(%rbp), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2104(%rbp)
  movq -2104(%rbp), %rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_90:
  movq $0, %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2112(%rbp)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2120(%rbp)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2128(%rbp)
  movq -2112(%rbp), %rdi
  movq -2120(%rbp), %rsi
  movq -2128(%rbp), %rdx
  call substring
  mov -2136(%rbp), rax
  movq -2136(%rbp), %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2144(%rbp)
  movq -2144(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2152(%rbp)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2160(%rbp)
  movq -2160(%rbp), %rax
  addq -2152(%rbp), %rax
  movq %rax, -2168(%rbp)
  movq -2168(%rbp), %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2176(%rbp)
  movq -2176(%rbp), %rdi
  call lm_list_len
  mov -2184(%rbp), rax
  movq -2184(%rbp), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2192(%rbp)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2200(%rbp)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2208(%rbp)
  movq -2192(%rbp), %rdi
  movq -2200(%rbp), %rsi
  movq -2208(%rbp), %rdx
  call substring
  mov -2216(%rbp), rax
  movq -2216(%rbp), %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2224(%rbp)
  movq -2224(%rbp), %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_31(%rip), %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2232(%rbp)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2240(%rbp)
  movq -2232(%rbp), %rdi
  movq -2240(%rbp), %rsi
  call std.semver.index_of
  mov -2248(%rbp), rax
  movq -2248(%rbp), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2256(%rbp)
  movq -2256(%rbp), %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2264(%rbp)
  movq -2264(%rbp), %rax
  negq %rax
  movq %rax, -2272(%rbp)
  movq -2272(%rbp), %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2280(%rbp)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2288(%rbp)
  movq -2288(%rbp), %rax
  cmpq -2280(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2296(%rbp)
  movq -2296(%rbp), %rax
  movq -704(%rbp), %rdx
  movl %eax, (%rdx)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2304(%rbp)
  movq -2304(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_106
  jmp std.semver.parse_block_108
std.semver.parse_block_106:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2312(%rbp)
  movq -2312(%rbp), %rdi
  call lm_error_new
  mov -2320(%rbp), rax
  movq -2320(%rbp), %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2328(%rbp)
  movq -2328(%rbp), %rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_108:
  movq $0, %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2336(%rbp)
  movq -720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2344(%rbp)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2352(%rbp)
  movq -2336(%rbp), %rdi
  movq -2344(%rbp), %rsi
  movq -2352(%rbp), %rdx
  call substring
  mov -2360(%rbp), rax
  movq -2360(%rbp), %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2368(%rbp)
  movq -2368(%rbp), %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2376(%rbp)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2384(%rbp)
  movq -2384(%rbp), %rax
  addq -2376(%rbp), %rax
  movq %rax, -2392(%rbp)
  movq -2392(%rbp), %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2400(%rbp)
  movq -2400(%rbp), %rdi
  call lm_list_len
  mov -2408(%rbp), rax
  movq -2408(%rbp), %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2416(%rbp)
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2424(%rbp)
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2432(%rbp)
  movq -2416(%rbp), %rdi
  movq -2424(%rbp), %rsi
  movq -2432(%rbp), %rdx
  call substring
  mov -2440(%rbp), rax
  movq -2440(%rbp), %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  movq -776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2448(%rbp)
  movq -2448(%rbp), %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_32(%rip), %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2456(%rbp)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2464(%rbp)
  movq -2456(%rbp), %rdi
  movq -2464(%rbp), %rsi
  call std.semver.index_of
  mov -2472(%rbp), rax
  movq -2472(%rbp), %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2480(%rbp)
  movq -2480(%rbp), %rax
  negq %rax
  movq %rax, -2488(%rbp)
  movq -2488(%rbp), %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2496(%rbp)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2504(%rbp)
  movq -2504(%rbp), %rax
  cmpq -2496(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -2512(%rbp)
  movq -2512(%rbp), %rax
  movq -824(%rbp), %rdx
  movl %eax, (%rdx)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2520(%rbp)
  movq -2520(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_123
  jmp std.semver.parse_block_125
std.semver.parse_block_123:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2528(%rbp)
  movq -2528(%rbp), %rdi
  call lm_error_new
  mov -2536(%rbp), rax
  movq -2536(%rbp), %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2544(%rbp)
  movq -2544(%rbp), %rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_125:
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2552(%rbp)
  movq -2552(%rbp), %rdi
  call std.semver.has_invalid_leading_zero
  mov -2560(%rbp), rax
  movq -2560(%rbp), %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2568(%rbp)
  movq -2568(%rbp), %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2576(%rbp)
  movq -2576(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_131
  jmp std.semver.parse_block_128
std.semver.parse_block_128:
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2584(%rbp)
  movq -2584(%rbp), %rdi
  call std.semver.has_invalid_leading_zero
  mov -2592(%rbp), rax
  movq -2592(%rbp), %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2600(%rbp)
  movq -2600(%rbp), %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.parse_block_131
std.semver.parse_block_131:
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2608(%rbp)
  movq -2608(%rbp), %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2616(%rbp)
  movq -2616(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_136
  jmp std.semver.parse_block_133
std.semver.parse_block_133:
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2624(%rbp)
  movq -2624(%rbp), %rdi
  call std.semver.has_invalid_leading_zero
  mov -2632(%rbp), rax
  movq -2632(%rbp), %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2640(%rbp)
  movq -2640(%rbp), %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.parse_block_136
std.semver.parse_block_136:
  movq -840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2648(%rbp)
  movq -2648(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_137
  jmp std.semver.parse_block_139
std.semver.parse_block_137:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2656(%rbp)
  movq -2656(%rbp), %rdi
  call lm_error_new
  mov -2664(%rbp), rax
  movq -2664(%rbp), %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2672(%rbp)
  movq -2672(%rbp), %rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_139:
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2680(%rbp)
  movq -2680(%rbp), %rdi
  call std.semver.to_int
  mov -2688(%rbp), rax
  movq -2688(%rbp), %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  movq -888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2696(%rbp)
  movq -2696(%rbp), %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2704(%rbp)
  movq -2704(%rbp), %rax
  negq %rax
  movq %rax, -2712(%rbp)
  movq -2712(%rbp), %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2720(%rbp)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2728(%rbp)
  movq -2728(%rbp), %rax
  cmpq -2720(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2736(%rbp)
  movq -2736(%rbp), %rax
  movq -920(%rbp), %rdx
  movl %eax, (%rdx)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2744(%rbp)
  movq -2744(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_145
  jmp std.semver.parse_block_147
std.semver.parse_block_145:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2752(%rbp)
  movq -2752(%rbp), %rdi
  call lm_error_new
  mov -2760(%rbp), rax
  movq -2760(%rbp), %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2768(%rbp)
  movq -2768(%rbp), %rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_147:
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2776(%rbp)
  movq -2776(%rbp), %rdi
  call std.semver.to_int
  mov -2784(%rbp), rax
  movq -2784(%rbp), %rax
  movq -936(%rbp), %rdx
  movq %rax, (%rdx)
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2792(%rbp)
  movq -2792(%rbp), %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  movq -952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2800(%rbp)
  movq -2800(%rbp), %rax
  negq %rax
  movq %rax, -2808(%rbp)
  movq -2808(%rbp), %rax
  movq -960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2816(%rbp)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2824(%rbp)
  movq -2824(%rbp), %rax
  cmpq -2816(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2832(%rbp)
  movq -2832(%rbp), %rax
  movq -968(%rbp), %rdx
  movl %eax, (%rdx)
  movq -968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2840(%rbp)
  movq -2840(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_153
  jmp std.semver.parse_block_155
std.semver.parse_block_153:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2848(%rbp)
  movq -2848(%rbp), %rdi
  call lm_error_new
  mov -2856(%rbp), rax
  movq -2856(%rbp), %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2864(%rbp)
  movq -2864(%rbp), %rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_155:
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2872(%rbp)
  movq -2872(%rbp), %rdi
  call std.semver.to_int
  mov -2880(%rbp), rax
  movq -2880(%rbp), %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  movq -984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2888(%rbp)
  movq -2888(%rbp), %rax
  movq -992(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1000(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2896(%rbp)
  movq -2896(%rbp), %rax
  negq %rax
  movq %rax, -2904(%rbp)
  movq -2904(%rbp), %rax
  movq -1008(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2912(%rbp)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2920(%rbp)
  movq -2920(%rbp), %rax
  cmpq -2912(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2928(%rbp)
  movq -2928(%rbp), %rax
  movq -1016(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2936(%rbp)
  movq -2936(%rbp), %rax
  testq %rax, %rax
  jne std.semver.parse_block_161
  jmp std.semver.parse_block_163
std.semver.parse_block_161:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2944(%rbp)
  movq -2944(%rbp), %rdi
  call lm_error_new
  mov -2952(%rbp), rax
  movq -2952(%rbp), %rax
  movq -1024(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2960(%rbp)
  movq -2960(%rbp), %rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_163:
  # Bump Allocation: 40 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2968(%rbp)
  addq $40, %rax
  movq %rax, heap_ptr(%rip)
  movq -2968(%rbp), %rax
  movq -1040(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2976(%rbp)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2984(%rbp)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2992(%rbp)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3000(%rbp)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3008(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3016(%rbp)
  movq -2976(%rbp), %rdi
  movq -2984(%rbp), %rsi
  movq -2992(%rbp), %rdx
  movq -3000(%rbp), %rcx
  movq -3008(%rbp), %r8
  movq -3016(%rbp), %r9
  call std.semver.Version.init
  mov -3024(%rbp), rax
  movq -3024(%rbp), %rax
  movq -1048(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3032(%rbp)
  movq -3032(%rbp), %rax
  movq -1032(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3040(%rbp)
  movq -3040(%rbp), %rax
  jmp std.semver.parse_epilogue
std.semver.parse_epilogue:
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
.Lfunc_end_std.semver.parse:

.globl std.semver.has_invalid_leading_zero
std.semver.has_invalid_leading_zero:
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
  subq $312, %rsp
  movq %rdi, -48(%rbp)
std.semver.has_invalid_leading_zero_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.has_invalid_leading_zero_block_0
std.semver.has_invalid_leading_zero_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -224(%rbp)
  movq -224(%rbp), %rdi
  call lm_list_len
  mov -232(%rbp), rax
  movq -232(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -240(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -248(%rbp)
  movq -248(%rbp), %rax
  cmpq -240(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -256(%rbp)
  movq -256(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rax
  testq %rax, %rax
  jne std.semver.has_invalid_leading_zero_block_4
  jmp std.semver.has_invalid_leading_zero_block_13
std.semver.has_invalid_leading_zero_block_4:
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -272(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -280(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -288(%rbp)
  movq -272(%rbp), %rdi
  movq -280(%rbp), %rsi
  movq -288(%rbp), %rdx
  call substring
  mov -296(%rbp), rax
  movq -296(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_33(%rip), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -304(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -312(%rbp)
  movq -304(%rbp), %rdi
  movq -312(%rbp), %rsi
  call lm_key_eq
  mov -320(%rbp), rax
  movq -320(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  testq %rax, %rax
  jne std.semver.has_invalid_leading_zero_block_10
  jmp std.semver.has_invalid_leading_zero_block_12
std.semver.has_invalid_leading_zero_block_10:
  movq $1, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rax
  jmp std.semver.has_invalid_leading_zero_epilogue
std.semver.has_invalid_leading_zero_block_12:
  jmp std.semver.has_invalid_leading_zero_block_13
std.semver.has_invalid_leading_zero_block_13:
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -344(%rbp)
  movq -344(%rbp), %rax
  jmp std.semver.has_invalid_leading_zero_epilogue
std.semver.has_invalid_leading_zero_epilogue:
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
.Lfunc_end_std.semver.has_invalid_leading_zero:

.globl std.semver.Version.init
std.semver.Version.init:
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
std.semver.Version.init_entry:
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
  movq $0, %rax
  jmp std.semver.Version.init_epilogue
std.semver.Version.init_epilogue:
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
.Lfunc_end_std.semver.Version.init:

.globl std.semver.Version.to_string
std.semver.Version.to_string:
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
std.semver.Version.to_string_entry:
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
  jmp std.semver.Version.to_string_epilogue
std.semver.Version.to_string_epilogue:
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
.Lfunc_end_std.semver.Version.to_string:

.globl std.semver.Version.greater_than
std.semver.Version.greater_than:
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
std.semver.Version.greater_than_entry:
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
  jmp std.semver.Version.greater_than_epilogue
std.semver.Version.greater_than_epilogue:
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
.Lfunc_end_std.semver.Version.greater_than:

.globl std.semver.Version.equals
std.semver.Version.equals:
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
std.semver.Version.equals_entry:
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
  jmp std.semver.Version.equals_epilogue
std.semver.Version.equals_epilogue:
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
.Lfunc_end_std.semver.Version.equals:

.globl std.semver.is_compatible
std.semver.is_compatible:
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
std.semver.is_compatible_entry:
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
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.is_compatible_block_0
std.semver.is_compatible_block_0:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -176(%rbp)
  movq -168(%rbp), %rdi
  movq -176(%rbp), %rsi
  call std.semver.Version.is_compatible
  mov -184(%rbp), rax
  movq -184(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -192(%rbp)
  movq -192(%rbp), %rax
  jmp std.semver.is_compatible_epilogue
std.semver.is_compatible_epilogue:
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
.Lfunc_end_std.semver.is_compatible:

.globl std.semver.Version.compare
std.semver.Version.compare:
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
std.semver.Version.compare_entry:
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
  jmp std.semver.Version.compare_epilogue
std.semver.Version.compare_epilogue:
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
.Lfunc_end_std.semver.Version.compare:

.globl std.semver.is_valid_char
std.semver.is_valid_char:
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
std.semver.is_valid_char_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.is_valid_char_block_0
std.semver.is_valid_char_block_0:
  leaq str_hdr_34(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -184(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -192(%rbp)
  movq -184(%rbp), %rdi
  movq -192(%rbp), %rsi
  call std.semver.index_of
  mov -200(%rbp), rax
  movq -200(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -208(%rbp)
  movq -208(%rbp), %rax
  negq %rax
  movq %rax, -216(%rbp)
  movq -216(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -224(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -232(%rbp)
  movq -232(%rbp), %rax
  cmpq -224(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -240(%rbp)
  movq -240(%rbp), %rax
  movq -96(%rbp), %rdx
  movl %eax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -248(%rbp)
  movq -248(%rbp), %rax
  jmp std.semver.is_valid_char_epilogue
std.semver.is_valid_char_epilogue:
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
.Lfunc_end_std.semver.is_valid_char:

.globl test_formatting
test_formatting:
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
test_formatting_entry:
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
  jmp test_formatting_block_0
test_formatting_block_0:
  leaq str_hdr_35(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -376(%rbp)
  movq -376(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -384(%rbp)
  movq -384(%rbp), %rax
  testq %rax, %rax
  jne test_formatting_pr_nil_0_9383
  jmp test_formatting_pr_str_0_9383
test_formatting_block_6:
  jmp test_formatting_block_11
test_formatting_block_7:
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_formatting_block_14
test_formatting_block_11:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -408(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -416(%rbp)
  movq -416(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_formatting_block_14
test_formatting_block_14:
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rdi
  call std.semver.Version.to_string
  mov -440(%rbp), rax
  movq -440(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_37(%rip), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -448(%rbp), %rdi
  movq -456(%rbp), %rsi
  call lm_key_eq
  mov -464(%rbp), rax
  movq -464(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_38(%rip), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -472(%rbp), %rax
  testq %rax, %rax
  jne test_formatting_assert_pass_39
  jmp test_formatting_assert_fail_39
test_formatting_block_24:
  jmp test_formatting_block_29
test_formatting_block_25:
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_formatting_block_32
test_formatting_block_29:
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_formatting_block_32
test_formatting_block_32:
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rdi
  call std.semver.Version.to_string
  mov -536(%rbp), rax
  movq -536(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_41(%rip), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -544(%rbp), %rdi
  movq -552(%rbp), %rsi
  call lm_key_eq
  mov -560(%rbp), rax
  movq -560(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_42(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -568(%rbp), %rax
  testq %rax, %rax
  jne test_formatting_assert_pass_43
  jmp test_formatting_assert_fail_43
test_formatting_pr_nil_0_9383:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -584(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -584(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -592(%rbp)
  jmp test_formatting_pr_next_0_9383
test_formatting_pr_str_0_9383:
  movq -376(%rbp), %rax
  addq $8, %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -376(%rbp), %rax
  addq $24, %rax
  movq %rax, -616(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -616(%rbp), %rsi
  movq -608(%rbp), %rdx
  syscall
  movq %rax, -624(%rbp)
  jmp test_formatting_pr_next_0_9383
test_formatting_pr_next_0_9383:
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
  leaq str_hdr_36(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rdi
  call std.semver.parse
  mov -656(%rbp), rax
  movq -656(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -672(%rbp)
  movq -672(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rax
  testq %rax, %rax
  jne test_formatting_block_7
  jmp test_formatting_block_6
test_formatting_assert_pass_39:
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_40(%rip), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rdi
  call std.semver.parse
  mov -696(%rbp), rax
  movq -696(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -704(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -712(%rbp)
  movq -712(%rbp), %rax
  movq -184(%rbp), %rdx
  movl %eax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -720(%rbp), %rax
  testq %rax, %rax
  jne test_formatting_block_25
  jmp test_formatting_block_24
test_formatting_assert_fail_39:
  movq -480(%rbp), %rax
  addq $8, %rax
  movq %rax, -728(%rbp)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -480(%rbp), %rax
  addq $24, %rax
  movq %rax, -744(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -744(%rbp), %rsi
  movq -736(%rbp), %rdx
  syscall
  movq %rax, -752(%rbp)
  movq $50397203, %rax
  movq %rax, -760(%rbp)
  jmp test_formatting_assert_pass_39
test_formatting_assert_pass_43:
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_44(%rip), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -768(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -776(%rbp)
  movq -776(%rbp), %rax
  testq %rax, %rax
  jne test_formatting_pr_nil_0_886
  jmp test_formatting_pr_str_0_886
test_formatting_assert_fail_43:
  movq -576(%rbp), %rax
  addq $8, %rax
  movq %rax, -784(%rbp)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -576(%rbp), %rax
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
  jmp test_formatting_assert_pass_43
test_formatting_pr_nil_0_886:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -824(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -824(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -832(%rbp)
  jmp test_formatting_pr_next_0_886
test_formatting_pr_str_0_886:
  movq -768(%rbp), %rax
  addq $8, %rax
  movq %rax, -840(%rbp)
  movq -840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -768(%rbp), %rax
  addq $24, %rax
  movq %rax, -856(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -856(%rbp), %rsi
  movq -848(%rbp), %rdx
  syscall
  movq %rax, -864(%rbp)
  jmp test_formatting_pr_next_0_886
test_formatting_pr_next_0_886:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -872(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -872(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -880(%rbp)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -888(%rbp), %rax
  jmp test_formatting_epilogue
test_formatting_epilogue:
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
.Lfunc_end_test_formatting:

.globl test_compatibility
test_compatibility:
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
  subq $2632, %rsp
test_compatibility_entry:
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
  jmp test_compatibility_block_0
test_compatibility_block_0:
  leaq str_hdr_45(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -1040(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1048(%rbp)
  movq -1048(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_pr_nil_0_2777
  jmp test_compatibility_pr_str_0_2777
test_compatibility_block_6:
  jmp test_compatibility_block_11
test_compatibility_block_7:
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1056(%rbp)
  movq -1056(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1064(%rbp)
  movq -1064(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_14
test_compatibility_block_11:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1072(%rbp)
  movq -1072(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1080(%rbp)
  movq -1080(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_14
test_compatibility_block_14:
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1088(%rbp)
  movq -1088(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_47(%rip), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -1096(%rbp), %rdi
  call std.semver.parse
  mov -1104(%rbp), rax
  movq -1104(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1112(%rbp)
  movq -1112(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -1120(%rbp)
  movq -1120(%rbp), %rax
  movq -144(%rbp), %rdx
  movl %eax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1128(%rbp)
  movq -1128(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_block_20
  jmp test_compatibility_block_19
test_compatibility_block_19:
  jmp test_compatibility_block_24
test_compatibility_block_20:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1136(%rbp)
  movq -1136(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1144(%rbp)
  movq -1144(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_27
test_compatibility_block_24:
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1152(%rbp)
  movq -1152(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1160(%rbp)
  movq -1160(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_27
test_compatibility_block_27:
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1168(%rbp)
  movq -1168(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_48(%rip), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1176(%rbp)
  movq -1176(%rbp), %rdi
  call std.semver.parse
  mov -1184(%rbp), rax
  movq -1184(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1192(%rbp)
  movq -1192(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -1200(%rbp)
  movq -1200(%rbp), %rax
  movq -208(%rbp), %rdx
  movl %eax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1208(%rbp)
  movq -1208(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_block_33
  jmp test_compatibility_block_32
test_compatibility_block_32:
  jmp test_compatibility_block_37
test_compatibility_block_33:
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1216(%rbp)
  movq -1216(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1224(%rbp)
  movq -1224(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_40
test_compatibility_block_37:
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1232(%rbp)
  movq -1232(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1240(%rbp)
  movq -1240(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_40
test_compatibility_block_40:
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1248(%rbp)
  movq -1248(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_49(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1256(%rbp)
  movq -1256(%rbp), %rdi
  call std.semver.parse
  mov -1264(%rbp), rax
  movq -1264(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1272(%rbp)
  movq -1272(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -1280(%rbp)
  movq -1280(%rbp), %rax
  movq -272(%rbp), %rdx
  movl %eax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -1288(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_block_46
  jmp test_compatibility_block_45
test_compatibility_block_45:
  jmp test_compatibility_block_50
test_compatibility_block_46:
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1296(%rbp)
  movq -1296(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1304(%rbp)
  movq -1304(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_53
test_compatibility_block_50:
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1312(%rbp)
  movq -1312(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1320(%rbp)
  movq -1320(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_53
test_compatibility_block_53:
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1328(%rbp)
  movq -1328(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1336(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1344(%rbp)
  movq -1336(%rbp), %rdi
  movq -1344(%rbp), %rsi
  call std.semver.Version.is_compatible
  mov -1352(%rbp), rax
  movq -1352(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_50(%rip), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1360(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1368(%rbp)
  movq -1360(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_assert_pass_51
  jmp test_compatibility_assert_fail_51
test_compatibility_block_71:
  jmp test_compatibility_block_76
test_compatibility_block_72:
  movq $0, %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1376(%rbp)
  movq -1376(%rbp), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1384(%rbp)
  movq -1384(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_79
test_compatibility_block_76:
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1392(%rbp)
  movq -1392(%rbp), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1400(%rbp)
  movq -1400(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_79
test_compatibility_block_79:
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1408(%rbp)
  movq -1408(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_57(%rip), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1416(%rbp)
  movq -1416(%rbp), %rdi
  call std.semver.parse
  mov -1424(%rbp), rax
  movq -1424(%rbp), %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1432(%rbp)
  movq -1432(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -1440(%rbp)
  movq -1440(%rbp), %rax
  movq -504(%rbp), %rdx
  movl %eax, (%rdx)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1448(%rbp)
  movq -1448(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_block_85
  jmp test_compatibility_block_84
test_compatibility_block_84:
  jmp test_compatibility_block_89
test_compatibility_block_85:
  movq $0, %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1456(%rbp)
  movq -1456(%rbp), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1464(%rbp)
  movq -1464(%rbp), %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_92
test_compatibility_block_89:
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1472(%rbp)
  movq -1472(%rbp), %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1480(%rbp)
  movq -1480(%rbp), %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_92
test_compatibility_block_92:
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1488(%rbp)
  movq -1488(%rbp), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_58(%rip), %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1496(%rbp)
  movq -1496(%rbp), %rdi
  call std.semver.parse
  mov -1504(%rbp), rax
  movq -1504(%rbp), %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1512(%rbp)
  movq -1512(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -1520(%rbp)
  movq -1520(%rbp), %rax
  movq -568(%rbp), %rdx
  movl %eax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1528(%rbp)
  movq -1528(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_block_98
  jmp test_compatibility_block_97
test_compatibility_block_97:
  jmp test_compatibility_block_102
test_compatibility_block_98:
  movq $0, %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1536(%rbp)
  movq -1536(%rbp), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1544(%rbp)
  movq -1544(%rbp), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_105
test_compatibility_block_102:
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1552(%rbp)
  movq -1552(%rbp), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1560(%rbp)
  movq -1560(%rbp), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_105
test_compatibility_block_105:
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1568(%rbp)
  movq -1568(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1576(%rbp)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1584(%rbp)
  movq -1576(%rbp), %rdi
  movq -1584(%rbp), %rsi
  call std.semver.Version.is_compatible
  mov -1592(%rbp), rax
  movq -1592(%rbp), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_59(%rip), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1600(%rbp)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1608(%rbp)
  movq -1600(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_assert_pass_60
  jmp test_compatibility_assert_fail_60
test_compatibility_block_118:
  jmp test_compatibility_block_123
test_compatibility_block_119:
  movq $0, %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1616(%rbp)
  movq -1616(%rbp), %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1624(%rbp)
  movq -1624(%rbp), %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_126
test_compatibility_block_123:
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1632(%rbp)
  movq -1632(%rbp), %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1640(%rbp)
  movq -1640(%rbp), %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_126
test_compatibility_block_126:
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1648(%rbp)
  movq -1648(%rbp), %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_64(%rip), %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1656(%rbp)
  movq -1656(%rbp), %rdi
  call std.semver.parse
  mov -1664(%rbp), rax
  movq -1664(%rbp), %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1672(%rbp)
  movq -1672(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -1680(%rbp)
  movq -1680(%rbp), %rax
  movq -760(%rbp), %rdx
  movl %eax, (%rdx)
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1688(%rbp)
  movq -1688(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_block_132
  jmp test_compatibility_block_131
test_compatibility_block_131:
  jmp test_compatibility_block_136
test_compatibility_block_132:
  movq $0, %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1696(%rbp)
  movq -1696(%rbp), %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1704(%rbp)
  movq -1704(%rbp), %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_139
test_compatibility_block_136:
  movq -752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1712(%rbp)
  movq -1712(%rbp), %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  movq -776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1720(%rbp)
  movq -1720(%rbp), %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_139
test_compatibility_block_139:
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1728(%rbp)
  movq -1728(%rbp), %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_65(%rip), %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1736(%rbp)
  movq -1736(%rbp), %rdi
  call std.semver.parse
  mov -1744(%rbp), rax
  movq -1744(%rbp), %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1752(%rbp)
  movq -1752(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -1760(%rbp)
  movq -1760(%rbp), %rax
  movq -824(%rbp), %rdx
  movl %eax, (%rdx)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1768(%rbp)
  movq -1768(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_block_145
  jmp test_compatibility_block_144
test_compatibility_block_144:
  jmp test_compatibility_block_149
test_compatibility_block_145:
  movq $0, %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1776(%rbp)
  movq -1776(%rbp), %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1784(%rbp)
  movq -1784(%rbp), %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_152
test_compatibility_block_149:
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1792(%rbp)
  movq -1792(%rbp), %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1800(%rbp)
  movq -1800(%rbp), %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_compatibility_block_152
test_compatibility_block_152:
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1808(%rbp)
  movq -1808(%rbp), %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1816(%rbp)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1824(%rbp)
  movq -1816(%rbp), %rdi
  movq -1824(%rbp), %rsi
  call std.semver.Version.is_compatible
  mov -1832(%rbp), rax
  movq -1832(%rbp), %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_66(%rip), %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1840(%rbp)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1848(%rbp)
  movq -1840(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_assert_pass_67
  jmp test_compatibility_assert_fail_67
test_compatibility_pr_nil_0_2777:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1856(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1856(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1864(%rbp)
  jmp test_compatibility_pr_next_0_2777
test_compatibility_pr_str_0_2777:
  movq -1040(%rbp), %rax
  addq $8, %rax
  movq %rax, -1872(%rbp)
  movq -1872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1880(%rbp)
  movq -1040(%rbp), %rax
  addq $24, %rax
  movq %rax, -1888(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1888(%rbp), %rsi
  movq -1880(%rbp), %rdx
  syscall
  movq %rax, -1896(%rbp)
  jmp test_compatibility_pr_next_0_2777
test_compatibility_pr_next_0_2777:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1904(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1912(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_46(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1920(%rbp)
  movq -1920(%rbp), %rdi
  call std.semver.parse
  mov -1928(%rbp), rax
  movq -1928(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1936(%rbp)
  movq -1936(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -1944(%rbp)
  movq -1944(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1952(%rbp)
  movq -1952(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_block_7
  jmp test_compatibility_block_6
test_compatibility_assert_pass_51:
  movq $0, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1960(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1968(%rbp)
  movq -1960(%rbp), %rdi
  movq -1968(%rbp), %rsi
  call std.semver.Version.is_compatible
  mov -1976(%rbp), rax
  movq -1976(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1984(%rbp)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1992(%rbp)
  movq -1992(%rbp), %rax
  cmpq -1984(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -2000(%rbp)
  movq -2000(%rbp), %rax
  movq -352(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_52(%rip), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2008(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2016(%rbp)
  movq -2008(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_assert_pass_53
  jmp test_compatibility_assert_fail_53
test_compatibility_assert_fail_51:
  movq -1368(%rbp), %rax
  addq $8, %rax
  movq %rax, -2024(%rbp)
  movq -2024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2032(%rbp)
  movq -1368(%rbp), %rax
  addq $24, %rax
  movq %rax, -2040(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2040(%rbp), %rsi
  movq -2032(%rbp), %rdx
  syscall
  movq %rax, -2048(%rbp)
  movq $50397203, %rax
  movq %rax, -2056(%rbp)
  jmp test_compatibility_assert_pass_51
test_compatibility_assert_pass_53:
  movq $0, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2064(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2072(%rbp)
  movq -2064(%rbp), %rdi
  movq -2072(%rbp), %rsi
  call std.semver.Version.is_compatible
  mov -2080(%rbp), rax
  movq -2080(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2088(%rbp)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2096(%rbp)
  movq -2096(%rbp), %rax
  cmpq -2088(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -2104(%rbp)
  movq -2104(%rbp), %rax
  movq -392(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_54(%rip), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2112(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2120(%rbp)
  movq -2112(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_assert_pass_55
  jmp test_compatibility_assert_fail_55
test_compatibility_assert_fail_53:
  movq -2016(%rbp), %rax
  addq $8, %rax
  movq %rax, -2128(%rbp)
  movq -2128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2136(%rbp)
  movq -2016(%rbp), %rax
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
  jmp test_compatibility_assert_pass_53
test_compatibility_assert_pass_55:
  movq $0, %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_56(%rip), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2168(%rbp)
  movq -2168(%rbp), %rdi
  call std.semver.parse
  mov -2176(%rbp), rax
  movq -2176(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2184(%rbp)
  movq -2184(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -2192(%rbp)
  movq -2192(%rbp), %rax
  movq -440(%rbp), %rdx
  movl %eax, (%rdx)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2200(%rbp)
  movq -2200(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_block_72
  jmp test_compatibility_block_71
test_compatibility_assert_fail_55:
  movq -2120(%rbp), %rax
  addq $8, %rax
  movq %rax, -2208(%rbp)
  movq -2208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2216(%rbp)
  movq -2120(%rbp), %rax
  addq $24, %rax
  movq %rax, -2224(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2224(%rbp), %rsi
  movq -2216(%rbp), %rdx
  syscall
  movq %rax, -2232(%rbp)
  movq $50397203, %rax
  movq %rax, -2240(%rbp)
  jmp test_compatibility_assert_pass_55
test_compatibility_assert_pass_60:
  movq $0, %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2248(%rbp)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2256(%rbp)
  movq -2248(%rbp), %rdi
  movq -2256(%rbp), %rsi
  call std.semver.Version.is_compatible
  mov -2264(%rbp), rax
  movq -2264(%rbp), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2272(%rbp)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2280(%rbp)
  movq -2280(%rbp), %rax
  cmpq -2272(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -2288(%rbp)
  movq -2288(%rbp), %rax
  movq -648(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_61(%rip), %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2296(%rbp)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2304(%rbp)
  movq -2296(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_assert_pass_62
  jmp test_compatibility_assert_fail_62
test_compatibility_assert_fail_60:
  movq -1608(%rbp), %rax
  addq $8, %rax
  movq %rax, -2312(%rbp)
  movq -2312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2320(%rbp)
  movq -1608(%rbp), %rax
  addq $24, %rax
  movq %rax, -2328(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2328(%rbp), %rsi
  movq -2320(%rbp), %rdx
  syscall
  movq %rax, -2336(%rbp)
  movq $50397203, %rax
  movq %rax, -2344(%rbp)
  jmp test_compatibility_assert_pass_60
test_compatibility_assert_pass_62:
  movq $0, %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_63(%rip), %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2352(%rbp)
  movq -2352(%rbp), %rdi
  call std.semver.parse
  mov -2360(%rbp), rax
  movq -2360(%rbp), %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2368(%rbp)
  movq -2368(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -2376(%rbp)
  movq -2376(%rbp), %rax
  movq -696(%rbp), %rdx
  movl %eax, (%rdx)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2384(%rbp)
  movq -2384(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_block_119
  jmp test_compatibility_block_118
test_compatibility_assert_fail_62:
  movq -2304(%rbp), %rax
  addq $8, %rax
  movq %rax, -2392(%rbp)
  movq -2392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2400(%rbp)
  movq -2304(%rbp), %rax
  addq $24, %rax
  movq %rax, -2408(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2408(%rbp), %rsi
  movq -2400(%rbp), %rdx
  syscall
  movq %rax, -2416(%rbp)
  movq $50397203, %rax
  movq %rax, -2424(%rbp)
  jmp test_compatibility_assert_pass_62
test_compatibility_assert_pass_67:
  movq $0, %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2432(%rbp)
  movq -864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2440(%rbp)
  movq -2432(%rbp), %rdi
  movq -2440(%rbp), %rsi
  call std.semver.Version.is_compatible
  mov -2448(%rbp), rax
  movq -2448(%rbp), %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2456(%rbp)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2464(%rbp)
  movq -2464(%rbp), %rax
  cmpq -2456(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -2472(%rbp)
  movq -2472(%rbp), %rax
  movq -904(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_68(%rip), %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2480(%rbp)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2488(%rbp)
  movq -2480(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_assert_pass_69
  jmp test_compatibility_assert_fail_69
test_compatibility_assert_fail_67:
  movq -1848(%rbp), %rax
  addq $8, %rax
  movq %rax, -2496(%rbp)
  movq -2496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2504(%rbp)
  movq -1848(%rbp), %rax
  addq $24, %rax
  movq %rax, -2512(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2512(%rbp), %rsi
  movq -2504(%rbp), %rdx
  syscall
  movq %rax, -2520(%rbp)
  movq $50397203, %rax
  movq %rax, -2528(%rbp)
  jmp test_compatibility_assert_pass_67
test_compatibility_assert_pass_69:
  movq $0, %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_70(%rip), %rax
  movq -936(%rbp), %rdx
  movq %rax, (%rdx)
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2536(%rbp)
  movq -2536(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2544(%rbp)
  movq -2544(%rbp), %rax
  testq %rax, %rax
  jne test_compatibility_pr_nil_0_6915
  jmp test_compatibility_pr_str_0_6915
test_compatibility_assert_fail_69:
  movq -2488(%rbp), %rax
  addq $8, %rax
  movq %rax, -2552(%rbp)
  movq -2552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2560(%rbp)
  movq -2488(%rbp), %rax
  addq $24, %rax
  movq %rax, -2568(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2568(%rbp), %rsi
  movq -2560(%rbp), %rdx
  syscall
  movq %rax, -2576(%rbp)
  movq $50397203, %rax
  movq %rax, -2584(%rbp)
  jmp test_compatibility_assert_pass_69
test_compatibility_pr_nil_0_6915:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2592(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2592(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2600(%rbp)
  jmp test_compatibility_pr_next_0_6915
test_compatibility_pr_str_0_6915:
  movq -2536(%rbp), %rax
  addq $8, %rax
  movq %rax, -2608(%rbp)
  movq -2608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2616(%rbp)
  movq -2536(%rbp), %rax
  addq $24, %rax
  movq %rax, -2624(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2624(%rbp), %rsi
  movq -2616(%rbp), %rdx
  syscall
  movq %rax, -2632(%rbp)
  jmp test_compatibility_pr_next_0_6915
test_compatibility_pr_next_0_6915:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2640(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2640(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2648(%rbp)
  movq $0, %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  movq -952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2656(%rbp)
  movq -2656(%rbp), %rax
  jmp test_compatibility_epilogue
test_compatibility_epilogue:
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
.Lfunc_end_test_compatibility:

.globl test_comparison
test_comparison:
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
  subq $4968, %rsp
test_comparison_entry:
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
  jmp test_comparison_block_0
test_comparison_block_0:
  leaq str_hdr_71(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1832(%rbp)
  movq -1832(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1840(%rbp)
  movq -1840(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_pr_nil_0_7793
  jmp test_comparison_pr_str_0_7793
test_comparison_block_6:
  jmp test_comparison_block_11
test_comparison_block_7:
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1848(%rbp)
  movq -1848(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1856(%rbp)
  movq -1856(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_14
test_comparison_block_11:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1864(%rbp)
  movq -1864(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1872(%rbp)
  movq -1872(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_14
test_comparison_block_14:
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1880(%rbp)
  movq -1880(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_73(%rip), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1888(%rbp)
  movq -1888(%rbp), %rdi
  call std.semver.parse
  mov -1896(%rbp), rax
  movq -1896(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1904(%rbp)
  movq -1904(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -1912(%rbp)
  movq -1912(%rbp), %rax
  movq -144(%rbp), %rdx
  movl %eax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1920(%rbp)
  movq -1920(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_20
  jmp test_comparison_block_19
test_comparison_block_19:
  jmp test_comparison_block_24
test_comparison_block_20:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1928(%rbp)
  movq -1928(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1936(%rbp)
  movq -1936(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_27
test_comparison_block_24:
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1944(%rbp)
  movq -1944(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1952(%rbp)
  movq -1952(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_27
test_comparison_block_27:
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1960(%rbp)
  movq -1960(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_74(%rip), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1968(%rbp)
  movq -1968(%rbp), %rdi
  call std.semver.parse
  mov -1976(%rbp), rax
  movq -1976(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1984(%rbp)
  movq -1984(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -1992(%rbp)
  movq -1992(%rbp), %rax
  movq -208(%rbp), %rdx
  movl %eax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2000(%rbp)
  movq -2000(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_33
  jmp test_comparison_block_32
test_comparison_block_32:
  jmp test_comparison_block_37
test_comparison_block_33:
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2008(%rbp)
  movq -2008(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2016(%rbp)
  movq -2016(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_40
test_comparison_block_37:
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2024(%rbp)
  movq -2024(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2032(%rbp)
  movq -2032(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_40
test_comparison_block_40:
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2040(%rbp)
  movq -2040(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_75(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2048(%rbp)
  movq -2048(%rbp), %rdi
  call std.semver.parse
  mov -2056(%rbp), rax
  movq -2056(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2064(%rbp)
  movq -2064(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -2072(%rbp)
  movq -2072(%rbp), %rax
  movq -272(%rbp), %rdx
  movl %eax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2080(%rbp)
  movq -2080(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_46
  jmp test_comparison_block_45
test_comparison_block_45:
  jmp test_comparison_block_50
test_comparison_block_46:
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2088(%rbp)
  movq -2088(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2096(%rbp)
  movq -2096(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_53
test_comparison_block_50:
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2104(%rbp)
  movq -2104(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2112(%rbp)
  movq -2112(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_53
test_comparison_block_53:
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2120(%rbp)
  movq -2120(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2128(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2136(%rbp)
  movq -2128(%rbp), %rdi
  movq -2136(%rbp), %rsi
  call std.semver.Version.compare
  mov -2144(%rbp), rax
  movq -2144(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2152(%rbp)
  movq -2152(%rbp), %rax
  negq %rax
  movq %rax, -2160(%rbp)
  movq -2160(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2168(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2176(%rbp)
  movq -2176(%rbp), %rax
  cmpq -2168(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2184(%rbp)
  movq -2184(%rbp), %rax
  movq -344(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_76(%rip), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2192(%rbp)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2200(%rbp)
  movq -2192(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_77
  jmp test_comparison_assert_fail_77
test_comparison_block_91:
  jmp test_comparison_block_96
test_comparison_block_92:
  movq $0, %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2208(%rbp)
  movq -2208(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2216(%rbp)
  movq -2216(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_99
test_comparison_block_96:
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2224(%rbp)
  movq -2224(%rbp), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2232(%rbp)
  movq -2232(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_99
test_comparison_block_99:
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2240(%rbp)
  movq -2240(%rbp), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_89(%rip), %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2248(%rbp)
  movq -2248(%rbp), %rdi
  call std.semver.parse
  mov -2256(%rbp), rax
  movq -2256(%rbp), %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2264(%rbp)
  movq -2264(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -2272(%rbp)
  movq -2272(%rbp), %rax
  movq -664(%rbp), %rdx
  movl %eax, (%rdx)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2280(%rbp)
  movq -2280(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_105
  jmp test_comparison_block_104
test_comparison_block_104:
  jmp test_comparison_block_109
test_comparison_block_105:
  movq $0, %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2288(%rbp)
  movq -2288(%rbp), %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2296(%rbp)
  movq -2296(%rbp), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_112
test_comparison_block_109:
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2304(%rbp)
  movq -2304(%rbp), %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2312(%rbp)
  movq -2312(%rbp), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_112
test_comparison_block_112:
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2320(%rbp)
  movq -2320(%rbp), %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2328(%rbp)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2336(%rbp)
  movq -2328(%rbp), %rdi
  movq -2336(%rbp), %rsi
  call std.semver.Version.compare
  mov -2344(%rbp), rax
  movq -2344(%rbp), %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2352(%rbp)
  movq -2352(%rbp), %rax
  negq %rax
  movq %rax, -2360(%rbp)
  movq -2360(%rbp), %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2368(%rbp)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2376(%rbp)
  movq -2376(%rbp), %rax
  cmpq -2368(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2384(%rbp)
  movq -2384(%rbp), %rax
  movq -736(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_90(%rip), %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2392(%rbp)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2400(%rbp)
  movq -2392(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_91
  jmp test_comparison_assert_fail_91
test_comparison_block_128:
  jmp test_comparison_block_133
test_comparison_block_129:
  movq $0, %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2408(%rbp)
  movq -2408(%rbp), %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2416(%rbp)
  movq -2416(%rbp), %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_136
test_comparison_block_133:
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2424(%rbp)
  movq -2424(%rbp), %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2432(%rbp)
  movq -2432(%rbp), %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_136
test_comparison_block_136:
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2440(%rbp)
  movq -2440(%rbp), %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_95(%rip), %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2448(%rbp)
  movq -2448(%rbp), %rdi
  call std.semver.parse
  mov -2456(%rbp), rax
  movq -2456(%rbp), %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2464(%rbp)
  movq -2464(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -2472(%rbp)
  movq -2472(%rbp), %rax
  movq -880(%rbp), %rdx
  movl %eax, (%rdx)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2480(%rbp)
  movq -2480(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_142
  jmp test_comparison_block_141
test_comparison_block_141:
  jmp test_comparison_block_146
test_comparison_block_142:
  movq $0, %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2488(%rbp)
  movq -2488(%rbp), %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2496(%rbp)
  movq -2496(%rbp), %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_149
test_comparison_block_146:
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2504(%rbp)
  movq -2504(%rbp), %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2512(%rbp)
  movq -2512(%rbp), %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_149
test_comparison_block_149:
  movq -888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2520(%rbp)
  movq -2520(%rbp), %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_96(%rip), %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2528(%rbp)
  movq -2528(%rbp), %rdi
  call std.semver.parse
  mov -2536(%rbp), rax
  movq -2536(%rbp), %rax
  movq -936(%rbp), %rdx
  movq %rax, (%rdx)
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2544(%rbp)
  movq -2544(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -2552(%rbp)
  movq -2552(%rbp), %rax
  movq -944(%rbp), %rdx
  movl %eax, (%rdx)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2560(%rbp)
  movq -2560(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_155
  jmp test_comparison_block_154
test_comparison_block_154:
  jmp test_comparison_block_159
test_comparison_block_155:
  movq $0, %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2568(%rbp)
  movq -2568(%rbp), %rax
  movq -968(%rbp), %rdx
  movq %rax, (%rdx)
  movq -968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2576(%rbp)
  movq -2576(%rbp), %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_162
test_comparison_block_159:
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2584(%rbp)
  movq -2584(%rbp), %rax
  movq -960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2592(%rbp)
  movq -2592(%rbp), %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_162
test_comparison_block_162:
  movq -952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2600(%rbp)
  movq -2600(%rbp), %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_97(%rip), %rax
  movq -992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2608(%rbp)
  movq -2608(%rbp), %rdi
  call std.semver.parse
  mov -2616(%rbp), rax
  movq -2616(%rbp), %rax
  movq -1000(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2624(%rbp)
  movq -2624(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -2632(%rbp)
  movq -2632(%rbp), %rax
  movq -1008(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2640(%rbp)
  movq -2640(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_168
  jmp test_comparison_block_167
test_comparison_block_167:
  jmp test_comparison_block_172
test_comparison_block_168:
  movq $0, %rax
  movq -1040(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2648(%rbp)
  movq -2648(%rbp), %rax
  movq -1032(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2656(%rbp)
  movq -2656(%rbp), %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_175
test_comparison_block_172:
  movq -1000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2664(%rbp)
  movq -2664(%rbp), %rax
  movq -1024(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2672(%rbp)
  movq -2672(%rbp), %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_175
test_comparison_block_175:
  movq -1016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2680(%rbp)
  movq -2680(%rbp), %rax
  movq -1048(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_98(%rip), %rax
  movq -1056(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2688(%rbp)
  movq -2688(%rbp), %rdi
  call std.semver.parse
  mov -2696(%rbp), rax
  movq -2696(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2704(%rbp)
  movq -2704(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -2712(%rbp)
  movq -2712(%rbp), %rax
  movq -1072(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2720(%rbp)
  movq -2720(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_181
  jmp test_comparison_block_180
test_comparison_block_180:
  jmp test_comparison_block_185
test_comparison_block_181:
  movq $0, %rax
  movq -1104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2728(%rbp)
  movq -2728(%rbp), %rax
  movq -1096(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2736(%rbp)
  movq -2736(%rbp), %rax
  movq -1080(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_188
test_comparison_block_185:
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2744(%rbp)
  movq -2744(%rbp), %rax
  movq -1088(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2752(%rbp)
  movq -2752(%rbp), %rax
  movq -1080(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_188
test_comparison_block_188:
  movq -1080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2760(%rbp)
  movq -2760(%rbp), %rax
  movq -1112(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_99(%rip), %rax
  movq -1120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2768(%rbp)
  movq -2768(%rbp), %rdi
  call std.semver.parse
  mov -2776(%rbp), rax
  movq -2776(%rbp), %rax
  movq -1128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2784(%rbp)
  movq -2784(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -2792(%rbp)
  movq -2792(%rbp), %rax
  movq -1136(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2800(%rbp)
  movq -2800(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_194
  jmp test_comparison_block_193
test_comparison_block_193:
  jmp test_comparison_block_198
test_comparison_block_194:
  movq $0, %rax
  movq -1168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2808(%rbp)
  movq -2808(%rbp), %rax
  movq -1160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2816(%rbp)
  movq -2816(%rbp), %rax
  movq -1144(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_201
test_comparison_block_198:
  movq -1128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2824(%rbp)
  movq -2824(%rbp), %rax
  movq -1152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2832(%rbp)
  movq -2832(%rbp), %rax
  movq -1144(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_201
test_comparison_block_201:
  movq -1144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2840(%rbp)
  movq -2840(%rbp), %rax
  movq -1176(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_100(%rip), %rax
  movq -1184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2848(%rbp)
  movq -2848(%rbp), %rdi
  call std.semver.parse
  mov -2856(%rbp), rax
  movq -2856(%rbp), %rax
  movq -1192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2864(%rbp)
  movq -2864(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -2872(%rbp)
  movq -2872(%rbp), %rax
  movq -1200(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2880(%rbp)
  movq -2880(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_207
  jmp test_comparison_block_206
test_comparison_block_206:
  jmp test_comparison_block_211
test_comparison_block_207:
  movq $0, %rax
  movq -1232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2888(%rbp)
  movq -2888(%rbp), %rax
  movq -1224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2896(%rbp)
  movq -2896(%rbp), %rax
  movq -1208(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_214
test_comparison_block_211:
  movq -1192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2904(%rbp)
  movq -2904(%rbp), %rax
  movq -1216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2912(%rbp)
  movq -2912(%rbp), %rax
  movq -1208(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_214
test_comparison_block_214:
  movq -1208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2920(%rbp)
  movq -2920(%rbp), %rax
  movq -1240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2928(%rbp)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2936(%rbp)
  movq -2928(%rbp), %rdi
  movq -2936(%rbp), %rsi
  call std.semver.Version.compare
  mov -2944(%rbp), rax
  movq -2944(%rbp), %rax
  movq -1248(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2952(%rbp)
  movq -2952(%rbp), %rax
  negq %rax
  movq %rax, -2960(%rbp)
  movq -2960(%rbp), %rax
  movq -1264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2968(%rbp)
  movq -1248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2976(%rbp)
  movq -2976(%rbp), %rax
  cmpq -2968(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2984(%rbp)
  movq -2984(%rbp), %rax
  movq -1272(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_101(%rip), %rax
  movq -1280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2992(%rbp)
  movq -1280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3000(%rbp)
  movq -2992(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_102
  jmp test_comparison_assert_fail_102
test_comparison_block_255:
  jmp test_comparison_block_260
test_comparison_block_256:
  movq $0, %rax
  movq -1584(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3008(%rbp)
  movq -3008(%rbp), %rax
  movq -1576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3016(%rbp)
  movq -3016(%rbp), %rax
  movq -1560(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_263
test_comparison_block_260:
  movq -1544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3024(%rbp)
  movq -3024(%rbp), %rax
  movq -1568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3032(%rbp)
  movq -3032(%rbp), %rax
  movq -1560(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_263
test_comparison_block_263:
  movq -1560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3040(%rbp)
  movq -3040(%rbp), %rax
  movq -1592(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_114(%rip), %rax
  movq -1600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3048(%rbp)
  movq -3048(%rbp), %rdi
  call std.semver.parse
  mov -3056(%rbp), rax
  movq -3056(%rbp), %rax
  movq -1608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3064(%rbp)
  movq -3064(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -3072(%rbp)
  movq -3072(%rbp), %rax
  movq -1616(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3080(%rbp)
  movq -3080(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_269
  jmp test_comparison_block_268
test_comparison_block_268:
  jmp test_comparison_block_273
test_comparison_block_269:
  movq $0, %rax
  movq -1648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3088(%rbp)
  movq -3088(%rbp), %rax
  movq -1640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3096(%rbp)
  movq -3096(%rbp), %rax
  movq -1624(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_276
test_comparison_block_273:
  movq -1608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3104(%rbp)
  movq -3104(%rbp), %rax
  movq -1632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3112(%rbp)
  movq -3112(%rbp), %rax
  movq -1624(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_comparison_block_276
test_comparison_block_276:
  movq -1624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3120(%rbp)
  movq -3120(%rbp), %rax
  movq -1656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3128(%rbp)
  movq -1656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3136(%rbp)
  movq -3128(%rbp), %rdi
  movq -3136(%rbp), %rsi
  call std.semver.Version.compare
  mov -3144(%rbp), rax
  movq -3144(%rbp), %rax
  movq -1664(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3152(%rbp)
  movq -1664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3160(%rbp)
  movq -3160(%rbp), %rax
  cmpq -3152(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3168(%rbp)
  movq -3168(%rbp), %rax
  movq -1680(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_115(%rip), %rax
  movq -1688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3176(%rbp)
  movq -1688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3184(%rbp)
  movq -3176(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_116
  jmp test_comparison_assert_fail_116
test_comparison_pr_nil_0_7793:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3192(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3192(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3200(%rbp)
  jmp test_comparison_pr_next_0_7793
test_comparison_pr_str_0_7793:
  movq -1832(%rbp), %rax
  addq $8, %rax
  movq %rax, -3208(%rbp)
  movq -3208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3216(%rbp)
  movq -1832(%rbp), %rax
  addq $24, %rax
  movq %rax, -3224(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3224(%rbp), %rsi
  movq -3216(%rbp), %rdx
  syscall
  movq %rax, -3232(%rbp)
  jmp test_comparison_pr_next_0_7793
test_comparison_pr_next_0_7793:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3240(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3240(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3248(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_72(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3256(%rbp)
  movq -3256(%rbp), %rdi
  call std.semver.parse
  mov -3264(%rbp), rax
  movq -3264(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3272(%rbp)
  movq -3272(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -3280(%rbp)
  movq -3280(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3288(%rbp)
  movq -3288(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_7
  jmp test_comparison_block_6
test_comparison_assert_pass_77:
  movq $0, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3296(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3304(%rbp)
  movq -3296(%rbp), %rdi
  movq -3304(%rbp), %rsi
  call std.semver.Version.compare
  mov -3312(%rbp), rax
  movq -3312(%rbp), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3320(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3328(%rbp)
  movq -3328(%rbp), %rax
  cmpq -3320(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3336(%rbp)
  movq -3336(%rbp), %rax
  movq -384(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_78(%rip), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3344(%rbp)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3352(%rbp)
  movq -3344(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_79
  jmp test_comparison_assert_fail_79
test_comparison_assert_fail_77:
  movq -2200(%rbp), %rax
  addq $8, %rax
  movq %rax, -3360(%rbp)
  movq -3360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3368(%rbp)
  movq -2200(%rbp), %rax
  addq $24, %rax
  movq %rax, -3376(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3376(%rbp), %rsi
  movq -3368(%rbp), %rdx
  syscall
  movq %rax, -3384(%rbp)
  movq $50397203, %rax
  movq %rax, -3392(%rbp)
  jmp test_comparison_assert_pass_77
test_comparison_assert_pass_79:
  movq $0, %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3400(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3408(%rbp)
  movq -3400(%rbp), %rdi
  movq -3408(%rbp), %rsi
  call std.semver.Version.compare
  mov -3416(%rbp), rax
  movq -3416(%rbp), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3424(%rbp)
  movq -3424(%rbp), %rax
  negq %rax
  movq %rax, -3432(%rbp)
  movq -3432(%rbp), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3440(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3448(%rbp)
  movq -3448(%rbp), %rax
  cmpq -3440(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3456(%rbp)
  movq -3456(%rbp), %rax
  movq -432(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_80(%rip), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3464(%rbp)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3472(%rbp)
  movq -3464(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_81
  jmp test_comparison_assert_fail_81
test_comparison_assert_fail_79:
  movq -3352(%rbp), %rax
  addq $8, %rax
  movq %rax, -3480(%rbp)
  movq -3480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3488(%rbp)
  movq -3352(%rbp), %rax
  addq $24, %rax
  movq %rax, -3496(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3496(%rbp), %rsi
  movq -3488(%rbp), %rdx
  syscall
  movq %rax, -3504(%rbp)
  movq $50397203, %rax
  movq %rax, -3512(%rbp)
  jmp test_comparison_assert_pass_79
test_comparison_assert_pass_81:
  movq $0, %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3520(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3528(%rbp)
  movq -3520(%rbp), %rdi
  movq -3528(%rbp), %rsi
  call std.semver.Version.compare
  mov -3536(%rbp), rax
  movq -3536(%rbp), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3544(%rbp)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3552(%rbp)
  movq -3552(%rbp), %rax
  cmpq -3544(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3560(%rbp)
  movq -3560(%rbp), %rax
  movq -472(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_82(%rip), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3568(%rbp)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3576(%rbp)
  movq -3568(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_83
  jmp test_comparison_assert_fail_83
test_comparison_assert_fail_81:
  movq -3472(%rbp), %rax
  addq $8, %rax
  movq %rax, -3584(%rbp)
  movq -3584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3592(%rbp)
  movq -3472(%rbp), %rax
  addq $24, %rax
  movq %rax, -3600(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3600(%rbp), %rsi
  movq -3592(%rbp), %rdx
  syscall
  movq %rax, -3608(%rbp)
  movq $50397203, %rax
  movq %rax, -3616(%rbp)
  jmp test_comparison_assert_pass_81
test_comparison_assert_pass_83:
  movq $0, %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3624(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3632(%rbp)
  movq -3624(%rbp), %rdi
  movq -3632(%rbp), %rsi
  call std.semver.Version.compare
  mov -3640(%rbp), rax
  movq -3640(%rbp), %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3648(%rbp)
  movq -3648(%rbp), %rax
  negq %rax
  movq %rax, -3656(%rbp)
  movq -3656(%rbp), %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3664(%rbp)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3672(%rbp)
  movq -3672(%rbp), %rax
  cmpq -3664(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3680(%rbp)
  movq -3680(%rbp), %rax
  movq -520(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_84(%rip), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3688(%rbp)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3696(%rbp)
  movq -3688(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_85
  jmp test_comparison_assert_fail_85
test_comparison_assert_fail_83:
  movq -3576(%rbp), %rax
  addq $8, %rax
  movq %rax, -3704(%rbp)
  movq -3704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3712(%rbp)
  movq -3576(%rbp), %rax
  addq $24, %rax
  movq %rax, -3720(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3720(%rbp), %rsi
  movq -3712(%rbp), %rdx
  syscall
  movq %rax, -3728(%rbp)
  movq $50397203, %rax
  movq %rax, -3736(%rbp)
  jmp test_comparison_assert_pass_83
test_comparison_assert_pass_85:
  movq $0, %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3744(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3752(%rbp)
  movq -3744(%rbp), %rdi
  movq -3752(%rbp), %rsi
  call std.semver.Version.compare
  mov -3760(%rbp), rax
  movq -3760(%rbp), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3768(%rbp)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3776(%rbp)
  movq -3776(%rbp), %rax
  cmpq -3768(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3784(%rbp)
  movq -3784(%rbp), %rax
  movq -560(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_86(%rip), %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3792(%rbp)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3800(%rbp)
  movq -3792(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_87
  jmp test_comparison_assert_fail_87
test_comparison_assert_fail_85:
  movq -3696(%rbp), %rax
  addq $8, %rax
  movq %rax, -3808(%rbp)
  movq -3808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3816(%rbp)
  movq -3696(%rbp), %rax
  addq $24, %rax
  movq %rax, -3824(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3824(%rbp), %rsi
  movq -3816(%rbp), %rdx
  syscall
  movq %rax, -3832(%rbp)
  movq $50397203, %rax
  movq %rax, -3840(%rbp)
  jmp test_comparison_assert_pass_85
test_comparison_assert_pass_87:
  movq $0, %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_88(%rip), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3848(%rbp)
  movq -3848(%rbp), %rdi
  call std.semver.parse
  mov -3856(%rbp), rax
  movq -3856(%rbp), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3864(%rbp)
  movq -3864(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -3872(%rbp)
  movq -3872(%rbp), %rax
  movq -600(%rbp), %rdx
  movl %eax, (%rdx)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3880(%rbp)
  movq -3880(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_92
  jmp test_comparison_block_91
test_comparison_assert_fail_87:
  movq -3800(%rbp), %rax
  addq $8, %rax
  movq %rax, -3888(%rbp)
  movq -3888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3896(%rbp)
  movq -3800(%rbp), %rax
  addq $24, %rax
  movq %rax, -3904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3904(%rbp), %rsi
  movq -3896(%rbp), %rdx
  syscall
  movq %rax, -3912(%rbp)
  movq $50397203, %rax
  movq %rax, -3920(%rbp)
  jmp test_comparison_assert_pass_87
test_comparison_assert_pass_91:
  movq $0, %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3928(%rbp)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3936(%rbp)
  movq -3928(%rbp), %rdi
  movq -3936(%rbp), %rsi
  call std.semver.Version.compare
  mov -3944(%rbp), rax
  movq -3944(%rbp), %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3952(%rbp)
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3960(%rbp)
  movq -3960(%rbp), %rax
  cmpq -3952(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3968(%rbp)
  movq -3968(%rbp), %rax
  movq -776(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_92(%rip), %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3976(%rbp)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3984(%rbp)
  movq -3976(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_93
  jmp test_comparison_assert_fail_93
test_comparison_assert_fail_91:
  movq -2400(%rbp), %rax
  addq $8, %rax
  movq %rax, -3992(%rbp)
  movq -3992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4000(%rbp)
  movq -2400(%rbp), %rax
  addq $24, %rax
  movq %rax, -4008(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4008(%rbp), %rsi
  movq -4000(%rbp), %rdx
  syscall
  movq %rax, -4016(%rbp)
  movq $50397203, %rax
  movq %rax, -4024(%rbp)
  jmp test_comparison_assert_pass_91
test_comparison_assert_pass_93:
  movq $0, %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_94(%rip), %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4032(%rbp)
  movq -4032(%rbp), %rdi
  call std.semver.parse
  mov -4040(%rbp), rax
  movq -4040(%rbp), %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4048(%rbp)
  movq -4048(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -4056(%rbp)
  movq -4056(%rbp), %rax
  movq -816(%rbp), %rdx
  movl %eax, (%rdx)
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4064(%rbp)
  movq -4064(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_129
  jmp test_comparison_block_128
test_comparison_assert_fail_93:
  movq -3984(%rbp), %rax
  addq $8, %rax
  movq %rax, -4072(%rbp)
  movq -4072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4080(%rbp)
  movq -3984(%rbp), %rax
  addq $24, %rax
  movq %rax, -4088(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4088(%rbp), %rsi
  movq -4080(%rbp), %rdx
  syscall
  movq %rax, -4096(%rbp)
  movq $50397203, %rax
  movq %rax, -4104(%rbp)
  jmp test_comparison_assert_pass_93
test_comparison_assert_pass_102:
  movq $0, %rax
  movq -1288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4112(%rbp)
  movq -984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4120(%rbp)
  movq -4112(%rbp), %rdi
  movq -4120(%rbp), %rsi
  call std.semver.Version.compare
  mov -4128(%rbp), rax
  movq -4128(%rbp), %rax
  movq -1296(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4136(%rbp)
  movq -4136(%rbp), %rax
  negq %rax
  movq %rax, -4144(%rbp)
  movq -4144(%rbp), %rax
  movq -1312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4152(%rbp)
  movq -1296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4160(%rbp)
  movq -4160(%rbp), %rax
  cmpq -4152(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4168(%rbp)
  movq -4168(%rbp), %rax
  movq -1320(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_103(%rip), %rax
  movq -1328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4176(%rbp)
  movq -1328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4184(%rbp)
  movq -4176(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_104
  jmp test_comparison_assert_fail_104
test_comparison_assert_fail_102:
  movq -3000(%rbp), %rax
  addq $8, %rax
  movq %rax, -4192(%rbp)
  movq -4192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4200(%rbp)
  movq -3000(%rbp), %rax
  addq $24, %rax
  movq %rax, -4208(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4208(%rbp), %rsi
  movq -4200(%rbp), %rdx
  syscall
  movq %rax, -4216(%rbp)
  movq $50397203, %rax
  movq %rax, -4224(%rbp)
  jmp test_comparison_assert_pass_102
test_comparison_assert_pass_104:
  movq $0, %rax
  movq -1336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4232(%rbp)
  movq -1048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4240(%rbp)
  movq -4232(%rbp), %rdi
  movq -4240(%rbp), %rsi
  call std.semver.Version.compare
  mov -4248(%rbp), rax
  movq -4248(%rbp), %rax
  movq -1344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4256(%rbp)
  movq -4256(%rbp), %rax
  negq %rax
  movq %rax, -4264(%rbp)
  movq -4264(%rbp), %rax
  movq -1360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4272(%rbp)
  movq -1344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4280(%rbp)
  movq -4280(%rbp), %rax
  cmpq -4272(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4288(%rbp)
  movq -4288(%rbp), %rax
  movq -1368(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_105(%rip), %rax
  movq -1376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4296(%rbp)
  movq -1376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4304(%rbp)
  movq -4296(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_106
  jmp test_comparison_assert_fail_106
test_comparison_assert_fail_104:
  movq -4184(%rbp), %rax
  addq $8, %rax
  movq %rax, -4312(%rbp)
  movq -4312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4320(%rbp)
  movq -4184(%rbp), %rax
  addq $24, %rax
  movq %rax, -4328(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4328(%rbp), %rsi
  movq -4320(%rbp), %rdx
  syscall
  movq %rax, -4336(%rbp)
  movq $50397203, %rax
  movq %rax, -4344(%rbp)
  jmp test_comparison_assert_pass_104
test_comparison_assert_pass_106:
  movq $0, %rax
  movq -1384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4352(%rbp)
  movq -1112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4360(%rbp)
  movq -4352(%rbp), %rdi
  movq -4360(%rbp), %rsi
  call std.semver.Version.compare
  mov -4368(%rbp), rax
  movq -4368(%rbp), %rax
  movq -1392(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4376(%rbp)
  movq -4376(%rbp), %rax
  negq %rax
  movq %rax, -4384(%rbp)
  movq -4384(%rbp), %rax
  movq -1408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4392(%rbp)
  movq -1392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4400(%rbp)
  movq -4400(%rbp), %rax
  cmpq -4392(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4408(%rbp)
  movq -4408(%rbp), %rax
  movq -1416(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_107(%rip), %rax
  movq -1424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4416(%rbp)
  movq -1424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4424(%rbp)
  movq -4416(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_108
  jmp test_comparison_assert_fail_108
test_comparison_assert_fail_106:
  movq -4304(%rbp), %rax
  addq $8, %rax
  movq %rax, -4432(%rbp)
  movq -4432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4440(%rbp)
  movq -4304(%rbp), %rax
  addq $24, %rax
  movq %rax, -4448(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4448(%rbp), %rsi
  movq -4440(%rbp), %rdx
  syscall
  movq %rax, -4456(%rbp)
  movq $50397203, %rax
  movq %rax, -4464(%rbp)
  jmp test_comparison_assert_pass_106
test_comparison_assert_pass_108:
  movq $0, %rax
  movq -1432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4472(%rbp)
  movq -1176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4480(%rbp)
  movq -4472(%rbp), %rdi
  movq -4480(%rbp), %rsi
  call std.semver.Version.compare
  mov -4488(%rbp), rax
  movq -4488(%rbp), %rax
  movq -1440(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4496(%rbp)
  movq -4496(%rbp), %rax
  negq %rax
  movq %rax, -4504(%rbp)
  movq -4504(%rbp), %rax
  movq -1456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4512(%rbp)
  movq -1440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4520(%rbp)
  movq -4520(%rbp), %rax
  cmpq -4512(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4528(%rbp)
  movq -4528(%rbp), %rax
  movq -1464(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_109(%rip), %rax
  movq -1472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4536(%rbp)
  movq -1472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4544(%rbp)
  movq -4536(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_110
  jmp test_comparison_assert_fail_110
test_comparison_assert_fail_108:
  movq -4424(%rbp), %rax
  addq $8, %rax
  movq %rax, -4552(%rbp)
  movq -4552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4560(%rbp)
  movq -4424(%rbp), %rax
  addq $24, %rax
  movq %rax, -4568(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4568(%rbp), %rsi
  movq -4560(%rbp), %rdx
  syscall
  movq %rax, -4576(%rbp)
  movq $50397203, %rax
  movq %rax, -4584(%rbp)
  jmp test_comparison_assert_pass_108
test_comparison_assert_pass_110:
  movq $0, %rax
  movq -1480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4592(%rbp)
  movq -1240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4600(%rbp)
  movq -4592(%rbp), %rdi
  movq -4600(%rbp), %rsi
  call std.semver.Version.compare
  mov -4608(%rbp), rax
  movq -4608(%rbp), %rax
  movq -1488(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4616(%rbp)
  movq -4616(%rbp), %rax
  negq %rax
  movq %rax, -4624(%rbp)
  movq -4624(%rbp), %rax
  movq -1504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4632(%rbp)
  movq -1488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4640(%rbp)
  movq -4640(%rbp), %rax
  cmpq -4632(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4648(%rbp)
  movq -4648(%rbp), %rax
  movq -1512(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_111(%rip), %rax
  movq -1520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4656(%rbp)
  movq -1520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4664(%rbp)
  movq -4656(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_112
  jmp test_comparison_assert_fail_112
test_comparison_assert_fail_110:
  movq -4544(%rbp), %rax
  addq $8, %rax
  movq %rax, -4672(%rbp)
  movq -4672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4680(%rbp)
  movq -4544(%rbp), %rax
  addq $24, %rax
  movq %rax, -4688(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4688(%rbp), %rsi
  movq -4680(%rbp), %rdx
  syscall
  movq %rax, -4696(%rbp)
  movq $50397203, %rax
  movq %rax, -4704(%rbp)
  jmp test_comparison_assert_pass_110
test_comparison_assert_pass_112:
  movq $0, %rax
  movq -1528(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_113(%rip), %rax
  movq -1536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4712(%rbp)
  movq -4712(%rbp), %rdi
  call std.semver.parse
  mov -4720(%rbp), rax
  movq -4720(%rbp), %rax
  movq -1544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4728(%rbp)
  movq -4728(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -4736(%rbp)
  movq -4736(%rbp), %rax
  movq -1552(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4744(%rbp)
  movq -4744(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_block_256
  jmp test_comparison_block_255
test_comparison_assert_fail_112:
  movq -4664(%rbp), %rax
  addq $8, %rax
  movq %rax, -4752(%rbp)
  movq -4752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4760(%rbp)
  movq -4664(%rbp), %rax
  addq $24, %rax
  movq %rax, -4768(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4768(%rbp), %rsi
  movq -4760(%rbp), %rdx
  syscall
  movq %rax, -4776(%rbp)
  movq $50397203, %rax
  movq %rax, -4784(%rbp)
  jmp test_comparison_assert_pass_112
test_comparison_assert_pass_116:
  movq $0, %rax
  movq -1696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4792(%rbp)
  movq -1656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4800(%rbp)
  movq -4792(%rbp), %rdi
  movq -4800(%rbp), %rsi
  call std.semver.Version.equals
  mov -4808(%rbp), rax
  movq -4808(%rbp), %rax
  movq -1704(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_117(%rip), %rax
  movq -1712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4816(%rbp)
  movq -1712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4824(%rbp)
  movq -4816(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_assert_pass_118
  jmp test_comparison_assert_fail_118
test_comparison_assert_fail_116:
  movq -3184(%rbp), %rax
  addq $8, %rax
  movq %rax, -4832(%rbp)
  movq -4832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4840(%rbp)
  movq -3184(%rbp), %rax
  addq $24, %rax
  movq %rax, -4848(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4848(%rbp), %rsi
  movq -4840(%rbp), %rdx
  syscall
  movq %rax, -4856(%rbp)
  movq $50397203, %rax
  movq %rax, -4864(%rbp)
  jmp test_comparison_assert_pass_116
test_comparison_assert_pass_118:
  movq $0, %rax
  movq -1720(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_119(%rip), %rax
  movq -1728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4872(%rbp)
  movq -4872(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4880(%rbp)
  movq -4880(%rbp), %rax
  testq %rax, %rax
  jne test_comparison_pr_nil_0_8335
  jmp test_comparison_pr_str_0_8335
test_comparison_assert_fail_118:
  movq -4824(%rbp), %rax
  addq $8, %rax
  movq %rax, -4888(%rbp)
  movq -4888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4896(%rbp)
  movq -4824(%rbp), %rax
  addq $24, %rax
  movq %rax, -4904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4904(%rbp), %rsi
  movq -4896(%rbp), %rdx
  syscall
  movq %rax, -4912(%rbp)
  movq $50397203, %rax
  movq %rax, -4920(%rbp)
  jmp test_comparison_assert_pass_118
test_comparison_pr_nil_0_8335:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4928(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4928(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4936(%rbp)
  jmp test_comparison_pr_next_0_8335
test_comparison_pr_str_0_8335:
  movq -4872(%rbp), %rax
  addq $8, %rax
  movq %rax, -4944(%rbp)
  movq -4944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4952(%rbp)
  movq -4872(%rbp), %rax
  addq $24, %rax
  movq %rax, -4960(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4960(%rbp), %rsi
  movq -4952(%rbp), %rdx
  syscall
  movq %rax, -4968(%rbp)
  jmp test_comparison_pr_next_0_8335
test_comparison_pr_next_0_8335:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4976(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4976(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4984(%rbp)
  movq $0, %rax
  movq -1736(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4992(%rbp)
  movq -4992(%rbp), %rax
  jmp test_comparison_epilogue
test_comparison_epilogue:
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
.Lfunc_end_test_comparison:

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
  subq $5288, %rsp
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
  jmp test_parsing_block_0
test_parsing_block_0:
  leaq str_hdr_120(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1872(%rbp)
  movq -1872(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1880(%rbp)
  movq -1880(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_pr_nil_0_5386
  jmp test_parsing_pr_str_0_5386
test_parsing_block_6:
  jmp test_parsing_block_14
test_parsing_block_7:
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_122(%rip), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1888(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1896(%rbp)
  movq -1888(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_123
  jmp test_parsing_assert_fail_123
test_parsing_block_14:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1904(%rbp)
  movq -1904(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1912(%rbp)
  movq -1912(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_17
test_parsing_block_17:
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1920(%rbp)
  movq -1920(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1928(%rbp)
  movq -1928(%rbp), %rax
  addq $0, %rax
  movq %rax, -1936(%rbp)
  movq -1936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1944(%rbp)
  movq -1944(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1952(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1960(%rbp)
  movq -1960(%rbp), %rax
  cmpq -1952(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1968(%rbp)
  movq -1968(%rbp), %rax
  movq -168(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_124(%rip), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1976(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1984(%rbp)
  movq -1976(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_125
  jmp test_parsing_assert_fail_125
test_parsing_block_47:
  jmp test_parsing_block_55
test_parsing_block_48:
  movq $0, %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_137(%rip), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1992(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2000(%rbp)
  movq -1992(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_138
  jmp test_parsing_assert_fail_138
test_parsing_block_55:
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2008(%rbp)
  movq -2008(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2016(%rbp)
  movq -2016(%rbp), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_58
test_parsing_block_58:
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2024(%rbp)
  movq -2024(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2032(%rbp)
  movq -2032(%rbp), %rax
  addq $0, %rax
  movq %rax, -2040(%rbp)
  movq -2040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2048(%rbp)
  movq -2048(%rbp), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2056(%rbp)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2064(%rbp)
  movq -2064(%rbp), %rax
  cmpq -2056(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2072(%rbp)
  movq -2072(%rbp), %rax
  movq -456(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_139(%rip), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2080(%rbp)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2088(%rbp)
  movq -2080(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_140
  jmp test_parsing_assert_fail_140
test_parsing_block_78:
  jmp test_parsing_block_86
test_parsing_block_79:
  movq $0, %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_146(%rip), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2096(%rbp)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2104(%rbp)
  movq -2096(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_147
  jmp test_parsing_assert_fail_147
test_parsing_block_86:
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2112(%rbp)
  movq -2112(%rbp), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2120(%rbp)
  movq -2120(%rbp), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_89
test_parsing_block_89:
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2128(%rbp)
  movq -2128(%rbp), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2136(%rbp)
  movq -2136(%rbp), %rax
  addq $24, %rax
  movq %rax, -2144(%rbp)
  movq -2144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2152(%rbp)
  movq -2152(%rbp), %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_148(%rip), %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2160(%rbp)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2168(%rbp)
  movq -2160(%rbp), %rdi
  movq -2168(%rbp), %rsi
  call lm_key_eq
  mov -2176(%rbp), rax
  movq -2176(%rbp), %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_149(%rip), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2184(%rbp)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2192(%rbp)
  movq -2184(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_150
  jmp test_parsing_assert_fail_150
test_parsing_block_104:
  jmp test_parsing_block_112
test_parsing_block_105:
  movq $0, %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_155(%rip), %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2200(%rbp)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2208(%rbp)
  movq -2200(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_156
  jmp test_parsing_assert_fail_156
test_parsing_block_112:
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2216(%rbp)
  movq -2216(%rbp), %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2224(%rbp)
  movq -2224(%rbp), %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_115
test_parsing_block_115:
  movq -752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2232(%rbp)
  movq -2232(%rbp), %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2240(%rbp)
  movq -2240(%rbp), %rax
  addq $24, %rax
  movq %rax, -2248(%rbp)
  movq -2248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2256(%rbp)
  movq -2256(%rbp), %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_157(%rip), %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2264(%rbp)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2272(%rbp)
  movq -2264(%rbp), %rdi
  movq -2272(%rbp), %rsi
  call lm_key_eq
  mov -2280(%rbp), rax
  movq -2280(%rbp), %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_158(%rip), %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2288(%rbp)
  movq -840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2296(%rbp)
  movq -2288(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_159
  jmp test_parsing_assert_fail_159
test_parsing_block_130:
  jmp test_parsing_block_138
test_parsing_block_131:
  movq $0, %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_164(%rip), %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2304(%rbp)
  movq -952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2312(%rbp)
  movq -2304(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_165
  jmp test_parsing_assert_fail_165
test_parsing_block_138:
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2320(%rbp)
  movq -2320(%rbp), %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2328(%rbp)
  movq -2328(%rbp), %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_141
test_parsing_block_141:
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2336(%rbp)
  movq -2336(%rbp), %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2344(%rbp)
  movq -2344(%rbp), %rax
  addq $24, %rax
  movq %rax, -2352(%rbp)
  movq -2352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2360(%rbp)
  movq -2360(%rbp), %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_166(%rip), %rax
  movq -992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2368(%rbp)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2376(%rbp)
  movq -2368(%rbp), %rdi
  movq -2376(%rbp), %rsi
  call lm_key_eq
  mov -2384(%rbp), rax
  movq -2384(%rbp), %rax
  movq -1000(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_167(%rip), %rax
  movq -1008(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2392(%rbp)
  movq -1008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2400(%rbp)
  movq -2392(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_168
  jmp test_parsing_assert_fail_168
test_parsing_block_157:
  jmp test_parsing_block_162
test_parsing_block_158:
  movq $1, %rax
  movq -1120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2408(%rbp)
  movq -2408(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2416(%rbp)
  movq -2416(%rbp), %rax
  movq -1096(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_165
test_parsing_block_162:
  movq -1080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2424(%rbp)
  movq -2424(%rbp), %rax
  movq -1104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2432(%rbp)
  movq -2432(%rbp), %rax
  movq -1096(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_165
test_parsing_block_165:
  movq -1096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2440(%rbp)
  movq -2440(%rbp), %rax
  movq -1128(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_173(%rip), %rax
  movq -1136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2448(%rbp)
  movq -1136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2456(%rbp)
  movq -2448(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_174
  jmp test_parsing_assert_fail_174
test_parsing_block_174:
  jmp test_parsing_block_179
test_parsing_block_175:
  movq $1, %rax
  movq -1208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2464(%rbp)
  movq -2464(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2472(%rbp)
  movq -2472(%rbp), %rax
  movq -1184(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_182
test_parsing_block_179:
  movq -1168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2480(%rbp)
  movq -2480(%rbp), %rax
  movq -1192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2488(%rbp)
  movq -2488(%rbp), %rax
  movq -1184(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_182
test_parsing_block_182:
  movq -1184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2496(%rbp)
  movq -2496(%rbp), %rax
  movq -1216(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_176(%rip), %rax
  movq -1224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2504(%rbp)
  movq -1224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2512(%rbp)
  movq -2504(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_177
  jmp test_parsing_assert_fail_177
test_parsing_block_191:
  jmp test_parsing_block_196
test_parsing_block_192:
  movq $1, %rax
  movq -1296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2520(%rbp)
  movq -2520(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2528(%rbp)
  movq -2528(%rbp), %rax
  movq -1272(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_199
test_parsing_block_196:
  movq -1256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2536(%rbp)
  movq -2536(%rbp), %rax
  movq -1280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2544(%rbp)
  movq -2544(%rbp), %rax
  movq -1272(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_199
test_parsing_block_199:
  movq -1272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2552(%rbp)
  movq -2552(%rbp), %rax
  movq -1304(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_179(%rip), %rax
  movq -1312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2560(%rbp)
  movq -1312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2568(%rbp)
  movq -2560(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_180
  jmp test_parsing_assert_fail_180
test_parsing_block_208:
  jmp test_parsing_block_213
test_parsing_block_209:
  movq $1, %rax
  movq -1384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2576(%rbp)
  movq -2576(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2584(%rbp)
  movq -2584(%rbp), %rax
  movq -1360(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_216
test_parsing_block_213:
  movq -1344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2592(%rbp)
  movq -2592(%rbp), %rax
  movq -1368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2600(%rbp)
  movq -2600(%rbp), %rax
  movq -1360(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_216
test_parsing_block_216:
  movq -1360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2608(%rbp)
  movq -2608(%rbp), %rax
  movq -1392(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_182(%rip), %rax
  movq -1400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2616(%rbp)
  movq -1400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2624(%rbp)
  movq -2616(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_183
  jmp test_parsing_assert_fail_183
test_parsing_block_225:
  jmp test_parsing_block_230
test_parsing_block_226:
  movq $1, %rax
  movq -1472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2632(%rbp)
  movq -2632(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2640(%rbp)
  movq -2640(%rbp), %rax
  movq -1448(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_233
test_parsing_block_230:
  movq -1432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2648(%rbp)
  movq -2648(%rbp), %rax
  movq -1456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2656(%rbp)
  movq -2656(%rbp), %rax
  movq -1448(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_233
test_parsing_block_233:
  movq -1448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2664(%rbp)
  movq -2664(%rbp), %rax
  movq -1480(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_185(%rip), %rax
  movq -1488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2672(%rbp)
  movq -1488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2680(%rbp)
  movq -2672(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_186
  jmp test_parsing_assert_fail_186
test_parsing_block_242:
  jmp test_parsing_block_247
test_parsing_block_243:
  movq $1, %rax
  movq -1560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2688(%rbp)
  movq -2688(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2696(%rbp)
  movq -2696(%rbp), %rax
  movq -1536(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_250
test_parsing_block_247:
  movq -1520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2704(%rbp)
  movq -2704(%rbp), %rax
  movq -1544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2712(%rbp)
  movq -2712(%rbp), %rax
  movq -1536(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_250
test_parsing_block_250:
  movq -1536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2720(%rbp)
  movq -2720(%rbp), %rax
  movq -1568(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_188(%rip), %rax
  movq -1576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2728(%rbp)
  movq -1576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2736(%rbp)
  movq -2728(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_189
  jmp test_parsing_assert_fail_189
test_parsing_block_259:
  jmp test_parsing_block_264
test_parsing_block_260:
  movq $1, %rax
  movq -1648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2744(%rbp)
  movq -2744(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2752(%rbp)
  movq -2752(%rbp), %rax
  movq -1624(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_267
test_parsing_block_264:
  movq -1608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2760(%rbp)
  movq -2760(%rbp), %rax
  movq -1632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2768(%rbp)
  movq -2768(%rbp), %rax
  movq -1624(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_267
test_parsing_block_267:
  movq -1624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2776(%rbp)
  movq -2776(%rbp), %rax
  movq -1656(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_191(%rip), %rax
  movq -1664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2784(%rbp)
  movq -1664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2792(%rbp)
  movq -2784(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_192
  jmp test_parsing_assert_fail_192
test_parsing_block_276:
  jmp test_parsing_block_281
test_parsing_block_277:
  movq $1, %rax
  movq -1736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2800(%rbp)
  movq -2800(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2808(%rbp)
  movq -2808(%rbp), %rax
  movq -1712(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_284
test_parsing_block_281:
  movq -1696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2816(%rbp)
  movq -2816(%rbp), %rax
  movq -1720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2824(%rbp)
  movq -2824(%rbp), %rax
  movq -1712(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_284
test_parsing_block_284:
  movq -1712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2832(%rbp)
  movq -2832(%rbp), %rax
  movq -1744(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_194(%rip), %rax
  movq -1752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2840(%rbp)
  movq -1752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2848(%rbp)
  movq -2840(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_195
  jmp test_parsing_assert_fail_195
test_parsing_pr_nil_0_5386:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2856(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2856(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2864(%rbp)
  jmp test_parsing_pr_next_0_5386
test_parsing_pr_str_0_5386:
  movq -1872(%rbp), %rax
  addq $8, %rax
  movq %rax, -2872(%rbp)
  movq -2872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2880(%rbp)
  movq -1872(%rbp), %rax
  addq $24, %rax
  movq %rax, -2888(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2888(%rbp), %rsi
  movq -2880(%rbp), %rdx
  syscall
  movq %rax, -2896(%rbp)
  jmp test_parsing_pr_next_0_5386
test_parsing_pr_next_0_5386:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2904(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2912(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_121(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2920(%rbp)
  movq -2920(%rbp), %rdi
  call std.semver.parse
  mov -2928(%rbp), rax
  movq -2928(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2936(%rbp)
  movq -2936(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -2944(%rbp)
  movq -2944(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2952(%rbp)
  movq -2952(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_block_7
  jmp test_parsing_block_6
test_parsing_assert_pass_123:
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2960(%rbp)
  movq -2960(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2968(%rbp)
  movq -2968(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_17
test_parsing_assert_fail_123:
  movq -1896(%rbp), %rax
  addq $8, %rax
  movq %rax, -2976(%rbp)
  movq -2976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2984(%rbp)
  movq -1896(%rbp), %rax
  addq $24, %rax
  movq %rax, -2992(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2992(%rbp), %rsi
  movq -2984(%rbp), %rdx
  syscall
  movq %rax, -3000(%rbp)
  movq $50397203, %rax
  movq %rax, -3008(%rbp)
  jmp test_parsing_assert_pass_123
test_parsing_assert_pass_125:
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3016(%rbp)
  movq -3016(%rbp), %rax
  addq $8, %rax
  movq %rax, -3024(%rbp)
  movq -3024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3032(%rbp)
  movq -3032(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3040(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3048(%rbp)
  movq -3048(%rbp), %rax
  cmpq -3040(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3056(%rbp)
  movq -3056(%rbp), %rax
  movq -208(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_126(%rip), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3064(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3072(%rbp)
  movq -3064(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_127
  jmp test_parsing_assert_fail_127
test_parsing_assert_fail_125:
  movq -1984(%rbp), %rax
  addq $8, %rax
  movq %rax, -3080(%rbp)
  movq -3080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3088(%rbp)
  movq -1984(%rbp), %rax
  addq $24, %rax
  movq %rax, -3096(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3096(%rbp), %rsi
  movq -3088(%rbp), %rdx
  syscall
  movq %rax, -3104(%rbp)
  movq $50397203, %rax
  movq %rax, -3112(%rbp)
  jmp test_parsing_assert_pass_125
test_parsing_assert_pass_127:
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3120(%rbp)
  movq -3120(%rbp), %rax
  addq $16, %rax
  movq %rax, -3128(%rbp)
  movq -3128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3136(%rbp)
  movq -3136(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3144(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3152(%rbp)
  movq -3152(%rbp), %rax
  cmpq -3144(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3160(%rbp)
  movq -3160(%rbp), %rax
  movq -248(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_128(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3168(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3176(%rbp)
  movq -3168(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_129
  jmp test_parsing_assert_fail_129
test_parsing_assert_fail_127:
  movq -3072(%rbp), %rax
  addq $8, %rax
  movq %rax, -3184(%rbp)
  movq -3184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3192(%rbp)
  movq -3072(%rbp), %rax
  addq $24, %rax
  movq %rax, -3200(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3200(%rbp), %rsi
  movq -3192(%rbp), %rdx
  syscall
  movq %rax, -3208(%rbp)
  movq $50397203, %rax
  movq %rax, -3216(%rbp)
  jmp test_parsing_assert_pass_127
test_parsing_assert_pass_129:
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3224(%rbp)
  movq -3224(%rbp), %rax
  addq $24, %rax
  movq %rax, -3232(%rbp)
  movq -3232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3240(%rbp)
  movq -3240(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_130(%rip), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3248(%rbp)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3256(%rbp)
  movq -3248(%rbp), %rdi
  movq -3256(%rbp), %rsi
  call lm_key_eq
  mov -3264(%rbp), rax
  movq -3264(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_131(%rip), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3272(%rbp)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3280(%rbp)
  movq -3272(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_132
  jmp test_parsing_assert_fail_132
test_parsing_assert_fail_129:
  movq -3176(%rbp), %rax
  addq $8, %rax
  movq %rax, -3288(%rbp)
  movq -3288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3296(%rbp)
  movq -3176(%rbp), %rax
  addq $24, %rax
  movq %rax, -3304(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3304(%rbp), %rsi
  movq -3296(%rbp), %rdx
  syscall
  movq %rax, -3312(%rbp)
  movq $50397203, %rax
  movq %rax, -3320(%rbp)
  jmp test_parsing_assert_pass_129
test_parsing_assert_pass_132:
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3328(%rbp)
  movq -3328(%rbp), %rax
  addq $32, %rax
  movq %rax, -3336(%rbp)
  movq -3336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3344(%rbp)
  movq -3344(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_133(%rip), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3352(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3360(%rbp)
  movq -3352(%rbp), %rdi
  movq -3360(%rbp), %rsi
  call lm_key_eq
  mov -3368(%rbp), rax
  movq -3368(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_134(%rip), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3376(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3384(%rbp)
  movq -3376(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_135
  jmp test_parsing_assert_fail_135
test_parsing_assert_fail_132:
  movq -3280(%rbp), %rax
  addq $8, %rax
  movq %rax, -3392(%rbp)
  movq -3392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3400(%rbp)
  movq -3280(%rbp), %rax
  addq $24, %rax
  movq %rax, -3408(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3408(%rbp), %rsi
  movq -3400(%rbp), %rdx
  syscall
  movq %rax, -3416(%rbp)
  movq $50397203, %rax
  movq %rax, -3424(%rbp)
  jmp test_parsing_assert_pass_132
test_parsing_assert_pass_135:
  movq $0, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_136(%rip), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3432(%rbp)
  movq -3432(%rbp), %rdi
  call std.semver.parse
  mov -3440(%rbp), rax
  movq -3440(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3448(%rbp)
  movq -3448(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -3456(%rbp)
  movq -3456(%rbp), %rax
  movq -368(%rbp), %rdx
  movl %eax, (%rdx)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3464(%rbp)
  movq -3464(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_block_48
  jmp test_parsing_block_47
test_parsing_assert_fail_135:
  movq -3384(%rbp), %rax
  addq $8, %rax
  movq %rax, -3472(%rbp)
  movq -3472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3480(%rbp)
  movq -3384(%rbp), %rax
  addq $24, %rax
  movq %rax, -3488(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3488(%rbp), %rsi
  movq -3480(%rbp), %rdx
  syscall
  movq %rax, -3496(%rbp)
  movq $50397203, %rax
  movq %rax, -3504(%rbp)
  jmp test_parsing_assert_pass_135
test_parsing_assert_pass_138:
  movq $0, %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3512(%rbp)
  movq -3512(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3520(%rbp)
  movq -3520(%rbp), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_58
test_parsing_assert_fail_138:
  movq -2000(%rbp), %rax
  addq $8, %rax
  movq %rax, -3528(%rbp)
  movq -3528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3536(%rbp)
  movq -2000(%rbp), %rax
  addq $24, %rax
  movq %rax, -3544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3544(%rbp), %rsi
  movq -3536(%rbp), %rdx
  syscall
  movq %rax, -3552(%rbp)
  movq $50397203, %rax
  movq %rax, -3560(%rbp)
  jmp test_parsing_assert_pass_138
test_parsing_assert_pass_140:
  movq $0, %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3568(%rbp)
  movq -3568(%rbp), %rax
  addq $8, %rax
  movq %rax, -3576(%rbp)
  movq -3576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3584(%rbp)
  movq -3584(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3592(%rbp)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3600(%rbp)
  movq -3600(%rbp), %rax
  cmpq -3592(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3608(%rbp)
  movq -3608(%rbp), %rax
  movq -496(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_141(%rip), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3616(%rbp)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3624(%rbp)
  movq -3616(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_142
  jmp test_parsing_assert_fail_142
test_parsing_assert_fail_140:
  movq -2088(%rbp), %rax
  addq $8, %rax
  movq %rax, -3632(%rbp)
  movq -3632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3640(%rbp)
  movq -2088(%rbp), %rax
  addq $24, %rax
  movq %rax, -3648(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3648(%rbp), %rsi
  movq -3640(%rbp), %rdx
  syscall
  movq %rax, -3656(%rbp)
  movq $50397203, %rax
  movq %rax, -3664(%rbp)
  jmp test_parsing_assert_pass_140
test_parsing_assert_pass_142:
  movq $0, %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3672(%rbp)
  movq -3672(%rbp), %rax
  addq $16, %rax
  movq %rax, -3680(%rbp)
  movq -3680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3688(%rbp)
  movq -3688(%rbp), %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3696(%rbp)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3704(%rbp)
  movq -3704(%rbp), %rax
  cmpq -3696(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3712(%rbp)
  movq -3712(%rbp), %rax
  movq -536(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_143(%rip), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3720(%rbp)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3728(%rbp)
  movq -3720(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_144
  jmp test_parsing_assert_fail_144
test_parsing_assert_fail_142:
  movq -3624(%rbp), %rax
  addq $8, %rax
  movq %rax, -3736(%rbp)
  movq -3736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3744(%rbp)
  movq -3624(%rbp), %rax
  addq $24, %rax
  movq %rax, -3752(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3752(%rbp), %rsi
  movq -3744(%rbp), %rdx
  syscall
  movq %rax, -3760(%rbp)
  movq $50397203, %rax
  movq %rax, -3768(%rbp)
  jmp test_parsing_assert_pass_142
test_parsing_assert_pass_144:
  movq $0, %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_145(%rip), %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3776(%rbp)
  movq -3776(%rbp), %rdi
  call std.semver.parse
  mov -3784(%rbp), rax
  movq -3784(%rbp), %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3792(%rbp)
  movq -3792(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -3800(%rbp)
  movq -3800(%rbp), %rax
  movq -576(%rbp), %rdx
  movl %eax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3808(%rbp)
  movq -3808(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_block_79
  jmp test_parsing_block_78
test_parsing_assert_fail_144:
  movq -3728(%rbp), %rax
  addq $8, %rax
  movq %rax, -3816(%rbp)
  movq -3816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3824(%rbp)
  movq -3728(%rbp), %rax
  addq $24, %rax
  movq %rax, -3832(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3832(%rbp), %rsi
  movq -3824(%rbp), %rdx
  syscall
  movq %rax, -3840(%rbp)
  movq $50397203, %rax
  movq %rax, -3848(%rbp)
  jmp test_parsing_assert_pass_144
test_parsing_assert_pass_147:
  movq $0, %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3856(%rbp)
  movq -3856(%rbp), %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3864(%rbp)
  movq -3864(%rbp), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_89
test_parsing_assert_fail_147:
  movq -2104(%rbp), %rax
  addq $8, %rax
  movq %rax, -3872(%rbp)
  movq -3872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3880(%rbp)
  movq -2104(%rbp), %rax
  addq $24, %rax
  movq %rax, -3888(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3888(%rbp), %rsi
  movq -3880(%rbp), %rdx
  syscall
  movq %rax, -3896(%rbp)
  movq $50397203, %rax
  movq %rax, -3904(%rbp)
  jmp test_parsing_assert_pass_147
test_parsing_assert_pass_150:
  movq $0, %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3912(%rbp)
  movq -3912(%rbp), %rax
  addq $32, %rax
  movq %rax, -3920(%rbp)
  movq -3920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3928(%rbp)
  movq -3928(%rbp), %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_151(%rip), %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3936(%rbp)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3944(%rbp)
  movq -3936(%rbp), %rdi
  movq -3944(%rbp), %rsi
  call lm_key_eq
  mov -3952(%rbp), rax
  movq -3952(%rbp), %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_152(%rip), %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3960(%rbp)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3968(%rbp)
  movq -3960(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_153
  jmp test_parsing_assert_fail_153
test_parsing_assert_fail_150:
  movq -2192(%rbp), %rax
  addq $8, %rax
  movq %rax, -3976(%rbp)
  movq -3976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3984(%rbp)
  movq -2192(%rbp), %rax
  addq $24, %rax
  movq %rax, -3992(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3992(%rbp), %rsi
  movq -3984(%rbp), %rdx
  syscall
  movq %rax, -4000(%rbp)
  movq $50397203, %rax
  movq %rax, -4008(%rbp)
  jmp test_parsing_assert_pass_150
test_parsing_assert_pass_153:
  movq $0, %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_154(%rip), %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4016(%rbp)
  movq -4016(%rbp), %rdi
  call std.semver.parse
  mov -4024(%rbp), rax
  movq -4024(%rbp), %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4032(%rbp)
  movq -4032(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -4040(%rbp)
  movq -4040(%rbp), %rax
  movq -744(%rbp), %rdx
  movl %eax, (%rdx)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4048(%rbp)
  movq -4048(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_block_105
  jmp test_parsing_block_104
test_parsing_assert_fail_153:
  movq -3968(%rbp), %rax
  addq $8, %rax
  movq %rax, -4056(%rbp)
  movq -4056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4064(%rbp)
  movq -3968(%rbp), %rax
  addq $24, %rax
  movq %rax, -4072(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4072(%rbp), %rsi
  movq -4064(%rbp), %rdx
  syscall
  movq %rax, -4080(%rbp)
  movq $50397203, %rax
  movq %rax, -4088(%rbp)
  jmp test_parsing_assert_pass_153
test_parsing_assert_pass_156:
  movq $0, %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4096(%rbp)
  movq -4096(%rbp), %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4104(%rbp)
  movq -4104(%rbp), %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_115
test_parsing_assert_fail_156:
  movq -2208(%rbp), %rax
  addq $8, %rax
  movq %rax, -4112(%rbp)
  movq -4112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4120(%rbp)
  movq -2208(%rbp), %rax
  addq $24, %rax
  movq %rax, -4128(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4128(%rbp), %rsi
  movq -4120(%rbp), %rdx
  syscall
  movq %rax, -4136(%rbp)
  movq $50397203, %rax
  movq %rax, -4144(%rbp)
  jmp test_parsing_assert_pass_156
test_parsing_assert_pass_159:
  movq $0, %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4152(%rbp)
  movq -4152(%rbp), %rax
  addq $32, %rax
  movq %rax, -4160(%rbp)
  movq -4160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4168(%rbp)
  movq -4168(%rbp), %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_160(%rip), %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4176(%rbp)
  movq -864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4184(%rbp)
  movq -4176(%rbp), %rdi
  movq -4184(%rbp), %rsi
  call lm_key_eq
  mov -4192(%rbp), rax
  movq -4192(%rbp), %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_161(%rip), %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4200(%rbp)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4208(%rbp)
  movq -4200(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_162
  jmp test_parsing_assert_fail_162
test_parsing_assert_fail_159:
  movq -2296(%rbp), %rax
  addq $8, %rax
  movq %rax, -4216(%rbp)
  movq -4216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4224(%rbp)
  movq -2296(%rbp), %rax
  addq $24, %rax
  movq %rax, -4232(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4232(%rbp), %rsi
  movq -4224(%rbp), %rdx
  syscall
  movq %rax, -4240(%rbp)
  movq $50397203, %rax
  movq %rax, -4248(%rbp)
  jmp test_parsing_assert_pass_159
test_parsing_assert_pass_162:
  movq $0, %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_163(%rip), %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4256(%rbp)
  movq -4256(%rbp), %rdi
  call std.semver.parse
  mov -4264(%rbp), rax
  movq -4264(%rbp), %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4272(%rbp)
  movq -4272(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -4280(%rbp)
  movq -4280(%rbp), %rax
  movq -912(%rbp), %rdx
  movl %eax, (%rdx)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4288(%rbp)
  movq -4288(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_block_131
  jmp test_parsing_block_130
test_parsing_assert_fail_162:
  movq -4208(%rbp), %rax
  addq $8, %rax
  movq %rax, -4296(%rbp)
  movq -4296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4304(%rbp)
  movq -4208(%rbp), %rax
  addq $24, %rax
  movq %rax, -4312(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4312(%rbp), %rsi
  movq -4304(%rbp), %rdx
  syscall
  movq %rax, -4320(%rbp)
  movq $50397203, %rax
  movq %rax, -4328(%rbp)
  jmp test_parsing_assert_pass_162
test_parsing_assert_pass_165:
  movq $0, %rax
  movq -960(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -968(%rbp), %rdx
  movq %rax, (%rdx)
  movq -968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4336(%rbp)
  movq -4336(%rbp), %rax
  movq -936(%rbp), %rdx
  movq %rax, (%rdx)
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4344(%rbp)
  movq -4344(%rbp), %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_parsing_block_141
test_parsing_assert_fail_165:
  movq -2312(%rbp), %rax
  addq $8, %rax
  movq %rax, -4352(%rbp)
  movq -4352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4360(%rbp)
  movq -2312(%rbp), %rax
  addq $24, %rax
  movq %rax, -4368(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4368(%rbp), %rsi
  movq -4360(%rbp), %rdx
  syscall
  movq %rax, -4376(%rbp)
  movq $50397203, %rax
  movq %rax, -4384(%rbp)
  jmp test_parsing_assert_pass_165
test_parsing_assert_pass_168:
  movq $0, %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4392(%rbp)
  movq -4392(%rbp), %rax
  addq $32, %rax
  movq %rax, -4400(%rbp)
  movq -4400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4408(%rbp)
  movq -4408(%rbp), %rax
  movq -1024(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_169(%rip), %rax
  movq -1032(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4416(%rbp)
  movq -1032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4424(%rbp)
  movq -4416(%rbp), %rdi
  movq -4424(%rbp), %rsi
  call lm_key_eq
  mov -4432(%rbp), rax
  movq -4432(%rbp), %rax
  movq -1040(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_170(%rip), %rax
  movq -1048(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4440(%rbp)
  movq -1048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4448(%rbp)
  movq -4440(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_assert_pass_171
  jmp test_parsing_assert_fail_171
test_parsing_assert_fail_168:
  movq -2400(%rbp), %rax
  addq $8, %rax
  movq %rax, -4456(%rbp)
  movq -4456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4464(%rbp)
  movq -2400(%rbp), %rax
  addq $24, %rax
  movq %rax, -4472(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4472(%rbp), %rsi
  movq -4464(%rbp), %rdx
  syscall
  movq %rax, -4480(%rbp)
  movq $50397203, %rax
  movq %rax, -4488(%rbp)
  jmp test_parsing_assert_pass_168
test_parsing_assert_pass_171:
  movq $0, %rax
  movq -1056(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_172(%rip), %rax
  movq -1072(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4496(%rbp)
  movq -4496(%rbp), %rdi
  call std.semver.parse
  mov -4504(%rbp), rax
  movq -4504(%rbp), %rax
  movq -1080(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4512(%rbp)
  movq -4512(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -4520(%rbp)
  movq -4520(%rbp), %rax
  movq -1088(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4528(%rbp)
  movq -4528(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_block_158
  jmp test_parsing_block_157
test_parsing_assert_fail_171:
  movq -4448(%rbp), %rax
  addq $8, %rax
  movq %rax, -4536(%rbp)
  movq -4536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4544(%rbp)
  movq -4448(%rbp), %rax
  addq $24, %rax
  movq %rax, -4552(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4552(%rbp), %rsi
  movq -4544(%rbp), %rdx
  syscall
  movq %rax, -4560(%rbp)
  movq $50397203, %rax
  movq %rax, -4568(%rbp)
  jmp test_parsing_assert_pass_171
test_parsing_assert_pass_174:
  movq $0, %rax
  movq -1144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4576(%rbp)
  movq -4576(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_175(%rip), %rax
  movq -1160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4584(%rbp)
  movq -4584(%rbp), %rdi
  call std.semver.parse
  mov -4592(%rbp), rax
  movq -4592(%rbp), %rax
  movq -1168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4600(%rbp)
  movq -4600(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -4608(%rbp)
  movq -4608(%rbp), %rax
  movq -1176(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4616(%rbp)
  movq -4616(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_block_175
  jmp test_parsing_block_174
test_parsing_assert_fail_174:
  movq -2456(%rbp), %rax
  addq $8, %rax
  movq %rax, -4624(%rbp)
  movq -4624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4632(%rbp)
  movq -2456(%rbp), %rax
  addq $24, %rax
  movq %rax, -4640(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4640(%rbp), %rsi
  movq -4632(%rbp), %rdx
  syscall
  movq %rax, -4648(%rbp)
  movq $50397203, %rax
  movq %rax, -4656(%rbp)
  jmp test_parsing_assert_pass_174
test_parsing_assert_pass_177:
  movq $0, %rax
  movq -1232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4664(%rbp)
  movq -4664(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_178(%rip), %rax
  movq -1248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4672(%rbp)
  movq -4672(%rbp), %rdi
  call std.semver.parse
  mov -4680(%rbp), rax
  movq -4680(%rbp), %rax
  movq -1256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4688(%rbp)
  movq -4688(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -4696(%rbp)
  movq -4696(%rbp), %rax
  movq -1264(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4704(%rbp)
  movq -4704(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_block_192
  jmp test_parsing_block_191
test_parsing_assert_fail_177:
  movq -2512(%rbp), %rax
  addq $8, %rax
  movq %rax, -4712(%rbp)
  movq -4712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4720(%rbp)
  movq -2512(%rbp), %rax
  addq $24, %rax
  movq %rax, -4728(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4728(%rbp), %rsi
  movq -4720(%rbp), %rdx
  syscall
  movq %rax, -4736(%rbp)
  movq $50397203, %rax
  movq %rax, -4744(%rbp)
  jmp test_parsing_assert_pass_177
test_parsing_assert_pass_180:
  movq $0, %rax
  movq -1320(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4752(%rbp)
  movq -4752(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_181(%rip), %rax
  movq -1336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4760(%rbp)
  movq -4760(%rbp), %rdi
  call std.semver.parse
  mov -4768(%rbp), rax
  movq -4768(%rbp), %rax
  movq -1344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4776(%rbp)
  movq -4776(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -4784(%rbp)
  movq -4784(%rbp), %rax
  movq -1352(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4792(%rbp)
  movq -4792(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_block_209
  jmp test_parsing_block_208
test_parsing_assert_fail_180:
  movq -2568(%rbp), %rax
  addq $8, %rax
  movq %rax, -4800(%rbp)
  movq -4800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4808(%rbp)
  movq -2568(%rbp), %rax
  addq $24, %rax
  movq %rax, -4816(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4816(%rbp), %rsi
  movq -4808(%rbp), %rdx
  syscall
  movq %rax, -4824(%rbp)
  movq $50397203, %rax
  movq %rax, -4832(%rbp)
  jmp test_parsing_assert_pass_180
test_parsing_assert_pass_183:
  movq $0, %rax
  movq -1408(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4840(%rbp)
  movq -4840(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_184(%rip), %rax
  movq -1424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4848(%rbp)
  movq -4848(%rbp), %rdi
  call std.semver.parse
  mov -4856(%rbp), rax
  movq -4856(%rbp), %rax
  movq -1432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4864(%rbp)
  movq -4864(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -4872(%rbp)
  movq -4872(%rbp), %rax
  movq -1440(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4880(%rbp)
  movq -4880(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_block_226
  jmp test_parsing_block_225
test_parsing_assert_fail_183:
  movq -2624(%rbp), %rax
  addq $8, %rax
  movq %rax, -4888(%rbp)
  movq -4888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4896(%rbp)
  movq -2624(%rbp), %rax
  addq $24, %rax
  movq %rax, -4904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4904(%rbp), %rsi
  movq -4896(%rbp), %rdx
  syscall
  movq %rax, -4912(%rbp)
  movq $50397203, %rax
  movq %rax, -4920(%rbp)
  jmp test_parsing_assert_pass_183
test_parsing_assert_pass_186:
  movq $0, %rax
  movq -1496(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4928(%rbp)
  movq -4928(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_187(%rip), %rax
  movq -1512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4936(%rbp)
  movq -4936(%rbp), %rdi
  call std.semver.parse
  mov -4944(%rbp), rax
  movq -4944(%rbp), %rax
  movq -1520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4952(%rbp)
  movq -4952(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -4960(%rbp)
  movq -4960(%rbp), %rax
  movq -1528(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4968(%rbp)
  movq -4968(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_block_243
  jmp test_parsing_block_242
test_parsing_assert_fail_186:
  movq -2680(%rbp), %rax
  addq $8, %rax
  movq %rax, -4976(%rbp)
  movq -4976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4984(%rbp)
  movq -2680(%rbp), %rax
  addq $24, %rax
  movq %rax, -4992(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4992(%rbp), %rsi
  movq -4984(%rbp), %rdx
  syscall
  movq %rax, -5000(%rbp)
  movq $50397203, %rax
  movq %rax, -5008(%rbp)
  jmp test_parsing_assert_pass_186
test_parsing_assert_pass_189:
  movq $0, %rax
  movq -1584(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5016(%rbp)
  movq -5016(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_190(%rip), %rax
  movq -1600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5024(%rbp)
  movq -5024(%rbp), %rdi
  call std.semver.parse
  mov -5032(%rbp), rax
  movq -5032(%rbp), %rax
  movq -1608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5040(%rbp)
  movq -5040(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -5048(%rbp)
  movq -5048(%rbp), %rax
  movq -1616(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5056(%rbp)
  movq -5056(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_block_260
  jmp test_parsing_block_259
test_parsing_assert_fail_189:
  movq -2736(%rbp), %rax
  addq $8, %rax
  movq %rax, -5064(%rbp)
  movq -5064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5072(%rbp)
  movq -2736(%rbp), %rax
  addq $24, %rax
  movq %rax, -5080(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5080(%rbp), %rsi
  movq -5072(%rbp), %rdx
  syscall
  movq %rax, -5088(%rbp)
  movq $50397203, %rax
  movq %rax, -5096(%rbp)
  jmp test_parsing_assert_pass_189
test_parsing_assert_pass_192:
  movq $0, %rax
  movq -1672(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5104(%rbp)
  movq -5104(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_193(%rip), %rax
  movq -1688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5112(%rbp)
  movq -5112(%rbp), %rdi
  call std.semver.parse
  mov -5120(%rbp), rax
  movq -5120(%rbp), %rax
  movq -1696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5128(%rbp)
  movq -5128(%rbp), %rax
  cmpq $9223372036854775807, %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -5136(%rbp)
  movq -5136(%rbp), %rax
  movq -1704(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5144(%rbp)
  movq -5144(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_block_277
  jmp test_parsing_block_276
test_parsing_assert_fail_192:
  movq -2792(%rbp), %rax
  addq $8, %rax
  movq %rax, -5152(%rbp)
  movq -5152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5160(%rbp)
  movq -2792(%rbp), %rax
  addq $24, %rax
  movq %rax, -5168(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5168(%rbp), %rsi
  movq -5160(%rbp), %rdx
  syscall
  movq %rax, -5176(%rbp)
  movq $50397203, %rax
  movq %rax, -5184(%rbp)
  jmp test_parsing_assert_pass_192
test_parsing_assert_pass_195:
  movq $0, %rax
  movq -1760(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_196(%rip), %rax
  movq -1768(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5192(%rbp)
  movq -5192(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5200(%rbp)
  movq -5200(%rbp), %rax
  testq %rax, %rax
  jne test_parsing_pr_nil_0_492
  jmp test_parsing_pr_str_0_492
test_parsing_assert_fail_195:
  movq -2848(%rbp), %rax
  addq $8, %rax
  movq %rax, -5208(%rbp)
  movq -5208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5216(%rbp)
  movq -2848(%rbp), %rax
  addq $24, %rax
  movq %rax, -5224(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5224(%rbp), %rsi
  movq -5216(%rbp), %rdx
  syscall
  movq %rax, -5232(%rbp)
  movq $50397203, %rax
  movq %rax, -5240(%rbp)
  jmp test_parsing_assert_pass_195
test_parsing_pr_nil_0_492:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5248(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5248(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5256(%rbp)
  jmp test_parsing_pr_next_0_492
test_parsing_pr_str_0_492:
  movq -5192(%rbp), %rax
  addq $8, %rax
  movq %rax, -5264(%rbp)
  movq -5264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5272(%rbp)
  movq -5192(%rbp), %rax
  addq $24, %rax
  movq %rax, -5280(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5280(%rbp), %rsi
  movq -5272(%rbp), %rdx
  syscall
  movq %rax, -5288(%rbp)
  jmp test_parsing_pr_next_0_492
test_parsing_pr_next_0_492:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5296(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5296(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5304(%rbp)
  movq $0, %rax
  movq -1776(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5312(%rbp)
  movq -5312(%rbp), %rax
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

.globl std.semver.Version.is_compatible
std.semver.Version.is_compatible:
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
std.semver.Version.is_compatible_entry:
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
  jmp std.semver.Version.is_compatible_epilogue
std.semver.Version.is_compatible_epilogue:
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
.Lfunc_end_std.semver.Version.is_compatible:

.globl std.semver.Version.less_than
std.semver.Version.less_than:
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
std.semver.Version.less_than_entry:
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
  jmp std.semver.Version.less_than_epilogue
std.semver.Version.less_than_epilogue:
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
.Lfunc_end_std.semver.Version.less_than:

.globl std.semver.__init__
std.semver.__init__:
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
std.semver.__init___entry:
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
  jmp std.semver.__init___epilogue
std.semver.__init___epilogue:
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
.Lfunc_end_std.semver.__init__:

.globl std.semver.compare_strings
std.semver.compare_strings:
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
  movq %rsi, -56(%rbp)
std.semver.compare_strings_entry:
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
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.compare_strings_block_0
std.semver.compare_strings_block_0:
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
  jne std.semver.compare_strings_block_2
  jmp std.semver.compare_strings_block_4
std.semver.compare_strings_block_2:
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  jmp std.semver.compare_strings_epilogue
std.semver.compare_strings_block_4:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rdi
  call lm_list_len
  mov -512(%rbp), rax
  movq -512(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rdi
  call lm_list_len
  mov -536(%rbp), rax
  movq -536(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rax
  cmpq -560(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -576(%rbp)
  movq -576(%rbp), %rax
  movq -136(%rbp), %rdx
  movl %eax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -584(%rbp), %rax
  testq %rax, %rax
  jne std.semver.compare_strings_block_11
  jmp std.semver.compare_strings_block_13
std.semver.compare_strings_block_11:
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.compare_strings_block_13
std.semver.compare_strings_block_13:
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.compare_strings_block_15
std.semver.compare_strings_block_15:
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  cmpq -600(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rax
  movq -152(%rbp), %rdx
  movl %eax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -624(%rbp), %rax
  testq %rax, %rax
  jne std.semver.compare_strings_block_17
  jmp std.semver.compare_strings_block_45
std.semver.compare_strings_block_17:
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -640(%rbp), %rax
  addq -632(%rbp), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -656(%rbp), %rdi
  movq -664(%rbp), %rsi
  movq -672(%rbp), %rdx
  call substring
  mov -680(%rbp), rax
  movq -680(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -704(%rbp), %rax
  addq -696(%rbp), %rax
  movq %rax, -712(%rbp)
  movq -712(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -720(%rbp), %rdi
  movq -728(%rbp), %rsi
  movq -736(%rbp), %rdx
  call substring
  mov -744(%rbp), rax
  movq -744(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -760(%rbp), %rdi
  movq -768(%rbp), %rsi
  call lm_key_eq
  mov -776(%rbp), rax
  movq -776(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -784(%rbp)
  movq -784(%rbp), %rax
  movq -240(%rbp), %rdx
  movl %eax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -792(%rbp), %rax
  testq %rax, %rax
  jne std.semver.compare_strings_block_29
  jmp std.semver.compare_strings_block_40
std.semver.compare_strings_block_29:
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -800(%rbp), %rdi
  call std.semver.byte_ord
  mov -808(%rbp), rax
  movq -808(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -816(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -824(%rbp), %rdi
  call std.semver.byte_ord
  mov -832(%rbp), rax
  movq -832(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -840(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -856(%rbp)
  movq -856(%rbp), %rax
  cmpq -848(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -864(%rbp)
  movq -864(%rbp), %rax
  movq -280(%rbp), %rdx
  movl %eax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -872(%rbp), %rax
  testq %rax, %rax
  jne std.semver.compare_strings_block_35
  jmp std.semver.compare_strings_block_37
std.semver.compare_strings_block_35:
  movq $1, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -880(%rbp), %rax
  jmp std.semver.compare_strings_epilogue
std.semver.compare_strings_block_37:
  movq $1, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -888(%rbp), %rax
  negq %rax
  movq %rax, -896(%rbp)
  movq -896(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -904(%rbp), %rax
  jmp std.semver.compare_strings_epilogue
std.semver.compare_strings_block_40:
  movq $1, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -912(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -920(%rbp), %rax
  addq -912(%rbp), %rax
  movq %rax, -928(%rbp)
  movq -928(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -936(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.compare_strings_block_15
std.semver.compare_strings_block_45:
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -952(%rbp), %rax
  cmpq -944(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -960(%rbp)
  movq -960(%rbp), %rax
  movq -336(%rbp), %rdx
  movl %eax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -968(%rbp), %rax
  testq %rax, %rax
  jne std.semver.compare_strings_block_47
  jmp std.semver.compare_strings_block_49
std.semver.compare_strings_block_47:
  movq $1, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -976(%rbp), %rax
  jmp std.semver.compare_strings_epilogue
std.semver.compare_strings_block_49:
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -984(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -992(%rbp), %rax
  cmpq -984(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1000(%rbp)
  movq -1000(%rbp), %rax
  movq -352(%rbp), %rdx
  movl %eax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1008(%rbp)
  movq -1008(%rbp), %rax
  testq %rax, %rax
  jne std.semver.compare_strings_block_51
  jmp std.semver.compare_strings_block_54
std.semver.compare_strings_block_51:
  movq $1, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1016(%rbp)
  movq -1016(%rbp), %rax
  negq %rax
  movq %rax, -1024(%rbp)
  movq -1024(%rbp), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1032(%rbp)
  movq -1032(%rbp), %rax
  jmp std.semver.compare_strings_epilogue
std.semver.compare_strings_block_54:
  movq $0, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -1040(%rbp), %rax
  jmp std.semver.compare_strings_epilogue
std.semver.compare_strings_epilogue:
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
.Lfunc_end_std.semver.compare_strings:

.globl std.semver.index_of
std.semver.index_of:
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
std.semver.index_of_entry:
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
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.index_of_block_0
std.semver.index_of_block_0:
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.index_of_block_2
std.semver.index_of_block_2:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rdi
  call lm_list_len
  mov -272(%rbp), rax
  movq -272(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -280(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rax
  cmpq -280(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -296(%rbp)
  movq -296(%rbp), %rax
  movq -96(%rbp), %rdx
  movl %eax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -304(%rbp)
  movq -304(%rbp), %rax
  testq %rax, %rax
  jne std.semver.index_of_block_5
  jmp std.semver.index_of_block_17
std.semver.index_of_block_5:
  movq $1, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -312(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rax
  addq -312(%rbp), %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -344(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -352(%rbp)
  movq -336(%rbp), %rdi
  movq -344(%rbp), %rsi
  movq -352(%rbp), %rdx
  call substring
  mov -360(%rbp), rax
  movq -360(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -376(%rbp)
  movq -368(%rbp), %rdi
  movq -376(%rbp), %rsi
  call lm_key_eq
  mov -384(%rbp), rax
  movq -384(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rax
  testq %rax, %rax
  jne std.semver.index_of_block_11
  jmp std.semver.index_of_block_12
std.semver.index_of_block_11:
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  jmp std.semver.index_of_epilogue
std.semver.index_of_block_12:
  movq $1, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -416(%rbp)
  movq -416(%rbp), %rax
  addq -408(%rbp), %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.semver.index_of_block_2
std.semver.index_of_block_17:
  movq $1, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -440(%rbp), %rax
  negq %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  jmp std.semver.index_of_epilogue
std.semver.index_of_epilogue:
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
.Lfunc_end_std.semver.index_of:

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
  leaq str_hdr_197(%rip), %rax
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
  jne __user_main_pr_nil_0_6649
  jmp __user_main_pr_str_0_6649
__user_main_pr_nil_0_6649:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -344(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -352(%rbp)
  jmp __user_main_pr_next_0_6649
__user_main_pr_str_0_6649:
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
  jmp __user_main_pr_next_0_6649
__user_main_pr_next_0_6649:
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
  leaq str_hdr_198(%rip), %rax
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
  jne __user_main_assert_pass_199
  jmp __user_main_assert_fail_199
__user_main_assert_pass_199:
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  call test_comparison
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
  leaq str_hdr_200(%rip), %rax
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
  jne __user_main_assert_pass_201
  jmp __user_main_assert_fail_201
__user_main_assert_fail_199:
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
  jmp __user_main_assert_pass_199
__user_main_assert_pass_201:
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  call test_compatibility
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
  leaq str_hdr_202(%rip), %rax
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
  jne __user_main_assert_pass_203
  jmp __user_main_assert_fail_203
__user_main_assert_fail_201:
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
  jmp __user_main_assert_pass_201
__user_main_assert_pass_203:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  call test_formatting
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
  leaq str_hdr_204(%rip), %rax
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
  jne __user_main_assert_pass_205
  jmp __user_main_assert_fail_205
__user_main_assert_fail_203:
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
  jmp __user_main_assert_pass_203
__user_main_assert_pass_205:
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_206(%rip), %rax
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
  jne __user_main_pr_nil_0_1421
  jmp __user_main_pr_str_0_1421
__user_main_assert_fail_205:
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
  jmp __user_main_assert_pass_205
__user_main_pr_nil_0_1421:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -776(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -776(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -784(%rbp)
  jmp __user_main_pr_next_0_1421
__user_main_pr_str_0_1421:
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
  jmp __user_main_pr_next_0_1421
__user_main_pr_next_0_1421:
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

.globl lm_error_new
lm_error_new:
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
lm_error_new_entry:
  movq -48(%rbp), %rax
  jmp lm_error_new_epilogue
lm_error_new_epilogue:
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
.Lfunc_end_lm_error_new:

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

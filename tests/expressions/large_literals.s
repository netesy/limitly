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
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 76
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 108
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
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 108
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 108
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
  .byte 58
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
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
  .byte 120
  .byte 32
  .byte 73
  .byte 54
  .byte 52
  .byte 58
  .byte 0
.align 8
str_space:
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
str_hdr_3:
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
  .byte 120
  .byte 32
  .byte 85
  .byte 54
  .byte 52
  .byte 58
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
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 70
  .byte 108
  .byte 111
  .byte 97
  .byte 116
  .byte 58
  .byte 0
.align 8
float_const_5:
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
  .byte 55
  .byte 57
  .byte 55
  .byte 54
  .byte 57
  .byte 101
  .byte 43
  .byte 51
  .byte 48
  .byte 56
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
  .byte 77
  .byte 97
  .byte 120
  .byte 32
  .byte 105
  .byte 54
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
  .byte 57
  .byte 50
  .byte 50
  .byte 51
  .byte 51
  .byte 55
  .byte 50
  .byte 48
  .byte 51
  .byte 54
  .byte 56
  .byte 53
  .byte 52
  .byte 55
  .byte 55
  .byte 53
  .byte 56
  .byte 48
  .byte 55
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
  .byte 77
  .byte 97
  .byte 120
  .byte 32
  .byte 117
  .byte 54
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
  .byte 49
  .byte 56
  .byte 52
  .byte 52
  .byte 54
  .byte 55
  .byte 52
  .byte 52
  .byte 48
  .byte 55
  .byte 51
  .byte 55
  .byte 48
  .byte 57
  .byte 53
  .byte 53
  .byte 49
  .byte 54
  .byte 49
  .byte 53
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
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 102
  .byte 108
  .byte 111
  .byte 97
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
  .byte 49
  .byte 46
  .byte 55
  .byte 57
  .byte 55
  .byte 54
  .byte 57
  .byte 51
  .byte 49
  .byte 51
  .byte 52
  .byte 56
  .byte 54
  .byte 50
  .byte 51
  .byte 49
  .byte 53
  .byte 55
  .byte 101
  .byte 43
  .byte 51
  .byte 48
  .byte 56
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
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 83
  .byte 109
  .byte 97
  .byte 108
  .byte 108
  .byte 32
  .byte 108
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 108
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
  .byte 58
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
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
  .byte 109
  .byte 97
  .byte 108
  .byte 108
  .byte 32
  .byte 70
  .byte 108
  .byte 111
  .byte 97
  .byte 116
  .byte 58
  .byte 0
.align 8
float_const_14:
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
  .byte 50
  .byte 46
  .byte 50
  .byte 50
  .byte 53
  .byte 48
  .byte 55
  .byte 101
  .byte 45
  .byte 51
  .byte 48
  .byte 56
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
  .byte 84
  .byte 105
  .byte 110
  .byte 121
  .byte 32
  .byte 70
  .byte 108
  .byte 111
  .byte 97
  .byte 116
  .byte 58
  .byte 0
.align 8
float_const_16:
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
  .byte 49
  .byte 101
  .byte 45
  .byte 49
  .byte 48
  .byte 48
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
  .byte 83
  .byte 109
  .byte 97
  .byte 108
  .byte 108
  .byte 32
  .byte 102
  .byte 108
  .byte 111
  .byte 97
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
  .byte 50
  .byte 46
  .byte 50
  .byte 50
  .byte 53
  .byte 48
  .byte 55
  .byte 51
  .byte 56
  .byte 53
  .byte 56
  .byte 53
  .byte 48
  .byte 55
  .byte 50
  .byte 48
  .byte 49
  .byte 52
  .byte 101
  .byte 45
  .byte 51
  .byte 48
  .byte 56
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
  .byte 84
  .byte 105
  .byte 110
  .byte 121
  .byte 32
  .byte 102
  .byte 108
  .byte 111
  .byte 97
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
  .byte 49
  .byte 101
  .byte 45
  .byte 49
  .byte 48
  .byte 48
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
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 78
  .byte 101
  .byte 103
  .byte 97
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 108
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 108
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
  .byte 58
  .byte 32
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
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
  .byte 101
  .byte 103
  .byte 97
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 73
  .byte 54
  .byte 52
  .byte 58
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
  .byte 78
  .byte 101
  .byte 103
  .byte 97
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 70
  .byte 108
  .byte 111
  .byte 97
  .byte 116
  .byte 58
  .byte 0
.align 8
float_const_24:
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
  .byte 45
  .byte 49
  .byte 46
  .byte 55
  .byte 57
  .byte 55
  .byte 54
  .byte 57
  .byte 101
  .byte 43
  .byte 51
  .byte 48
  .byte 56
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
  .byte 80
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 103
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
str_hdr_27:
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
  .byte 78
  .byte 101
  .byte 103
  .byte 97
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 103
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
  .byte 45
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
str_hdr_29:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 55
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 55
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 78
  .byte 101
  .byte 103
  .byte 97
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 102
  .byte 108
  .byte 111
  .byte 97
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
  .byte 45
  .byte 49
  .byte 46
  .byte 55
  .byte 57
  .byte 55
  .byte 54
  .byte 57
  .byte 51
  .byte 49
  .byte 51
  .byte 52
  .byte 56
  .byte 54
  .byte 50
  .byte 51
  .byte 49
  .byte 53
  .byte 55
  .byte 101
  .byte 43
  .byte 51
  .byte 48
  .byte 56
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
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 65
  .byte 114
  .byte 105
  .byte 116
  .byte 104
  .byte 109
  .byte 101
  .byte 116
  .byte 105
  .byte 99
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 108
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 108
  .byte 115
  .byte 58
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
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
  .byte 83
  .byte 117
  .byte 109
  .byte 32
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 58
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
  .byte 68
  .byte 105
  .byte 102
  .byte 102
  .byte 32
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 58
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
  .byte 80
  .byte 114
  .byte 111
  .byte 100
  .byte 117
  .byte 99
  .byte 116
  .byte 32
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 58
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
  .byte 83
  .byte 117
  .byte 109
  .byte 32
  .byte 111
  .byte 102
  .byte 32
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 103
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
  .byte 119
  .byte 111
  .byte 114
  .byte 107
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
  .byte 80
  .byte 114
  .byte 111
  .byte 100
  .byte 117
  .byte 99
  .byte 116
  .byte 32
  .byte 111
  .byte 102
  .byte 32
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 103
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
  .byte 119
  .byte 111
  .byte 114
  .byte 107
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
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
  .byte 45
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
  .byte 115
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 108
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 108
  .byte 115
  .byte 58
  .byte 45
  .byte 45
  .byte 45
  .byte 45
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
  .byte 97
  .byte 120
  .byte 73
  .byte 54
  .byte 52
  .byte 32
  .byte 62
  .byte 32
  .byte 112
  .byte 111
  .byte 115
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 58
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
str_hdr_41:
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
  .byte 110
  .byte 101
  .byte 103
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 60
  .byte 32
  .byte 112
  .byte 111
  .byte 115
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 58
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
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 70
  .byte 108
  .byte 111
  .byte 97
  .byte 116
  .byte 32
  .byte 62
  .byte 32
  .byte 48
  .byte 46
  .byte 48
  .byte 58
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
  .byte 109
  .byte 97
  .byte 120
  .byte 73
  .byte 54
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
  .byte 103
  .byte 114
  .byte 101
  .byte 97
  .byte 116
  .byte 101
  .byte 114
  .byte 32
  .byte 116
  .byte 104
  .byte 97
  .byte 110
  .byte 32
  .byte 112
  .byte 111
  .byte 115
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
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
  .byte 110
  .byte 101
  .byte 103
  .byte 76
  .byte 97
  .byte 114
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
  .byte 108
  .byte 101
  .byte 115
  .byte 115
  .byte 32
  .byte 116
  .byte 104
  .byte 97
  .byte 110
  .byte 32
  .byte 112
  .byte 111
  .byte 115
  .byte 76
  .byte 97
  .byte 114
  .byte 103
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
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 70
  .byte 108
  .byte 111
  .byte 97
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
  .byte 103
  .byte 114
  .byte 101
  .byte 97
  .byte 116
  .byte 101
  .byte 114
  .byte 32
  .byte 116
  .byte 104
  .byte 97
  .byte 110
  .byte 32
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
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 76
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 108
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
  subq $5944, %rsp
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
  jmp main_block_0
main_block_0:
  leaq str_hdr_0(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1120(%rbp)
  movq -1120(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1128(%rbp)
  movq -1128(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9383
  jmp main_pr_str_0_9383
main_pr_nil_0_9383:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1136(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1136(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1144(%rbp)
  jmp main_pr_next_0_9383
main_pr_str_0_9383:
  movq -1120(%rbp), %rax
  addq $8, %rax
  movq %rax, -1152(%rbp)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1160(%rbp)
  movq -1120(%rbp), %rax
  addq $24, %rax
  movq %rax, -1168(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1168(%rbp), %rsi
  movq -1160(%rbp), %rdx
  syscall
  movq %rax, -1176(%rbp)
  jmp main_pr_next_0_9383
main_pr_next_0_9383:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1184(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1184(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1192(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $9218868437227405311, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_1(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1200(%rbp)
  movq -1200(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1208(%rbp)
  movq -1208(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_886
  jmp main_pr_str_0_886
main_pr_nil_0_886:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1216(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1216(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1224(%rbp)
  jmp main_pr_next_0_886
main_pr_str_0_886:
  movq -1200(%rbp), %rax
  addq $8, %rax
  movq %rax, -1232(%rbp)
  movq -1232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1240(%rbp)
  movq -1200(%rbp), %rax
  addq $24, %rax
  movq %rax, -1248(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1248(%rbp), %rsi
  movq -1240(%rbp), %rdx
  syscall
  movq %rax, -1256(%rbp)
  jmp main_pr_next_0_886
main_pr_next_0_886:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1264(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1264(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1272(%rbp)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_2(%rip), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1280(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -1280(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1296(%rbp)
  movq -1296(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2777
  jmp main_pr_str_0_2777
main_pr_nil_0_2777:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1304(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1304(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1312(%rbp)
  jmp main_pr_next_0_2777
main_pr_str_0_2777:
  movq -1280(%rbp), %rax
  addq $8, %rax
  movq %rax, -1320(%rbp)
  movq -1320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1328(%rbp)
  movq -1280(%rbp), %rax
  addq $24, %rax
  movq %rax, -1336(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1336(%rbp), %rsi
  movq -1328(%rbp), %rdx
  syscall
  movq %rax, -1344(%rbp)
  jmp main_pr_next_0_2777
main_pr_next_0_2777:
  leaq str_space(%rip), %rax
  addq $24, %rax
  movq %rax, -1352(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1352(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1360(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -1368(%rbp)
  movq $11, %rax
  movq -1368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1368(%rbp), %rax
  addq $63, %rax
  movq %rax, -1376(%rbp)
  movq $0, %rax
  movq -1376(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1384(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1376(%rbp), %rax
  movq -1384(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1392(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1400(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1288(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1408(%rbp)
  movq -1408(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_1
  jmp main_i2s_pos_1
main_i2s_neg_1:
  movq $1, %rax
  movq -1400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1288(%rbp), %rax
  negq %rax
  movq %rax, -1416(%rbp)
  movq -1416(%rbp), %rax
  movq -1392(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_1
main_i2s_pos_1:
  movq $0, %rax
  movq -1400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1288(%rbp), %rax
  movq -1392(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_1
main_i2s_loop_1:
  movq -1392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1424(%rbp)
  movq -1424(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -1432(%rbp)
  movq -1424(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -1440(%rbp)
  movq -1440(%rbp), %rax
  movq -1392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1432(%rbp), %rax
  addq $48, %rax
  movq %rax, -1448(%rbp)
  movq -1384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1456(%rbp)
  movq -1456(%rbp), %rax
  subq $1, %rax
  movq %rax, -1464(%rbp)
  movq -1448(%rbp), %rax
  movq -1464(%rbp), %rdx
  movb %al, (%rdx)
  movq -1464(%rbp), %rax
  movq -1384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1440(%rbp), %rax
  cmpq $1, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -1472(%rbp)
  movq -1472(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_1
  jmp main_i2s_sign_1
main_i2s_sign_1:
  movq -1400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1480(%rbp)
  movq -1480(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1488(%rbp)
  movq -1488(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_1
  jmp main_i2s_done_1
main_i2s_minus_1:
  movq -1384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1496(%rbp)
  movq -1496(%rbp), %rax
  subq $1, %rax
  movq %rax, -1504(%rbp)
  movq $45, %rax
  movq -1504(%rbp), %rdx
  movb %al, (%rdx)
  movq -1504(%rbp), %rax
  movq -1384(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_1
main_i2s_done_1:
  movq -1384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1512(%rbp)
  movq -1376(%rbp), %rax
  subq -1512(%rbp), %rax
  movq %rax, -1520(%rbp)
  movq -1368(%rbp), %rax
  addq $8, %rax
  movq %rax, -1528(%rbp)
  movq -1520(%rbp), %rax
  movq -1528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1368(%rbp), %rax
  addq $16, %rax
  movq %rax, -1536(%rbp)
  movq -1520(%rbp), %rax
  movq -1536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1368(%rbp), %rax
  addq $24, %rax
  movq %rax, -1544(%rbp)
  movq -1520(%rbp), %rax
  addq $1, %rax
  movq %rax, -1552(%rbp)
  movq $184614912, %rax
  movq %rax, -1560(%rbp)
  movq -1368(%rbp), %rax
  addq $8, %rax
  movq %rax, -1568(%rbp)
  movq -1568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1576(%rbp)
  movq -1368(%rbp), %rax
  addq $24, %rax
  movq %rax, -1584(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1584(%rbp), %rsi
  movq -1576(%rbp), %rdx
  syscall
  movq %rax, -1592(%rbp)
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1600(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1600(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1608(%rbp)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_3(%rip), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1616(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1624(%rbp)
  movq -1616(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1632(%rbp)
  movq -1632(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6915
  jmp main_pr_str_0_6915
main_pr_nil_0_6915:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1640(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1640(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1648(%rbp)
  jmp main_pr_next_0_6915
main_pr_str_0_6915:
  movq -1616(%rbp), %rax
  addq $8, %rax
  movq %rax, -1656(%rbp)
  movq -1656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1664(%rbp)
  movq -1616(%rbp), %rax
  addq $24, %rax
  movq %rax, -1672(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1672(%rbp), %rsi
  movq -1664(%rbp), %rdx
  syscall
  movq %rax, -1680(%rbp)
  jmp main_pr_next_0_6915
main_pr_next_0_6915:
  leaq str_space(%rip), %rax
  addq $24, %rax
  movq %rax, -1688(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1688(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1696(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -1704(%rbp)
  movq $11, %rax
  movq -1704(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1704(%rbp), %rax
  addq $63, %rax
  movq %rax, -1712(%rbp)
  movq $0, %rax
  movq -1712(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1720(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1712(%rbp), %rax
  movq -1720(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1728(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1736(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1624(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1744(%rbp)
  movq -1744(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_2
  jmp main_i2s_pos_2
main_i2s_neg_2:
  movq $1, %rax
  movq -1736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1624(%rbp), %rax
  negq %rax
  movq %rax, -1752(%rbp)
  movq -1752(%rbp), %rax
  movq -1728(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_2
main_i2s_pos_2:
  movq $0, %rax
  movq -1736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1624(%rbp), %rax
  movq -1728(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_2
main_i2s_loop_2:
  movq -1728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1760(%rbp)
  movq -1760(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -1768(%rbp)
  movq -1760(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -1776(%rbp)
  movq -1776(%rbp), %rax
  movq -1728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1768(%rbp), %rax
  addq $48, %rax
  movq %rax, -1784(%rbp)
  movq -1720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1792(%rbp)
  movq -1792(%rbp), %rax
  subq $1, %rax
  movq %rax, -1800(%rbp)
  movq -1784(%rbp), %rax
  movq -1800(%rbp), %rdx
  movb %al, (%rdx)
  movq -1800(%rbp), %rax
  movq -1720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1776(%rbp), %rax
  cmpq $1, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -1808(%rbp)
  movq -1808(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_2
  jmp main_i2s_sign_2
main_i2s_sign_2:
  movq -1736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1816(%rbp)
  movq -1816(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1824(%rbp)
  movq -1824(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_2
  jmp main_i2s_done_2
main_i2s_minus_2:
  movq -1720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1832(%rbp)
  movq -1832(%rbp), %rax
  subq $1, %rax
  movq %rax, -1840(%rbp)
  movq $45, %rax
  movq -1840(%rbp), %rdx
  movb %al, (%rdx)
  movq -1840(%rbp), %rax
  movq -1720(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_2
main_i2s_done_2:
  movq -1720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1848(%rbp)
  movq -1712(%rbp), %rax
  subq -1848(%rbp), %rax
  movq %rax, -1856(%rbp)
  movq -1704(%rbp), %rax
  addq $8, %rax
  movq %rax, -1864(%rbp)
  movq -1856(%rbp), %rax
  movq -1864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1704(%rbp), %rax
  addq $16, %rax
  movq %rax, -1872(%rbp)
  movq -1856(%rbp), %rax
  movq -1872(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1704(%rbp), %rax
  addq $24, %rax
  movq %rax, -1880(%rbp)
  movq -1856(%rbp), %rax
  addq $1, %rax
  movq %rax, -1888(%rbp)
  movq $184614912, %rax
  movq %rax, -1896(%rbp)
  movq -1704(%rbp), %rax
  addq $8, %rax
  movq %rax, -1904(%rbp)
  movq -1904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1912(%rbp)
  movq -1704(%rbp), %rax
  addq $24, %rax
  movq %rax, -1920(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1920(%rbp), %rsi
  movq -1912(%rbp), %rdx
  syscall
  movq %rax, -1928(%rbp)
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1936(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1936(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1944(%rbp)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_4(%rip), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1952(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1960(%rbp)
  movq -1952(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1968(%rbp)
  movq -1968(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7793
  jmp main_pr_str_0_7793
main_pr_nil_0_7793:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1976(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1976(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1984(%rbp)
  jmp main_pr_next_0_7793
main_pr_str_0_7793:
  movq -1952(%rbp), %rax
  addq $8, %rax
  movq %rax, -1992(%rbp)
  movq -1992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2000(%rbp)
  movq -1952(%rbp), %rax
  addq $24, %rax
  movq %rax, -2008(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2008(%rbp), %rsi
  movq -2000(%rbp), %rdx
  syscall
  movq %rax, -2016(%rbp)
  jmp main_pr_next_0_7793
main_pr_next_0_7793:
  leaq str_space(%rip), %rax
  addq $24, %rax
  movq %rax, -2024(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2024(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2032(%rbp)
  leaq float_const_5(%rip), %rax
  addq $8, %rax
  movq %rax, -2040(%rbp)
  movq -2040(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -2048(%rbp)
  leaq float_const_5(%rip), %rax
  addq $24, %rax
  movq %rax, -2056(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2056(%rbp), %rsi
  movq -2048(%rbp), %rdx
  syscall
  movq %rax, -2064(%rbp)
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2072(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2072(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2080(%rbp)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2088(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2096(%rbp)
  movq -2096(%rbp), %rax
  cmpq -2088(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2104(%rbp)
  movq -2104(%rbp), %rax
  movq -160(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_6(%rip), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2112(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2120(%rbp)
  movq -2112(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_7
  jmp main_assert_fail_7
main_assert_pass_7:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2128(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2136(%rbp)
  movq -2136(%rbp), %rax
  cmpq -2128(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2144(%rbp)
  movq -2144(%rbp), %rax
  movq -192(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_8(%rip), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2152(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2160(%rbp)
  movq -2152(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_9
  jmp main_assert_fail_9
main_assert_fail_7:
  movq -2120(%rbp), %rax
  addq $8, %rax
  movq %rax, -2168(%rbp)
  movq -2168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2176(%rbp)
  movq -2120(%rbp), %rax
  addq $24, %rax
  movq %rax, -2184(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2184(%rbp), %rsi
  movq -2176(%rbp), %rdx
  syscall
  movq %rax, -2192(%rbp)
  movq $50397203, %rax
  movq %rax, -2200(%rbp)
  jmp main_assert_pass_7
main_assert_pass_9:
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq $9218868437227405311, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2208(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2216(%rbp)
  movq -2216(%rbp), %rax
  cmpq -2208(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2224(%rbp)
  movq -2224(%rbp), %rax
  movq -232(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_10(%rip), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2232(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2240(%rbp)
  movq -2232(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_11
  jmp main_assert_fail_11
main_assert_fail_9:
  movq -2160(%rbp), %rax
  addq $8, %rax
  movq %rax, -2248(%rbp)
  movq -2248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2256(%rbp)
  movq -2160(%rbp), %rax
  addq $24, %rax
  movq %rax, -2264(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2264(%rbp), %rsi
  movq -2256(%rbp), %rdx
  syscall
  movq %rax, -2272(%rbp)
  movq $50397203, %rax
  movq %rax, -2280(%rbp)
  jmp main_assert_pass_9
main_assert_pass_11:
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4503599627370496, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3110860544497550640, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_12(%rip), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2288(%rbp)
  movq -2288(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2296(%rbp)
  movq -2296(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8335
  jmp main_pr_str_0_8335
main_assert_fail_11:
  movq -2240(%rbp), %rax
  addq $8, %rax
  movq %rax, -2304(%rbp)
  movq -2304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2312(%rbp)
  movq -2240(%rbp), %rax
  addq $24, %rax
  movq %rax, -2320(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2320(%rbp), %rsi
  movq -2312(%rbp), %rdx
  syscall
  movq %rax, -2328(%rbp)
  movq $50397203, %rax
  movq %rax, -2336(%rbp)
  jmp main_assert_pass_11
main_pr_nil_0_8335:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2344(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2352(%rbp)
  jmp main_pr_next_0_8335
main_pr_str_0_8335:
  movq -2288(%rbp), %rax
  addq $8, %rax
  movq %rax, -2360(%rbp)
  movq -2360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2368(%rbp)
  movq -2288(%rbp), %rax
  addq $24, %rax
  movq %rax, -2376(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2376(%rbp), %rsi
  movq -2368(%rbp), %rdx
  syscall
  movq %rax, -2384(%rbp)
  jmp main_pr_next_0_8335
main_pr_next_0_8335:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2392(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2392(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2400(%rbp)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_13(%rip), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2408(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2416(%rbp)
  movq -2408(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2424(%rbp)
  movq -2424(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5386
  jmp main_pr_str_0_5386
main_pr_nil_0_5386:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2432(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2432(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2440(%rbp)
  jmp main_pr_next_0_5386
main_pr_str_0_5386:
  movq -2408(%rbp), %rax
  addq $8, %rax
  movq %rax, -2448(%rbp)
  movq -2448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2456(%rbp)
  movq -2408(%rbp), %rax
  addq $24, %rax
  movq %rax, -2464(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2464(%rbp), %rsi
  movq -2456(%rbp), %rdx
  syscall
  movq %rax, -2472(%rbp)
  jmp main_pr_next_0_5386
main_pr_next_0_5386:
  leaq str_space(%rip), %rax
  addq $24, %rax
  movq %rax, -2480(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2480(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2488(%rbp)
  leaq float_const_14(%rip), %rax
  addq $8, %rax
  movq %rax, -2496(%rbp)
  movq -2496(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -2504(%rbp)
  leaq float_const_14(%rip), %rax
  addq $24, %rax
  movq %rax, -2512(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2512(%rbp), %rsi
  movq -2504(%rbp), %rdx
  syscall
  movq %rax, -2520(%rbp)
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2528(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2528(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2536(%rbp)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_15(%rip), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2544(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2552(%rbp)
  movq -2544(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2560(%rbp)
  movq -2560(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_492
  jmp main_pr_str_0_492
main_pr_nil_0_492:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2568(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2568(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2576(%rbp)
  jmp main_pr_next_0_492
main_pr_str_0_492:
  movq -2544(%rbp), %rax
  addq $8, %rax
  movq %rax, -2584(%rbp)
  movq -2584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2592(%rbp)
  movq -2544(%rbp), %rax
  addq $24, %rax
  movq %rax, -2600(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2600(%rbp), %rsi
  movq -2592(%rbp), %rdx
  syscall
  movq %rax, -2608(%rbp)
  jmp main_pr_next_0_492
main_pr_next_0_492:
  leaq str_space(%rip), %rax
  addq $24, %rax
  movq %rax, -2616(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2616(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2624(%rbp)
  leaq float_const_16(%rip), %rax
  addq $8, %rax
  movq %rax, -2632(%rbp)
  movq -2632(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -2640(%rbp)
  leaq float_const_16(%rip), %rax
  addq $24, %rax
  movq %rax, -2648(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2648(%rbp), %rsi
  movq -2640(%rbp), %rdx
  syscall
  movq %rax, -2656(%rbp)
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2664(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2664(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2672(%rbp)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4503599627370496, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2680(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2688(%rbp)
  movq -2688(%rbp), %rax
  cmpq -2680(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2696(%rbp)
  movq -2696(%rbp), %rax
  movq -328(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_17(%rip), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2704(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2712(%rbp)
  movq -2704(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_18
  jmp main_assert_fail_18
main_assert_pass_18:
  movq $0, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3110860544497550640, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2720(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2728(%rbp)
  movq -2728(%rbp), %rax
  cmpq -2720(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2736(%rbp)
  movq -2736(%rbp), %rax
  movq -360(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_19(%rip), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2744(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2752(%rbp)
  movq -2744(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_20
  jmp main_assert_fail_20
main_assert_fail_18:
  movq -2712(%rbp), %rax
  addq $8, %rax
  movq %rax, -2760(%rbp)
  movq -2760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2768(%rbp)
  movq -2712(%rbp), %rax
  addq $24, %rax
  movq %rax, -2776(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2776(%rbp), %rsi
  movq -2768(%rbp), %rdx
  syscall
  movq %rax, -2784(%rbp)
  movq $50397203, %rax
  movq %rax, -2792(%rbp)
  jmp main_assert_pass_18
main_assert_pass_20:
  movq $0, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq $123456789, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq $123456789, %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2800(%rbp)
  movq -2800(%rbp), %rax
  negq %rax
  movq %rax, -2808(%rbp)
  movq -2808(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2816(%rbp)
  movq -2816(%rbp), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq $9218868437227405311, %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2824(%rbp)
  movq -2824(%rbp), %rax
  negq %rax
  movq %rax, -2832(%rbp)
  movq -2832(%rbp), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2840(%rbp)
  movq -2840(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_21(%rip), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2848(%rbp)
  movq -2848(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2856(%rbp)
  movq -2856(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6649
  jmp main_pr_str_0_6649
main_assert_fail_20:
  movq -2752(%rbp), %rax
  addq $8, %rax
  movq %rax, -2864(%rbp)
  movq -2864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2872(%rbp)
  movq -2752(%rbp), %rax
  addq $24, %rax
  movq %rax, -2880(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2880(%rbp), %rsi
  movq -2872(%rbp), %rdx
  syscall
  movq %rax, -2888(%rbp)
  movq $50397203, %rax
  movq %rax, -2896(%rbp)
  jmp main_assert_pass_20
main_pr_nil_0_6649:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2904(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2912(%rbp)
  jmp main_pr_next_0_6649
main_pr_str_0_6649:
  movq -2848(%rbp), %rax
  addq $8, %rax
  movq %rax, -2920(%rbp)
  movq -2920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2928(%rbp)
  movq -2848(%rbp), %rax
  addq $24, %rax
  movq %rax, -2936(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2936(%rbp), %rsi
  movq -2928(%rbp), %rdx
  syscall
  movq %rax, -2944(%rbp)
  jmp main_pr_next_0_6649
main_pr_next_0_6649:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2952(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2952(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2960(%rbp)
  movq $0, %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_22(%rip), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2968(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2976(%rbp)
  movq -2968(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2984(%rbp)
  movq -2984(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1421
  jmp main_pr_str_0_1421
main_pr_nil_0_1421:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2992(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2992(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3000(%rbp)
  jmp main_pr_next_0_1421
main_pr_str_0_1421:
  movq -2968(%rbp), %rax
  addq $8, %rax
  movq %rax, -3008(%rbp)
  movq -3008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3016(%rbp)
  movq -2968(%rbp), %rax
  addq $24, %rax
  movq %rax, -3024(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3024(%rbp), %rsi
  movq -3016(%rbp), %rdx
  syscall
  movq %rax, -3032(%rbp)
  jmp main_pr_next_0_1421
main_pr_next_0_1421:
  leaq str_space(%rip), %rax
  addq $24, %rax
  movq %rax, -3040(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3040(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3048(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -3056(%rbp)
  movq $11, %rax
  movq -3056(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3056(%rbp), %rax
  addq $63, %rax
  movq %rax, -3064(%rbp)
  movq $0, %rax
  movq -3064(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3072(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -3064(%rbp), %rax
  movq -3072(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3080(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3088(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -2976(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -3096(%rbp)
  movq -3096(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_3
  jmp main_i2s_pos_3
main_i2s_neg_3:
  movq $1, %rax
  movq -3088(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2976(%rbp), %rax
  negq %rax
  movq %rax, -3104(%rbp)
  movq -3104(%rbp), %rax
  movq -3080(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_3
main_i2s_pos_3:
  movq $0, %rax
  movq -3088(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2976(%rbp), %rax
  movq -3080(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_3
main_i2s_loop_3:
  movq -3080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3112(%rbp)
  movq -3112(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -3120(%rbp)
  movq -3112(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -3128(%rbp)
  movq -3128(%rbp), %rax
  movq -3080(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3120(%rbp), %rax
  addq $48, %rax
  movq %rax, -3136(%rbp)
  movq -3072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3144(%rbp)
  movq -3144(%rbp), %rax
  subq $1, %rax
  movq %rax, -3152(%rbp)
  movq -3136(%rbp), %rax
  movq -3152(%rbp), %rdx
  movb %al, (%rdx)
  movq -3152(%rbp), %rax
  movq -3072(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3128(%rbp), %rax
  cmpq $1, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -3160(%rbp)
  movq -3160(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_3
  jmp main_i2s_sign_3
main_i2s_sign_3:
  movq -3088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3168(%rbp)
  movq -3168(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3176(%rbp)
  movq -3176(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_3
  jmp main_i2s_done_3
main_i2s_minus_3:
  movq -3072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3184(%rbp)
  movq -3184(%rbp), %rax
  subq $1, %rax
  movq %rax, -3192(%rbp)
  movq $45, %rax
  movq -3192(%rbp), %rdx
  movb %al, (%rdx)
  movq -3192(%rbp), %rax
  movq -3072(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_3
main_i2s_done_3:
  movq -3072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3200(%rbp)
  movq -3064(%rbp), %rax
  subq -3200(%rbp), %rax
  movq %rax, -3208(%rbp)
  movq -3056(%rbp), %rax
  addq $8, %rax
  movq %rax, -3216(%rbp)
  movq -3208(%rbp), %rax
  movq -3216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3056(%rbp), %rax
  addq $16, %rax
  movq %rax, -3224(%rbp)
  movq -3208(%rbp), %rax
  movq -3224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3056(%rbp), %rax
  addq $24, %rax
  movq %rax, -3232(%rbp)
  movq -3208(%rbp), %rax
  addq $1, %rax
  movq %rax, -3240(%rbp)
  movq $184614912, %rax
  movq %rax, -3248(%rbp)
  movq -3056(%rbp), %rax
  addq $8, %rax
  movq %rax, -3256(%rbp)
  movq -3256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3264(%rbp)
  movq -3056(%rbp), %rax
  addq $24, %rax
  movq %rax, -3272(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3272(%rbp), %rsi
  movq -3264(%rbp), %rdx
  syscall
  movq %rax, -3280(%rbp)
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3288(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3288(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3296(%rbp)
  movq $0, %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_23(%rip), %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3304(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3312(%rbp)
  movq -3304(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3320(%rbp)
  movq -3320(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2362
  jmp main_pr_str_0_2362
main_pr_nil_0_2362:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3328(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3328(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3336(%rbp)
  jmp main_pr_next_0_2362
main_pr_str_0_2362:
  movq -3304(%rbp), %rax
  addq $8, %rax
  movq %rax, -3344(%rbp)
  movq -3344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3352(%rbp)
  movq -3304(%rbp), %rax
  addq $24, %rax
  movq %rax, -3360(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3360(%rbp), %rsi
  movq -3352(%rbp), %rdx
  syscall
  movq %rax, -3368(%rbp)
  jmp main_pr_next_0_2362
main_pr_next_0_2362:
  leaq str_space(%rip), %rax
  addq $24, %rax
  movq %rax, -3376(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3376(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3384(%rbp)
  leaq float_const_24(%rip), %rax
  addq $8, %rax
  movq %rax, -3392(%rbp)
  movq -3392(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -3400(%rbp)
  leaq float_const_24(%rip), %rax
  addq $24, %rax
  movq %rax, -3408(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3408(%rbp), %rsi
  movq -3400(%rbp), %rdx
  syscall
  movq %rax, -3416(%rbp)
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3424(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3424(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3432(%rbp)
  movq $0, %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq $123456789, %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3440(%rbp)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3448(%rbp)
  movq -3448(%rbp), %rax
  cmpq -3440(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3456(%rbp)
  movq -3456(%rbp), %rax
  movq -496(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_25(%rip), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3464(%rbp)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3472(%rbp)
  movq -3464(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_26
  jmp main_assert_fail_26
main_assert_pass_26:
  movq $0, %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq $123456789, %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3480(%rbp)
  movq -3480(%rbp), %rax
  negq %rax
  movq %rax, -3488(%rbp)
  movq -3488(%rbp), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3496(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3504(%rbp)
  movq -3504(%rbp), %rax
  cmpq -3496(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3512(%rbp)
  movq -3512(%rbp), %rax
  movq -536(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_27(%rip), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3520(%rbp)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3528(%rbp)
  movq -3520(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_28
  jmp main_assert_fail_28
main_assert_fail_26:
  movq -3472(%rbp), %rax
  addq $8, %rax
  movq %rax, -3536(%rbp)
  movq -3536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3544(%rbp)
  movq -3472(%rbp), %rax
  addq $24, %rax
  movq %rax, -3552(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3552(%rbp), %rsi
  movq -3544(%rbp), %rdx
  syscall
  movq %rax, -3560(%rbp)
  movq $50397203, %rax
  movq %rax, -3568(%rbp)
  jmp main_assert_pass_26
main_assert_pass_28:
  movq $0, %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq $9218868437227405311, %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3576(%rbp)
  movq -3576(%rbp), %rax
  negq %rax
  movq %rax, -3584(%rbp)
  movq -3584(%rbp), %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3592(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3600(%rbp)
  movq -3600(%rbp), %rax
  cmpq -3592(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3608(%rbp)
  movq -3608(%rbp), %rax
  movq -576(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_29(%rip), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3616(%rbp)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3624(%rbp)
  movq -3616(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_30
  jmp main_assert_fail_30
main_assert_fail_28:
  movq -3528(%rbp), %rax
  addq $8, %rax
  movq %rax, -3632(%rbp)
  movq -3632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3640(%rbp)
  movq -3528(%rbp), %rax
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
  jmp main_assert_pass_28
main_assert_pass_30:
  movq $0, %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq $876543211, %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  movq $876543211, %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3672(%rbp)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3680(%rbp)
  movq -3680(%rbp), %rax
  addq -3672(%rbp), %rax
  movq %rax, -3688(%rbp)
  movq -3688(%rbp), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3696(%rbp)
  movq -3696(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3704(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3712(%rbp)
  movq -3712(%rbp), %rax
  subq -3704(%rbp), %rax
  movq %rax, -3720(%rbp)
  movq -3720(%rbp), %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3728(%rbp)
  movq -3728(%rbp), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1000, %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3736(%rbp)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3744(%rbp)
  movq -3744(%rbp), %rax
  imulq -3736(%rbp), %rax
  movq %rax, -3752(%rbp)
  movq -3752(%rbp), %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3760(%rbp)
  movq -3760(%rbp), %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_31(%rip), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3768(%rbp)
  movq -3768(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3776(%rbp)
  movq -3776(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_27
  jmp main_pr_str_0_27
main_assert_fail_30:
  movq -3624(%rbp), %rax
  addq $8, %rax
  movq %rax, -3784(%rbp)
  movq -3784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3792(%rbp)
  movq -3624(%rbp), %rax
  addq $24, %rax
  movq %rax, -3800(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3800(%rbp), %rsi
  movq -3792(%rbp), %rdx
  syscall
  movq %rax, -3808(%rbp)
  movq $50397203, %rax
  movq %rax, -3816(%rbp)
  jmp main_assert_pass_30
main_pr_nil_0_27:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3824(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3824(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3832(%rbp)
  jmp main_pr_next_0_27
main_pr_str_0_27:
  movq -3768(%rbp), %rax
  addq $8, %rax
  movq %rax, -3840(%rbp)
  movq -3840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3848(%rbp)
  movq -3768(%rbp), %rax
  addq $24, %rax
  movq %rax, -3856(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3856(%rbp), %rsi
  movq -3848(%rbp), %rdx
  syscall
  movq %rax, -3864(%rbp)
  jmp main_pr_next_0_27
main_pr_next_0_27:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3872(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3872(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3880(%rbp)
  movq $0, %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_32(%rip), %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3888(%rbp)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3896(%rbp)
  movq -3888(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3904(%rbp)
  movq -3904(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8690
  jmp main_pr_str_0_8690
main_pr_nil_0_8690:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3912(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3912(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3920(%rbp)
  jmp main_pr_next_0_8690
main_pr_str_0_8690:
  movq -3888(%rbp), %rax
  addq $8, %rax
  movq %rax, -3928(%rbp)
  movq -3928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3936(%rbp)
  movq -3888(%rbp), %rax
  addq $24, %rax
  movq %rax, -3944(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3944(%rbp), %rsi
  movq -3936(%rbp), %rdx
  syscall
  movq %rax, -3952(%rbp)
  jmp main_pr_next_0_8690
main_pr_next_0_8690:
  leaq str_space(%rip), %rax
  addq $24, %rax
  movq %rax, -3960(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3960(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3968(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -3976(%rbp)
  movq $11, %rax
  movq -3976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3976(%rbp), %rax
  addq $63, %rax
  movq %rax, -3984(%rbp)
  movq $0, %rax
  movq -3984(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3992(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -3984(%rbp), %rax
  movq -3992(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4000(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4008(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -3896(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -4016(%rbp)
  movq -4016(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_4
  jmp main_i2s_pos_4
main_i2s_neg_4:
  movq $1, %rax
  movq -4008(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3896(%rbp), %rax
  negq %rax
  movq %rax, -4024(%rbp)
  movq -4024(%rbp), %rax
  movq -4000(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_4
main_i2s_pos_4:
  movq $0, %rax
  movq -4008(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3896(%rbp), %rax
  movq -4000(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_4
main_i2s_loop_4:
  movq -4000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4032(%rbp)
  movq -4032(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -4040(%rbp)
  movq -4032(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -4048(%rbp)
  movq -4048(%rbp), %rax
  movq -4000(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4040(%rbp), %rax
  addq $48, %rax
  movq %rax, -4056(%rbp)
  movq -3992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4064(%rbp)
  movq -4064(%rbp), %rax
  subq $1, %rax
  movq %rax, -4072(%rbp)
  movq -4056(%rbp), %rax
  movq -4072(%rbp), %rdx
  movb %al, (%rdx)
  movq -4072(%rbp), %rax
  movq -3992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4048(%rbp), %rax
  cmpq $1, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -4080(%rbp)
  movq -4080(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_4
  jmp main_i2s_sign_4
main_i2s_sign_4:
  movq -4008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4088(%rbp)
  movq -4088(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4096(%rbp)
  movq -4096(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_4
  jmp main_i2s_done_4
main_i2s_minus_4:
  movq -3992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4104(%rbp)
  movq -4104(%rbp), %rax
  subq $1, %rax
  movq %rax, -4112(%rbp)
  movq $45, %rax
  movq -4112(%rbp), %rdx
  movb %al, (%rdx)
  movq -4112(%rbp), %rax
  movq -3992(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_4
main_i2s_done_4:
  movq -3992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4120(%rbp)
  movq -3984(%rbp), %rax
  subq -4120(%rbp), %rax
  movq %rax, -4128(%rbp)
  movq -3976(%rbp), %rax
  addq $8, %rax
  movq %rax, -4136(%rbp)
  movq -4128(%rbp), %rax
  movq -4136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3976(%rbp), %rax
  addq $16, %rax
  movq %rax, -4144(%rbp)
  movq -4128(%rbp), %rax
  movq -4144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3976(%rbp), %rax
  addq $24, %rax
  movq %rax, -4152(%rbp)
  movq -4128(%rbp), %rax
  addq $1, %rax
  movq %rax, -4160(%rbp)
  movq $184614912, %rax
  movq %rax, -4168(%rbp)
  movq -3976(%rbp), %rax
  addq $8, %rax
  movq %rax, -4176(%rbp)
  movq -4176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4184(%rbp)
  movq -3976(%rbp), %rax
  addq $24, %rax
  movq %rax, -4192(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4192(%rbp), %rsi
  movq -4184(%rbp), %rdx
  syscall
  movq %rax, -4200(%rbp)
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4208(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4208(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4216(%rbp)
  movq $0, %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_33(%rip), %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4224(%rbp)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4232(%rbp)
  movq -4224(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4240(%rbp)
  movq -4240(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_59
  jmp main_pr_str_0_59
main_pr_nil_0_59:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4248(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4248(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4256(%rbp)
  jmp main_pr_next_0_59
main_pr_str_0_59:
  movq -4224(%rbp), %rax
  addq $8, %rax
  movq %rax, -4264(%rbp)
  movq -4264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4272(%rbp)
  movq -4224(%rbp), %rax
  addq $24, %rax
  movq %rax, -4280(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4280(%rbp), %rsi
  movq -4272(%rbp), %rdx
  syscall
  movq %rax, -4288(%rbp)
  jmp main_pr_next_0_59
main_pr_next_0_59:
  leaq str_space(%rip), %rax
  addq $24, %rax
  movq %rax, -4296(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4296(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4304(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -4312(%rbp)
  movq $11, %rax
  movq -4312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4312(%rbp), %rax
  addq $63, %rax
  movq %rax, -4320(%rbp)
  movq $0, %rax
  movq -4320(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4328(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -4320(%rbp), %rax
  movq -4328(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4336(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4344(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -4232(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -4352(%rbp)
  movq -4352(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_5
  jmp main_i2s_pos_5
main_i2s_neg_5:
  movq $1, %rax
  movq -4344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4232(%rbp), %rax
  negq %rax
  movq %rax, -4360(%rbp)
  movq -4360(%rbp), %rax
  movq -4336(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_5
main_i2s_pos_5:
  movq $0, %rax
  movq -4344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4232(%rbp), %rax
  movq -4336(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_5
main_i2s_loop_5:
  movq -4336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4368(%rbp)
  movq -4368(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -4376(%rbp)
  movq -4368(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -4384(%rbp)
  movq -4384(%rbp), %rax
  movq -4336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4376(%rbp), %rax
  addq $48, %rax
  movq %rax, -4392(%rbp)
  movq -4328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4400(%rbp)
  movq -4400(%rbp), %rax
  subq $1, %rax
  movq %rax, -4408(%rbp)
  movq -4392(%rbp), %rax
  movq -4408(%rbp), %rdx
  movb %al, (%rdx)
  movq -4408(%rbp), %rax
  movq -4328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4384(%rbp), %rax
  cmpq $1, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -4416(%rbp)
  movq -4416(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_5
  jmp main_i2s_sign_5
main_i2s_sign_5:
  movq -4344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4424(%rbp)
  movq -4424(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4432(%rbp)
  movq -4432(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_5
  jmp main_i2s_done_5
main_i2s_minus_5:
  movq -4328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4440(%rbp)
  movq -4440(%rbp), %rax
  subq $1, %rax
  movq %rax, -4448(%rbp)
  movq $45, %rax
  movq -4448(%rbp), %rdx
  movb %al, (%rdx)
  movq -4448(%rbp), %rax
  movq -4328(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_5
main_i2s_done_5:
  movq -4328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4456(%rbp)
  movq -4320(%rbp), %rax
  subq -4456(%rbp), %rax
  movq %rax, -4464(%rbp)
  movq -4312(%rbp), %rax
  addq $8, %rax
  movq %rax, -4472(%rbp)
  movq -4464(%rbp), %rax
  movq -4472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4312(%rbp), %rax
  addq $16, %rax
  movq %rax, -4480(%rbp)
  movq -4464(%rbp), %rax
  movq -4480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4312(%rbp), %rax
  addq $24, %rax
  movq %rax, -4488(%rbp)
  movq -4464(%rbp), %rax
  addq $1, %rax
  movq %rax, -4496(%rbp)
  movq $184614912, %rax
  movq %rax, -4504(%rbp)
  movq -4312(%rbp), %rax
  addq $8, %rax
  movq %rax, -4512(%rbp)
  movq -4512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4520(%rbp)
  movq -4312(%rbp), %rax
  addq $24, %rax
  movq %rax, -4528(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4528(%rbp), %rsi
  movq -4520(%rbp), %rdx
  syscall
  movq %rax, -4536(%rbp)
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4544(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4552(%rbp)
  movq $0, %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_34(%rip), %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4560(%rbp)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4568(%rbp)
  movq -4560(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4576(%rbp)
  movq -4576(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7763
  jmp main_pr_str_0_7763
main_pr_nil_0_7763:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4584(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4584(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4592(%rbp)
  jmp main_pr_next_0_7763
main_pr_str_0_7763:
  movq -4560(%rbp), %rax
  addq $8, %rax
  movq %rax, -4600(%rbp)
  movq -4600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4608(%rbp)
  movq -4560(%rbp), %rax
  addq $24, %rax
  movq %rax, -4616(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4616(%rbp), %rsi
  movq -4608(%rbp), %rdx
  syscall
  movq %rax, -4624(%rbp)
  jmp main_pr_next_0_7763
main_pr_next_0_7763:
  leaq str_space(%rip), %rax
  addq $24, %rax
  movq %rax, -4632(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4632(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4640(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -4648(%rbp)
  movq $11, %rax
  movq -4648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4648(%rbp), %rax
  addq $63, %rax
  movq %rax, -4656(%rbp)
  movq $0, %rax
  movq -4656(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4664(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -4656(%rbp), %rax
  movq -4664(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4672(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4680(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -4568(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -4688(%rbp)
  movq -4688(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_6
  jmp main_i2s_pos_6
main_i2s_neg_6:
  movq $1, %rax
  movq -4680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4568(%rbp), %rax
  negq %rax
  movq %rax, -4696(%rbp)
  movq -4696(%rbp), %rax
  movq -4672(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_6
main_i2s_pos_6:
  movq $0, %rax
  movq -4680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4568(%rbp), %rax
  movq -4672(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_6
main_i2s_loop_6:
  movq -4672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4704(%rbp)
  movq -4704(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -4712(%rbp)
  movq -4704(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -4720(%rbp)
  movq -4720(%rbp), %rax
  movq -4672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4712(%rbp), %rax
  addq $48, %rax
  movq %rax, -4728(%rbp)
  movq -4664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4736(%rbp)
  movq -4736(%rbp), %rax
  subq $1, %rax
  movq %rax, -4744(%rbp)
  movq -4728(%rbp), %rax
  movq -4744(%rbp), %rdx
  movb %al, (%rdx)
  movq -4744(%rbp), %rax
  movq -4664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4720(%rbp), %rax
  cmpq $1, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -4752(%rbp)
  movq -4752(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_6
  jmp main_i2s_sign_6
main_i2s_sign_6:
  movq -4680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4760(%rbp)
  movq -4760(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4768(%rbp)
  movq -4768(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_6
  jmp main_i2s_done_6
main_i2s_minus_6:
  movq -4664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4776(%rbp)
  movq -4776(%rbp), %rax
  subq $1, %rax
  movq %rax, -4784(%rbp)
  movq $45, %rax
  movq -4784(%rbp), %rdx
  movb %al, (%rdx)
  movq -4784(%rbp), %rax
  movq -4664(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_6
main_i2s_done_6:
  movq -4664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4792(%rbp)
  movq -4656(%rbp), %rax
  subq -4792(%rbp), %rax
  movq %rax, -4800(%rbp)
  movq -4648(%rbp), %rax
  addq $8, %rax
  movq %rax, -4808(%rbp)
  movq -4800(%rbp), %rax
  movq -4808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4648(%rbp), %rax
  addq $16, %rax
  movq %rax, -4816(%rbp)
  movq -4800(%rbp), %rax
  movq -4816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4648(%rbp), %rax
  addq $24, %rax
  movq %rax, -4824(%rbp)
  movq -4800(%rbp), %rax
  addq $1, %rax
  movq %rax, -4832(%rbp)
  movq $184614912, %rax
  movq %rax, -4840(%rbp)
  movq -4648(%rbp), %rax
  addq $8, %rax
  movq %rax, -4848(%rbp)
  movq -4848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4856(%rbp)
  movq -4648(%rbp), %rax
  addq $24, %rax
  movq %rax, -4864(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4864(%rbp), %rsi
  movq -4856(%rbp), %rdx
  syscall
  movq %rax, -4872(%rbp)
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4880(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4880(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4888(%rbp)
  movq $0, %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1000000000, %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4896(%rbp)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4904(%rbp)
  movq -4904(%rbp), %rax
  cmpq -4896(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4912(%rbp)
  movq -4912(%rbp), %rax
  movq -744(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_35(%rip), %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4920(%rbp)
  movq -752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4928(%rbp)
  movq -4920(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_36
  jmp main_assert_fail_36
main_assert_pass_36:
  movq $0, %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq $123456789000, %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4936(%rbp)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4944(%rbp)
  movq -4944(%rbp), %rax
  cmpq -4936(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4952(%rbp)
  movq -4952(%rbp), %rax
  movq -776(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_37(%rip), %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4960(%rbp)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4968(%rbp)
  movq -4960(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_38
  jmp main_assert_fail_38
main_assert_fail_36:
  movq -4928(%rbp), %rax
  addq $8, %rax
  movq %rax, -4976(%rbp)
  movq -4976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4984(%rbp)
  movq -4928(%rbp), %rax
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
  jmp main_assert_pass_36
main_assert_pass_38:
  movq $0, %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5016(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5024(%rbp)
  movq -5024(%rbp), %rax
  cmpq -5016(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -5032(%rbp)
  movq -5032(%rbp), %rax
  movq -800(%rbp), %rdx
  movl %eax, (%rdx)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5040(%rbp)
  movq -5040(%rbp), %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5048(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5056(%rbp)
  movq -5056(%rbp), %rax
  cmpq -5048(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -5064(%rbp)
  movq -5064(%rbp), %rax
  movq -816(%rbp), %rdx
  movl %eax, (%rdx)
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5072(%rbp)
  movq -5072(%rbp), %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5080(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5088(%rbp)
  movq -5088(%rbp), %rax
  cmpq -5080(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -5096(%rbp)
  movq -5096(%rbp), %rax
  movq -840(%rbp), %rdx
  movl %eax, (%rdx)
  movq -840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5104(%rbp)
  movq -5104(%rbp), %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_39(%rip), %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5112(%rbp)
  movq -5112(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5120(%rbp)
  movq -5120(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3926
  jmp main_pr_str_0_3926
main_assert_fail_38:
  movq -4968(%rbp), %rax
  addq $8, %rax
  movq %rax, -5128(%rbp)
  movq -5128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5136(%rbp)
  movq -4968(%rbp), %rax
  addq $24, %rax
  movq %rax, -5144(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5144(%rbp), %rsi
  movq -5136(%rbp), %rdx
  syscall
  movq %rax, -5152(%rbp)
  movq $50397203, %rax
  movq %rax, -5160(%rbp)
  jmp main_assert_pass_38
main_pr_nil_0_3926:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5168(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5168(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5176(%rbp)
  jmp main_pr_next_0_3926
main_pr_str_0_3926:
  movq -5112(%rbp), %rax
  addq $8, %rax
  movq %rax, -5184(%rbp)
  movq -5184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5192(%rbp)
  movq -5112(%rbp), %rax
  addq $24, %rax
  movq %rax, -5200(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5200(%rbp), %rsi
  movq -5192(%rbp), %rdx
  syscall
  movq %rax, -5208(%rbp)
  jmp main_pr_next_0_3926
main_pr_next_0_3926:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5216(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5216(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5224(%rbp)
  movq $0, %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_40(%rip), %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5232(%rbp)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5240(%rbp)
  movq -5232(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5248(%rbp)
  movq -5248(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_540
  jmp main_pr_str_0_540
main_pr_nil_0_540:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5256(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5256(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5264(%rbp)
  jmp main_pr_next_0_540
main_pr_str_0_540:
  movq -5232(%rbp), %rax
  addq $8, %rax
  movq %rax, -5272(%rbp)
  movq -5272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5280(%rbp)
  movq -5232(%rbp), %rax
  addq $24, %rax
  movq %rax, -5288(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5288(%rbp), %rsi
  movq -5280(%rbp), %rdx
  syscall
  movq %rax, -5296(%rbp)
  jmp main_pr_next_0_540
main_pr_next_0_540:
  leaq str_space(%rip), %rax
  addq $24, %rax
  movq %rax, -5304(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5304(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5312(%rbp)
  movq -5240(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -5320(%rbp)
  movq -5320(%rbp), %rax
  testq %rax, %rax
  jne main_pb_true_1
  jmp main_pb_false_1
main_pb_true_1:
  leaq str_true(%rip), %rax
  addq $24, %rax
  movq %rax, -5328(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5328(%rbp), %rsi
  movq $4, %rdx
  syscall
  movq %rax, -5336(%rbp)
  jmp main_pb_done_1
main_pb_false_1:
  leaq str_false(%rip), %rax
  addq $24, %rax
  movq %rax, -5344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5344(%rbp), %rsi
  movq $5, %rdx
  syscall
  movq %rax, -5352(%rbp)
  jmp main_pb_done_1
main_pb_done_1:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5360(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5360(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5368(%rbp)
  movq $0, %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_41(%rip), %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  movq -888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5376(%rbp)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5384(%rbp)
  movq -5376(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5392(%rbp)
  movq -5392(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3426
  jmp main_pr_str_0_3426
main_pr_nil_0_3426:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5400(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5400(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5408(%rbp)
  jmp main_pr_next_0_3426
main_pr_str_0_3426:
  movq -5376(%rbp), %rax
  addq $8, %rax
  movq %rax, -5416(%rbp)
  movq -5416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5424(%rbp)
  movq -5376(%rbp), %rax
  addq $24, %rax
  movq %rax, -5432(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5432(%rbp), %rsi
  movq -5424(%rbp), %rdx
  syscall
  movq %rax, -5440(%rbp)
  jmp main_pr_next_0_3426
main_pr_next_0_3426:
  leaq str_space(%rip), %rax
  addq $24, %rax
  movq %rax, -5448(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5448(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5456(%rbp)
  movq -5384(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -5464(%rbp)
  movq -5464(%rbp), %rax
  testq %rax, %rax
  jne main_pb_true_2
  jmp main_pb_false_2
main_pb_true_2:
  leaq str_true(%rip), %rax
  addq $24, %rax
  movq %rax, -5472(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5472(%rbp), %rsi
  movq $4, %rdx
  syscall
  movq %rax, -5480(%rbp)
  jmp main_pb_done_2
main_pb_false_2:
  leaq str_false(%rip), %rax
  addq $24, %rax
  movq %rax, -5488(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5488(%rbp), %rsi
  movq $5, %rdx
  syscall
  movq %rax, -5496(%rbp)
  jmp main_pb_done_2
main_pb_done_2:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5504(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5504(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5512(%rbp)
  movq $0, %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_42(%rip), %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5520(%rbp)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5528(%rbp)
  movq -5520(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5536(%rbp)
  movq -5536(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9172
  jmp main_pr_str_0_9172
main_pr_nil_0_9172:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5544(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5552(%rbp)
  jmp main_pr_next_0_9172
main_pr_str_0_9172:
  movq -5520(%rbp), %rax
  addq $8, %rax
  movq %rax, -5560(%rbp)
  movq -5560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5568(%rbp)
  movq -5520(%rbp), %rax
  addq $24, %rax
  movq %rax, -5576(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5576(%rbp), %rsi
  movq -5568(%rbp), %rdx
  syscall
  movq %rax, -5584(%rbp)
  jmp main_pr_next_0_9172
main_pr_next_0_9172:
  leaq str_space(%rip), %rax
  addq $24, %rax
  movq %rax, -5592(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5592(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5600(%rbp)
  movq -5528(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -5608(%rbp)
  movq -5608(%rbp), %rax
  testq %rax, %rax
  jne main_pb_true_3
  jmp main_pb_false_3
main_pb_true_3:
  leaq str_true(%rip), %rax
  addq $24, %rax
  movq %rax, -5616(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5616(%rbp), %rsi
  movq $4, %rdx
  syscall
  movq %rax, -5624(%rbp)
  jmp main_pb_done_3
main_pb_false_3:
  leaq str_false(%rip), %rax
  addq $24, %rax
  movq %rax, -5632(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5632(%rbp), %rsi
  movq $5, %rdx
  syscall
  movq %rax, -5640(%rbp)
  jmp main_pb_done_3
main_pb_done_3:
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
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5664(%rbp)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5672(%rbp)
  movq -5672(%rbp), %rax
  cmpq -5664(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5680(%rbp)
  movq -5680(%rbp), %rax
  movq -928(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_43(%rip), %rax
  movq -936(%rbp), %rdx
  movq %rax, (%rdx)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5688(%rbp)
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5696(%rbp)
  movq -5688(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_44
  jmp main_assert_fail_44
main_assert_pass_44:
  movq $0, %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  movq -952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5704(%rbp)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5712(%rbp)
  movq -5712(%rbp), %rax
  cmpq -5704(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5720(%rbp)
  movq -5720(%rbp), %rax
  movq -960(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_45(%rip), %rax
  movq -968(%rbp), %rdx
  movq %rax, (%rdx)
  movq -960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5728(%rbp)
  movq -968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5736(%rbp)
  movq -5728(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_46
  jmp main_assert_fail_46
main_assert_fail_44:
  movq -5696(%rbp), %rax
  addq $8, %rax
  movq %rax, -5744(%rbp)
  movq -5744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5752(%rbp)
  movq -5696(%rbp), %rax
  addq $24, %rax
  movq %rax, -5760(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5760(%rbp), %rsi
  movq -5752(%rbp), %rdx
  syscall
  movq %rax, -5768(%rbp)
  movq $50397203, %rax
  movq %rax, -5776(%rbp)
  jmp main_assert_pass_44
main_assert_pass_46:
  movq $0, %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  movq -984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5784(%rbp)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5792(%rbp)
  movq -5792(%rbp), %rax
  cmpq -5784(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5800(%rbp)
  movq -5800(%rbp), %rax
  movq -992(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_47(%rip), %rax
  movq -1000(%rbp), %rdx
  movq %rax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5808(%rbp)
  movq -1000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5816(%rbp)
  movq -5808(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_48
  jmp main_assert_fail_48
main_assert_fail_46:
  movq -5736(%rbp), %rax
  addq $8, %rax
  movq %rax, -5824(%rbp)
  movq -5824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5832(%rbp)
  movq -5736(%rbp), %rax
  addq $24, %rax
  movq %rax, -5840(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5840(%rbp), %rsi
  movq -5832(%rbp), %rdx
  syscall
  movq %rax, -5848(%rbp)
  movq $50397203, %rax
  movq %rax, -5856(%rbp)
  jmp main_assert_pass_46
main_assert_pass_48:
  movq $0, %rax
  movq -1008(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_49(%rip), %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5864(%rbp)
  movq -5864(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5872(%rbp)
  movq -5872(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5736
  jmp main_pr_str_0_5736
main_assert_fail_48:
  movq -5816(%rbp), %rax
  addq $8, %rax
  movq %rax, -5880(%rbp)
  movq -5880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5888(%rbp)
  movq -5816(%rbp), %rax
  addq $24, %rax
  movq %rax, -5896(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5896(%rbp), %rsi
  movq -5888(%rbp), %rdx
  syscall
  movq %rax, -5904(%rbp)
  movq $50397203, %rax
  movq %rax, -5912(%rbp)
  jmp main_assert_pass_48
main_pr_nil_0_5736:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5920(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5920(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5928(%rbp)
  jmp main_pr_next_0_5736
main_pr_str_0_5736:
  movq -5864(%rbp), %rax
  addq $8, %rax
  movq %rax, -5936(%rbp)
  movq -5936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5944(%rbp)
  movq -5864(%rbp), %rax
  addq $24, %rax
  movq %rax, -5952(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5952(%rbp), %rsi
  movq -5944(%rbp), %rdx
  syscall
  movq %rax, -5960(%rbp)
  jmp main_pr_next_0_5736
main_pr_next_0_5736:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5968(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5968(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5976(%rbp)
  movq $0, %rax
  movq -1024(%rbp), %rdx
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

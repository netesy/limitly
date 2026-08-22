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
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
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
  .byte 61
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 61
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
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
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
  .byte 67
  .byte 111
  .byte 110
  .byte 100
  .byte 105
  .byte 116
  .byte 105
  .byte 111
  .byte 110
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
  .byte 80
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 80
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 32
  .byte 50
  .byte 58
  .byte 32
  .byte 37
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
  .byte 80
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 32
  .byte 51
  .byte 58
  .byte 32
  .byte 37
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
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
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
  .byte 79
  .byte 112
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 111
  .byte 114
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
  .byte 69
  .byte 118
  .byte 101
  .byte 110
  .byte 32
  .byte 110
  .byte 117
  .byte 109
  .byte 98
  .byte 101
  .byte 114
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 69
  .byte 118
  .byte 101
  .byte 110
  .byte 32
  .byte 110
  .byte 117
  .byte 109
  .byte 98
  .byte 101
  .byte 114
  .byte 32
  .byte 50
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 79
  .byte 100
  .byte 100
  .byte 32
  .byte 110
  .byte 117
  .byte 109
  .byte 98
  .byte 101
  .byte 114
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 79
  .byte 100
  .byte 100
  .byte 32
  .byte 110
  .byte 117
  .byte 109
  .byte 98
  .byte 101
  .byte 114
  .byte 32
  .byte 50
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 53
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 53
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
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 67
  .byte 111
  .byte 109
  .byte 112
  .byte 108
  .byte 101
  .byte 120
  .byte 32
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
  .byte 45
  .byte 45
  .byte 45
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
  .byte 68
  .byte 111
  .byte 117
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 100
  .byte 105
  .byte 103
  .byte 105
  .byte 116
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 68
  .byte 111
  .byte 117
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 100
  .byte 105
  .byte 103
  .byte 105
  .byte 116
  .byte 32
  .byte 50
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 114
  .byte 105
  .byte 112
  .byte 108
  .byte 101
  .byte 32
  .byte 100
  .byte 105
  .byte 103
  .byte 105
  .byte 116
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 83
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
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
str_hdr_15:
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
  .byte 104
  .byte 101
  .byte 108
  .byte 108
  .byte 111
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
  .byte 115
  .byte 101
  .byte 108
  .byte 102
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 97
  .byte 32
  .byte 108
  .byte 111
  .byte 110
  .byte 103
  .byte 32
  .byte 115
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
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
  .byte 104
  .byte 105
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
  .byte 78
  .byte 111
  .byte 110
  .byte 45
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
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 76
  .byte 111
  .byte 110
  .byte 103
  .byte 32
  .byte 115
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 83
  .byte 104
  .byte 111
  .byte 114
  .byte 116
  .byte 32
  .byte 115
  .byte 116
  .byte 114
  .byte 105
  .byte 110
  .byte 103
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 53
  .byte 58
  .byte 32
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 32
  .byte 70
  .byte 117
  .byte 110
  .byte 99
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 32
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
  .byte 80
  .byte 114
  .byte 111
  .byte 99
  .byte 101
  .byte 115
  .byte 115
  .byte 32
  .byte 112
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 114
  .byte 101
  .byte 115
  .byte 117
  .byte 108
  .byte 116
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 114
  .byte 111
  .byte 99
  .byte 101
  .byte 115
  .byte 115
  .byte 32
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 114
  .byte 101
  .byte 115
  .byte 117
  .byte 108
  .byte 116
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 32
  .byte 70
  .byte 117
  .byte 110
  .byte 99
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 82
  .byte 101
  .byte 116
  .byte 117
  .byte 114
  .byte 110
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 80
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
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
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
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
  .byte 55
  .byte 58
  .byte 32
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 76
  .byte 111
  .byte 103
  .byte 105
  .byte 99
  .byte 97
  .byte 108
  .byte 32
  .byte 79
  .byte 112
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 111
  .byte 114
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 86
  .byte 97
  .byte 108
  .byte 105
  .byte 100
  .byte 32
  .byte 97
  .byte 103
  .byte 101
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 86
  .byte 97
  .byte 108
  .byte 105
  .byte 100
  .byte 32
  .byte 97
  .byte 103
  .byte 101
  .byte 32
  .byte 50
  .byte 58
  .byte 32
  .byte 37
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
  .byte 87
  .byte 111
  .byte 114
  .byte 107
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 97
  .byte 103
  .byte 101
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 87
  .byte 111
  .byte 114
  .byte 107
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 97
  .byte 103
  .byte 101
  .byte 32
  .byte 50
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
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
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
str_hdr_33:
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
  .byte 66
  .byte 97
  .byte 115
  .byte 101
  .byte 32
  .byte 112
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
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
  .byte 99
  .byte 116
  .byte 32
  .byte 112
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
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
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 32
  .byte 67
  .byte 111
  .byte 108
  .byte 108
  .byte 101
  .byte 99
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 115
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
  .byte 80
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 115
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 115
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 69
  .byte 118
  .byte 101
  .byte 110
  .byte 115
  .byte 58
  .byte 32
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
  .byte 58
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 58
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
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
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
  .byte 69
  .byte 120
  .byte 112
  .byte 114
  .byte 101
  .byte 115
  .byte 115
  .byte 105
  .byte 111
  .byte 110
  .byte 115
  .byte 32
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
  .byte 80
  .byte 111
  .byte 119
  .byte 101
  .byte 114
  .byte 32
  .byte 111
  .byte 102
  .byte 32
  .byte 116
  .byte 119
  .byte 111
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 80
  .byte 111
  .byte 119
  .byte 101
  .byte 114
  .byte 32
  .byte 111
  .byte 102
  .byte 32
  .byte 116
  .byte 119
  .byte 111
  .byte 32
  .byte 50
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 68
  .byte 105
  .byte 118
  .byte 105
  .byte 115
  .byte 105
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 49
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
  .byte 68
  .byte 105
  .byte 118
  .byte 105
  .byte 115
  .byte 105
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 50
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
  .byte 73
  .byte 110
  .byte 32
  .byte 98
  .byte 111
  .byte 117
  .byte 110
  .byte 100
  .byte 115
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 49
  .byte 49
  .byte 58
  .byte 32
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 65
  .byte 108
  .byte 105
  .byte 97
  .byte 115
  .byte 101
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 97
  .byte 108
  .byte 105
  .byte 97
  .byte 115
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 97
  .byte 108
  .byte 105
  .byte 97
  .byte 115
  .byte 32
  .byte 50
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
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 70
  .byte 117
  .byte 110
  .byte 99
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 67
  .byte 97
  .byte 108
  .byte 108
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 73
  .byte 115
  .byte 32
  .byte 112
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
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
str_hdr_50:
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
  .byte 73
  .byte 115
  .byte 32
  .byte 108
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 49
  .byte 51
  .byte 58
  .byte 32
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 68
  .byte 105
  .byte 118
  .byte 105
  .byte 115
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 78
  .byte 111
  .byte 110
  .byte 45
  .byte 122
  .byte 101
  .byte 114
  .byte 111
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 78
  .byte 111
  .byte 110
  .byte 45
  .byte 122
  .byte 101
  .byte 114
  .byte 111
  .byte 32
  .byte 50
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
  .byte 72
  .byte 105
  .byte 103
  .byte 104
  .byte 32
  .byte 118
  .byte 97
  .byte 108
  .byte 117
  .byte 101
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
  .byte 49
  .byte 52
  .byte 58
  .byte 32
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 77
  .byte 111
  .byte 100
  .byte 117
  .byte 108
  .byte 111
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 77
  .byte 117
  .byte 108
  .byte 116
  .byte 105
  .byte 112
  .byte 108
  .byte 101
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 77
  .byte 117
  .byte 108
  .byte 116
  .byte 105
  .byte 112
  .byte 108
  .byte 101
  .byte 32
  .byte 50
  .byte 58
  .byte 32
  .byte 37
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
  .byte 78
  .byte 111
  .byte 116
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
  .byte 49
  .byte 58
  .byte 32
  .byte 37
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
  .byte 78
  .byte 111
  .byte 116
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
  .byte 50
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 49
  .byte 53
  .byte 58
  .byte 32
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 32
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
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 66
  .byte 111
  .byte 98
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
  .byte 67
  .byte 104
  .byte 97
  .byte 114
  .byte 108
  .byte 105
  .byte 101
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
  .byte 112
  .byte 108
  .byte 97
  .byte 121
  .byte 101
  .byte 114
  .byte 49
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
  .byte 112
  .byte 108
  .byte 97
  .byte 121
  .byte 101
  .byte 114
  .byte 50
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
  .byte 65
  .byte 103
  .byte 101
  .byte 32
  .byte 109
  .byte 97
  .byte 112
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
  .byte 83
  .byte 99
  .byte 111
  .byte 114
  .byte 101
  .byte 32
  .byte 109
  .byte 97
  .byte 112
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
  .byte 54
  .byte 58
  .byte 32
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 83
  .byte 117
  .byte 98
  .byte 116
  .byte 114
  .byte 97
  .byte 99
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 65
  .byte 98
  .byte 111
  .byte 118
  .byte 101
  .byte 32
  .byte 122
  .byte 101
  .byte 114
  .byte 111
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 66
  .byte 101
  .byte 108
  .byte 111
  .byte 119
  .byte 32
  .byte 104
  .byte 117
  .byte 110
  .byte 100
  .byte 114
  .byte 101
  .byte 100
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 49
  .byte 55
  .byte 58
  .byte 32
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 65
  .byte 100
  .byte 100
  .byte 105
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 83
  .byte 117
  .byte 109
  .byte 32
  .byte 112
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 32
  .byte 37
  .byte 115
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
  .byte 56
  .byte 58
  .byte 32
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
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
  .byte 105
  .byte 99
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 32
  .byte 37
  .byte 115
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
  .byte 114
  .byte 111
  .byte 100
  .byte 117
  .byte 99
  .byte 116
  .byte 32
  .byte 115
  .byte 109
  .byte 97
  .byte 108
  .byte 108
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 60
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 60
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
  .byte 57
  .byte 58
  .byte 32
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 32
  .byte 70
  .byte 117
  .byte 110
  .byte 99
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 67
  .byte 111
  .byte 110
  .byte 100
  .byte 105
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 97
  .byte 108
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 86
  .byte 97
  .byte 108
  .byte 105
  .byte 100
  .byte 97
  .byte 116
  .byte 101
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 86
  .byte 97
  .byte 108
  .byte 105
  .byte 100
  .byte 97
  .byte 116
  .byte 101
  .byte 32
  .byte 50
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 86
  .byte 97
  .byte 108
  .byte 105
  .byte 100
  .byte 97
  .byte 116
  .byte 101
  .byte 32
  .byte 51
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 53
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 53
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
  .byte 48
  .byte 58
  .byte 32
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
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
  .byte 114
  .byte 101
  .byte 104
  .byte 101
  .byte 110
  .byte 115
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 67
  .byte 111
  .byte 118
  .byte 101
  .byte 114
  .byte 97
  .byte 103
  .byte 101
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 114
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
str_hdr_83:
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
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
  .byte 32
  .byte 114
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
str_hdr_84:
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
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 82
  .byte 101
  .byte 102
  .byte 105
  .byte 110
  .byte 101
  .byte 100
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
str_hdr_85:
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
  .byte 76
  .byte 97
  .byte 114
  .byte 103
  .byte 101
  .byte 32
  .byte 112
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
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
  .byte 77
  .byte 101
  .byte 100
  .byte 105
  .byte 117
  .byte 109
  .byte 32
  .byte 112
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
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
  .byte 83
  .byte 109
  .byte 97
  .byte 108
  .byte 108
  .byte 32
  .byte 112
  .byte 111
  .byte 115
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
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
  subq $11112, %rsp
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
  jmp main_block_0
main_block_0:
  leaq str_hdr_0(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2784(%rbp)
  movq -2784(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2792(%rbp)
  movq -2792(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9383
  jmp main_pr_str_0_9383
main_pr_nil_0_9383:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2800(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2800(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2808(%rbp)
  jmp main_pr_next_0_9383
main_pr_str_0_9383:
  movq -2784(%rbp), %rax
  addq $8, %rax
  movq %rax, -2816(%rbp)
  movq -2816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2824(%rbp)
  movq -2784(%rbp), %rax
  addq $24, %rax
  movq %rax, -2832(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2832(%rbp), %rsi
  movq -2824(%rbp), %rdx
  syscall
  movq %rax, -2840(%rbp)
  jmp main_pr_next_0_9383
main_pr_next_0_9383:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2848(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2848(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2856(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_1(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2864(%rbp)
  movq -2864(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2872(%rbp)
  movq -2872(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_886
  jmp main_pr_str_0_886
main_pr_nil_0_886:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2880(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2880(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2888(%rbp)
  jmp main_pr_next_0_886
main_pr_str_0_886:
  movq -2864(%rbp), %rax
  addq $8, %rax
  movq %rax, -2896(%rbp)
  movq -2896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2904(%rbp)
  movq -2864(%rbp), %rax
  addq $24, %rax
  movq %rax, -2912(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2912(%rbp), %rsi
  movq -2904(%rbp), %rdx
  syscall
  movq %rax, -2920(%rbp)
  jmp main_pr_next_0_886
main_pr_next_0_886:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2928(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2928(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2936(%rbp)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq $42, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1000, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_2(%rip), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2944(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2952(%rbp)
  movq -2944(%rbp), %rdi
  movq -2952(%rbp), %rsi
  call lm_rt_str_format
  mov -2960(%rbp), rax
  movq -2960(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2968(%rbp)
  movq -2968(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2976(%rbp)
  movq -2976(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2777
  jmp main_pr_str_0_2777
main_pr_nil_0_2777:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2984(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2984(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2992(%rbp)
  jmp main_pr_next_0_2777
main_pr_str_0_2777:
  movq -2968(%rbp), %rax
  addq $8, %rax
  movq %rax, -3000(%rbp)
  movq -3000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3008(%rbp)
  movq -2968(%rbp), %rax
  addq $24, %rax
  movq %rax, -3016(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3016(%rbp), %rsi
  movq -3008(%rbp), %rdx
  syscall
  movq %rax, -3024(%rbp)
  jmp main_pr_next_0_2777
main_pr_next_0_2777:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3032(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3032(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3040(%rbp)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_3(%rip), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3048(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3056(%rbp)
  movq -3048(%rbp), %rdi
  movq -3056(%rbp), %rsi
  call lm_rt_str_format
  mov -3064(%rbp), rax
  movq -3064(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3072(%rbp)
  movq -3072(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3080(%rbp)
  movq -3080(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6915
  jmp main_pr_str_0_6915
main_pr_nil_0_6915:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3088(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3088(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3096(%rbp)
  jmp main_pr_next_0_6915
main_pr_str_0_6915:
  movq -3072(%rbp), %rax
  addq $8, %rax
  movq %rax, -3104(%rbp)
  movq -3104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3112(%rbp)
  movq -3072(%rbp), %rax
  addq $24, %rax
  movq %rax, -3120(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3120(%rbp), %rsi
  movq -3112(%rbp), %rdx
  syscall
  movq %rax, -3128(%rbp)
  jmp main_pr_next_0_6915
main_pr_next_0_6915:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3136(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3136(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3144(%rbp)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_4(%rip), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3152(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3160(%rbp)
  movq -3152(%rbp), %rdi
  movq -3160(%rbp), %rsi
  call lm_rt_str_format
  mov -3168(%rbp), rax
  movq -3168(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3176(%rbp)
  movq -3176(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3184(%rbp)
  movq -3184(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7793
  jmp main_pr_str_0_7793
main_pr_nil_0_7793:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3192(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3192(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3200(%rbp)
  jmp main_pr_next_0_7793
main_pr_str_0_7793:
  movq -3176(%rbp), %rax
  addq $8, %rax
  movq %rax, -3208(%rbp)
  movq -3208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3216(%rbp)
  movq -3176(%rbp), %rax
  addq $24, %rax
  movq %rax, -3224(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3224(%rbp), %rsi
  movq -3216(%rbp), %rdx
  syscall
  movq %rax, -3232(%rbp)
  jmp main_pr_next_0_7793
main_pr_next_0_7793:
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
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_5(%rip), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3256(%rbp)
  movq -3256(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3264(%rbp)
  movq -3264(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8335
  jmp main_pr_str_0_8335
main_pr_nil_0_8335:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3272(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3272(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3280(%rbp)
  jmp main_pr_next_0_8335
main_pr_str_0_8335:
  movq -3256(%rbp), %rax
  addq $8, %rax
  movq %rax, -3288(%rbp)
  movq -3288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3296(%rbp)
  movq -3256(%rbp), %rax
  addq $24, %rax
  movq %rax, -3304(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3304(%rbp), %rsi
  movq -3296(%rbp), %rdx
  syscall
  movq %rax, -3312(%rbp)
  jmp main_pr_next_0_8335
main_pr_next_0_8335:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3320(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3320(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3328(%rbp)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $100, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq $99, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_6(%rip), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3336(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3344(%rbp)
  movq -3336(%rbp), %rdi
  movq -3344(%rbp), %rsi
  call lm_rt_str_format
  mov -3352(%rbp), rax
  movq -3352(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3360(%rbp)
  movq -3360(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3368(%rbp)
  movq -3368(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5386
  jmp main_pr_str_0_5386
main_pr_nil_0_5386:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3376(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3376(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3384(%rbp)
  jmp main_pr_next_0_5386
main_pr_str_0_5386:
  movq -3360(%rbp), %rax
  addq $8, %rax
  movq %rax, -3392(%rbp)
  movq -3392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3400(%rbp)
  movq -3360(%rbp), %rax
  addq $24, %rax
  movq %rax, -3408(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3408(%rbp), %rsi
  movq -3400(%rbp), %rdx
  syscall
  movq %rax, -3416(%rbp)
  jmp main_pr_next_0_5386
main_pr_next_0_5386:
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
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_7(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3440(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3448(%rbp)
  movq -3440(%rbp), %rdi
  movq -3448(%rbp), %rsi
  call lm_rt_str_format
  mov -3456(%rbp), rax
  movq -3456(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3464(%rbp)
  movq -3464(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3472(%rbp)
  movq -3472(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_492
  jmp main_pr_str_0_492
main_pr_nil_0_492:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3480(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3480(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3488(%rbp)
  jmp main_pr_next_0_492
main_pr_str_0_492:
  movq -3464(%rbp), %rax
  addq $8, %rax
  movq %rax, -3496(%rbp)
  movq -3496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3504(%rbp)
  movq -3464(%rbp), %rax
  addq $24, %rax
  movq %rax, -3512(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3512(%rbp), %rsi
  movq -3504(%rbp), %rdx
  syscall
  movq %rax, -3520(%rbp)
  jmp main_pr_next_0_492
main_pr_next_0_492:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3528(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3528(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3536(%rbp)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_8(%rip), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3544(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3552(%rbp)
  movq -3544(%rbp), %rdi
  movq -3552(%rbp), %rsi
  call lm_rt_str_format
  mov -3560(%rbp), rax
  movq -3560(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3568(%rbp)
  movq -3568(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3576(%rbp)
  movq -3576(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6649
  jmp main_pr_str_0_6649
main_pr_nil_0_6649:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3584(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3584(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3592(%rbp)
  jmp main_pr_next_0_6649
main_pr_str_0_6649:
  movq -3568(%rbp), %rax
  addq $8, %rax
  movq %rax, -3600(%rbp)
  movq -3600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3608(%rbp)
  movq -3568(%rbp), %rax
  addq $24, %rax
  movq %rax, -3616(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3616(%rbp), %rsi
  movq -3608(%rbp), %rdx
  syscall
  movq %rax, -3624(%rbp)
  jmp main_pr_next_0_6649
main_pr_next_0_6649:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3632(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3632(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3640(%rbp)
  movq $0, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_9(%rip), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3648(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3656(%rbp)
  movq -3648(%rbp), %rdi
  movq -3656(%rbp), %rsi
  call lm_rt_str_format
  mov -3664(%rbp), rax
  movq -3664(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3672(%rbp)
  movq -3672(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3680(%rbp)
  movq -3680(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1421
  jmp main_pr_str_0_1421
main_pr_nil_0_1421:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3688(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3688(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3696(%rbp)
  jmp main_pr_next_0_1421
main_pr_str_0_1421:
  movq -3672(%rbp), %rax
  addq $8, %rax
  movq %rax, -3704(%rbp)
  movq -3704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3712(%rbp)
  movq -3672(%rbp), %rax
  addq $24, %rax
  movq %rax, -3720(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3720(%rbp), %rsi
  movq -3712(%rbp), %rdx
  syscall
  movq %rax, -3728(%rbp)
  jmp main_pr_next_0_1421
main_pr_next_0_1421:
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
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_10(%rip), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3752(%rbp)
  movq -3752(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3760(%rbp)
  movq -3760(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2362
  jmp main_pr_str_0_2362
main_pr_nil_0_2362:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3768(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3768(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3776(%rbp)
  jmp main_pr_next_0_2362
main_pr_str_0_2362:
  movq -3752(%rbp), %rax
  addq $8, %rax
  movq %rax, -3784(%rbp)
  movq -3784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3792(%rbp)
  movq -3752(%rbp), %rax
  addq $24, %rax
  movq %rax, -3800(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3800(%rbp), %rsi
  movq -3792(%rbp), %rdx
  syscall
  movq %rax, -3808(%rbp)
  jmp main_pr_next_0_2362
main_pr_next_0_2362:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3816(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3816(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3824(%rbp)
  movq $0, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq $21, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq $999, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $201, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_11(%rip), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3832(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3840(%rbp)
  movq -3832(%rbp), %rdi
  movq -3840(%rbp), %rsi
  call lm_rt_str_format
  mov -3848(%rbp), rax
  movq -3848(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3856(%rbp)
  movq -3856(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3864(%rbp)
  movq -3864(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_27
  jmp main_pr_str_0_27
main_pr_nil_0_27:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3872(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3872(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3880(%rbp)
  jmp main_pr_next_0_27
main_pr_str_0_27:
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
  jmp main_pr_next_0_27
main_pr_next_0_27:
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
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_12(%rip), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3936(%rbp)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3944(%rbp)
  movq -3936(%rbp), %rdi
  movq -3944(%rbp), %rsi
  call lm_rt_str_format
  mov -3952(%rbp), rax
  movq -3952(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3960(%rbp)
  movq -3960(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3968(%rbp)
  movq -3968(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8690
  jmp main_pr_str_0_8690
main_pr_nil_0_8690:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3976(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3976(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3984(%rbp)
  jmp main_pr_next_0_8690
main_pr_str_0_8690:
  movq -3960(%rbp), %rax
  addq $8, %rax
  movq %rax, -3992(%rbp)
  movq -3992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4000(%rbp)
  movq -3960(%rbp), %rax
  addq $24, %rax
  movq %rax, -4008(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4008(%rbp), %rsi
  movq -4000(%rbp), %rdx
  syscall
  movq %rax, -4016(%rbp)
  jmp main_pr_next_0_8690
main_pr_next_0_8690:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4024(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4024(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4032(%rbp)
  movq $0, %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_13(%rip), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4040(%rbp)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4048(%rbp)
  movq -4040(%rbp), %rdi
  movq -4048(%rbp), %rsi
  call lm_rt_str_format
  mov -4056(%rbp), rax
  movq -4056(%rbp), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4064(%rbp)
  movq -4064(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4072(%rbp)
  movq -4072(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_59
  jmp main_pr_str_0_59
main_pr_nil_0_59:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4080(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4080(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4088(%rbp)
  jmp main_pr_next_0_59
main_pr_str_0_59:
  movq -4064(%rbp), %rax
  addq $8, %rax
  movq %rax, -4096(%rbp)
  movq -4096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4104(%rbp)
  movq -4064(%rbp), %rax
  addq $24, %rax
  movq %rax, -4112(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4112(%rbp), %rsi
  movq -4104(%rbp), %rdx
  syscall
  movq %rax, -4120(%rbp)
  jmp main_pr_next_0_59
main_pr_next_0_59:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4128(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4128(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4136(%rbp)
  movq $0, %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_14(%rip), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4144(%rbp)
  movq -4144(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4152(%rbp)
  movq -4152(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7763
  jmp main_pr_str_0_7763
main_pr_nil_0_7763:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4160(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4168(%rbp)
  jmp main_pr_next_0_7763
main_pr_str_0_7763:
  movq -4144(%rbp), %rax
  addq $8, %rax
  movq %rax, -4176(%rbp)
  movq -4176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4184(%rbp)
  movq -4144(%rbp), %rax
  addq $24, %rax
  movq %rax, -4192(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4192(%rbp), %rsi
  movq -4184(%rbp), %rdx
  syscall
  movq %rax, -4200(%rbp)
  jmp main_pr_next_0_7763
main_pr_next_0_7763:
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
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_15(%rip), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_16(%rip), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_17(%rip), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_18(%rip), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4224(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4232(%rbp)
  movq -4224(%rbp), %rdi
  movq -4232(%rbp), %rsi
  call lm_rt_str_format
  mov -4240(%rbp), rax
  movq -4240(%rbp), %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4248(%rbp)
  movq -4248(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4256(%rbp)
  movq -4256(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3926
  jmp main_pr_str_0_3926
main_pr_nil_0_3926:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4264(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4264(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4272(%rbp)
  jmp main_pr_next_0_3926
main_pr_str_0_3926:
  movq -4248(%rbp), %rax
  addq $8, %rax
  movq %rax, -4280(%rbp)
  movq -4280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4288(%rbp)
  movq -4248(%rbp), %rax
  addq $24, %rax
  movq %rax, -4296(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4296(%rbp), %rsi
  movq -4288(%rbp), %rdx
  syscall
  movq %rax, -4304(%rbp)
  jmp main_pr_next_0_3926
main_pr_next_0_3926:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4312(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4312(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4320(%rbp)
  movq $0, %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_19(%rip), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4328(%rbp)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4336(%rbp)
  movq -4328(%rbp), %rdi
  movq -4336(%rbp), %rsi
  call lm_rt_str_format
  mov -4344(%rbp), rax
  movq -4344(%rbp), %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4352(%rbp)
  movq -4352(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4360(%rbp)
  movq -4360(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_540
  jmp main_pr_str_0_540
main_pr_nil_0_540:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4368(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4368(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4376(%rbp)
  jmp main_pr_next_0_540
main_pr_str_0_540:
  movq -4352(%rbp), %rax
  addq $8, %rax
  movq %rax, -4384(%rbp)
  movq -4384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4392(%rbp)
  movq -4352(%rbp), %rax
  addq $24, %rax
  movq %rax, -4400(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4400(%rbp), %rsi
  movq -4392(%rbp), %rdx
  syscall
  movq %rax, -4408(%rbp)
  jmp main_pr_next_0_540
main_pr_next_0_540:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4416(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4416(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4424(%rbp)
  movq $0, %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_20(%rip), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4432(%rbp)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4440(%rbp)
  movq -4432(%rbp), %rdi
  movq -4440(%rbp), %rsi
  call lm_rt_str_format
  mov -4448(%rbp), rax
  movq -4448(%rbp), %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4456(%rbp)
  movq -4456(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4464(%rbp)
  movq -4464(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3426
  jmp main_pr_str_0_3426
main_pr_nil_0_3426:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4472(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4472(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4480(%rbp)
  jmp main_pr_next_0_3426
main_pr_str_0_3426:
  movq -4456(%rbp), %rax
  addq $8, %rax
  movq %rax, -4488(%rbp)
  movq -4488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4496(%rbp)
  movq -4456(%rbp), %rax
  addq $24, %rax
  movq %rax, -4504(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4504(%rbp), %rsi
  movq -4496(%rbp), %rdx
  syscall
  movq %rax, -4512(%rbp)
  jmp main_pr_next_0_3426
main_pr_next_0_3426:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4520(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4520(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4528(%rbp)
  movq $0, %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_21(%rip), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4536(%rbp)
  movq -4536(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4544(%rbp)
  movq -4544(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9172
  jmp main_pr_str_0_9172
main_pr_nil_0_9172:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4552(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4552(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4560(%rbp)
  jmp main_pr_next_0_9172
main_pr_str_0_9172:
  movq -4536(%rbp), %rax
  addq $8, %rax
  movq %rax, -4568(%rbp)
  movq -4568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4576(%rbp)
  movq -4536(%rbp), %rax
  addq $24, %rax
  movq %rax, -4584(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4584(%rbp), %rsi
  movq -4576(%rbp), %rdx
  syscall
  movq %rax, -4592(%rbp)
  jmp main_pr_next_0_9172
main_pr_next_0_9172:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4600(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4600(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4608(%rbp)
  movq $0, %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4616(%rbp)
  movq -4616(%rbp), %rdi
  call processPositive
  mov -4624(%rbp), rax
  movq -4624(%rbp), %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4632(%rbp)
  movq -4632(%rbp), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  movq $150, %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4640(%rbp)
  movq -4640(%rbp), %rdi
  call processLarge
  mov -4648(%rbp), rax
  movq -4648(%rbp), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4656(%rbp)
  movq -4656(%rbp), %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_22(%rip), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4664(%rbp)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4672(%rbp)
  movq -4664(%rbp), %rdi
  movq -4672(%rbp), %rsi
  call lm_rt_str_format
  mov -4680(%rbp), rax
  movq -4680(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4688(%rbp)
  movq -4688(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4696(%rbp)
  movq -4696(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5736
  jmp main_pr_str_0_5736
main_pr_nil_0_5736:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4704(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4704(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4712(%rbp)
  jmp main_pr_next_0_5736
main_pr_str_0_5736:
  movq -4688(%rbp), %rax
  addq $8, %rax
  movq %rax, -4720(%rbp)
  movq -4720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4728(%rbp)
  movq -4688(%rbp), %rax
  addq $24, %rax
  movq %rax, -4736(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4736(%rbp), %rsi
  movq -4728(%rbp), %rdx
  syscall
  movq %rax, -4744(%rbp)
  jmp main_pr_next_0_5736
main_pr_next_0_5736:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4752(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4752(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4760(%rbp)
  movq $0, %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_23(%rip), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4768(%rbp)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4776(%rbp)
  movq -4768(%rbp), %rdi
  movq -4776(%rbp), %rsi
  call lm_rt_str_format
  mov -4784(%rbp), rax
  movq -4784(%rbp), %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4792(%rbp)
  movq -4792(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4800(%rbp)
  movq -4800(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5211
  jmp main_pr_str_0_5211
main_pr_nil_0_5211:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4808(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4808(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4816(%rbp)
  jmp main_pr_next_0_5211
main_pr_str_0_5211:
  movq -4792(%rbp), %rax
  addq $8, %rax
  movq %rax, -4824(%rbp)
  movq -4824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4832(%rbp)
  movq -4792(%rbp), %rax
  addq $24, %rax
  movq %rax, -4840(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4840(%rbp), %rsi
  movq -4832(%rbp), %rdx
  syscall
  movq %rax, -4848(%rbp)
  jmp main_pr_next_0_5211
main_pr_next_0_5211:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4856(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4856(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4864(%rbp)
  movq $0, %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_24(%rip), %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4872(%rbp)
  movq -4872(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4880(%rbp)
  movq -4880(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5368
  jmp main_pr_str_0_5368
main_pr_nil_0_5368:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4888(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4888(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4896(%rbp)
  jmp main_pr_next_0_5368
main_pr_str_0_5368:
  movq -4872(%rbp), %rax
  addq $8, %rax
  movq %rax, -4904(%rbp)
  movq -4904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4912(%rbp)
  movq -4872(%rbp), %rax
  addq $24, %rax
  movq %rax, -4920(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4920(%rbp), %rsi
  movq -4912(%rbp), %rdx
  syscall
  movq %rax, -4928(%rbp)
  jmp main_pr_next_0_5368
main_pr_next_0_5368:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4936(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4936(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4944(%rbp)
  movq $0, %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  call getPositiveNumber
  mov -4952(%rbp), rax
  movq -4952(%rbp), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4960(%rbp)
  movq -4960(%rbp), %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  call getLargeNumber
  mov -4968(%rbp), rax
  movq -4968(%rbp), %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4976(%rbp)
  movq -4976(%rbp), %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_25(%rip), %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4984(%rbp)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4992(%rbp)
  movq -4984(%rbp), %rdi
  movq -4992(%rbp), %rsi
  call lm_rt_str_format
  mov -5000(%rbp), rax
  movq -5000(%rbp), %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5008(%rbp)
  movq -5008(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5016(%rbp)
  movq -5016(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2567
  jmp main_pr_str_0_2567
main_pr_nil_0_2567:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5024(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5024(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5032(%rbp)
  jmp main_pr_next_0_2567
main_pr_str_0_2567:
  movq -5008(%rbp), %rax
  addq $8, %rax
  movq %rax, -5040(%rbp)
  movq -5040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5048(%rbp)
  movq -5008(%rbp), %rax
  addq $24, %rax
  movq %rax, -5056(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5056(%rbp), %rsi
  movq -5048(%rbp), %rdx
  syscall
  movq %rax, -5064(%rbp)
  jmp main_pr_next_0_2567
main_pr_next_0_2567:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5072(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5072(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5080(%rbp)
  movq $0, %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_26(%rip), %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5088(%rbp)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5096(%rbp)
  movq -5088(%rbp), %rdi
  movq -5096(%rbp), %rsi
  call lm_rt_str_format
  mov -5104(%rbp), rax
  movq -5104(%rbp), %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5112(%rbp)
  movq -5112(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5120(%rbp)
  movq -5120(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6429
  jmp main_pr_str_0_6429
main_pr_nil_0_6429:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5128(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5128(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5136(%rbp)
  jmp main_pr_next_0_6429
main_pr_str_0_6429:
  movq -5112(%rbp), %rax
  addq $8, %rax
  movq %rax, -5144(%rbp)
  movq -5144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5152(%rbp)
  movq -5112(%rbp), %rax
  addq $24, %rax
  movq %rax, -5160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5160(%rbp), %rsi
  movq -5152(%rbp), %rdx
  syscall
  movq %rax, -5168(%rbp)
  jmp main_pr_next_0_6429
main_pr_next_0_6429:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5176(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5176(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5184(%rbp)
  movq $0, %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_27(%rip), %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5192(%rbp)
  movq -5192(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5200(%rbp)
  movq -5200(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5782
  jmp main_pr_str_0_5782
main_pr_nil_0_5782:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5208(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5208(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5216(%rbp)
  jmp main_pr_next_0_5782
main_pr_str_0_5782:
  movq -5192(%rbp), %rax
  addq $8, %rax
  movq %rax, -5224(%rbp)
  movq -5224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5232(%rbp)
  movq -5192(%rbp), %rax
  addq $24, %rax
  movq %rax, -5240(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5240(%rbp), %rsi
  movq -5232(%rbp), %rdx
  syscall
  movq %rax, -5248(%rbp)
  jmp main_pr_next_0_5782
main_pr_next_0_5782:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5256(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5256(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5264(%rbp)
  movq $0, %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq $25, %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  movq $100, %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  movq $30, %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  movq $65, %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_28(%rip), %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5272(%rbp)
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5280(%rbp)
  movq -5272(%rbp), %rdi
  movq -5280(%rbp), %rsi
  call lm_rt_str_format
  mov -5288(%rbp), rax
  movq -5288(%rbp), %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5296(%rbp)
  movq -5296(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5304(%rbp)
  movq -5304(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1530
  jmp main_pr_str_0_1530
main_pr_nil_0_1530:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5312(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5312(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5320(%rbp)
  jmp main_pr_next_0_1530
main_pr_str_0_1530:
  movq -5296(%rbp), %rax
  addq $8, %rax
  movq %rax, -5328(%rbp)
  movq -5328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5336(%rbp)
  movq -5296(%rbp), %rax
  addq $24, %rax
  movq %rax, -5344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5344(%rbp), %rsi
  movq -5336(%rbp), %rdx
  syscall
  movq %rax, -5352(%rbp)
  jmp main_pr_next_0_1530
main_pr_next_0_1530:
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
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_29(%rip), %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5376(%rbp)
  movq -776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5384(%rbp)
  movq -5376(%rbp), %rdi
  movq -5384(%rbp), %rsi
  call lm_rt_str_format
  mov -5392(%rbp), rax
  movq -5392(%rbp), %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5400(%rbp)
  movq -5400(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5408(%rbp)
  movq -5408(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2862
  jmp main_pr_str_0_2862
main_pr_nil_0_2862:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5416(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5416(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5424(%rbp)
  jmp main_pr_next_0_2862
main_pr_str_0_2862:
  movq -5400(%rbp), %rax
  addq $8, %rax
  movq %rax, -5432(%rbp)
  movq -5432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5440(%rbp)
  movq -5400(%rbp), %rax
  addq $24, %rax
  movq %rax, -5448(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5448(%rbp), %rsi
  movq -5440(%rbp), %rdx
  syscall
  movq %rax, -5456(%rbp)
  jmp main_pr_next_0_2862
main_pr_next_0_2862:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5464(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5464(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5472(%rbp)
  movq $0, %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_30(%rip), %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5480(%rbp)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5488(%rbp)
  movq -5480(%rbp), %rdi
  movq -5488(%rbp), %rsi
  call lm_rt_str_format
  mov -5496(%rbp), rax
  movq -5496(%rbp), %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5504(%rbp)
  movq -5504(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5512(%rbp)
  movq -5512(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5123
  jmp main_pr_str_0_5123
main_pr_nil_0_5123:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5520(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5520(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5528(%rbp)
  jmp main_pr_next_0_5123
main_pr_str_0_5123:
  movq -5504(%rbp), %rax
  addq $8, %rax
  movq %rax, -5536(%rbp)
  movq -5536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5544(%rbp)
  movq -5504(%rbp), %rax
  addq $24, %rax
  movq %rax, -5552(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5552(%rbp), %rsi
  movq -5544(%rbp), %rdx
  syscall
  movq %rax, -5560(%rbp)
  jmp main_pr_next_0_5123
main_pr_next_0_5123:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5568(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5568(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5576(%rbp)
  movq $0, %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_31(%rip), %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5584(%rbp)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5592(%rbp)
  movq -5584(%rbp), %rdi
  movq -5592(%rbp), %rsi
  call lm_rt_str_format
  mov -5600(%rbp), rax
  movq -5600(%rbp), %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5608(%rbp)
  movq -5608(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5616(%rbp)
  movq -5616(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_4067
  jmp main_pr_str_0_4067
main_pr_nil_0_4067:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5624(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5624(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5632(%rbp)
  jmp main_pr_next_0_4067
main_pr_str_0_4067:
  movq -5608(%rbp), %rax
  addq $8, %rax
  movq %rax, -5640(%rbp)
  movq -5640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5648(%rbp)
  movq -5608(%rbp), %rax
  addq $24, %rax
  movq %rax, -5656(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5656(%rbp), %rsi
  movq -5648(%rbp), %rdx
  syscall
  movq %rax, -5664(%rbp)
  jmp main_pr_next_0_4067
main_pr_next_0_4067:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5672(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5672(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5680(%rbp)
  movq $0, %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_32(%rip), %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5688(%rbp)
  movq -5688(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5696(%rbp)
  movq -5696(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3135
  jmp main_pr_str_0_3135
main_pr_nil_0_3135:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5704(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5704(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5712(%rbp)
  jmp main_pr_next_0_3135
main_pr_str_0_3135:
  movq -5688(%rbp), %rax
  addq $8, %rax
  movq %rax, -5720(%rbp)
  movq -5720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5728(%rbp)
  movq -5688(%rbp), %rax
  addq $24, %rax
  movq %rax, -5736(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5736(%rbp), %rsi
  movq -5728(%rbp), %rdx
  syscall
  movq %rax, -5744(%rbp)
  jmp main_pr_next_0_3135
main_pr_next_0_3135:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5752(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5752(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5760(%rbp)
  movq $0, %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  movq $20, %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_33(%rip), %rax
  movq -936(%rbp), %rdx
  movq %rax, (%rdx)
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5768(%rbp)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5776(%rbp)
  movq -5768(%rbp), %rdi
  movq -5776(%rbp), %rsi
  call lm_rt_str_format
  mov -5784(%rbp), rax
  movq -5784(%rbp), %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5792(%rbp)
  movq -5792(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5800(%rbp)
  movq -5800(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3929
  jmp main_pr_str_0_3929
main_pr_nil_0_3929:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5808(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5808(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5816(%rbp)
  jmp main_pr_next_0_3929
main_pr_str_0_3929:
  movq -5792(%rbp), %rax
  addq $8, %rax
  movq %rax, -5824(%rbp)
  movq -5824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5832(%rbp)
  movq -5792(%rbp), %rax
  addq $24, %rax
  movq %rax, -5840(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5840(%rbp), %rsi
  movq -5832(%rbp), %rdx
  syscall
  movq %rax, -5848(%rbp)
  jmp main_pr_next_0_3929
main_pr_next_0_3929:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5856(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5856(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5864(%rbp)
  movq $0, %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_34(%rip), %rax
  movq -960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5872(%rbp)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5880(%rbp)
  movq -5872(%rbp), %rdi
  movq -5880(%rbp), %rsi
  call lm_rt_str_format
  mov -5888(%rbp), rax
  movq -5888(%rbp), %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  movq -952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5896(%rbp)
  movq -5896(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5904(%rbp)
  movq -5904(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9802
  jmp main_pr_str_0_9802
main_pr_nil_0_9802:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5912(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5912(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5920(%rbp)
  jmp main_pr_next_0_9802
main_pr_str_0_9802:
  movq -5896(%rbp), %rax
  addq $8, %rax
  movq %rax, -5928(%rbp)
  movq -5928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5936(%rbp)
  movq -5896(%rbp), %rax
  addq $24, %rax
  movq %rax, -5944(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5944(%rbp), %rsi
  movq -5936(%rbp), %rdx
  syscall
  movq %rax, -5952(%rbp)
  jmp main_pr_next_0_9802
main_pr_next_0_9802:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5960(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5960(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5968(%rbp)
  movq $0, %rax
  movq -968(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_35(%rip), %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5976(%rbp)
  movq -5976(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5984(%rbp)
  movq -5984(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_4022
  jmp main_pr_str_0_4022
main_pr_nil_0_4022:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5992(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5992(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6000(%rbp)
  jmp main_pr_next_0_4022
main_pr_str_0_4022:
  movq -5976(%rbp), %rax
  addq $8, %rax
  movq %rax, -6008(%rbp)
  movq -6008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6016(%rbp)
  movq -5976(%rbp), %rax
  addq $24, %rax
  movq %rax, -6024(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6024(%rbp), %rsi
  movq -6016(%rbp), %rdx
  syscall
  movq %rax, -6032(%rbp)
  jmp main_pr_next_0_4022
main_pr_next_0_4022:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6040(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6040(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6048(%rbp)
  movq $0, %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -6056(%rbp), rax
  movq -6056(%rbp), %rax
  movq -992(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1000(%rbp), %rdx
  movq %rax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6064(%rbp)
  movq -1000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6072(%rbp)
  movq -6064(%rbp), %rdi
  movq -6072(%rbp), %rsi
  call lm_list_append
  mov -6080(%rbp), rax
  movq $2, %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6088(%rbp)
  movq -1016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6096(%rbp)
  movq -6088(%rbp), %rdi
  movq -6096(%rbp), %rsi
  call lm_list_append
  mov -6104(%rbp), rax
  movq $3, %rax
  movq -1032(%rbp), %rdx
  movq %rax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6112(%rbp)
  movq -1032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6120(%rbp)
  movq -6112(%rbp), %rdi
  movq -6120(%rbp), %rsi
  call lm_list_append
  mov -6128(%rbp), rax
  movq $4, %rax
  movq -1048(%rbp), %rdx
  movq %rax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6136(%rbp)
  movq -1048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6144(%rbp)
  movq -6136(%rbp), %rdi
  movq -6144(%rbp), %rsi
  call lm_list_append
  mov -6152(%rbp), rax
  movq $5, %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6160(%rbp)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6168(%rbp)
  movq -6160(%rbp), %rdi
  movq -6168(%rbp), %rsi
  call lm_list_append
  mov -6176(%rbp), rax
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6184(%rbp)
  movq -6184(%rbp), %rax
  movq -1080(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -6192(%rbp), rax
  movq -6192(%rbp), %rax
  movq -1088(%rbp), %rdx
  movq %rax, (%rdx)
  movq $101, %rax
  movq -1096(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6200(%rbp)
  movq -1096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6208(%rbp)
  movq -6200(%rbp), %rdi
  movq -6208(%rbp), %rsi
  call lm_list_append
  mov -6216(%rbp), rax
  movq $200, %rax
  movq -1112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6224(%rbp)
  movq -1112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6232(%rbp)
  movq -6224(%rbp), %rdi
  movq -6232(%rbp), %rsi
  call lm_list_append
  mov -6240(%rbp), rax
  movq $500, %rax
  movq -1128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6248(%rbp)
  movq -1128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6256(%rbp)
  movq -6248(%rbp), %rdi
  movq -6256(%rbp), %rsi
  call lm_list_append
  mov -6264(%rbp), rax
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6272(%rbp)
  movq -6272(%rbp), %rax
  movq -1144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -6280(%rbp), rax
  movq -6280(%rbp), %rax
  movq -1152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -1160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6288(%rbp)
  movq -1160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6296(%rbp)
  movq -6288(%rbp), %rdi
  movq -6296(%rbp), %rsi
  call lm_list_append
  mov -6304(%rbp), rax
  movq $4, %rax
  movq -1176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6312(%rbp)
  movq -1176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6320(%rbp)
  movq -6312(%rbp), %rdi
  movq -6320(%rbp), %rsi
  call lm_list_append
  mov -6328(%rbp), rax
  movq $6, %rax
  movq -1192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6336(%rbp)
  movq -1192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6344(%rbp)
  movq -6336(%rbp), %rdi
  movq -6344(%rbp), %rsi
  call lm_list_append
  mov -6352(%rbp), rax
  movq $8, %rax
  movq -1208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6360(%rbp)
  movq -1208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6368(%rbp)
  movq -6360(%rbp), %rdi
  movq -6368(%rbp), %rsi
  call lm_list_append
  mov -6376(%rbp), rax
  movq $10, %rax
  movq -1224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6384(%rbp)
  movq -1224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6392(%rbp)
  movq -6384(%rbp), %rdi
  movq -6392(%rbp), %rsi
  call lm_list_append
  mov -6400(%rbp), rax
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6408(%rbp)
  movq -6408(%rbp), %rax
  movq -1240(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_36(%rip), %rax
  movq -1256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6416(%rbp)
  movq -1080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6424(%rbp)
  movq -6416(%rbp), %rdi
  movq -6424(%rbp), %rsi
  call lm_rt_str_format
  mov -6432(%rbp), rax
  movq -6432(%rbp), %rax
  movq -1248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6440(%rbp)
  movq -6440(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6448(%rbp)
  movq -6448(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3058
  jmp main_pr_str_0_3058
main_pr_nil_0_3058:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6456(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6456(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6464(%rbp)
  jmp main_pr_next_0_3058
main_pr_str_0_3058:
  movq -6440(%rbp), %rax
  addq $8, %rax
  movq %rax, -6472(%rbp)
  movq -6472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6480(%rbp)
  movq -6440(%rbp), %rax
  addq $24, %rax
  movq %rax, -6488(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6488(%rbp), %rsi
  movq -6480(%rbp), %rdx
  syscall
  movq %rax, -6496(%rbp)
  jmp main_pr_next_0_3058
main_pr_next_0_3058:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6504(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6504(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6512(%rbp)
  movq $0, %rax
  movq -1264(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_37(%rip), %rax
  movq -1280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6520(%rbp)
  movq -1144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6528(%rbp)
  movq -6520(%rbp), %rdi
  movq -6528(%rbp), %rsi
  call lm_rt_str_format
  mov -6536(%rbp), rax
  movq -6536(%rbp), %rax
  movq -1272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6544(%rbp)
  movq -6544(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6552(%rbp)
  movq -6552(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3069
  jmp main_pr_str_0_3069
main_pr_nil_0_3069:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6560(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6560(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6568(%rbp)
  jmp main_pr_next_0_3069
main_pr_str_0_3069:
  movq -6544(%rbp), %rax
  addq $8, %rax
  movq %rax, -6576(%rbp)
  movq -6576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6584(%rbp)
  movq -6544(%rbp), %rax
  addq $24, %rax
  movq %rax, -6592(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6592(%rbp), %rsi
  movq -6584(%rbp), %rdx
  syscall
  movq %rax, -6600(%rbp)
  jmp main_pr_next_0_3069
main_pr_next_0_3069:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6608(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6608(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6616(%rbp)
  movq $0, %rax
  movq -1288(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_38(%rip), %rax
  movq -1304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6624(%rbp)
  movq -1240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6632(%rbp)
  movq -6624(%rbp), %rdi
  movq -6632(%rbp), %rsi
  call lm_rt_str_format
  mov -6640(%rbp), rax
  movq -6640(%rbp), %rax
  movq -1296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6648(%rbp)
  movq -6648(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6656(%rbp)
  movq -6656(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8167
  jmp main_pr_str_0_8167
main_pr_nil_0_8167:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6664(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6664(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6672(%rbp)
  jmp main_pr_next_0_8167
main_pr_str_0_8167:
  movq -6648(%rbp), %rax
  addq $8, %rax
  movq %rax, -6680(%rbp)
  movq -6680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6688(%rbp)
  movq -6648(%rbp), %rax
  addq $24, %rax
  movq %rax, -6696(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6696(%rbp), %rsi
  movq -6688(%rbp), %rdx
  syscall
  movq %rax, -6704(%rbp)
  jmp main_pr_next_0_8167
main_pr_next_0_8167:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6712(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6712(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6720(%rbp)
  movq $0, %rax
  movq -1312(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_39(%rip), %rax
  movq -1320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6728(%rbp)
  movq -6728(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6736(%rbp)
  movq -6736(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1393
  jmp main_pr_str_0_1393
main_pr_nil_0_1393:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6744(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6744(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6752(%rbp)
  jmp main_pr_next_0_1393
main_pr_str_0_1393:
  movq -6728(%rbp), %rax
  addq $8, %rax
  movq %rax, -6760(%rbp)
  movq -6760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6768(%rbp)
  movq -6728(%rbp), %rax
  addq $24, %rax
  movq %rax, -6776(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6776(%rbp), %rsi
  movq -6768(%rbp), %rdx
  syscall
  movq %rax, -6784(%rbp)
  jmp main_pr_next_0_1393
main_pr_next_0_1393:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6792(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6792(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6800(%rbp)
  movq $0, %rax
  movq -1328(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -1336(%rbp), %rdx
  movq %rax, (%rdx)
  movq $64, %rax
  movq -1344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $9, %rax
  movq -1352(%rbp), %rdx
  movq %rax, (%rdx)
  movq $30, %rax
  movq -1360(%rbp), %rdx
  movq %rax, (%rdx)
  movq $500, %rax
  movq -1368(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_40(%rip), %rax
  movq -1384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6808(%rbp)
  movq -1336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6816(%rbp)
  movq -6808(%rbp), %rdi
  movq -6816(%rbp), %rsi
  call lm_rt_str_format
  mov -6824(%rbp), rax
  movq -6824(%rbp), %rax
  movq -1376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6832(%rbp)
  movq -6832(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6840(%rbp)
  movq -6840(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8456
  jmp main_pr_str_0_8456
main_pr_nil_0_8456:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6848(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6848(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6856(%rbp)
  jmp main_pr_next_0_8456
main_pr_str_0_8456:
  movq -6832(%rbp), %rax
  addq $8, %rax
  movq %rax, -6864(%rbp)
  movq -6864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6872(%rbp)
  movq -6832(%rbp), %rax
  addq $24, %rax
  movq %rax, -6880(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6880(%rbp), %rsi
  movq -6872(%rbp), %rdx
  syscall
  movq %rax, -6888(%rbp)
  jmp main_pr_next_0_8456
main_pr_next_0_8456:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6896(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6896(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6904(%rbp)
  movq $0, %rax
  movq -1392(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_41(%rip), %rax
  movq -1408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6912(%rbp)
  movq -1344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6920(%rbp)
  movq -6912(%rbp), %rdi
  movq -6920(%rbp), %rsi
  call lm_rt_str_format
  mov -6928(%rbp), rax
  movq -6928(%rbp), %rax
  movq -1400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6936(%rbp)
  movq -6936(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6944(%rbp)
  movq -6944(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5011
  jmp main_pr_str_0_5011
main_pr_nil_0_5011:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6952(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6952(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6960(%rbp)
  jmp main_pr_next_0_5011
main_pr_str_0_5011:
  movq -6936(%rbp), %rax
  addq $8, %rax
  movq %rax, -6968(%rbp)
  movq -6968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6976(%rbp)
  movq -6936(%rbp), %rax
  addq $24, %rax
  movq %rax, -6984(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6984(%rbp), %rsi
  movq -6976(%rbp), %rdx
  syscall
  movq %rax, -6992(%rbp)
  jmp main_pr_next_0_5011
main_pr_next_0_5011:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7000(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7000(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7008(%rbp)
  movq $0, %rax
  movq -1416(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_42(%rip), %rax
  movq -1432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7016(%rbp)
  movq -1352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7024(%rbp)
  movq -7016(%rbp), %rdi
  movq -7024(%rbp), %rsi
  call lm_rt_str_format
  mov -7032(%rbp), rax
  movq -7032(%rbp), %rax
  movq -1424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7040(%rbp)
  movq -7040(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7048(%rbp)
  movq -7048(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8042
  jmp main_pr_str_0_8042
main_pr_nil_0_8042:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7056(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7056(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7064(%rbp)
  jmp main_pr_next_0_8042
main_pr_str_0_8042:
  movq -7040(%rbp), %rax
  addq $8, %rax
  movq %rax, -7072(%rbp)
  movq -7072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7080(%rbp)
  movq -7040(%rbp), %rax
  addq $24, %rax
  movq %rax, -7088(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7088(%rbp), %rsi
  movq -7080(%rbp), %rdx
  syscall
  movq %rax, -7096(%rbp)
  jmp main_pr_next_0_8042
main_pr_next_0_8042:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7104(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7104(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7112(%rbp)
  movq $0, %rax
  movq -1440(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_43(%rip), %rax
  movq -1456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7120(%rbp)
  movq -1360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7128(%rbp)
  movq -7120(%rbp), %rdi
  movq -7128(%rbp), %rsi
  call lm_rt_str_format
  mov -7136(%rbp), rax
  movq -7136(%rbp), %rax
  movq -1448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7144(%rbp)
  movq -7144(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7152(%rbp)
  movq -7152(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6229
  jmp main_pr_str_0_6229
main_pr_nil_0_6229:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7160(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7168(%rbp)
  jmp main_pr_next_0_6229
main_pr_str_0_6229:
  movq -7144(%rbp), %rax
  addq $8, %rax
  movq %rax, -7176(%rbp)
  movq -7176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7184(%rbp)
  movq -7144(%rbp), %rax
  addq $24, %rax
  movq %rax, -7192(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7192(%rbp), %rsi
  movq -7184(%rbp), %rdx
  syscall
  movq %rax, -7200(%rbp)
  jmp main_pr_next_0_6229
main_pr_next_0_6229:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7208(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7208(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7216(%rbp)
  movq $0, %rax
  movq -1464(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_44(%rip), %rax
  movq -1480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7224(%rbp)
  movq -1368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7232(%rbp)
  movq -7224(%rbp), %rdi
  movq -7232(%rbp), %rsi
  call lm_rt_str_format
  mov -7240(%rbp), rax
  movq -7240(%rbp), %rax
  movq -1472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7248(%rbp)
  movq -7248(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7256(%rbp)
  movq -7256(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7373
  jmp main_pr_str_0_7373
main_pr_nil_0_7373:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7264(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7264(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7272(%rbp)
  jmp main_pr_next_0_7373
main_pr_str_0_7373:
  movq -7248(%rbp), %rax
  addq $8, %rax
  movq %rax, -7280(%rbp)
  movq -7280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7288(%rbp)
  movq -7248(%rbp), %rax
  addq $24, %rax
  movq %rax, -7296(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7296(%rbp), %rsi
  movq -7288(%rbp), %rdx
  syscall
  movq %rax, -7304(%rbp)
  jmp main_pr_next_0_7373
main_pr_next_0_7373:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7312(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7312(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7320(%rbp)
  movq $0, %rax
  movq -1488(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_45(%rip), %rax
  movq -1496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7328(%rbp)
  movq -7328(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7336(%rbp)
  movq -7336(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_4421
  jmp main_pr_str_0_4421
main_pr_nil_0_4421:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7344(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7352(%rbp)
  jmp main_pr_next_0_4421
main_pr_str_0_4421:
  movq -7328(%rbp), %rax
  addq $8, %rax
  movq %rax, -7360(%rbp)
  movq -7360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7368(%rbp)
  movq -7328(%rbp), %rax
  addq $24, %rax
  movq %rax, -7376(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7376(%rbp), %rsi
  movq -7368(%rbp), %rdx
  syscall
  movq %rax, -7384(%rbp)
  jmp main_pr_next_0_4421
main_pr_next_0_4421:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7392(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7392(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7400(%rbp)
  movq $0, %rax
  movq -1504(%rbp), %rdx
  movq %rax, (%rdx)
  movq $50, %rax
  movq -1512(%rbp), %rdx
  movq %rax, (%rdx)
  movq $99, %rax
  movq -1520(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_46(%rip), %rax
  movq -1536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7408(%rbp)
  movq -1512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7416(%rbp)
  movq -7408(%rbp), %rdi
  movq -7416(%rbp), %rsi
  call lm_rt_str_format
  mov -7424(%rbp), rax
  movq -7424(%rbp), %rax
  movq -1528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7432(%rbp)
  movq -7432(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7440(%rbp)
  movq -7440(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_4919
  jmp main_pr_str_0_4919
main_pr_nil_0_4919:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7448(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7448(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7456(%rbp)
  jmp main_pr_next_0_4919
main_pr_str_0_4919:
  movq -7432(%rbp), %rax
  addq $8, %rax
  movq %rax, -7464(%rbp)
  movq -7464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7472(%rbp)
  movq -7432(%rbp), %rax
  addq $24, %rax
  movq %rax, -7480(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7480(%rbp), %rsi
  movq -7472(%rbp), %rdx
  syscall
  movq %rax, -7488(%rbp)
  jmp main_pr_next_0_4919
main_pr_next_0_4919:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7496(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7496(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7504(%rbp)
  movq $0, %rax
  movq -1544(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_47(%rip), %rax
  movq -1560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7512(%rbp)
  movq -1520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7520(%rbp)
  movq -7512(%rbp), %rdi
  movq -7520(%rbp), %rsi
  call lm_rt_str_format
  mov -7528(%rbp), rax
  movq -7528(%rbp), %rax
  movq -1552(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7536(%rbp)
  movq -7536(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7544(%rbp)
  movq -7544(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3784
  jmp main_pr_str_0_3784
main_pr_nil_0_3784:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7552(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7552(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7560(%rbp)
  jmp main_pr_next_0_3784
main_pr_str_0_3784:
  movq -7536(%rbp), %rax
  addq $8, %rax
  movq %rax, -7568(%rbp)
  movq -7568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7576(%rbp)
  movq -7536(%rbp), %rax
  addq $24, %rax
  movq %rax, -7584(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7584(%rbp), %rsi
  movq -7576(%rbp), %rdx
  syscall
  movq %rax, -7592(%rbp)
  jmp main_pr_next_0_3784
main_pr_next_0_3784:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7600(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7600(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7608(%rbp)
  movq $0, %rax
  movq -1568(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_48(%rip), %rax
  movq -1576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7616(%rbp)
  movq -7616(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7624(%rbp)
  movq -7624(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8537
  jmp main_pr_str_0_8537
main_pr_nil_0_8537:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7632(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7632(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7640(%rbp)
  jmp main_pr_next_0_8537
main_pr_str_0_8537:
  movq -7616(%rbp), %rax
  addq $8, %rax
  movq %rax, -7648(%rbp)
  movq -7648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7656(%rbp)
  movq -7616(%rbp), %rax
  addq $24, %rax
  movq %rax, -7664(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7664(%rbp), %rsi
  movq -7656(%rbp), %rdx
  syscall
  movq %rax, -7672(%rbp)
  jmp main_pr_next_0_8537
main_pr_next_0_8537:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7680(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7680(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7688(%rbp)
  movq $0, %rax
  movq -1584(%rbp), %rdx
  movq %rax, (%rdx)
  movq $42, %rax
  movq -1592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7696(%rbp)
  movq -7696(%rbp), %rdi
  call isPositive
  mov -7704(%rbp), rax
  movq -7704(%rbp), %rax
  movq -1600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7712(%rbp)
  movq -7712(%rbp), %rax
  movq -1608(%rbp), %rdx
  movq %rax, (%rdx)
  movq $500, %rax
  movq -1616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7720(%rbp)
  movq -7720(%rbp), %rdi
  call isLarge
  mov -7728(%rbp), rax
  movq -7728(%rbp), %rax
  movq -1624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7736(%rbp)
  movq -7736(%rbp), %rax
  movq -1632(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_49(%rip), %rax
  movq -1648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7744(%rbp)
  movq -1608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7752(%rbp)
  movq -7752(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -7760(%rbp)
  movq -7760(%rbp), %rax
  testq %rax, %rax
  jne main_b2s_t_1
  jmp main_b2s_f_1
main_b2s_t_1:
  movq str_true(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -7768(%rbp)
  jmp main_b2s_d_1
main_b2s_f_1:
  movq str_false(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -7768(%rbp)
  jmp main_b2s_d_1
main_b2s_d_1:
  movq -7744(%rbp), %rdi
  movq -7768(%rbp), %rsi
  call lm_rt_str_format
  mov -7776(%rbp), rax
  movq -7776(%rbp), %rax
  movq -1640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7784(%rbp)
  movq -7784(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7792(%rbp)
  movq -7792(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5198
  jmp main_pr_str_0_5198
main_pr_nil_0_5198:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7800(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7800(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7808(%rbp)
  jmp main_pr_next_0_5198
main_pr_str_0_5198:
  movq -7784(%rbp), %rax
  addq $8, %rax
  movq %rax, -7816(%rbp)
  movq -7816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7824(%rbp)
  movq -7784(%rbp), %rax
  addq $24, %rax
  movq %rax, -7832(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7832(%rbp), %rsi
  movq -7824(%rbp), %rdx
  syscall
  movq %rax, -7840(%rbp)
  jmp main_pr_next_0_5198
main_pr_next_0_5198:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7848(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7848(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7856(%rbp)
  movq $0, %rax
  movq -1656(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_50(%rip), %rax
  movq -1672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7864(%rbp)
  movq -1632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7872(%rbp)
  movq -7872(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -7880(%rbp)
  movq -7880(%rbp), %rax
  testq %rax, %rax
  jne main_b2s_t_2
  jmp main_b2s_f_2
main_b2s_t_2:
  movq str_true(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -7888(%rbp)
  jmp main_b2s_d_2
main_b2s_f_2:
  movq str_false(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -7888(%rbp)
  jmp main_b2s_d_2
main_b2s_d_2:
  movq -7864(%rbp), %rdi
  movq -7888(%rbp), %rsi
  call lm_rt_str_format
  mov -7896(%rbp), rax
  movq -7896(%rbp), %rax
  movq -1664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7904(%rbp)
  movq -7904(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7912(%rbp)
  movq -7912(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_4324
  jmp main_pr_str_0_4324
main_pr_nil_0_4324:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7920(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7920(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7928(%rbp)
  jmp main_pr_next_0_4324
main_pr_str_0_4324:
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
  jmp main_pr_next_0_4324
main_pr_next_0_4324:
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
  movq -1680(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_51(%rip), %rax
  movq -1688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7984(%rbp)
  movq -7984(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7992(%rbp)
  movq -7992(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8315
  jmp main_pr_str_0_8315
main_pr_nil_0_8315:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8000(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8000(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8008(%rbp)
  jmp main_pr_next_0_8315
main_pr_str_0_8315:
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
  jmp main_pr_next_0_8315
main_pr_next_0_8315:
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
  movq -1696(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -1704(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -1712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8064(%rbp)
  movq -8064(%rbp), %rax
  negq %rax
  movq %rax, -8072(%rbp)
  movq -8072(%rbp), %rax
  movq -1720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8080(%rbp)
  movq -8080(%rbp), %rax
  movq -1728(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2000, %rax
  movq -1736(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_52(%rip), %rax
  movq -1752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8088(%rbp)
  movq -1704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8096(%rbp)
  movq -8088(%rbp), %rdi
  movq -8096(%rbp), %rsi
  call lm_rt_str_format
  mov -8104(%rbp), rax
  movq -8104(%rbp), %rax
  movq -1744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8112(%rbp)
  movq -8112(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8120(%rbp)
  movq -8120(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_4370
  jmp main_pr_str_0_4370
main_pr_nil_0_4370:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8128(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8128(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8136(%rbp)
  jmp main_pr_next_0_4370
main_pr_str_0_4370:
  movq -8112(%rbp), %rax
  addq $8, %rax
  movq %rax, -8144(%rbp)
  movq -8144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8152(%rbp)
  movq -8112(%rbp), %rax
  addq $24, %rax
  movq %rax, -8160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8160(%rbp), %rsi
  movq -8152(%rbp), %rdx
  syscall
  movq %rax, -8168(%rbp)
  jmp main_pr_next_0_4370
main_pr_next_0_4370:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8176(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8176(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8184(%rbp)
  movq $0, %rax
  movq -1760(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_53(%rip), %rax
  movq -1776(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8192(%rbp)
  movq -1728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8200(%rbp)
  movq -8192(%rbp), %rdi
  movq -8200(%rbp), %rsi
  call lm_rt_str_format
  mov -8208(%rbp), rax
  movq -8208(%rbp), %rax
  movq -1768(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8216(%rbp)
  movq -8216(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8224(%rbp)
  movq -8224(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6413
  jmp main_pr_str_0_6413
main_pr_nil_0_6413:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8232(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8232(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8240(%rbp)
  jmp main_pr_next_0_6413
main_pr_str_0_6413:
  movq -8216(%rbp), %rax
  addq $8, %rax
  movq %rax, -8248(%rbp)
  movq -8248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8256(%rbp)
  movq -8216(%rbp), %rax
  addq $24, %rax
  movq %rax, -8264(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8264(%rbp), %rsi
  movq -8256(%rbp), %rdx
  syscall
  movq %rax, -8272(%rbp)
  jmp main_pr_next_0_6413
main_pr_next_0_6413:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8280(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8280(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8288(%rbp)
  movq $0, %rax
  movq -1784(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_54(%rip), %rax
  movq -1800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8296(%rbp)
  movq -1736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8304(%rbp)
  movq -8296(%rbp), %rdi
  movq -8304(%rbp), %rsi
  call lm_rt_str_format
  mov -8312(%rbp), rax
  movq -8312(%rbp), %rax
  movq -1792(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8320(%rbp)
  movq -8320(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8328(%rbp)
  movq -8328(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3526
  jmp main_pr_str_0_3526
main_pr_nil_0_3526:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8336(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8336(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8344(%rbp)
  jmp main_pr_next_0_3526
main_pr_str_0_3526:
  movq -8320(%rbp), %rax
  addq $8, %rax
  movq %rax, -8352(%rbp)
  movq -8352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8360(%rbp)
  movq -8320(%rbp), %rax
  addq $24, %rax
  movq %rax, -8368(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8368(%rbp), %rsi
  movq -8360(%rbp), %rdx
  syscall
  movq %rax, -8376(%rbp)
  jmp main_pr_next_0_3526
main_pr_next_0_3526:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8384(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8384(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8392(%rbp)
  movq $0, %rax
  movq -1808(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_55(%rip), %rax
  movq -1816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8400(%rbp)
  movq -8400(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8408(%rbp)
  movq -8408(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6091
  jmp main_pr_str_0_6091
main_pr_nil_0_6091:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8416(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8416(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8424(%rbp)
  jmp main_pr_next_0_6091
main_pr_str_0_6091:
  movq -8400(%rbp), %rax
  addq $8, %rax
  movq %rax, -8432(%rbp)
  movq -8432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8440(%rbp)
  movq -8400(%rbp), %rax
  addq $24, %rax
  movq %rax, -8448(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8448(%rbp), %rsi
  movq -8440(%rbp), %rdx
  syscall
  movq %rax, -8456(%rbp)
  jmp main_pr_next_0_6091
main_pr_next_0_6091:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8464(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8464(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8472(%rbp)
  movq $0, %rax
  movq -1824(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -1832(%rbp), %rdx
  movq %rax, (%rdx)
  movq $25, %rax
  movq -1840(%rbp), %rdx
  movq %rax, (%rdx)
  movq $7, %rax
  movq -1848(%rbp), %rdx
  movq %rax, (%rdx)
  movq $13, %rax
  movq -1856(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_56(%rip), %rax
  movq -1872(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8480(%rbp)
  movq -1832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8488(%rbp)
  movq -8480(%rbp), %rdi
  movq -8488(%rbp), %rsi
  call lm_rt_str_format
  mov -8496(%rbp), rax
  movq -8496(%rbp), %rax
  movq -1864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8504(%rbp)
  movq -8504(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8512(%rbp)
  movq -8512(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8980
  jmp main_pr_str_0_8980
main_pr_nil_0_8980:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8520(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8520(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8528(%rbp)
  jmp main_pr_next_0_8980
main_pr_str_0_8980:
  movq -8504(%rbp), %rax
  addq $8, %rax
  movq %rax, -8536(%rbp)
  movq -8536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8544(%rbp)
  movq -8504(%rbp), %rax
  addq $24, %rax
  movq %rax, -8552(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8552(%rbp), %rsi
  movq -8544(%rbp), %rdx
  syscall
  movq %rax, -8560(%rbp)
  jmp main_pr_next_0_8980
main_pr_next_0_8980:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8568(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8568(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8576(%rbp)
  movq $0, %rax
  movq -1880(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_57(%rip), %rax
  movq -1896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8584(%rbp)
  movq -1840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8592(%rbp)
  movq -8584(%rbp), %rdi
  movq -8592(%rbp), %rsi
  call lm_rt_str_format
  mov -8600(%rbp), rax
  movq -8600(%rbp), %rax
  movq -1888(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8608(%rbp)
  movq -8608(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8616(%rbp)
  movq -8616(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9956
  jmp main_pr_str_0_9956
main_pr_nil_0_9956:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8624(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8624(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8632(%rbp)
  jmp main_pr_next_0_9956
main_pr_str_0_9956:
  movq -8608(%rbp), %rax
  addq $8, %rax
  movq %rax, -8640(%rbp)
  movq -8640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8648(%rbp)
  movq -8608(%rbp), %rax
  addq $24, %rax
  movq %rax, -8656(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8656(%rbp), %rsi
  movq -8648(%rbp), %rdx
  syscall
  movq %rax, -8664(%rbp)
  jmp main_pr_next_0_9956
main_pr_next_0_9956:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8672(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8672(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8680(%rbp)
  movq $0, %rax
  movq -1904(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_58(%rip), %rax
  movq -1920(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8688(%rbp)
  movq -1848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8696(%rbp)
  movq -8688(%rbp), %rdi
  movq -8696(%rbp), %rsi
  call lm_rt_str_format
  mov -8704(%rbp), rax
  movq -8704(%rbp), %rax
  movq -1912(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8712(%rbp)
  movq -8712(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8720(%rbp)
  movq -8720(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1873
  jmp main_pr_str_0_1873
main_pr_nil_0_1873:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8728(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8728(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8736(%rbp)
  jmp main_pr_next_0_1873
main_pr_str_0_1873:
  movq -8712(%rbp), %rax
  addq $8, %rax
  movq %rax, -8744(%rbp)
  movq -8744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8752(%rbp)
  movq -8712(%rbp), %rax
  addq $24, %rax
  movq %rax, -8760(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8760(%rbp), %rsi
  movq -8752(%rbp), %rdx
  syscall
  movq %rax, -8768(%rbp)
  jmp main_pr_next_0_1873
main_pr_next_0_1873:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8776(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8776(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8784(%rbp)
  movq $0, %rax
  movq -1928(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_59(%rip), %rax
  movq -1944(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8792(%rbp)
  movq -1856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8800(%rbp)
  movq -8792(%rbp), %rdi
  movq -8800(%rbp), %rsi
  call lm_rt_str_format
  mov -8808(%rbp), rax
  movq -8808(%rbp), %rax
  movq -1936(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8816(%rbp)
  movq -8816(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8824(%rbp)
  movq -8824(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6862
  jmp main_pr_str_0_6862
main_pr_nil_0_6862:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8832(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8832(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8840(%rbp)
  jmp main_pr_next_0_6862
main_pr_str_0_6862:
  movq -8816(%rbp), %rax
  addq $8, %rax
  movq %rax, -8848(%rbp)
  movq -8848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8856(%rbp)
  movq -8816(%rbp), %rax
  addq $24, %rax
  movq %rax, -8864(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8864(%rbp), %rsi
  movq -8856(%rbp), %rdx
  syscall
  movq %rax, -8872(%rbp)
  jmp main_pr_next_0_6862
main_pr_next_0_6862:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8880(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8880(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8888(%rbp)
  movq $0, %rax
  movq -1952(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_60(%rip), %rax
  movq -1960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8896(%rbp)
  movq -8896(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8904(%rbp)
  movq -8904(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9170
  jmp main_pr_str_0_9170
main_pr_nil_0_9170:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8912(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8912(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8920(%rbp)
  jmp main_pr_next_0_9170
main_pr_str_0_9170:
  movq -8896(%rbp), %rax
  addq $8, %rax
  movq %rax, -8928(%rbp)
  movq -8928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8936(%rbp)
  movq -8896(%rbp), %rax
  addq $24, %rax
  movq %rax, -8944(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8944(%rbp), %rsi
  movq -8936(%rbp), %rdx
  syscall
  movq %rax, -8952(%rbp)
  jmp main_pr_next_0_9170
main_pr_next_0_9170:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8960(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8960(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8968(%rbp)
  movq $0, %rax
  movq -1968(%rbp), %rdx
  movq %rax, (%rdx)
  call lm_dict_new
  mov -8976(%rbp), rax
  movq -8976(%rbp), %rax
  movq -1976(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_61(%rip), %rax
  movq -1984(%rbp), %rdx
  movq %rax, (%rdx)
  movq $25, %rax
  movq -1992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8984(%rbp)
  movq -1984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8992(%rbp)
  movq -1992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9000(%rbp)
  movq -8984(%rbp), %rdi
  movq -8992(%rbp), %rsi
  movq -9000(%rbp), %rdx
  call lm_dict_set
  mov -9008(%rbp), rax
  leaq str_hdr_62(%rip), %rax
  movq -2000(%rbp), %rdx
  movq %rax, (%rdx)
  movq $30, %rax
  movq -2008(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9016(%rbp)
  movq -2000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9024(%rbp)
  movq -2008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9032(%rbp)
  movq -9016(%rbp), %rdi
  movq -9024(%rbp), %rsi
  movq -9032(%rbp), %rdx
  call lm_dict_set
  mov -9040(%rbp), rax
  leaq str_hdr_63(%rip), %rax
  movq -2016(%rbp), %rdx
  movq %rax, (%rdx)
  movq $35, %rax
  movq -2024(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9048(%rbp)
  movq -2016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9056(%rbp)
  movq -2024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9064(%rbp)
  movq -9048(%rbp), %rdi
  movq -9056(%rbp), %rsi
  movq -9064(%rbp), %rdx
  call lm_dict_set
  mov -9072(%rbp), rax
  movq -1976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9080(%rbp)
  movq -9080(%rbp), %rax
  movq -2032(%rbp), %rdx
  movq %rax, (%rdx)
  call lm_dict_new
  mov -9088(%rbp), rax
  movq -9088(%rbp), %rax
  movq -2040(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_64(%rip), %rax
  movq -2048(%rbp), %rdx
  movq %rax, (%rdx)
  movq $100, %rax
  movq -2056(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9096(%rbp)
  movq -2048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9104(%rbp)
  movq -2056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9112(%rbp)
  movq -9096(%rbp), %rdi
  movq -9104(%rbp), %rsi
  movq -9112(%rbp), %rdx
  call lm_dict_set
  mov -9120(%rbp), rax
  leaq str_hdr_65(%rip), %rax
  movq -2064(%rbp), %rdx
  movq %rax, (%rdx)
  movq $250, %rax
  movq -2072(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9128(%rbp)
  movq -2064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9136(%rbp)
  movq -2072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9144(%rbp)
  movq -9128(%rbp), %rdi
  movq -9136(%rbp), %rsi
  movq -9144(%rbp), %rdx
  call lm_dict_set
  mov -9152(%rbp), rax
  movq -2040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9160(%rbp)
  movq -9160(%rbp), %rax
  movq -2080(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_66(%rip), %rax
  movq -2096(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9168(%rbp)
  movq -2032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9176(%rbp)
  movq -9168(%rbp), %rdi
  movq -9176(%rbp), %rsi
  call lm_rt_str_format
  mov -9184(%rbp), rax
  movq -9184(%rbp), %rax
  movq -2088(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9192(%rbp)
  movq -9192(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9200(%rbp)
  movq -9200(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6996
  jmp main_pr_str_0_6996
main_pr_nil_0_6996:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9208(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9208(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9216(%rbp)
  jmp main_pr_next_0_6996
main_pr_str_0_6996:
  movq -9192(%rbp), %rax
  addq $8, %rax
  movq %rax, -9224(%rbp)
  movq -9224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9232(%rbp)
  movq -9192(%rbp), %rax
  addq $24, %rax
  movq %rax, -9240(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9240(%rbp), %rsi
  movq -9232(%rbp), %rdx
  syscall
  movq %rax, -9248(%rbp)
  jmp main_pr_next_0_6996
main_pr_next_0_6996:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9256(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9256(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9264(%rbp)
  movq $0, %rax
  movq -2104(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_67(%rip), %rax
  movq -2120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9272(%rbp)
  movq -2080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9280(%rbp)
  movq -9272(%rbp), %rdi
  movq -9280(%rbp), %rsi
  call lm_rt_str_format
  mov -9288(%rbp), rax
  movq -9288(%rbp), %rax
  movq -2112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9296(%rbp)
  movq -9296(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9304(%rbp)
  movq -9304(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7281
  jmp main_pr_str_0_7281
main_pr_nil_0_7281:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9312(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9312(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9320(%rbp)
  jmp main_pr_next_0_7281
main_pr_str_0_7281:
  movq -9296(%rbp), %rax
  addq $8, %rax
  movq %rax, -9328(%rbp)
  movq -9328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9336(%rbp)
  movq -9296(%rbp), %rax
  addq $24, %rax
  movq %rax, -9344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9344(%rbp), %rsi
  movq -9336(%rbp), %rdx
  syscall
  movq %rax, -9352(%rbp)
  jmp main_pr_next_0_7281
main_pr_next_0_7281:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9360(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9360(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9368(%rbp)
  movq $0, %rax
  movq -2128(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_68(%rip), %rax
  movq -2136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9376(%rbp)
  movq -9376(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9384(%rbp)
  movq -9384(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2305
  jmp main_pr_str_0_2305
main_pr_nil_0_2305:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9392(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9392(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9400(%rbp)
  jmp main_pr_next_0_2305
main_pr_str_0_2305:
  movq -9376(%rbp), %rax
  addq $8, %rax
  movq %rax, -9408(%rbp)
  movq -9408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9416(%rbp)
  movq -9376(%rbp), %rax
  addq $24, %rax
  movq %rax, -9424(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9424(%rbp), %rsi
  movq -9416(%rbp), %rdx
  syscall
  movq %rax, -9432(%rbp)
  jmp main_pr_next_0_2305
main_pr_next_0_2305:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9440(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9440(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9448(%rbp)
  movq $0, %rax
  movq -2144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $50, %rax
  movq -2152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $75, %rax
  movq -2160(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_69(%rip), %rax
  movq -2176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9456(%rbp)
  movq -2152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9464(%rbp)
  movq -9456(%rbp), %rdi
  movq -9464(%rbp), %rsi
  call lm_rt_str_format
  mov -9472(%rbp), rax
  movq -9472(%rbp), %rax
  movq -2168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9480(%rbp)
  movq -9480(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9488(%rbp)
  movq -9488(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_925
  jmp main_pr_str_0_925
main_pr_nil_0_925:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9496(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9496(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9504(%rbp)
  jmp main_pr_next_0_925
main_pr_str_0_925:
  movq -9480(%rbp), %rax
  addq $8, %rax
  movq %rax, -9512(%rbp)
  movq -9512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9520(%rbp)
  movq -9480(%rbp), %rax
  addq $24, %rax
  movq %rax, -9528(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9528(%rbp), %rsi
  movq -9520(%rbp), %rdx
  syscall
  movq %rax, -9536(%rbp)
  jmp main_pr_next_0_925
main_pr_next_0_925:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9544(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9552(%rbp)
  movq $0, %rax
  movq -2184(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_70(%rip), %rax
  movq -2200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9560(%rbp)
  movq -2160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9568(%rbp)
  movq -9560(%rbp), %rdi
  movq -9568(%rbp), %rsi
  call lm_rt_str_format
  mov -9576(%rbp), rax
  movq -9576(%rbp), %rax
  movq -2192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9584(%rbp)
  movq -9584(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9592(%rbp)
  movq -9592(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7084
  jmp main_pr_str_0_7084
main_pr_nil_0_7084:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9600(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9600(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9608(%rbp)
  jmp main_pr_next_0_7084
main_pr_str_0_7084:
  movq -9584(%rbp), %rax
  addq $8, %rax
  movq %rax, -9616(%rbp)
  movq -9616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9624(%rbp)
  movq -9584(%rbp), %rax
  addq $24, %rax
  movq %rax, -9632(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9632(%rbp), %rsi
  movq -9624(%rbp), %rdx
  syscall
  movq %rax, -9640(%rbp)
  jmp main_pr_next_0_7084
main_pr_next_0_7084:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9648(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9648(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9656(%rbp)
  movq $0, %rax
  movq -2208(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_71(%rip), %rax
  movq -2216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9664(%rbp)
  movq -9664(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9672(%rbp)
  movq -9672(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6327
  jmp main_pr_str_0_6327
main_pr_nil_0_6327:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9680(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9680(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9688(%rbp)
  jmp main_pr_next_0_6327
main_pr_str_0_6327:
  movq -9664(%rbp), %rax
  addq $8, %rax
  movq %rax, -9696(%rbp)
  movq -9696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9704(%rbp)
  movq -9664(%rbp), %rax
  addq $24, %rax
  movq %rax, -9712(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9712(%rbp), %rsi
  movq -9704(%rbp), %rdx
  syscall
  movq %rax, -9720(%rbp)
  jmp main_pr_next_0_6327
main_pr_next_0_6327:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9728(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9728(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9736(%rbp)
  movq $0, %rax
  movq -2224(%rbp), %rdx
  movq %rax, (%rdx)
  movq $15, %rax
  movq -2232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $250, %rax
  movq -2240(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_72(%rip), %rax
  movq -2256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9744(%rbp)
  movq -2232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9752(%rbp)
  movq -9744(%rbp), %rdi
  movq -9752(%rbp), %rsi
  call lm_rt_str_format
  mov -9760(%rbp), rax
  movq -9760(%rbp), %rax
  movq -2248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9768(%rbp)
  movq -9768(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9776(%rbp)
  movq -9776(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_336
  jmp main_pr_str_0_336
main_pr_nil_0_336:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9784(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9784(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9792(%rbp)
  jmp main_pr_next_0_336
main_pr_str_0_336:
  movq -9768(%rbp), %rax
  addq $8, %rax
  movq %rax, -9800(%rbp)
  movq -9800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9808(%rbp)
  movq -9768(%rbp), %rax
  addq $24, %rax
  movq %rax, -9816(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9816(%rbp), %rsi
  movq -9808(%rbp), %rdx
  syscall
  movq %rax, -9824(%rbp)
  jmp main_pr_next_0_336
main_pr_next_0_336:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9832(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9832(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9840(%rbp)
  movq $0, %rax
  movq -2264(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_73(%rip), %rax
  movq -2280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9848(%rbp)
  movq -2240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9856(%rbp)
  movq -9848(%rbp), %rdi
  movq -9856(%rbp), %rsi
  call lm_rt_str_format
  mov -9864(%rbp), rax
  movq -9864(%rbp), %rax
  movq -2272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9872(%rbp)
  movq -9872(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9880(%rbp)
  movq -9880(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6505
  jmp main_pr_str_0_6505
main_pr_nil_0_6505:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9888(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9888(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9896(%rbp)
  jmp main_pr_next_0_6505
main_pr_str_0_6505:
  movq -9872(%rbp), %rax
  addq $8, %rax
  movq %rax, -9904(%rbp)
  movq -9904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9912(%rbp)
  movq -9872(%rbp), %rax
  addq $24, %rax
  movq %rax, -9920(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9920(%rbp), %rsi
  movq -9912(%rbp), %rdx
  syscall
  movq %rax, -9928(%rbp)
  jmp main_pr_next_0_6505
main_pr_next_0_6505:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -9936(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9936(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -9944(%rbp)
  movq $0, %rax
  movq -2288(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_74(%rip), %rax
  movq -2296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9952(%rbp)
  movq -9952(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9960(%rbp)
  movq -9960(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_846
  jmp main_pr_str_0_846
main_pr_nil_0_846:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9968(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9968(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9976(%rbp)
  jmp main_pr_next_0_846
main_pr_str_0_846:
  movq -9952(%rbp), %rax
  addq $8, %rax
  movq %rax, -9984(%rbp)
  movq -9984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9992(%rbp)
  movq -9952(%rbp), %rax
  addq $24, %rax
  movq %rax, -10000(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10000(%rbp), %rsi
  movq -9992(%rbp), %rdx
  syscall
  movq %rax, -10008(%rbp)
  jmp main_pr_next_0_846
main_pr_next_0_846:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10016(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10016(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10024(%rbp)
  movq $0, %rax
  movq -2304(%rbp), %rdx
  movq %rax, (%rdx)
  movq $150, %rax
  movq -2312(%rbp), %rdx
  movq %rax, (%rdx)
  movq $20, %rax
  movq -2320(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_75(%rip), %rax
  movq -2336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10032(%rbp)
  movq -2312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10040(%rbp)
  movq -10032(%rbp), %rdi
  movq -10040(%rbp), %rsi
  call lm_rt_str_format
  mov -10048(%rbp), rax
  movq -10048(%rbp), %rax
  movq -2328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10056(%rbp)
  movq -10056(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10064(%rbp)
  movq -10064(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1729
  jmp main_pr_str_0_1729
main_pr_nil_0_1729:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10072(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10072(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10080(%rbp)
  jmp main_pr_next_0_1729
main_pr_str_0_1729:
  movq -10056(%rbp), %rax
  addq $8, %rax
  movq %rax, -10088(%rbp)
  movq -10088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10096(%rbp)
  movq -10056(%rbp), %rax
  addq $24, %rax
  movq %rax, -10104(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10104(%rbp), %rsi
  movq -10096(%rbp), %rdx
  syscall
  movq %rax, -10112(%rbp)
  jmp main_pr_next_0_1729
main_pr_next_0_1729:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10120(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10120(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10128(%rbp)
  movq $0, %rax
  movq -2344(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_76(%rip), %rax
  movq -2360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10136(%rbp)
  movq -2320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10144(%rbp)
  movq -10136(%rbp), %rdi
  movq -10144(%rbp), %rsi
  call lm_rt_str_format
  mov -10152(%rbp), rax
  movq -10152(%rbp), %rax
  movq -2352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10160(%rbp)
  movq -10160(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10168(%rbp)
  movq -10168(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1313
  jmp main_pr_str_0_1313
main_pr_nil_0_1313:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10176(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10176(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10184(%rbp)
  jmp main_pr_next_0_1313
main_pr_str_0_1313:
  movq -10160(%rbp), %rax
  addq $8, %rax
  movq %rax, -10192(%rbp)
  movq -10192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10200(%rbp)
  movq -10160(%rbp), %rax
  addq $24, %rax
  movq %rax, -10208(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10208(%rbp), %rsi
  movq -10200(%rbp), %rdx
  syscall
  movq %rax, -10216(%rbp)
  jmp main_pr_next_0_1313
main_pr_next_0_1313:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10224(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10224(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10232(%rbp)
  movq $0, %rax
  movq -2368(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_77(%rip), %rax
  movq -2376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10240(%rbp)
  movq -10240(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10248(%rbp)
  movq -10248(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5857
  jmp main_pr_str_0_5857
main_pr_nil_0_5857:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10256(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10256(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10264(%rbp)
  jmp main_pr_next_0_5857
main_pr_str_0_5857:
  movq -10240(%rbp), %rax
  addq $8, %rax
  movq %rax, -10272(%rbp)
  movq -10272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10280(%rbp)
  movq -10240(%rbp), %rax
  addq $24, %rax
  movq %rax, -10288(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10288(%rbp), %rsi
  movq -10280(%rbp), %rdx
  syscall
  movq %rax, -10296(%rbp)
  jmp main_pr_next_0_5857
main_pr_next_0_5857:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10304(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10304(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10312(%rbp)
  movq $0, %rax
  movq -2384(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -2392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10320(%rbp)
  movq -10320(%rbp), %rdi
  call validatePositive
  mov -10328(%rbp), rax
  movq -10328(%rbp), %rax
  movq -2400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10336(%rbp)
  movq -10336(%rbp), %rax
  movq -2408(%rbp), %rdx
  movq %rax, (%rdx)
  movq $25, %rax
  movq -2416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10344(%rbp)
  movq -10344(%rbp), %rdi
  call validatePositive
  mov -10352(%rbp), rax
  movq -10352(%rbp), %rax
  movq -2424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10360(%rbp)
  movq -10360(%rbp), %rax
  movq -2432(%rbp), %rdx
  movq %rax, (%rdx)
  movq $100, %rax
  movq -2440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10368(%rbp)
  movq -10368(%rbp), %rdi
  call validatePositive
  mov -10376(%rbp), rax
  movq -10376(%rbp), %rax
  movq -2448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10384(%rbp)
  movq -10384(%rbp), %rax
  movq -2456(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_78(%rip), %rax
  movq -2472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10392(%rbp)
  movq -2408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10400(%rbp)
  movq -10392(%rbp), %rdi
  movq -10400(%rbp), %rsi
  call lm_rt_str_format
  mov -10408(%rbp), rax
  movq -10408(%rbp), %rax
  movq -2464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10416(%rbp)
  movq -10416(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10424(%rbp)
  movq -10424(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6124
  jmp main_pr_str_0_6124
main_pr_nil_0_6124:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10432(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10432(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10440(%rbp)
  jmp main_pr_next_0_6124
main_pr_str_0_6124:
  movq -10416(%rbp), %rax
  addq $8, %rax
  movq %rax, -10448(%rbp)
  movq -10448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10456(%rbp)
  movq -10416(%rbp), %rax
  addq $24, %rax
  movq %rax, -10464(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10464(%rbp), %rsi
  movq -10456(%rbp), %rdx
  syscall
  movq %rax, -10472(%rbp)
  jmp main_pr_next_0_6124
main_pr_next_0_6124:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10480(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10480(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10488(%rbp)
  movq $0, %rax
  movq -2480(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_79(%rip), %rax
  movq -2496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10496(%rbp)
  movq -2432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10504(%rbp)
  movq -10496(%rbp), %rdi
  movq -10504(%rbp), %rsi
  call lm_rt_str_format
  mov -10512(%rbp), rax
  movq -10512(%rbp), %rax
  movq -2488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10520(%rbp)
  movq -10520(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10528(%rbp)
  movq -10528(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3895
  jmp main_pr_str_0_3895
main_pr_nil_0_3895:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10536(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10536(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10544(%rbp)
  jmp main_pr_next_0_3895
main_pr_str_0_3895:
  movq -10520(%rbp), %rax
  addq $8, %rax
  movq %rax, -10552(%rbp)
  movq -10552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10560(%rbp)
  movq -10520(%rbp), %rax
  addq $24, %rax
  movq %rax, -10568(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10568(%rbp), %rsi
  movq -10560(%rbp), %rdx
  syscall
  movq %rax, -10576(%rbp)
  jmp main_pr_next_0_3895
main_pr_next_0_3895:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10584(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10584(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10592(%rbp)
  movq $0, %rax
  movq -2504(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_80(%rip), %rax
  movq -2520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10600(%rbp)
  movq -2456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10608(%rbp)
  movq -10600(%rbp), %rdi
  movq -10608(%rbp), %rsi
  call lm_rt_str_format
  mov -10616(%rbp), rax
  movq -10616(%rbp), %rax
  movq -2512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10624(%rbp)
  movq -10624(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10632(%rbp)
  movq -10632(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9582
  jmp main_pr_str_0_9582
main_pr_nil_0_9582:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10640(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10640(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10648(%rbp)
  jmp main_pr_next_0_9582
main_pr_str_0_9582:
  movq -10624(%rbp), %rax
  addq $8, %rax
  movq %rax, -10656(%rbp)
  movq -10656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10664(%rbp)
  movq -10624(%rbp), %rax
  addq $24, %rax
  movq %rax, -10672(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10672(%rbp), %rsi
  movq -10664(%rbp), %rdx
  syscall
  movq %rax, -10680(%rbp)
  jmp main_pr_next_0_9582
main_pr_next_0_9582:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10688(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10688(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10696(%rbp)
  movq $0, %rax
  movq -2528(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_81(%rip), %rax
  movq -2536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10704(%rbp)
  movq -10704(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10712(%rbp)
  movq -10712(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_545
  jmp main_pr_str_0_545
main_pr_nil_0_545:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10720(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10720(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10728(%rbp)
  jmp main_pr_next_0_545
main_pr_str_0_545:
  movq -10704(%rbp), %rax
  addq $8, %rax
  movq %rax, -10736(%rbp)
  movq -10736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10744(%rbp)
  movq -10704(%rbp), %rax
  addq $24, %rax
  movq %rax, -10752(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10752(%rbp), %rsi
  movq -10744(%rbp), %rdx
  syscall
  movq %rax, -10760(%rbp)
  jmp main_pr_next_0_545
main_pr_next_0_545:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10768(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10768(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10776(%rbp)
  movq $0, %rax
  movq -2544(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -2552(%rbp), %rdx
  movq %rax, (%rdx)
  movq $500, %rax
  movq -2560(%rbp), %rdx
  movq %rax, (%rdx)
  movq $200, %rax
  movq -2568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10784(%rbp)
  movq -2560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10792(%rbp)
  movq -2568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10800(%rbp)
  movq -10784(%rbp), %rdi
  movq -10792(%rbp), %rsi
  movq -10800(%rbp), %rdx
  call processRefined
  mov -10808(%rbp), rax
  movq -10808(%rbp), %rax
  movq -2576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10816(%rbp)
  movq -10816(%rbp), %rax
  movq -2584(%rbp), %rdx
  movq %rax, (%rdx)
  movq $50, %rax
  movq -2592(%rbp), %rdx
  movq %rax, (%rdx)
  movq $900, %rax
  movq -2600(%rbp), %rdx
  movq %rax, (%rdx)
  movq $300, %rax
  movq -2608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10824(%rbp)
  movq -2600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10832(%rbp)
  movq -2608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10840(%rbp)
  movq -10824(%rbp), %rdi
  movq -10832(%rbp), %rsi
  movq -10840(%rbp), %rdx
  call processRefined
  mov -10848(%rbp), rax
  movq -10848(%rbp), %rax
  movq -2616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10856(%rbp)
  movq -10856(%rbp), %rax
  movq -2624(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_82(%rip), %rax
  movq -2640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10864(%rbp)
  movq -2584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10872(%rbp)
  movq -10864(%rbp), %rdi
  movq -10872(%rbp), %rsi
  call lm_rt_str_format
  mov -10880(%rbp), rax
  movq -10880(%rbp), %rax
  movq -2632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10888(%rbp)
  movq -10888(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10896(%rbp)
  movq -10896(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8814
  jmp main_pr_str_0_8814
main_pr_nil_0_8814:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10904(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10912(%rbp)
  jmp main_pr_next_0_8814
main_pr_str_0_8814:
  movq -10888(%rbp), %rax
  addq $8, %rax
  movq %rax, -10920(%rbp)
  movq -10920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10928(%rbp)
  movq -10888(%rbp), %rax
  addq $24, %rax
  movq %rax, -10936(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10936(%rbp), %rsi
  movq -10928(%rbp), %rdx
  syscall
  movq %rax, -10944(%rbp)
  jmp main_pr_next_0_8814
main_pr_next_0_8814:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10952(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10952(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10960(%rbp)
  movq $0, %rax
  movq -2648(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_83(%rip), %rax
  movq -2664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10968(%rbp)
  movq -2624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10976(%rbp)
  movq -10968(%rbp), %rdi
  movq -10976(%rbp), %rsi
  call lm_rt_str_format
  mov -10984(%rbp), rax
  movq -10984(%rbp), %rax
  movq -2656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10992(%rbp)
  movq -10992(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11000(%rbp)
  movq -11000(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3367
  jmp main_pr_str_0_3367
main_pr_nil_0_3367:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -11008(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11008(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -11016(%rbp)
  jmp main_pr_next_0_3367
main_pr_str_0_3367:
  movq -10992(%rbp), %rax
  addq $8, %rax
  movq %rax, -11024(%rbp)
  movq -11024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11032(%rbp)
  movq -10992(%rbp), %rax
  addq $24, %rax
  movq %rax, -11040(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11040(%rbp), %rsi
  movq -11032(%rbp), %rdx
  syscall
  movq %rax, -11048(%rbp)
  jmp main_pr_next_0_3367
main_pr_next_0_3367:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -11056(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11056(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -11064(%rbp)
  movq $0, %rax
  movq -2672(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_84(%rip), %rax
  movq -2680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11072(%rbp)
  movq -11072(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11080(%rbp)
  movq -11080(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5434
  jmp main_pr_str_0_5434
main_pr_nil_0_5434:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -11088(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11088(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -11096(%rbp)
  jmp main_pr_next_0_5434
main_pr_str_0_5434:
  movq -11072(%rbp), %rax
  addq $8, %rax
  movq %rax, -11104(%rbp)
  movq -11104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11112(%rbp)
  movq -11072(%rbp), %rax
  addq $24, %rax
  movq %rax, -11120(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11120(%rbp), %rsi
  movq -11112(%rbp), %rdx
  syscall
  movq %rax, -11128(%rbp)
  jmp main_pr_next_0_5434
main_pr_next_0_5434:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -11136(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11136(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -11144(%rbp)
  movq $0, %rax
  movq -2688(%rbp), %rdx
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

.globl processRefined
processRefined:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
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
  movq %rdx, -64(%rbp)
processRefined_entry:
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
  movq -48(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp processRefined_block_0
processRefined_block_0:
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -200(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -208(%rbp)
  movq -208(%rbp), %rax
  addq -200(%rbp), %rax
  movq %rax, -216(%rbp)
  movq -216(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -224(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -232(%rbp)
  movq -232(%rbp), %rax
  addq -224(%rbp), %rax
  movq %rax, -240(%rbp)
  movq -240(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -248(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -256(%rbp)
  movq -256(%rbp), %rax
  addq -248(%rbp), %rax
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -272(%rbp)
  movq -272(%rbp), %rax
  jmp processRefined_epilogue
processRefined_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_processRefined:

.globl validatePositive
validatePositive:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
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
validatePositive_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp validatePositive_block_0
validatePositive_block_0:
  movq $50, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -200(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -208(%rbp)
  movq -208(%rbp), %rax
  cmpq -200(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -216(%rbp)
  movq -216(%rbp), %rax
  movq -72(%rbp), %rdx
  movl %eax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -224(%rbp)
  movq -224(%rbp), %rax
  testq %rax, %rax
  jne validatePositive_block_3
  jmp validatePositive_block_5
validatePositive_block_3:
  leaq str_hdr_85(%rip), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -232(%rbp)
  movq -232(%rbp), %rax
  jmp validatePositive_epilogue
validatePositive_block_5:
  movq $10, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -240(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -248(%rbp)
  movq -248(%rbp), %rax
  cmpq -240(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -256(%rbp)
  movq -256(%rbp), %rax
  movq -96(%rbp), %rdx
  movl %eax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rax
  testq %rax, %rax
  jne validatePositive_block_8
  jmp validatePositive_block_10
validatePositive_block_8:
  leaq str_hdr_86(%rip), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -272(%rbp)
  movq -272(%rbp), %rax
  jmp validatePositive_epilogue
validatePositive_block_10:
  leaq str_hdr_87(%rip), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -280(%rbp)
  movq -280(%rbp), %rax
  jmp validatePositive_epilogue
validatePositive_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_validatePositive:

.globl isLarge
isLarge:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
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
isLarge_entry:
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
  jmp isLarge_block_0
isLarge_block_0:
  movq $100, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -160(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rax
  cmpq -160(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -176(%rbp)
  movq -176(%rbp), %rax
  movq -72(%rbp), %rdx
  movl %eax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  jmp isLarge_epilogue
isLarge_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_isLarge:

.globl isPositive
isPositive:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
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
isPositive_entry:
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
  jmp isPositive_block_0
isPositive_block_0:
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -160(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rax
  cmpq -160(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -176(%rbp)
  movq -176(%rbp), %rax
  movq -72(%rbp), %rdx
  movl %eax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  jmp isPositive_epilogue
isPositive_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_isPositive:

.globl getLargeNumber
getLargeNumber:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
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
getLargeNumber_entry:
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
  jmp getLargeNumber_block_0
getLargeNumber_block_0:
  movq $500, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -136(%rbp)
  movq -136(%rbp), %rax
  jmp getLargeNumber_epilogue
getLargeNumber_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_getLargeNumber:

.globl processLarge
processLarge:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
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
processLarge_entry:
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
  jmp processLarge_block_0
processLarge_block_0:
  movq $50, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $50, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -176(%rbp)
  movq -176(%rbp), %rax
  addq -168(%rbp), %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -192(%rbp)
  movq -192(%rbp), %rax
  jmp processLarge_epilogue
processLarge_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_processLarge:

.globl getPositiveNumber
getPositiveNumber:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
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
getPositiveNumber_entry:
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
  jmp getPositiveNumber_block_0
getPositiveNumber_block_0:
  movq $42, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -136(%rbp)
  movq -136(%rbp), %rax
  jmp getPositiveNumber_epilogue
getPositiveNumber_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_getPositiveNumber:

.globl processPositive
processPositive:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
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
processPositive_entry:
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
  jmp processPositive_block_0
processPositive_block_0:
  movq $2, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -160(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rax
  imulq -160(%rbp), %rax
  movq %rax, -176(%rbp)
  movq -176(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  jmp processPositive_epilogue
processPositive_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_processPositive:

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

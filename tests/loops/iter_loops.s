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
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 73
  .byte 116
  .byte 101
  .byte 114
  .byte 32
  .byte 76
  .byte 111
  .byte 111
  .byte 112
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
  .byte 66
  .byte 97
  .byte 115
  .byte 105
  .byte 99
  .byte 32
  .byte 114
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 32
  .byte 40
  .byte 49
  .byte 32
  .byte 116
  .byte 111
  .byte 32
  .byte 53
  .byte 41
  .byte 58
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
  .byte 105
  .byte 32
  .byte 61
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
  .byte 66
  .byte 97
  .byte 115
  .byte 105
  .byte 99
  .byte 32
  .byte 105
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
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 101
  .byte 32
  .byte 53
  .byte 32
  .byte 116
  .byte 105
  .byte 109
  .byte 101
  .byte 115
  .byte 32
  .byte 40
  .byte 49
  .byte 45
  .byte 53
  .byte 41
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
  .byte 83
  .byte 117
  .byte 109
  .byte 32
  .byte 111
  .byte 102
  .byte 32
  .byte 49
  .byte 43
  .byte 50
  .byte 43
  .byte 51
  .byte 43
  .byte 52
  .byte 43
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
  .byte 49
  .byte 53
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
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 32
  .byte 40
  .byte 48
  .byte 32
  .byte 116
  .byte 111
  .byte 32
  .byte 51
  .byte 41
  .byte 58
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
  .byte 120
  .byte 32
  .byte 61
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
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 32
  .byte 105
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
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 101
  .byte 32
  .byte 52
  .byte 32
  .byte 116
  .byte 105
  .byte 109
  .byte 101
  .byte 115
  .byte 32
  .byte 40
  .byte 48
  .byte 45
  .byte 51
  .byte 41
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
  .byte 83
  .byte 117
  .byte 109
  .byte 32
  .byte 111
  .byte 102
  .byte 32
  .byte 48
  .byte 43
  .byte 49
  .byte 43
  .byte 50
  .byte 43
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
  .byte 54
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 32
  .byte 108
  .byte 111
  .byte 111
  .byte 112
  .byte 115
  .byte 58
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
  .byte 79
  .byte 117
  .byte 116
  .byte 101
  .byte 114
  .byte 32
  .byte 37
  .byte 115
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
str_hdr_16:
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 105
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
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 101
  .byte 32
  .byte 54
  .byte 32
  .byte 116
  .byte 105
  .byte 109
  .byte 101
  .byte 115
  .byte 32
  .byte 40
  .byte 50
  .byte 120
  .byte 51
  .byte 41
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
  .byte 77
  .byte 105
  .byte 120
  .byte 101
  .byte 100
  .byte 32
  .byte 108
  .byte 111
  .byte 111
  .byte 112
  .byte 115
  .byte 32
  .byte 40
  .byte 102
  .byte 111
  .byte 114
  .byte 32
  .byte 111
  .byte 117
  .byte 116
  .byte 101
  .byte 114
  .byte 44
  .byte 32
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 32
  .byte 105
  .byte 110
  .byte 110
  .byte 101
  .byte 114
  .byte 41
  .byte 58
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
  .byte 102
  .byte 111
  .byte 114
  .byte 45
  .byte 105
  .byte 116
  .byte 101
  .byte 114
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
str_hdr_20:
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
  .byte 77
  .byte 105
  .byte 120
  .byte 101
  .byte 100
  .byte 32
  .byte 102
  .byte 111
  .byte 114
  .byte 45
  .byte 105
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
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 101
  .byte 32
  .byte 54
  .byte 32
  .byte 116
  .byte 105
  .byte 109
  .byte 101
  .byte 115
  .byte 32
  .byte 40
  .byte 50
  .byte 120
  .byte 51
  .byte 41
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
  .byte 77
  .byte 105
  .byte 120
  .byte 101
  .byte 100
  .byte 32
  .byte 108
  .byte 111
  .byte 111
  .byte 112
  .byte 115
  .byte 32
  .byte 40
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 32
  .byte 111
  .byte 117
  .byte 116
  .byte 101
  .byte 114
  .byte 44
  .byte 32
  .byte 102
  .byte 111
  .byte 114
  .byte 32
  .byte 105
  .byte 110
  .byte 110
  .byte 101
  .byte 114
  .byte 41
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
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 45
  .byte 102
  .byte 111
  .byte 114
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
str_hdr_24:
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
  .byte 77
  .byte 105
  .byte 120
  .byte 101
  .byte 100
  .byte 32
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 45
  .byte 102
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
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 101
  .byte 32
  .byte 54
  .byte 32
  .byte 116
  .byte 105
  .byte 109
  .byte 101
  .byte 115
  .byte 32
  .byte 40
  .byte 50
  .byte 120
  .byte 51
  .byte 41
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
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 118
  .byte 97
  .byte 114
  .byte 105
  .byte 97
  .byte 98
  .byte 108
  .byte 101
  .byte 115
  .byte 32
  .byte 40
  .byte 37
  .byte 115
  .byte 32
  .byte 116
  .byte 111
  .byte 32
  .byte 37
  .byte 115
  .byte 41
  .byte 58
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
  .byte 107
  .byte 32
  .byte 61
  .byte 32
  .byte 37
  .byte 115
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
  .byte 86
  .byte 97
  .byte 114
  .byte 105
  .byte 97
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 114
  .byte 97
  .byte 110
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
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 101
  .byte 32
  .byte 51
  .byte 32
  .byte 116
  .byte 105
  .byte 109
  .byte 101
  .byte 115
  .byte 32
  .byte 40
  .byte 50
  .byte 45
  .byte 52
  .byte 41
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
  .byte 83
  .byte 117
  .byte 109
  .byte 32
  .byte 111
  .byte 102
  .byte 32
  .byte 50
  .byte 43
  .byte 51
  .byte 43
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
  .byte 73
  .byte 116
  .byte 101
  .byte 114
  .byte 32
  .byte 108
  .byte 111
  .byte 111
  .byte 112
  .byte 32
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 98
  .byte 114
  .byte 101
  .byte 97
  .byte 107
  .byte 47
  .byte 99
  .byte 111
  .byte 110
  .byte 116
  .byte 105
  .byte 110
  .byte 117
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
  .byte 73
  .byte 116
  .byte 101
  .byte 114
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
str_hdr_34:
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
  .byte 73
  .byte 116
  .byte 101
  .byte 114
  .byte 32
  .byte 108
  .byte 111
  .byte 111
  .byte 112
  .byte 32
  .byte 115
  .byte 104
  .byte 111
  .byte 117
  .byte 108
  .byte 100
  .byte 32
  .byte 101
  .byte 120
  .byte 101
  .byte 99
  .byte 117
  .byte 116
  .byte 101
  .byte 32
  .byte 54
  .byte 32
  .byte 116
  .byte 105
  .byte 109
  .byte 101
  .byte 115
  .byte 32
  .byte 40
  .byte 115
  .byte 107
  .byte 105
  .byte 112
  .byte 32
  .byte 51
  .byte 44
  .byte 32
  .byte 98
  .byte 114
  .byte 101
  .byte 97
  .byte 107
  .byte 32
  .byte 97
  .byte 116
  .byte 32
  .byte 55
  .byte 41
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
  .byte 117
  .byte 109
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
  .byte 43
  .byte 49
  .byte 43
  .byte 50
  .byte 43
  .byte 52
  .byte 43
  .byte 53
  .byte 43
  .byte 54
  .byte 32
  .byte 61
  .byte 32
  .byte 49
  .byte 56
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
  .byte 73
  .byte 116
  .byte 101
  .byte 114
  .byte 32
  .byte 111
  .byte 118
  .byte 101
  .byte 114
  .byte 32
  .byte 99
  .byte 97
  .byte 108
  .byte 99
  .byte 117
  .byte 108
  .byte 97
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 114
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 58
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
  .byte 67
  .byte 97
  .byte 108
  .byte 99
  .byte 117
  .byte 108
  .byte 97
  .byte 116
  .byte 101
  .byte 100
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
  .byte 67
  .byte 97
  .byte 108
  .byte 99
  .byte 117
  .byte 108
  .byte 97
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 114
  .byte 97
  .byte 110
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
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 101
  .byte 32
  .byte 51
  .byte 32
  .byte 116
  .byte 105
  .byte 109
  .byte 101
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
  .byte 83
  .byte 117
  .byte 109
  .byte 32
  .byte 111
  .byte 102
  .byte 32
  .byte 49
  .byte 48
  .byte 43
  .byte 49
  .byte 49
  .byte 43
  .byte 49
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
  .byte 51
  .byte 51
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
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 73
  .byte 116
  .byte 101
  .byte 114
  .byte 32
  .byte 76
  .byte 111
  .byte 111
  .byte 112
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
  subq $6008, %rsp
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
  jmp main_block_0
main_block_0:
  leaq str_hdr_0(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1768(%rbp)
  movq -1768(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1776(%rbp)
  movq -1776(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9383
  jmp main_pr_str_0_9383
main_block_9:
  movq $6, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1784(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1792(%rbp)
  movq -1792(%rbp), %rax
  cmpq -1784(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1800(%rbp)
  movq -1800(%rbp), %rax
  movq -120(%rbp), %rdx
  movl %eax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1808(%rbp)
  movq -1808(%rbp), %rax
  testq %rax, %rax
  jne main_block_12
  jmp main_block_23
main_block_12:
  leaq str_hdr_2(%rip), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1816(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1824(%rbp)
  movq -1816(%rbp), %rdi
  movq -1824(%rbp), %rsi
  call lm_rt_str_format
  mov -1832(%rbp), rax
  movq -1832(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1840(%rbp)
  movq -1840(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1848(%rbp)
  movq -1848(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2777
  jmp main_pr_str_0_2777
main_block_19:
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1856(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1864(%rbp)
  movq -1864(%rbp), %rax
  addq -1856(%rbp), %rax
  movq %rax, -1872(%rbp)
  movq -1872(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1880(%rbp)
  movq -1880(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_9
main_block_23:
  movq $5, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1888(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1896(%rbp)
  movq -1896(%rbp), %rax
  cmpq -1888(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1904(%rbp)
  movq -1904(%rbp), %rax
  movq -184(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_3(%rip), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1912(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1920(%rbp)
  movq -1912(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_4
  jmp main_assert_fail_4
main_block_38:
  movq $4, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1928(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1936(%rbp)
  movq -1936(%rbp), %rax
  cmpq -1928(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1944(%rbp)
  movq -1944(%rbp), %rax
  movq -296(%rbp), %rdx
  movl %eax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1952(%rbp)
  movq -1952(%rbp), %rax
  testq %rax, %rax
  jne main_block_41
  jmp main_block_52
main_block_41:
  leaq str_hdr_8(%rip), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1960(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1968(%rbp)
  movq -1960(%rbp), %rdi
  movq -1968(%rbp), %rsi
  call lm_rt_str_format
  mov -1976(%rbp), rax
  movq -1976(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1984(%rbp)
  movq -1984(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1992(%rbp)
  movq -1992(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7793
  jmp main_pr_str_0_7793
main_block_48:
  movq $1, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2000(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2008(%rbp)
  movq -2008(%rbp), %rax
  addq -2000(%rbp), %rax
  movq %rax, -2016(%rbp)
  movq -2016(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2024(%rbp)
  movq -2024(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_38
main_block_52:
  movq $4, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2032(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2040(%rbp)
  movq -2040(%rbp), %rax
  cmpq -2032(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2048(%rbp)
  movq -2048(%rbp), %rax
  movq -360(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_9(%rip), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2056(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2064(%rbp)
  movq -2056(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_10
  jmp main_assert_fail_10
main_block_67:
  movq $3, %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2072(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2080(%rbp)
  movq -2080(%rbp), %rax
  cmpq -2072(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2088(%rbp)
  movq -2088(%rbp), %rax
  movq -472(%rbp), %rdx
  movl %eax, (%rdx)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2096(%rbp)
  movq -2096(%rbp), %rax
  testq %rax, %rax
  jne main_block_70
  jmp main_block_102
main_block_70:
  leaq str_hdr_14(%rip), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2104(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2112(%rbp)
  movq -2104(%rbp), %rdi
  movq -2112(%rbp), %rsi
  call lm_rt_str_format
  mov -2120(%rbp), rax
  movq -2120(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2128(%rbp)
  movq -2128(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2136(%rbp)
  movq -2136(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5386
  jmp main_pr_str_0_5386
main_block_76:
  movq $13, %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2144(%rbp)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2152(%rbp)
  movq -2152(%rbp), %rax
  cmpq -2144(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2160(%rbp)
  movq -2160(%rbp), %rax
  movq -528(%rbp), %rdx
  movl %eax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2168(%rbp)
  movq -2168(%rbp), %rax
  testq %rax, %rax
  jne main_block_79
  jmp main_block_97
main_block_79:
  leaq str_hdr_15(%rip), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2176(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2184(%rbp)
  movq -2176(%rbp), %rdi
  movq -2184(%rbp), %rsi
  call lm_rt_str_format
  mov -2192(%rbp), rax
  movq -2192(%rbp), %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2200(%rbp)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2208(%rbp)
  movq -2200(%rbp), %rdi
  movq -2208(%rbp), %rsi
  call lm_rt_str_format
  mov -2216(%rbp), rax
  movq -2216(%rbp), %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2224(%rbp)
  movq -2224(%rbp), %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2232(%rbp)
  movq -2232(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2240(%rbp)
  movq -2240(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_492
  jmp main_pr_str_0_492
main_block_93:
  movq $1, %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2248(%rbp)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2256(%rbp)
  movq -2256(%rbp), %rax
  addq -2248(%rbp), %rax
  movq %rax, -2264(%rbp)
  movq -2264(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2272(%rbp)
  movq -2272(%rbp), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_76
main_block_97:
  jmp main_block_98
main_block_98:
  movq $1, %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2280(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2288(%rbp)
  movq -2288(%rbp), %rax
  addq -2280(%rbp), %rax
  movq %rax, -2296(%rbp)
  movq -2296(%rbp), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2304(%rbp)
  movq -2304(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_67
main_block_102:
  movq $6, %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2312(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2320(%rbp)
  movq -2320(%rbp), %rax
  cmpq -2312(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2328(%rbp)
  movq -2328(%rbp), %rax
  movq -656(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_16(%rip), %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2336(%rbp)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2344(%rbp)
  movq -2336(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_17
  jmp main_assert_fail_17
main_block_111:
  movq $0, %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_113
main_block_113:
  movq $4, %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2352(%rbp)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2360(%rbp)
  movq -2360(%rbp), %rax
  cmpq -2352(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2368(%rbp)
  movq -2368(%rbp), %rax
  movq -736(%rbp), %rdx
  movl %eax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2376(%rbp)
  movq -2376(%rbp), %rax
  testq %rax, %rax
  jne main_block_116
  jmp main_block_140
main_block_116:
  movq $5, %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2384(%rbp)
  movq -2384(%rbp), %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_119
main_block_119:
  movq $8, %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2392(%rbp)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2400(%rbp)
  movq -2400(%rbp), %rax
  cmpq -2392(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2408(%rbp)
  movq -2408(%rbp), %rax
  movq -768(%rbp), %rdx
  movl %eax, (%rdx)
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2416(%rbp)
  movq -2416(%rbp), %rax
  testq %rax, %rax
  jne main_block_122
  jmp main_block_136
main_block_122:
  leaq str_hdr_19(%rip), %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2424(%rbp)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2432(%rbp)
  movq -2424(%rbp), %rdi
  movq -2432(%rbp), %rsi
  call lm_rt_str_format
  mov -2440(%rbp), rax
  movq -2440(%rbp), %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  movq -776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2448(%rbp)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2456(%rbp)
  movq -2448(%rbp), %rdi
  movq -2456(%rbp), %rsi
  call lm_rt_str_format
  mov -2464(%rbp), rax
  movq -2464(%rbp), %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2472(%rbp)
  movq -2472(%rbp), %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  movq -776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2480(%rbp)
  movq -2480(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2488(%rbp)
  movq -2488(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1421
  jmp main_pr_str_0_1421
main_block_132:
  movq $1, %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2496(%rbp)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2504(%rbp)
  movq -2504(%rbp), %rax
  addq -2496(%rbp), %rax
  movq %rax, -2512(%rbp)
  movq -2512(%rbp), %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2520(%rbp)
  movq -2520(%rbp), %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_119
main_block_136:
  jmp main_block_137
main_block_137:
  movq $2, %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2528(%rbp)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2536(%rbp)
  movq -2536(%rbp), %rax
  addq -2528(%rbp), %rax
  movq %rax, -2544(%rbp)
  movq -2544(%rbp), %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_113
main_block_140:
  movq $6, %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2552(%rbp)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2560(%rbp)
  movq -2560(%rbp), %rax
  cmpq -2552(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2568(%rbp)
  movq -2568(%rbp), %rax
  movq -856(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_20(%rip), %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2576(%rbp)
  movq -864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2584(%rbp)
  movq -2576(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_21
  jmp main_assert_fail_21
main_block_151:
  movq $3, %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2592(%rbp)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2600(%rbp)
  movq -2600(%rbp), %rax
  cmpq -2592(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2608(%rbp)
  movq -2608(%rbp), %rax
  movq -936(%rbp), %rdx
  movl %eax, (%rdx)
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2616(%rbp)
  movq -2616(%rbp), %rax
  testq %rax, %rax
  jne main_block_154
  jmp main_block_178
main_block_154:
  jmp main_block_155
main_block_155:
  movq $0, %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_157
main_block_157:
  movq $5, %rax
  movq -960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2624(%rbp)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2632(%rbp)
  movq -2632(%rbp), %rax
  cmpq -2624(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2640(%rbp)
  movq -2640(%rbp), %rax
  movq -968(%rbp), %rdx
  movl %eax, (%rdx)
  movq -968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2648(%rbp)
  movq -2648(%rbp), %rax
  testq %rax, %rax
  jne main_block_160
  jmp main_block_173
main_block_160:
  leaq str_hdr_23(%rip), %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  movq -984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2656(%rbp)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2664(%rbp)
  movq -2656(%rbp), %rdi
  movq -2664(%rbp), %rsi
  call lm_rt_str_format
  mov -2672(%rbp), rax
  movq -2672(%rbp), %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2680(%rbp)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2688(%rbp)
  movq -2680(%rbp), %rdi
  movq -2688(%rbp), %rsi
  call lm_rt_str_format
  mov -2696(%rbp), rax
  movq -2696(%rbp), %rax
  movq -992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2704(%rbp)
  movq -2704(%rbp), %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2712(%rbp)
  movq -2712(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2720(%rbp)
  movq -2720(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_27
  jmp main_pr_str_0_27
main_block_170:
  movq $2, %rax
  movq -1024(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2728(%rbp)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2736(%rbp)
  movq -2736(%rbp), %rax
  addq -2728(%rbp), %rax
  movq %rax, -2744(%rbp)
  movq -2744(%rbp), %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_157
main_block_173:
  jmp main_block_174
main_block_174:
  movq $1, %rax
  movq -1032(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2752(%rbp)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2760(%rbp)
  movq -2760(%rbp), %rax
  addq -2752(%rbp), %rax
  movq %rax, -2768(%rbp)
  movq -2768(%rbp), %rax
  movq -1040(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2776(%rbp)
  movq -2776(%rbp), %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_151
main_block_178:
  movq $6, %rax
  movq -1048(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2784(%rbp)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2792(%rbp)
  movq -2792(%rbp), %rax
  cmpq -2784(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2800(%rbp)
  movq -2800(%rbp), %rax
  movq -1056(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_24(%rip), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2808(%rbp)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2816(%rbp)
  movq -2808(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_25
  jmp main_assert_fail_25
main_block_193:
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2824(%rbp)
  movq -1144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2832(%rbp)
  movq -2832(%rbp), %rax
  cmpq -2824(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2840(%rbp)
  movq -2840(%rbp), %rax
  movq -1152(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2848(%rbp)
  movq -2848(%rbp), %rax
  testq %rax, %rax
  jne main_block_195
  jmp main_block_206
main_block_195:
  leaq str_hdr_27(%rip), %rax
  movq -1168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2856(%rbp)
  movq -1144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2864(%rbp)
  movq -2856(%rbp), %rdi
  movq -2864(%rbp), %rsi
  call lm_rt_str_format
  mov -2872(%rbp), rax
  movq -2872(%rbp), %rax
  movq -1160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2880(%rbp)
  movq -2880(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2888(%rbp)
  movq -2888(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_59
  jmp main_pr_str_0_59
main_block_202:
  movq $1, %rax
  movq -1192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2896(%rbp)
  movq -1144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2904(%rbp)
  movq -2904(%rbp), %rax
  addq -2896(%rbp), %rax
  movq %rax, -2912(%rbp)
  movq -2912(%rbp), %rax
  movq -1200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2920(%rbp)
  movq -2920(%rbp), %rax
  movq -1144(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_193
main_block_206:
  movq $3, %rax
  movq -1208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2928(%rbp)
  movq -1128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2936(%rbp)
  movq -2936(%rbp), %rax
  cmpq -2928(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2944(%rbp)
  movq -2944(%rbp), %rax
  movq -1216(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_28(%rip), %rax
  movq -1224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2952(%rbp)
  movq -1224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2960(%rbp)
  movq -2952(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_29
  jmp main_assert_fail_29
main_block_221:
  movq $10, %rax
  movq -1320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2968(%rbp)
  movq -1304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2976(%rbp)
  movq -2976(%rbp), %rax
  cmpq -2968(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2984(%rbp)
  movq -2984(%rbp), %rax
  movq -1328(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2992(%rbp)
  movq -2992(%rbp), %rax
  testq %rax, %rax
  jne main_block_224
  jmp main_block_243
main_block_224:
  movq $3, %rax
  movq -1336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3000(%rbp)
  movq -1304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3008(%rbp)
  movq -3008(%rbp), %rax
  cmpq -3000(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3016(%rbp)
  movq -3016(%rbp), %rax
  movq -1344(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3024(%rbp)
  movq -3024(%rbp), %rax
  testq %rax, %rax
  jne main_block_227
  jmp main_block_228
main_block_227:
  jmp main_block_239
main_block_228:
  movq $7, %rax
  movq -1352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3032(%rbp)
  movq -1304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3040(%rbp)
  movq -3040(%rbp), %rax
  cmpq -3032(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3048(%rbp)
  movq -3048(%rbp), %rax
  movq -1360(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3056(%rbp)
  movq -3056(%rbp), %rax
  testq %rax, %rax
  jne main_block_231
  jmp main_block_232
main_block_231:
  jmp main_block_243
main_block_232:
  leaq str_hdr_33(%rip), %rax
  movq -1376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3064(%rbp)
  movq -1304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3072(%rbp)
  movq -3064(%rbp), %rdi
  movq -3072(%rbp), %rsi
  call lm_rt_str_format
  mov -3080(%rbp), rax
  movq -3080(%rbp), %rax
  movq -1368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3088(%rbp)
  movq -3088(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3096(%rbp)
  movq -3096(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3926
  jmp main_pr_str_0_3926
main_block_239:
  movq $1, %rax
  movq -1400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3104(%rbp)
  movq -1304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3112(%rbp)
  movq -3112(%rbp), %rax
  addq -3104(%rbp), %rax
  movq %rax, -3120(%rbp)
  movq -3120(%rbp), %rax
  movq -1408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3128(%rbp)
  movq -3128(%rbp), %rax
  movq -1304(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_221
main_block_243:
  movq $6, %rax
  movq -1416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3136(%rbp)
  movq -1288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3144(%rbp)
  movq -3144(%rbp), %rax
  cmpq -3136(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3152(%rbp)
  movq -3152(%rbp), %rax
  movq -1424(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_34(%rip), %rax
  movq -1432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3160(%rbp)
  movq -1432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3168(%rbp)
  movq -3160(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_35
  jmp main_assert_fail_35
main_block_259:
  movq -1504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3176(%rbp)
  movq -1496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3184(%rbp)
  movq -3184(%rbp), %rax
  addq -3176(%rbp), %rax
  movq %rax, -3192(%rbp)
  movq -3192(%rbp), %rax
  movq -1536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3200(%rbp)
  movq -1528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3208(%rbp)
  movq -3208(%rbp), %rax
  cmpq -3200(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -3216(%rbp)
  movq -3216(%rbp), %rax
  movq -1544(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3224(%rbp)
  movq -3224(%rbp), %rax
  testq %rax, %rax
  jne main_block_262
  jmp main_block_273
main_block_262:
  leaq str_hdr_39(%rip), %rax
  movq -1560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3232(%rbp)
  movq -1528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3240(%rbp)
  movq -3232(%rbp), %rdi
  movq -3240(%rbp), %rsi
  call lm_rt_str_format
  mov -3248(%rbp), rax
  movq -3248(%rbp), %rax
  movq -1552(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3256(%rbp)
  movq -3256(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3264(%rbp)
  movq -3264(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3426
  jmp main_pr_str_0_3426
main_block_269:
  movq $1, %rax
  movq -1584(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3272(%rbp)
  movq -1528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3280(%rbp)
  movq -3280(%rbp), %rax
  addq -3272(%rbp), %rax
  movq %rax, -3288(%rbp)
  movq -3288(%rbp), %rax
  movq -1592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3296(%rbp)
  movq -3296(%rbp), %rax
  movq -1528(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_259
main_block_273:
  movq $3, %rax
  movq -1600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3304(%rbp)
  movq -1512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3312(%rbp)
  movq -3312(%rbp), %rax
  cmpq -3304(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3320(%rbp)
  movq -3320(%rbp), %rax
  movq -1608(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_40(%rip), %rax
  movq -1616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3328(%rbp)
  movq -1616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3336(%rbp)
  movq -3328(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_41
  jmp main_assert_fail_41
main_pr_nil_0_9383:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3344(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3352(%rbp)
  jmp main_pr_next_0_9383
main_pr_str_0_9383:
  movq -1768(%rbp), %rax
  addq $8, %rax
  movq %rax, -3360(%rbp)
  movq -3360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3368(%rbp)
  movq -1768(%rbp), %rax
  addq $24, %rax
  movq %rax, -3376(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3376(%rbp), %rsi
  movq -3368(%rbp), %rdx
  syscall
  movq %rax, -3384(%rbp)
  jmp main_pr_next_0_9383
main_pr_next_0_9383:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3392(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3392(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3400(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_1(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3408(%rbp)
  movq -3408(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3416(%rbp)
  movq -3416(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_886
  jmp main_pr_str_0_886
main_pr_nil_0_886:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3424(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3424(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3432(%rbp)
  jmp main_pr_next_0_886
main_pr_str_0_886:
  movq -3408(%rbp), %rax
  addq $8, %rax
  movq %rax, -3440(%rbp)
  movq -3440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3448(%rbp)
  movq -3408(%rbp), %rax
  addq $24, %rax
  movq %rax, -3456(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3456(%rbp), %rsi
  movq -3448(%rbp), %rdx
  syscall
  movq %rax, -3464(%rbp)
  jmp main_pr_next_0_886
main_pr_next_0_886:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3472(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3472(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3480(%rbp)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3488(%rbp)
  movq -3488(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_9
main_pr_nil_0_2777:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3496(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3496(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3504(%rbp)
  jmp main_pr_next_0_2777
main_pr_str_0_2777:
  movq -1840(%rbp), %rax
  addq $8, %rax
  movq %rax, -3512(%rbp)
  movq -3512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3520(%rbp)
  movq -1840(%rbp), %rax
  addq $24, %rax
  movq %rax, -3528(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3528(%rbp), %rsi
  movq -3520(%rbp), %rdx
  syscall
  movq %rax, -3536(%rbp)
  jmp main_pr_next_0_2777
main_pr_next_0_2777:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3544(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3552(%rbp)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3560(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3568(%rbp)
  movq -3568(%rbp), %rax
  addq -3560(%rbp), %rax
  movq %rax, -3576(%rbp)
  movq -3576(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3584(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3592(%rbp)
  movq -3592(%rbp), %rax
  addq -3584(%rbp), %rax
  movq %rax, -3600(%rbp)
  movq -3600(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_19
main_assert_pass_4:
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq $15, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3608(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3616(%rbp)
  movq -3616(%rbp), %rax
  cmpq -3608(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3624(%rbp)
  movq -3624(%rbp), %rax
  movq -216(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_5(%rip), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3632(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3640(%rbp)
  movq -3632(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_6
  jmp main_assert_fail_6
main_assert_fail_4:
  movq -1920(%rbp), %rax
  addq $8, %rax
  movq %rax, -3648(%rbp)
  movq -3648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3656(%rbp)
  movq -1920(%rbp), %rax
  addq $24, %rax
  movq %rax, -3664(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3664(%rbp), %rsi
  movq -3656(%rbp), %rdx
  syscall
  movq %rax, -3672(%rbp)
  movq $50397203, %rax
  movq %rax, -3680(%rbp)
  jmp main_assert_pass_4
main_assert_pass_6:
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_7(%rip), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3688(%rbp)
  movq -3688(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3696(%rbp)
  movq -3696(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6915
  jmp main_pr_str_0_6915
main_assert_fail_6:
  movq -3640(%rbp), %rax
  addq $8, %rax
  movq %rax, -3704(%rbp)
  movq -3704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3712(%rbp)
  movq -3640(%rbp), %rax
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
  jmp main_assert_pass_6
main_pr_nil_0_6915:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3744(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3744(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3752(%rbp)
  jmp main_pr_next_0_6915
main_pr_str_0_6915:
  movq -3688(%rbp), %rax
  addq $8, %rax
  movq %rax, -3760(%rbp)
  movq -3760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3768(%rbp)
  movq -3688(%rbp), %rax
  addq $24, %rax
  movq %rax, -3776(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3776(%rbp), %rsi
  movq -3768(%rbp), %rdx
  syscall
  movq %rax, -3784(%rbp)
  jmp main_pr_next_0_6915
main_pr_next_0_6915:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3792(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3792(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3800(%rbp)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3808(%rbp)
  movq -3808(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_38
main_pr_nil_0_7793:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3816(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3816(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3824(%rbp)
  jmp main_pr_next_0_7793
main_pr_str_0_7793:
  movq -1984(%rbp), %rax
  addq $8, %rax
  movq %rax, -3832(%rbp)
  movq -3832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3840(%rbp)
  movq -1984(%rbp), %rax
  addq $24, %rax
  movq %rax, -3848(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3848(%rbp), %rsi
  movq -3840(%rbp), %rdx
  syscall
  movq %rax, -3856(%rbp)
  jmp main_pr_next_0_7793
main_pr_next_0_7793:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3864(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3864(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3872(%rbp)
  movq $0, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3880(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3888(%rbp)
  movq -3888(%rbp), %rax
  addq -3880(%rbp), %rax
  movq %rax, -3896(%rbp)
  movq -3896(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3904(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3912(%rbp)
  movq -3912(%rbp), %rax
  addq -3904(%rbp), %rax
  movq %rax, -3920(%rbp)
  movq -3920(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_48
main_assert_pass_10:
  movq $0, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq $6, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3928(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3936(%rbp)
  movq -3936(%rbp), %rax
  cmpq -3928(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3944(%rbp)
  movq -3944(%rbp), %rax
  movq -392(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_11(%rip), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3952(%rbp)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3960(%rbp)
  movq -3952(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_12
  jmp main_assert_fail_12
main_assert_fail_10:
  movq -2064(%rbp), %rax
  addq $8, %rax
  movq %rax, -3968(%rbp)
  movq -3968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3976(%rbp)
  movq -2064(%rbp), %rax
  addq $24, %rax
  movq %rax, -3984(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3984(%rbp), %rsi
  movq -3976(%rbp), %rdx
  syscall
  movq %rax, -3992(%rbp)
  movq $50397203, %rax
  movq %rax, -4000(%rbp)
  jmp main_assert_pass_10
main_assert_pass_12:
  movq $0, %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_13(%rip), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4008(%rbp)
  movq -4008(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4016(%rbp)
  movq -4016(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8335
  jmp main_pr_str_0_8335
main_assert_fail_12:
  movq -3960(%rbp), %rax
  addq $8, %rax
  movq %rax, -4024(%rbp)
  movq -4024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4032(%rbp)
  movq -3960(%rbp), %rax
  addq $24, %rax
  movq %rax, -4040(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4040(%rbp), %rsi
  movq -4032(%rbp), %rdx
  syscall
  movq %rax, -4048(%rbp)
  movq $50397203, %rax
  movq %rax, -4056(%rbp)
  jmp main_assert_pass_12
main_pr_nil_0_8335:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4064(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4064(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4072(%rbp)
  jmp main_pr_next_0_8335
main_pr_str_0_8335:
  movq -4008(%rbp), %rax
  addq $8, %rax
  movq %rax, -4080(%rbp)
  movq -4080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4088(%rbp)
  movq -4008(%rbp), %rax
  addq $24, %rax
  movq %rax, -4096(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4096(%rbp), %rsi
  movq -4088(%rbp), %rdx
  syscall
  movq %rax, -4104(%rbp)
  jmp main_pr_next_0_8335
main_pr_next_0_8335:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4112(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4112(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4120(%rbp)
  movq $0, %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4128(%rbp)
  movq -4128(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_67
main_pr_nil_0_5386:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4136(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4136(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4144(%rbp)
  jmp main_pr_next_0_5386
main_pr_str_0_5386:
  movq -2128(%rbp), %rax
  addq $8, %rax
  movq %rax, -4152(%rbp)
  movq -4152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4160(%rbp)
  movq -2128(%rbp), %rax
  addq $24, %rax
  movq %rax, -4168(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4168(%rbp), %rsi
  movq -4160(%rbp), %rdx
  syscall
  movq %rax, -4176(%rbp)
  jmp main_pr_next_0_5386
main_pr_next_0_5386:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4184(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4184(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4192(%rbp)
  movq $0, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4200(%rbp)
  movq -4200(%rbp), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_76
main_pr_nil_0_492:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4208(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4208(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4216(%rbp)
  jmp main_pr_next_0_492
main_pr_str_0_492:
  movq -2232(%rbp), %rax
  addq $8, %rax
  movq %rax, -4224(%rbp)
  movq -4224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4232(%rbp)
  movq -2232(%rbp), %rax
  addq $24, %rax
  movq %rax, -4240(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4240(%rbp), %rsi
  movq -4232(%rbp), %rdx
  syscall
  movq %rax, -4248(%rbp)
  jmp main_pr_next_0_492
main_pr_next_0_492:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4256(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4256(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4264(%rbp)
  movq $0, %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4272(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4280(%rbp)
  movq -4280(%rbp), %rax
  addq -4272(%rbp), %rax
  movq %rax, -4288(%rbp)
  movq -4288(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq $100, %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4296(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4304(%rbp)
  movq -4304(%rbp), %rax
  imulq -4296(%rbp), %rax
  movq %rax, -4312(%rbp)
  movq -4312(%rbp), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  movq $100, %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4320(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4328(%rbp)
  movq -4328(%rbp), %rax
  imulq -4320(%rbp), %rax
  movq %rax, -4336(%rbp)
  movq -4336(%rbp), %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4344(%rbp)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4352(%rbp)
  movq -4352(%rbp), %rax
  addq -4344(%rbp), %rax
  movq %rax, -4360(%rbp)
  movq -4360(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4368(%rbp)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4376(%rbp)
  movq -4376(%rbp), %rax
  addq -4368(%rbp), %rax
  movq %rax, -4384(%rbp)
  movq -4384(%rbp), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_93
main_assert_pass_17:
  movq $0, %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_18(%rip), %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4392(%rbp)
  movq -4392(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4400(%rbp)
  movq -4400(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6649
  jmp main_pr_str_0_6649
main_assert_fail_17:
  movq -2344(%rbp), %rax
  addq $8, %rax
  movq %rax, -4408(%rbp)
  movq -4408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4416(%rbp)
  movq -2344(%rbp), %rax
  addq $24, %rax
  movq %rax, -4424(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4424(%rbp), %rsi
  movq -4416(%rbp), %rdx
  syscall
  movq %rax, -4432(%rbp)
  movq $50397203, %rax
  movq %rax, -4440(%rbp)
  jmp main_assert_pass_17
main_pr_nil_0_6649:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4448(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4448(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4456(%rbp)
  jmp main_pr_next_0_6649
main_pr_str_0_6649:
  movq -4392(%rbp), %rax
  addq $8, %rax
  movq %rax, -4464(%rbp)
  movq -4464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4472(%rbp)
  movq -4392(%rbp), %rax
  addq $24, %rax
  movq %rax, -4480(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4480(%rbp), %rsi
  movq -4472(%rbp), %rdx
  syscall
  movq %rax, -4488(%rbp)
  jmp main_pr_next_0_6649
main_pr_next_0_6649:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4496(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4496(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4504(%rbp)
  movq $0, %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_111
main_pr_nil_0_1421:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4512(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4512(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4520(%rbp)
  jmp main_pr_next_0_1421
main_pr_str_0_1421:
  movq -2480(%rbp), %rax
  addq $8, %rax
  movq %rax, -4528(%rbp)
  movq -4528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4536(%rbp)
  movq -2480(%rbp), %rax
  addq $24, %rax
  movq %rax, -4544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4544(%rbp), %rsi
  movq -4536(%rbp), %rdx
  syscall
  movq %rax, -4552(%rbp)
  jmp main_pr_next_0_1421
main_pr_next_0_1421:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4560(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4560(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4568(%rbp)
  movq $0, %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4576(%rbp)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4584(%rbp)
  movq -4584(%rbp), %rax
  addq -4576(%rbp), %rax
  movq %rax, -4592(%rbp)
  movq -4592(%rbp), %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4600(%rbp)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4608(%rbp)
  movq -4608(%rbp), %rax
  addq -4600(%rbp), %rax
  movq %rax, -4616(%rbp)
  movq -4616(%rbp), %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4624(%rbp)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4632(%rbp)
  movq -4632(%rbp), %rax
  addq -4624(%rbp), %rax
  movq %rax, -4640(%rbp)
  movq -4640(%rbp), %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_132
main_assert_pass_21:
  movq $0, %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_22(%rip), %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4648(%rbp)
  movq -4648(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4656(%rbp)
  movq -4656(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2362
  jmp main_pr_str_0_2362
main_assert_fail_21:
  movq -2584(%rbp), %rax
  addq $8, %rax
  movq %rax, -4664(%rbp)
  movq -4664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4672(%rbp)
  movq -2584(%rbp), %rax
  addq $24, %rax
  movq %rax, -4680(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4680(%rbp), %rsi
  movq -4672(%rbp), %rdx
  syscall
  movq %rax, -4688(%rbp)
  movq $50397203, %rax
  movq %rax, -4696(%rbp)
  jmp main_assert_pass_21
main_pr_nil_0_2362:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4704(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4704(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4712(%rbp)
  jmp main_pr_next_0_2362
main_pr_str_0_2362:
  movq -4648(%rbp), %rax
  addq $8, %rax
  movq %rax, -4720(%rbp)
  movq -4720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4728(%rbp)
  movq -4648(%rbp), %rax
  addq $24, %rax
  movq %rax, -4736(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4736(%rbp), %rsi
  movq -4728(%rbp), %rdx
  syscall
  movq %rax, -4744(%rbp)
  jmp main_pr_next_0_2362
main_pr_next_0_2362:
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
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4768(%rbp)
  movq -4768(%rbp), %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_151
main_pr_nil_0_27:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4776(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4776(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4784(%rbp)
  jmp main_pr_next_0_27
main_pr_str_0_27:
  movq -2712(%rbp), %rax
  addq $8, %rax
  movq %rax, -4792(%rbp)
  movq -4792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4800(%rbp)
  movq -2712(%rbp), %rax
  addq $24, %rax
  movq %rax, -4808(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4808(%rbp), %rsi
  movq -4800(%rbp), %rdx
  syscall
  movq %rax, -4816(%rbp)
  jmp main_pr_next_0_27
main_pr_next_0_27:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4824(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4824(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4832(%rbp)
  movq $0, %rax
  movq -1000(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1008(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4840(%rbp)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4848(%rbp)
  movq -4848(%rbp), %rax
  addq -4840(%rbp), %rax
  movq %rax, -4856(%rbp)
  movq -4856(%rbp), %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4864(%rbp)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4872(%rbp)
  movq -4872(%rbp), %rax
  imulq -4864(%rbp), %rax
  movq %rax, -4880(%rbp)
  movq -4880(%rbp), %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4888(%rbp)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4896(%rbp)
  movq -4896(%rbp), %rax
  addq -4888(%rbp), %rax
  movq %rax, -4904(%rbp)
  movq -4904(%rbp), %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_170
main_assert_pass_25:
  movq $0, %rax
  movq -1072(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -1080(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -1088(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_26(%rip), %rax
  movq -1104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4912(%rbp)
  movq -1080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4920(%rbp)
  movq -4912(%rbp), %rdi
  movq -4920(%rbp), %rsi
  call lm_rt_str_format
  mov -4928(%rbp), rax
  movq -4928(%rbp), %rax
  movq -1096(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4936(%rbp)
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4944(%rbp)
  movq -4936(%rbp), %rdi
  movq -4944(%rbp), %rsi
  call lm_rt_str_format
  mov -4952(%rbp), rax
  movq -4952(%rbp), %rax
  movq -1112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4960(%rbp)
  movq -4960(%rbp), %rax
  movq -1096(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4968(%rbp)
  movq -4968(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4976(%rbp)
  movq -4976(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8690
  jmp main_pr_str_0_8690
main_assert_fail_25:
  movq -2816(%rbp), %rax
  addq $8, %rax
  movq %rax, -4984(%rbp)
  movq -4984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4992(%rbp)
  movq -2816(%rbp), %rax
  addq $24, %rax
  movq %rax, -5000(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5000(%rbp), %rsi
  movq -4992(%rbp), %rdx
  syscall
  movq %rax, -5008(%rbp)
  movq $50397203, %rax
  movq %rax, -5016(%rbp)
  jmp main_assert_pass_25
main_pr_nil_0_8690:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5024(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5024(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5032(%rbp)
  jmp main_pr_next_0_8690
main_pr_str_0_8690:
  movq -4968(%rbp), %rax
  addq $8, %rax
  movq %rax, -5040(%rbp)
  movq -5040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5048(%rbp)
  movq -4968(%rbp), %rax
  addq $24, %rax
  movq %rax, -5056(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5056(%rbp), %rsi
  movq -5048(%rbp), %rdx
  syscall
  movq %rax, -5064(%rbp)
  jmp main_pr_next_0_8690
main_pr_next_0_8690:
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
  movq -1120(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5088(%rbp)
  movq -5088(%rbp), %rax
  movq -1144(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_193
main_pr_nil_0_59:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5096(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5096(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5104(%rbp)
  jmp main_pr_next_0_59
main_pr_str_0_59:
  movq -2880(%rbp), %rax
  addq $8, %rax
  movq %rax, -5112(%rbp)
  movq -5112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5120(%rbp)
  movq -2880(%rbp), %rax
  addq $24, %rax
  movq %rax, -5128(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5128(%rbp), %rsi
  movq -5120(%rbp), %rdx
  syscall
  movq %rax, -5136(%rbp)
  jmp main_pr_next_0_59
main_pr_next_0_59:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5144(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5144(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5152(%rbp)
  movq $0, %rax
  movq -1176(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5160(%rbp)
  movq -1128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5168(%rbp)
  movq -5168(%rbp), %rax
  addq -5160(%rbp), %rax
  movq %rax, -5176(%rbp)
  movq -5176(%rbp), %rax
  movq -1128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5184(%rbp)
  movq -1136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5192(%rbp)
  movq -5192(%rbp), %rax
  addq -5184(%rbp), %rax
  movq %rax, -5200(%rbp)
  movq -5200(%rbp), %rax
  movq -1136(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_202
main_assert_pass_29:
  movq $0, %rax
  movq -1232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $9, %rax
  movq -1240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5208(%rbp)
  movq -1136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5216(%rbp)
  movq -5216(%rbp), %rax
  cmpq -5208(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5224(%rbp)
  movq -5224(%rbp), %rax
  movq -1248(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_30(%rip), %rax
  movq -1256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5232(%rbp)
  movq -1256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5240(%rbp)
  movq -5232(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_31
  jmp main_assert_fail_31
main_assert_fail_29:
  movq -2960(%rbp), %rax
  addq $8, %rax
  movq %rax, -5248(%rbp)
  movq -5248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5256(%rbp)
  movq -2960(%rbp), %rax
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
  jmp main_assert_pass_29
main_assert_pass_31:
  movq $0, %rax
  movq -1264(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_32(%rip), %rax
  movq -1272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5288(%rbp)
  movq -5288(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5296(%rbp)
  movq -5296(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7763
  jmp main_pr_str_0_7763
main_assert_fail_31:
  movq -5240(%rbp), %rax
  addq $8, %rax
  movq %rax, -5304(%rbp)
  movq -5304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5312(%rbp)
  movq -5240(%rbp), %rax
  addq $24, %rax
  movq %rax, -5320(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5320(%rbp), %rsi
  movq -5312(%rbp), %rdx
  syscall
  movq %rax, -5328(%rbp)
  movq $50397203, %rax
  movq %rax, -5336(%rbp)
  jmp main_assert_pass_31
main_pr_nil_0_7763:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5344(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5352(%rbp)
  jmp main_pr_next_0_7763
main_pr_str_0_7763:
  movq -5288(%rbp), %rax
  addq $8, %rax
  movq %rax, -5360(%rbp)
  movq -5360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5368(%rbp)
  movq -5288(%rbp), %rax
  addq $24, %rax
  movq %rax, -5376(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5376(%rbp), %rsi
  movq -5368(%rbp), %rdx
  syscall
  movq %rax, -5384(%rbp)
  jmp main_pr_next_0_7763
main_pr_next_0_7763:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5392(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5392(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5400(%rbp)
  movq $0, %rax
  movq -1280(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1288(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1296(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5408(%rbp)
  movq -5408(%rbp), %rax
  movq -1304(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_221
main_pr_nil_0_3926:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5416(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5416(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5424(%rbp)
  jmp main_pr_next_0_3926
main_pr_str_0_3926:
  movq -3088(%rbp), %rax
  addq $8, %rax
  movq %rax, -5432(%rbp)
  movq -5432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5440(%rbp)
  movq -3088(%rbp), %rax
  addq $24, %rax
  movq %rax, -5448(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5448(%rbp), %rsi
  movq -5440(%rbp), %rdx
  syscall
  movq %rax, -5456(%rbp)
  jmp main_pr_next_0_3926
main_pr_next_0_3926:
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
  movq -1384(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5480(%rbp)
  movq -1288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5488(%rbp)
  movq -5488(%rbp), %rax
  addq -5480(%rbp), %rax
  movq %rax, -5496(%rbp)
  movq -5496(%rbp), %rax
  movq -1288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5504(%rbp)
  movq -1296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5512(%rbp)
  movq -5512(%rbp), %rax
  addq -5504(%rbp), %rax
  movq %rax, -5520(%rbp)
  movq -5520(%rbp), %rax
  movq -1296(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_239
main_assert_pass_35:
  movq $0, %rax
  movq -1440(%rbp), %rdx
  movq %rax, (%rdx)
  movq $18, %rax
  movq -1448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5528(%rbp)
  movq -1296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5536(%rbp)
  movq -5536(%rbp), %rax
  cmpq -5528(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5544(%rbp)
  movq -5544(%rbp), %rax
  movq -1456(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_36(%rip), %rax
  movq -1464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5552(%rbp)
  movq -1464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5560(%rbp)
  movq -5552(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_37
  jmp main_assert_fail_37
main_assert_fail_35:
  movq -3168(%rbp), %rax
  addq $8, %rax
  movq %rax, -5568(%rbp)
  movq -5568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5576(%rbp)
  movq -3168(%rbp), %rax
  addq $24, %rax
  movq %rax, -5584(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5584(%rbp), %rsi
  movq -5576(%rbp), %rdx
  syscall
  movq %rax, -5592(%rbp)
  movq $50397203, %rax
  movq %rax, -5600(%rbp)
  jmp main_assert_pass_35
main_assert_pass_37:
  movq $0, %rax
  movq -1472(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_38(%rip), %rax
  movq -1480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5608(%rbp)
  movq -5608(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5616(%rbp)
  movq -5616(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_540
  jmp main_pr_str_0_540
main_assert_fail_37:
  movq -5560(%rbp), %rax
  addq $8, %rax
  movq %rax, -5624(%rbp)
  movq -5624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5632(%rbp)
  movq -5560(%rbp), %rax
  addq $24, %rax
  movq %rax, -5640(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5640(%rbp), %rsi
  movq -5632(%rbp), %rdx
  syscall
  movq %rax, -5648(%rbp)
  movq $50397203, %rax
  movq %rax, -5656(%rbp)
  jmp main_assert_pass_37
main_pr_nil_0_540:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5664(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5664(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5672(%rbp)
  jmp main_pr_next_0_540
main_pr_str_0_540:
  movq -5608(%rbp), %rax
  addq $8, %rax
  movq %rax, -5680(%rbp)
  movq -5680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5688(%rbp)
  movq -5608(%rbp), %rax
  addq $24, %rax
  movq %rax, -5696(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5696(%rbp), %rsi
  movq -5688(%rbp), %rdx
  syscall
  movq %rax, -5704(%rbp)
  jmp main_pr_next_0_540
main_pr_next_0_540:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5712(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5712(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5720(%rbp)
  movq $0, %rax
  movq -1488(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -1496(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -1504(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1512(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5728(%rbp)
  movq -5728(%rbp), %rax
  movq -1528(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_259
main_pr_nil_0_3426:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5736(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5736(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5744(%rbp)
  jmp main_pr_next_0_3426
main_pr_str_0_3426:
  movq -3256(%rbp), %rax
  addq $8, %rax
  movq %rax, -5752(%rbp)
  movq -5752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5760(%rbp)
  movq -3256(%rbp), %rax
  addq $24, %rax
  movq %rax, -5768(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5768(%rbp), %rsi
  movq -5760(%rbp), %rdx
  syscall
  movq %rax, -5776(%rbp)
  jmp main_pr_next_0_3426
main_pr_next_0_3426:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5784(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5784(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5792(%rbp)
  movq $0, %rax
  movq -1568(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5800(%rbp)
  movq -1512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5808(%rbp)
  movq -5808(%rbp), %rax
  addq -5800(%rbp), %rax
  movq %rax, -5816(%rbp)
  movq -5816(%rbp), %rax
  movq -1512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5824(%rbp)
  movq -1520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5832(%rbp)
  movq -5832(%rbp), %rax
  addq -5824(%rbp), %rax
  movq %rax, -5840(%rbp)
  movq -5840(%rbp), %rax
  movq -1520(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_269
main_assert_pass_41:
  movq $0, %rax
  movq -1624(%rbp), %rdx
  movq %rax, (%rdx)
  movq $33, %rax
  movq -1632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5848(%rbp)
  movq -1520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5856(%rbp)
  movq -5856(%rbp), %rax
  cmpq -5848(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5864(%rbp)
  movq -5864(%rbp), %rax
  movq -1640(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_42(%rip), %rax
  movq -1648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5872(%rbp)
  movq -1648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5880(%rbp)
  movq -5872(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_43
  jmp main_assert_fail_43
main_assert_fail_41:
  movq -3336(%rbp), %rax
  addq $8, %rax
  movq %rax, -5888(%rbp)
  movq -5888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5896(%rbp)
  movq -3336(%rbp), %rax
  addq $24, %rax
  movq %rax, -5904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5904(%rbp), %rsi
  movq -5896(%rbp), %rdx
  syscall
  movq %rax, -5912(%rbp)
  movq $50397203, %rax
  movq %rax, -5920(%rbp)
  jmp main_assert_pass_41
main_assert_pass_43:
  movq $0, %rax
  movq -1656(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_44(%rip), %rax
  movq -1664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5928(%rbp)
  movq -5928(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5936(%rbp)
  movq -5936(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9172
  jmp main_pr_str_0_9172
main_assert_fail_43:
  movq -5880(%rbp), %rax
  addq $8, %rax
  movq %rax, -5944(%rbp)
  movq -5944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5952(%rbp)
  movq -5880(%rbp), %rax
  addq $24, %rax
  movq %rax, -5960(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5960(%rbp), %rsi
  movq -5952(%rbp), %rdx
  syscall
  movq %rax, -5968(%rbp)
  movq $50397203, %rax
  movq %rax, -5976(%rbp)
  jmp main_assert_pass_43
main_pr_nil_0_9172:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5984(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5984(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5992(%rbp)
  jmp main_pr_next_0_9172
main_pr_str_0_9172:
  movq -5928(%rbp), %rax
  addq $8, %rax
  movq %rax, -6000(%rbp)
  movq -6000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6008(%rbp)
  movq -5928(%rbp), %rax
  addq $24, %rax
  movq %rax, -6016(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6016(%rbp), %rsi
  movq -6008(%rbp), %rdx
  syscall
  movq %rax, -6024(%rbp)
  jmp main_pr_next_0_9172
main_pr_next_0_9172:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6032(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6032(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6040(%rbp)
  movq $0, %rax
  movq -1672(%rbp), %rdx
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

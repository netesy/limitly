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
  .byte 73
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
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
  .byte 87
  .byte 111
  .byte 114
  .byte 108
  .byte 100
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
  .byte 86
  .byte 97
  .byte 114
  .byte 105
  .byte 97
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 110
  .byte 97
  .byte 109
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
  .byte 39
  .byte 87
  .byte 111
  .byte 114
  .byte 108
  .byte 100
  .byte 39
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
  .byte 86
  .byte 97
  .byte 114
  .byte 105
  .byte 97
  .byte 98
  .byte 108
  .byte 101
  .byte 32
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
  .byte 50
  .byte 53
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
  .byte 86
  .byte 97
  .byte 114
  .byte 105
  .byte 97
  .byte 98
  .byte 108
  .byte 101
  .byte 32
  .byte 112
  .byte 105
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
  .byte 46
  .byte 49
  .byte 52
  .byte 49
  .byte 53
  .byte 57
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
  .byte 72
  .byte 101
  .byte 108
  .byte 108
  .byte 111
  .byte 44
  .byte 32
  .byte 37
  .byte 115
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
  .byte 65
  .byte 103
  .byte 101
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
  .byte 80
  .byte 105
  .byte 58
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
  .byte 72
  .byte 101
  .byte 108
  .byte 108
  .byte 111
  .byte 44
  .byte 32
  .byte 87
  .byte 111
  .byte 114
  .byte 108
  .byte 100
  .byte 33
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
  .byte 66
  .byte 97
  .byte 115
  .byte 105
  .byte 99
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
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
  .byte 65
  .byte 103
  .byte 101
  .byte 58
  .byte 32
  .byte 50
  .byte 53
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
  .byte 73
  .byte 110
  .byte 116
  .byte 101
  .byte 103
  .byte 101
  .byte 114
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
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
str_hdr_22:
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
  .byte 80
  .byte 105
  .byte 58
  .byte 32
  .byte 51
  .byte 46
  .byte 49
  .byte 52
  .byte 49
  .byte 53
  .byte 57
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
  .byte 70
  .byte 108
  .byte 111
  .byte 97
  .byte 116
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
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
str_hdr_25:
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
  .byte 78
  .byte 101
  .byte 120
  .byte 116
  .byte 32
  .byte 121
  .byte 101
  .byte 97
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
  .byte 78
  .byte 101
  .byte 120
  .byte 116
  .byte 32
  .byte 121
  .byte 101
  .byte 97
  .byte 114
  .byte 58
  .byte 32
  .byte 50
  .byte 54
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
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
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
str_hdr_30:
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
  .byte 65
  .byte 114
  .byte 101
  .byte 97
  .byte 32
  .byte 111
  .byte 102
  .byte 32
  .byte 99
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
str_hdr_32:
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
  .byte 114
  .byte 101
  .byte 97
  .byte 32
  .byte 111
  .byte 102
  .byte 32
  .byte 99
  .byte 105
  .byte 114
  .byte 99
  .byte 108
  .byte 101
  .byte 58
  .byte 32
  .byte 49
  .byte 50
  .byte 46
  .byte 53
  .byte 54
  .byte 54
  .byte 52
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
  .byte 77
  .byte 97
  .byte 116
  .byte 104
  .byte 32
  .byte 101
  .byte 120
  .byte 112
  .byte 114
  .byte 101
  .byte 115
  .byte 115
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
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
str_hdr_35:
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
  .byte 37
  .byte 115
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 37
  .byte 115
  .byte 32
  .byte 121
  .byte 101
  .byte 97
  .byte 114
  .byte 115
  .byte 32
  .byte 111
  .byte 108
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
  .byte 97
  .byte 109
  .byte 101
  .byte 58
  .byte 32
  .byte 87
  .byte 111
  .byte 114
  .byte 108
  .byte 100
  .byte 44
  .byte 32
  .byte 65
  .byte 103
  .byte 101
  .byte 58
  .byte 32
  .byte 50
  .byte 53
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
  .byte 77
  .byte 117
  .byte 108
  .byte 116
  .byte 105
  .byte 112
  .byte 108
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
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
str_hdr_42:
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
  .byte 87
  .byte 111
  .byte 114
  .byte 108
  .byte 100
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 50
  .byte 53
  .byte 32
  .byte 121
  .byte 101
  .byte 97
  .byte 114
  .byte 115
  .byte 32
  .byte 111
  .byte 108
  .byte 100
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
  .byte 77
  .byte 117
  .byte 108
  .byte 116
  .byte 105
  .byte 112
  .byte 108
  .byte 101
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
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
str_hdr_45:
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
  .byte 37
  .byte 115
  .byte 32
  .byte 115
  .byte 97
  .byte 121
  .byte 115
  .byte 32
  .byte 104
  .byte 101
  .byte 108
  .byte 108
  .byte 111
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
  .byte 37
  .byte 115
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 116
  .byte 104
  .byte 101
  .byte 32
  .byte 97
  .byte 103
  .byte 101
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
  .byte 111
  .byte 114
  .byte 108
  .byte 100
  .byte 32
  .byte 115
  .byte 97
  .byte 121
  .byte 115
  .byte 32
  .byte 104
  .byte 101
  .byte 108
  .byte 108
  .byte 111
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
  .byte 83
  .byte 116
  .byte 97
  .byte 114
  .byte 116
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
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
str_hdr_52:
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
  .byte 53
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 116
  .byte 104
  .byte 101
  .byte 32
  .byte 97
  .byte 103
  .byte 101
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
  .byte 83
  .byte 116
  .byte 97
  .byte 114
  .byte 116
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
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
str_hdr_55:
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
  .byte 77
  .byte 97
  .byte 116
  .byte 104
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
  .byte 61
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
  .byte 58
  .byte 32
  .byte 37
  .byte 115
  .byte 32
  .byte 62
  .byte 32
  .byte 37
  .byte 115
  .byte 32
  .byte 105
  .byte 115
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
str_hdr_59:
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
  .byte 77
  .byte 97
  .byte 116
  .byte 104
  .byte 58
  .byte 32
  .byte 49
  .byte 48
  .byte 32
  .byte 43
  .byte 32
  .byte 53
  .byte 32
  .byte 61
  .byte 32
  .byte 49
  .byte 53
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
  .byte 32
  .byte 109
  .byte 97
  .byte 116
  .byte 104
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
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
str_hdr_62:
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
  .byte 114
  .byte 105
  .byte 115
  .byte 111
  .byte 110
  .byte 58
  .byte 32
  .byte 49
  .byte 48
  .byte 32
  .byte 62
  .byte 32
  .byte 53
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 116
  .byte 114
  .byte 117
  .byte 101
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
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
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
str_hdr_65:
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
str_hdr_67:
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
  .byte 50
  .byte 57
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
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 101
  .byte 120
  .byte 112
  .byte 114
  .byte 101
  .byte 115
  .byte 115
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
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
str_hdr_70:
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
  .byte 72
  .byte 101
  .byte 108
  .byte 108
  .byte 111
  .byte 44
  .byte 32
  .byte 37
  .byte 115
  .byte 33
  .byte 32
  .byte 89
  .byte 111
  .byte 117
  .byte 32
  .byte 97
  .byte 114
  .byte 101
  .byte 32
  .byte 37
  .byte 115
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
  .byte 72
  .byte 101
  .byte 108
  .byte 108
  .byte 111
  .byte 44
  .byte 32
  .byte 87
  .byte 111
  .byte 114
  .byte 108
  .byte 100
  .byte 33
  .byte 32
  .byte 89
  .byte 111
  .byte 117
  .byte 32
  .byte 97
  .byte 114
  .byte 101
  .byte 32
  .byte 50
  .byte 53
  .byte 46
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
  .byte 83
  .byte 116
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
  .byte 105
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
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
str_hdr_75:
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
  .byte 73
  .byte 110
  .byte 116
  .byte 101
  .byte 114
  .byte 112
  .byte 111
  .byte 108
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
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
  subq $12504, %rsp
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
  jmp main_block_0
main_block_0:
  leaq str_hdr_0(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1320(%rbp)
  movq -1320(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -1328(%rbp)
  movq -1320(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -1336(%rbp)
  movq -1336(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1344(%rbp)
  movq -1328(%rbp), %rax
  andq -1344(%rbp), %rax
  movq %rax, -1352(%rbp)
  movq -1352(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_1
  jmp main_pr_int_0_1
main_pr_ptr_0_1:
  movq -1320(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1360(%rbp)
  movq -1320(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1368(%rbp)
  movq -1360(%rbp), %rax
  orq -1368(%rbp), %rax
  movq %rax, -1376(%rbp)
  movq -1376(%rbp), %rax
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
  movq %rax, -1384(%rbp)
  movq $11, %rax
  movq -1384(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1384(%rbp), %rax
  addq $4, %rax
  movq %rax, -1392(%rbp)
  movq $0, %rax
  movq -1392(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1384(%rbp), %rax
  addq $63, %rax
  movq %rax, -1400(%rbp)
  movq $0, %rax
  movq -1400(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1408(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1400(%rbp), %rax
  movq -1408(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1416(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1424(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1320(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1432(%rbp)
  movq -1432(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_1
  jmp main_i2s_pos_1
main_pr_nil_0_1:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1440(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1440(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1448(%rbp)
  jmp main_pr_next_0_1
main_pr_obj_0_1:
  movq -1320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1456(%rbp)
  movq -1456(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -1464(%rbp)
  movq -1464(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1472(%rbp)
  movq -1472(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_1
  jmp main_pr_nonstr_0_1
main_pr_next_0_1:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1480(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1480(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1488(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_2(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $25, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4614256650576692846, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_3(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1496(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1504(%rbp)
  movq -1496(%rbp), %rdi
  movq -1504(%rbp), %rsi
  call lm_key_eq
  mov -1512(%rbp), rax
  movq -1512(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_4(%rip), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1520(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1528(%rbp)
  movq -1520(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_5
  jmp main_assert_fail_5
main_i2s_neg_1:
  movq $1, %rax
  movq -1424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1320(%rbp), %rax
  negq %rax
  movq %rax, -1536(%rbp)
  movq -1536(%rbp), %rax
  movq -1416(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_1
main_i2s_pos_1:
  movq $0, %rax
  movq -1424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1320(%rbp), %rax
  movq -1416(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_1
main_i2s_loop_1:
  movq -1416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1544(%rbp)
  movq -1544(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -1552(%rbp)
  movq -1544(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -1560(%rbp)
  movq -1560(%rbp), %rax
  movq -1416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1552(%rbp), %rax
  addq $48, %rax
  movq %rax, -1568(%rbp)
  movq -1408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1576(%rbp)
  movq -1576(%rbp), %rax
  subq $1, %rax
  movq %rax, -1584(%rbp)
  movq -1568(%rbp), %rax
  movq -1584(%rbp), %rdx
  movb %al, (%rdx)
  movq -1584(%rbp), %rax
  movq -1408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1544(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -1592(%rbp)
  movq -1592(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_1
  jmp main_i2s_sign_1
main_i2s_sign_1:
  movq -1424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1600(%rbp)
  movq -1600(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1608(%rbp)
  movq -1608(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_1
  jmp main_i2s_done_1
main_i2s_minus_1:
  movq -1408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1616(%rbp)
  movq -1616(%rbp), %rax
  subq $1, %rax
  movq %rax, -1624(%rbp)
  movq $45, %rax
  movq -1624(%rbp), %rdx
  movb %al, (%rdx)
  movq -1624(%rbp), %rax
  movq -1408(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_1
main_i2s_done_1:
  movq -1408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1632(%rbp)
  movq -1400(%rbp), %rax
  subq -1632(%rbp), %rax
  movq %rax, -1640(%rbp)
  movq -1384(%rbp), %rax
  addq $8, %rax
  movq %rax, -1648(%rbp)
  movq -1640(%rbp), %rax
  movq -1648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1384(%rbp), %rax
  addq $16, %rax
  movq %rax, -1656(%rbp)
  movq -1640(%rbp), %rax
  movq -1656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1384(%rbp), %rax
  addq $24, %rax
  movq %rax, -1664(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1672(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1640(%rbp), %rax
  addq $1, %rax
  movq %rax, -1680(%rbp)
  jmp main_d2s_copy_loop_1
main_d2s_copy_loop_1:
  movq -1672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1688(%rbp)
  movq -1688(%rbp), %rax
  cmpq -1680(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1696(%rbp)
  movq -1696(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_1
  jmp main_d2s_copy_done_1
main_d2s_copy_body_1:
  movq -1632(%rbp), %rax
  addq -1688(%rbp), %rax
  movq %rax, -1704(%rbp)
  movq -1704(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -1712(%rbp)
  movq -1664(%rbp), %rax
  addq -1688(%rbp), %rax
  movq %rax, -1720(%rbp)
  movq -1712(%rbp), %rax
  movq -1720(%rbp), %rdx
  movb %al, (%rdx)
  movq -1688(%rbp), %rax
  addq $1, %rax
  movq %rax, -1728(%rbp)
  movq -1728(%rbp), %rax
  movq -1672(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_1
main_d2s_copy_done_1:
  movq -1384(%rbp), %rax
  addq $24, %rax
  movq %rax, -1736(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1744(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -1744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1640(%rbp), %rax
  addq $1, %rax
  movq %rax, -1752(%rbp)
  jmp main_i2s_copy_loop_1
main_i2s_copy_loop_1:
  movq -1744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1760(%rbp)
  movq -1760(%rbp), %rax
  cmpq -1752(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1768(%rbp)
  movq -1768(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_1
  jmp main_i2s_copy_done_1
main_i2s_copy_body_1:
  movq -1632(%rbp), %rax
  addq -1760(%rbp), %rax
  movq %rax, -1776(%rbp)
  movq -1776(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -1784(%rbp)
  movq -1736(%rbp), %rax
  addq -1760(%rbp), %rax
  movq %rax, -1792(%rbp)
  movq -1784(%rbp), %rax
  movq -1792(%rbp), %rdx
  movb %al, (%rdx)
  movq -1760(%rbp), %rax
  addq $1, %rax
  movq %rax, -1800(%rbp)
  movq -1800(%rbp), %rax
  movq -1744(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_1
main_i2s_copy_done_1:
  movq -1384(%rbp), %rax
  addq $8, %rax
  movq %rax, -1808(%rbp)
  movq -1808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1816(%rbp)
  movq -1384(%rbp), %rax
  addq $24, %rax
  movq %rax, -1824(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1824(%rbp), %rsi
  movq -1816(%rbp), %rdx
  syscall
  movq %rax, -1832(%rbp)
  jmp main_pr_next_0_1
main_pr_str_0_1:
  movq -1320(%rbp), %rax
  addq $8, %rax
  movq %rax, -1840(%rbp)
  movq -1840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1848(%rbp)
  movq -1320(%rbp), %rax
  addq $24, %rax
  movq %rax, -1856(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1856(%rbp), %rsi
  movq -1848(%rbp), %rdx
  syscall
  movq %rax, -1864(%rbp)
  jmp main_pr_next_0_1
main_pr_enum_0_1:
  movq -1320(%rbp), %rdi
  call lm_enum_to_str
  mov -1872(%rbp), rax
  movq -1872(%rbp), %rax
  addq $8, %rax
  movq %rax, -1880(%rbp)
  movq -1880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1888(%rbp)
  movq -1872(%rbp), %rax
  addq $24, %rax
  movq %rax, -1896(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1896(%rbp), %rsi
  movq -1888(%rbp), %rdx
  syscall
  movq %rax, -1904(%rbp)
  jmp main_pr_next_0_1
main_pr_list_0_1:
  movq -1320(%rbp), %rdi
  call lm_list_to_str
  mov -1912(%rbp), rax
  movq -1912(%rbp), %rax
  addq $8, %rax
  movq %rax, -1920(%rbp)
  movq -1920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1928(%rbp)
  movq -1912(%rbp), %rax
  addq $24, %rax
  movq %rax, -1936(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1936(%rbp), %rsi
  movq -1928(%rbp), %rdx
  syscall
  movq %rax, -1944(%rbp)
  jmp main_pr_next_0_1
main_pr_nonstr_0_1:
  movq -1456(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1952(%rbp)
  movq -1952(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_1
  jmp main_pr_list_0_1
main_assert_pass_5:
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq $25, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1960(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1968(%rbp)
  movq -1968(%rbp), %rax
  cmpq -1960(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1976(%rbp)
  movq -1976(%rbp), %rax
  movq -128(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_6(%rip), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1984(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1992(%rbp)
  movq -1984(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_7
  jmp main_assert_fail_7
main_assert_fail_5:
  movq -1528(%rbp), %rax
  addq $8, %rax
  movq %rax, -2000(%rbp)
  movq -2000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2008(%rbp)
  movq -1528(%rbp), %rax
  addq $24, %rax
  movq %rax, -2016(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2016(%rbp), %rsi
  movq -2008(%rbp), %rdx
  syscall
  movq %rax, -2024(%rbp)
  movq $50397203, %rax
  movq %rax, -2032(%rbp)
  jmp main_assert_pass_5
main_assert_pass_7:
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4614256650576692846, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2040(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2048(%rbp)
  movq -2048(%rbp), %rax
  cmpq -2040(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2056(%rbp)
  movq -2056(%rbp), %rax
  movq -160(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_8(%rip), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2064(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2072(%rbp)
  movq -2064(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_9
  jmp main_assert_fail_9
main_assert_fail_7:
  movq -1992(%rbp), %rax
  addq $8, %rax
  movq %rax, -2080(%rbp)
  movq -2080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2088(%rbp)
  movq -1992(%rbp), %rax
  addq $24, %rax
  movq %rax, -2096(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2096(%rbp), %rsi
  movq -2088(%rbp), %rdx
  syscall
  movq %rax, -2104(%rbp)
  movq $50397203, %rax
  movq %rax, -2112(%rbp)
  jmp main_assert_pass_7
main_assert_pass_9:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_10(%rip), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2120(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2128(%rbp)
  movq -2120(%rbp), %rdi
  movq -2128(%rbp), %rsi
  call lm_rt_str_format
  mov -2136(%rbp), rax
  movq -2136(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2144(%rbp)
  movq -2144(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_11(%rip), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2152(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2160(%rbp)
  movq -2160(%rbp), %rdi
  call lm_to_string
  mov -2168(%rbp), rax
  movq -2152(%rbp), %rdi
  movq -2168(%rbp), %rsi
  call lm_rt_str_format
  mov -2176(%rbp), rax
  movq -2176(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2184(%rbp)
  movq -2184(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_12(%rip), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2192(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2200(%rbp)
  movq -2200(%rbp), %rdi
  call lm_to_string
  mov -2208(%rbp), rax
  movq -2192(%rbp), %rdi
  movq -2208(%rbp), %rsi
  call lm_rt_str_format
  mov -2216(%rbp), rax
  movq -2216(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2224(%rbp)
  movq -2224(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2232(%rbp)
  movq -2232(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -2240(%rbp)
  movq -2232(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -2248(%rbp)
  movq -2248(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2256(%rbp)
  movq -2240(%rbp), %rax
  andq -2256(%rbp), %rax
  movq %rax, -2264(%rbp)
  movq -2264(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_13
  jmp main_pr_int_0_13
main_assert_fail_9:
  movq -2072(%rbp), %rax
  addq $8, %rax
  movq %rax, -2272(%rbp)
  movq -2272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2280(%rbp)
  movq -2072(%rbp), %rax
  addq $24, %rax
  movq %rax, -2288(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2288(%rbp), %rsi
  movq -2280(%rbp), %rdx
  syscall
  movq %rax, -2296(%rbp)
  movq $50397203, %rax
  movq %rax, -2304(%rbp)
  jmp main_assert_pass_9
main_pr_ptr_0_13:
  movq -2232(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2312(%rbp)
  movq -2232(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2320(%rbp)
  movq -2312(%rbp), %rax
  orq -2320(%rbp), %rax
  movq %rax, -2328(%rbp)
  movq -2328(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_13
  jmp main_pr_obj_0_13
main_pr_int_0_13:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -2336(%rbp)
  movq $11, %rax
  movq -2336(%rbp), %rdx
  movl %eax, (%rdx)
  movq -2336(%rbp), %rax
  addq $4, %rax
  movq %rax, -2344(%rbp)
  movq $0, %rax
  movq -2344(%rbp), %rdx
  movl %eax, (%rdx)
  movq -2336(%rbp), %rax
  addq $63, %rax
  movq %rax, -2352(%rbp)
  movq $0, %rax
  movq -2352(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2360(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -2352(%rbp), %rax
  movq -2360(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2368(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2376(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -2232(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2384(%rbp)
  movq -2384(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_5
  jmp main_i2s_pos_5
main_pr_nil_0_13:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2392(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2392(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2400(%rbp)
  jmp main_pr_next_0_13
main_pr_obj_0_13:
  movq -2232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2408(%rbp)
  movq -2408(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -2416(%rbp)
  movq -2416(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2424(%rbp)
  movq -2424(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_13
  jmp main_pr_nonstr_0_13
main_pr_next_0_13:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2432(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2432(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2440(%rbp)
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2448(%rbp)
  movq -2448(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -2456(%rbp)
  movq -2448(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -2464(%rbp)
  movq -2464(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2472(%rbp)
  movq -2456(%rbp), %rax
  andq -2472(%rbp), %rax
  movq %rax, -2480(%rbp)
  movq -2480(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_14
  jmp main_pr_int_0_14
main_i2s_neg_5:
  movq $1, %rax
  movq -2376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2232(%rbp), %rax
  negq %rax
  movq %rax, -2488(%rbp)
  movq -2488(%rbp), %rax
  movq -2368(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_5
main_i2s_pos_5:
  movq $0, %rax
  movq -2376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2232(%rbp), %rax
  movq -2368(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_5
main_i2s_loop_5:
  movq -2368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2496(%rbp)
  movq -2496(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -2504(%rbp)
  movq -2496(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -2512(%rbp)
  movq -2512(%rbp), %rax
  movq -2368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2504(%rbp), %rax
  addq $48, %rax
  movq %rax, -2520(%rbp)
  movq -2360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2528(%rbp)
  movq -2528(%rbp), %rax
  subq $1, %rax
  movq %rax, -2536(%rbp)
  movq -2520(%rbp), %rax
  movq -2536(%rbp), %rdx
  movb %al, (%rdx)
  movq -2536(%rbp), %rax
  movq -2360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2496(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -2544(%rbp)
  movq -2544(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_5
  jmp main_i2s_sign_5
main_i2s_sign_5:
  movq -2376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2552(%rbp)
  movq -2552(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2560(%rbp)
  movq -2560(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_5
  jmp main_i2s_done_5
main_i2s_minus_5:
  movq -2360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2568(%rbp)
  movq -2568(%rbp), %rax
  subq $1, %rax
  movq %rax, -2576(%rbp)
  movq $45, %rax
  movq -2576(%rbp), %rdx
  movb %al, (%rdx)
  movq -2576(%rbp), %rax
  movq -2360(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_5
main_i2s_done_5:
  movq -2360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2584(%rbp)
  movq -2352(%rbp), %rax
  subq -2584(%rbp), %rax
  movq %rax, -2592(%rbp)
  movq -2336(%rbp), %rax
  addq $8, %rax
  movq %rax, -2600(%rbp)
  movq -2592(%rbp), %rax
  movq -2600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2336(%rbp), %rax
  addq $16, %rax
  movq %rax, -2608(%rbp)
  movq -2592(%rbp), %rax
  movq -2608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2336(%rbp), %rax
  addq $24, %rax
  movq %rax, -2616(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2624(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2592(%rbp), %rax
  addq $1, %rax
  movq %rax, -2632(%rbp)
  jmp main_d2s_copy_loop_5
main_d2s_copy_loop_5:
  movq -2624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2640(%rbp)
  movq -2640(%rbp), %rax
  cmpq -2632(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2648(%rbp)
  movq -2648(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_5
  jmp main_d2s_copy_done_5
main_d2s_copy_body_5:
  movq -2584(%rbp), %rax
  addq -2640(%rbp), %rax
  movq %rax, -2656(%rbp)
  movq -2656(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -2664(%rbp)
  movq -2616(%rbp), %rax
  addq -2640(%rbp), %rax
  movq %rax, -2672(%rbp)
  movq -2664(%rbp), %rax
  movq -2672(%rbp), %rdx
  movb %al, (%rdx)
  movq -2640(%rbp), %rax
  addq $1, %rax
  movq %rax, -2680(%rbp)
  movq -2680(%rbp), %rax
  movq -2624(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_5
main_d2s_copy_done_5:
  movq -2336(%rbp), %rax
  addq $24, %rax
  movq %rax, -2688(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2696(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -2696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2592(%rbp), %rax
  addq $1, %rax
  movq %rax, -2704(%rbp)
  jmp main_i2s_copy_loop_5
main_i2s_copy_loop_5:
  movq -2696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2712(%rbp)
  movq -2712(%rbp), %rax
  cmpq -2704(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2720(%rbp)
  movq -2720(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_5
  jmp main_i2s_copy_done_5
main_i2s_copy_body_5:
  movq -2584(%rbp), %rax
  addq -2712(%rbp), %rax
  movq %rax, -2728(%rbp)
  movq -2728(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -2736(%rbp)
  movq -2688(%rbp), %rax
  addq -2712(%rbp), %rax
  movq %rax, -2744(%rbp)
  movq -2736(%rbp), %rax
  movq -2744(%rbp), %rdx
  movb %al, (%rdx)
  movq -2712(%rbp), %rax
  addq $1, %rax
  movq %rax, -2752(%rbp)
  movq -2752(%rbp), %rax
  movq -2696(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_5
main_i2s_copy_done_5:
  movq -2336(%rbp), %rax
  addq $8, %rax
  movq %rax, -2760(%rbp)
  movq -2760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2768(%rbp)
  movq -2336(%rbp), %rax
  addq $24, %rax
  movq %rax, -2776(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2776(%rbp), %rsi
  movq -2768(%rbp), %rdx
  syscall
  movq %rax, -2784(%rbp)
  jmp main_pr_next_0_13
main_pr_str_0_13:
  movq -2232(%rbp), %rax
  addq $8, %rax
  movq %rax, -2792(%rbp)
  movq -2792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2800(%rbp)
  movq -2232(%rbp), %rax
  addq $24, %rax
  movq %rax, -2808(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2808(%rbp), %rsi
  movq -2800(%rbp), %rdx
  syscall
  movq %rax, -2816(%rbp)
  jmp main_pr_next_0_13
main_pr_enum_0_13:
  movq -2232(%rbp), %rdi
  call lm_enum_to_str
  mov -2824(%rbp), rax
  movq -2824(%rbp), %rax
  addq $8, %rax
  movq %rax, -2832(%rbp)
  movq -2832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2840(%rbp)
  movq -2824(%rbp), %rax
  addq $24, %rax
  movq %rax, -2848(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2848(%rbp), %rsi
  movq -2840(%rbp), %rdx
  syscall
  movq %rax, -2856(%rbp)
  jmp main_pr_next_0_13
main_pr_list_0_13:
  movq -2232(%rbp), %rdi
  call lm_list_to_str
  mov -2864(%rbp), rax
  movq -2864(%rbp), %rax
  addq $8, %rax
  movq %rax, -2872(%rbp)
  movq -2872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2880(%rbp)
  movq -2864(%rbp), %rax
  addq $24, %rax
  movq %rax, -2888(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2888(%rbp), %rsi
  movq -2880(%rbp), %rdx
  syscall
  movq %rax, -2896(%rbp)
  jmp main_pr_next_0_13
main_pr_nonstr_0_13:
  movq -2408(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2904(%rbp)
  movq -2904(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_13
  jmp main_pr_list_0_13
main_pr_ptr_0_14:
  movq -2448(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2912(%rbp)
  movq -2448(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2920(%rbp)
  movq -2912(%rbp), %rax
  orq -2920(%rbp), %rax
  movq %rax, -2928(%rbp)
  movq -2928(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_14
  jmp main_pr_obj_0_14
main_pr_int_0_14:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -2936(%rbp)
  movq $11, %rax
  movq -2936(%rbp), %rdx
  movl %eax, (%rdx)
  movq -2936(%rbp), %rax
  addq $4, %rax
  movq %rax, -2944(%rbp)
  movq $0, %rax
  movq -2944(%rbp), %rdx
  movl %eax, (%rdx)
  movq -2936(%rbp), %rax
  addq $63, %rax
  movq %rax, -2952(%rbp)
  movq $0, %rax
  movq -2952(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2960(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -2952(%rbp), %rax
  movq -2960(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2968(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -2976(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -2448(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2984(%rbp)
  movq -2984(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_6
  jmp main_i2s_pos_6
main_pr_nil_0_14:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2992(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2992(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3000(%rbp)
  jmp main_pr_next_0_14
main_pr_obj_0_14:
  movq -2448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3008(%rbp)
  movq -3008(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -3016(%rbp)
  movq -3016(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3024(%rbp)
  movq -3024(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_14
  jmp main_pr_nonstr_0_14
main_pr_next_0_14:
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
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3048(%rbp)
  movq -3048(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -3056(%rbp)
  movq -3048(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -3064(%rbp)
  movq -3064(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3072(%rbp)
  movq -3056(%rbp), %rax
  andq -3072(%rbp), %rax
  movq %rax, -3080(%rbp)
  movq -3080(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_15
  jmp main_pr_int_0_15
main_i2s_neg_6:
  movq $1, %rax
  movq -2976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2448(%rbp), %rax
  negq %rax
  movq %rax, -3088(%rbp)
  movq -3088(%rbp), %rax
  movq -2968(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_6
main_i2s_pos_6:
  movq $0, %rax
  movq -2976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2448(%rbp), %rax
  movq -2968(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_6
main_i2s_loop_6:
  movq -2968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3096(%rbp)
  movq -3096(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -3104(%rbp)
  movq -3096(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -3112(%rbp)
  movq -3112(%rbp), %rax
  movq -2968(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3104(%rbp), %rax
  addq $48, %rax
  movq %rax, -3120(%rbp)
  movq -2960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3128(%rbp)
  movq -3128(%rbp), %rax
  subq $1, %rax
  movq %rax, -3136(%rbp)
  movq -3120(%rbp), %rax
  movq -3136(%rbp), %rdx
  movb %al, (%rdx)
  movq -3136(%rbp), %rax
  movq -2960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3096(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -3144(%rbp)
  movq -3144(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_6
  jmp main_i2s_sign_6
main_i2s_sign_6:
  movq -2976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3152(%rbp)
  movq -3152(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3160(%rbp)
  movq -3160(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_6
  jmp main_i2s_done_6
main_i2s_minus_6:
  movq -2960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3168(%rbp)
  movq -3168(%rbp), %rax
  subq $1, %rax
  movq %rax, -3176(%rbp)
  movq $45, %rax
  movq -3176(%rbp), %rdx
  movb %al, (%rdx)
  movq -3176(%rbp), %rax
  movq -2960(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_6
main_i2s_done_6:
  movq -2960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3184(%rbp)
  movq -2952(%rbp), %rax
  subq -3184(%rbp), %rax
  movq %rax, -3192(%rbp)
  movq -2936(%rbp), %rax
  addq $8, %rax
  movq %rax, -3200(%rbp)
  movq -3192(%rbp), %rax
  movq -3200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2936(%rbp), %rax
  addq $16, %rax
  movq %rax, -3208(%rbp)
  movq -3192(%rbp), %rax
  movq -3208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2936(%rbp), %rax
  addq $24, %rax
  movq %rax, -3216(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3192(%rbp), %rax
  addq $1, %rax
  movq %rax, -3232(%rbp)
  jmp main_d2s_copy_loop_6
main_d2s_copy_loop_6:
  movq -3224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3240(%rbp)
  movq -3240(%rbp), %rax
  cmpq -3232(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -3248(%rbp)
  movq -3248(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_6
  jmp main_d2s_copy_done_6
main_d2s_copy_body_6:
  movq -3184(%rbp), %rax
  addq -3240(%rbp), %rax
  movq %rax, -3256(%rbp)
  movq -3256(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -3264(%rbp)
  movq -3216(%rbp), %rax
  addq -3240(%rbp), %rax
  movq %rax, -3272(%rbp)
  movq -3264(%rbp), %rax
  movq -3272(%rbp), %rdx
  movb %al, (%rdx)
  movq -3240(%rbp), %rax
  addq $1, %rax
  movq %rax, -3280(%rbp)
  movq -3280(%rbp), %rax
  movq -3224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_6
main_d2s_copy_done_6:
  movq -2936(%rbp), %rax
  addq $24, %rax
  movq %rax, -3288(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3192(%rbp), %rax
  addq $1, %rax
  movq %rax, -3304(%rbp)
  jmp main_i2s_copy_loop_6
main_i2s_copy_loop_6:
  movq -3296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3312(%rbp)
  movq -3312(%rbp), %rax
  cmpq -3304(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -3320(%rbp)
  movq -3320(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_6
  jmp main_i2s_copy_done_6
main_i2s_copy_body_6:
  movq -3184(%rbp), %rax
  addq -3312(%rbp), %rax
  movq %rax, -3328(%rbp)
  movq -3328(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -3336(%rbp)
  movq -3288(%rbp), %rax
  addq -3312(%rbp), %rax
  movq %rax, -3344(%rbp)
  movq -3336(%rbp), %rax
  movq -3344(%rbp), %rdx
  movb %al, (%rdx)
  movq -3312(%rbp), %rax
  addq $1, %rax
  movq %rax, -3352(%rbp)
  movq -3352(%rbp), %rax
  movq -3296(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_6
main_i2s_copy_done_6:
  movq -2936(%rbp), %rax
  addq $8, %rax
  movq %rax, -3360(%rbp)
  movq -3360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3368(%rbp)
  movq -2936(%rbp), %rax
  addq $24, %rax
  movq %rax, -3376(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3376(%rbp), %rsi
  movq -3368(%rbp), %rdx
  syscall
  movq %rax, -3384(%rbp)
  jmp main_pr_next_0_14
main_pr_str_0_14:
  movq -2448(%rbp), %rax
  addq $8, %rax
  movq %rax, -3392(%rbp)
  movq -3392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3400(%rbp)
  movq -2448(%rbp), %rax
  addq $24, %rax
  movq %rax, -3408(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3408(%rbp), %rsi
  movq -3400(%rbp), %rdx
  syscall
  movq %rax, -3416(%rbp)
  jmp main_pr_next_0_14
main_pr_enum_0_14:
  movq -2448(%rbp), %rdi
  call lm_enum_to_str
  mov -3424(%rbp), rax
  movq -3424(%rbp), %rax
  addq $8, %rax
  movq %rax, -3432(%rbp)
  movq -3432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3440(%rbp)
  movq -3424(%rbp), %rax
  addq $24, %rax
  movq %rax, -3448(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3448(%rbp), %rsi
  movq -3440(%rbp), %rdx
  syscall
  movq %rax, -3456(%rbp)
  jmp main_pr_next_0_14
main_pr_list_0_14:
  movq -2448(%rbp), %rdi
  call lm_list_to_str
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
  jmp main_pr_next_0_14
main_pr_nonstr_0_14:
  movq -3008(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3504(%rbp)
  movq -3504(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_14
  jmp main_pr_list_0_14
main_pr_ptr_0_15:
  movq -3048(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3512(%rbp)
  movq -3048(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3520(%rbp)
  movq -3512(%rbp), %rax
  orq -3520(%rbp), %rax
  movq %rax, -3528(%rbp)
  movq -3528(%rbp), %rax
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
  movq %rax, -3536(%rbp)
  movq $11, %rax
  movq -3536(%rbp), %rdx
  movl %eax, (%rdx)
  movq -3536(%rbp), %rax
  addq $4, %rax
  movq %rax, -3544(%rbp)
  movq $0, %rax
  movq -3544(%rbp), %rdx
  movl %eax, (%rdx)
  movq -3536(%rbp), %rax
  addq $63, %rax
  movq %rax, -3552(%rbp)
  movq $0, %rax
  movq -3552(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3560(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -3552(%rbp), %rax
  movq -3560(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3568(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3576(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -3048(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -3584(%rbp)
  movq -3584(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_7
  jmp main_i2s_pos_7
main_pr_nil_0_15:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3592(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3592(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3600(%rbp)
  jmp main_pr_next_0_15
main_pr_obj_0_15:
  movq -3048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3608(%rbp)
  movq -3608(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -3616(%rbp)
  movq -3616(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3624(%rbp)
  movq -3624(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_15
  jmp main_pr_nonstr_0_15
main_pr_next_0_15:
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
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_16(%rip), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3648(%rbp)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3656(%rbp)
  movq -3648(%rbp), %rdi
  movq -3656(%rbp), %rsi
  call lm_key_eq
  mov -3664(%rbp), rax
  movq -3664(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_17(%rip), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3672(%rbp)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3680(%rbp)
  movq -3672(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_18
  jmp main_assert_fail_18
main_i2s_neg_7:
  movq $1, %rax
  movq -3576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3048(%rbp), %rax
  negq %rax
  movq %rax, -3688(%rbp)
  movq -3688(%rbp), %rax
  movq -3568(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_7
main_i2s_pos_7:
  movq $0, %rax
  movq -3576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3048(%rbp), %rax
  movq -3568(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_7
main_i2s_loop_7:
  movq -3568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3696(%rbp)
  movq -3696(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -3704(%rbp)
  movq -3696(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -3712(%rbp)
  movq -3712(%rbp), %rax
  movq -3568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3704(%rbp), %rax
  addq $48, %rax
  movq %rax, -3720(%rbp)
  movq -3560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3728(%rbp)
  movq -3728(%rbp), %rax
  subq $1, %rax
  movq %rax, -3736(%rbp)
  movq -3720(%rbp), %rax
  movq -3736(%rbp), %rdx
  movb %al, (%rdx)
  movq -3736(%rbp), %rax
  movq -3560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3696(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -3744(%rbp)
  movq -3744(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_7
  jmp main_i2s_sign_7
main_i2s_sign_7:
  movq -3576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3752(%rbp)
  movq -3752(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3760(%rbp)
  movq -3760(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_7
  jmp main_i2s_done_7
main_i2s_minus_7:
  movq -3560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3768(%rbp)
  movq -3768(%rbp), %rax
  subq $1, %rax
  movq %rax, -3776(%rbp)
  movq $45, %rax
  movq -3776(%rbp), %rdx
  movb %al, (%rdx)
  movq -3776(%rbp), %rax
  movq -3560(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_7
main_i2s_done_7:
  movq -3560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3784(%rbp)
  movq -3552(%rbp), %rax
  subq -3784(%rbp), %rax
  movq %rax, -3792(%rbp)
  movq -3536(%rbp), %rax
  addq $8, %rax
  movq %rax, -3800(%rbp)
  movq -3792(%rbp), %rax
  movq -3800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3536(%rbp), %rax
  addq $16, %rax
  movq %rax, -3808(%rbp)
  movq -3792(%rbp), %rax
  movq -3808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3536(%rbp), %rax
  addq $24, %rax
  movq %rax, -3816(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3824(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3824(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3792(%rbp), %rax
  addq $1, %rax
  movq %rax, -3832(%rbp)
  jmp main_d2s_copy_loop_7
main_d2s_copy_loop_7:
  movq -3824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3840(%rbp)
  movq -3840(%rbp), %rax
  cmpq -3832(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -3848(%rbp)
  movq -3848(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_7
  jmp main_d2s_copy_done_7
main_d2s_copy_body_7:
  movq -3784(%rbp), %rax
  addq -3840(%rbp), %rax
  movq %rax, -3856(%rbp)
  movq -3856(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -3864(%rbp)
  movq -3816(%rbp), %rax
  addq -3840(%rbp), %rax
  movq %rax, -3872(%rbp)
  movq -3864(%rbp), %rax
  movq -3872(%rbp), %rdx
  movb %al, (%rdx)
  movq -3840(%rbp), %rax
  addq $1, %rax
  movq %rax, -3880(%rbp)
  movq -3880(%rbp), %rax
  movq -3824(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_7
main_d2s_copy_done_7:
  movq -3536(%rbp), %rax
  addq $24, %rax
  movq %rax, -3888(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -3896(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -3896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3792(%rbp), %rax
  addq $1, %rax
  movq %rax, -3904(%rbp)
  jmp main_i2s_copy_loop_7
main_i2s_copy_loop_7:
  movq -3896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3912(%rbp)
  movq -3912(%rbp), %rax
  cmpq -3904(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -3920(%rbp)
  movq -3920(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_7
  jmp main_i2s_copy_done_7
main_i2s_copy_body_7:
  movq -3784(%rbp), %rax
  addq -3912(%rbp), %rax
  movq %rax, -3928(%rbp)
  movq -3928(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -3936(%rbp)
  movq -3888(%rbp), %rax
  addq -3912(%rbp), %rax
  movq %rax, -3944(%rbp)
  movq -3936(%rbp), %rax
  movq -3944(%rbp), %rdx
  movb %al, (%rdx)
  movq -3912(%rbp), %rax
  addq $1, %rax
  movq %rax, -3952(%rbp)
  movq -3952(%rbp), %rax
  movq -3896(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_7
main_i2s_copy_done_7:
  movq -3536(%rbp), %rax
  addq $8, %rax
  movq %rax, -3960(%rbp)
  movq -3960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3968(%rbp)
  movq -3536(%rbp), %rax
  addq $24, %rax
  movq %rax, -3976(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3976(%rbp), %rsi
  movq -3968(%rbp), %rdx
  syscall
  movq %rax, -3984(%rbp)
  jmp main_pr_next_0_15
main_pr_str_0_15:
  movq -3048(%rbp), %rax
  addq $8, %rax
  movq %rax, -3992(%rbp)
  movq -3992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4000(%rbp)
  movq -3048(%rbp), %rax
  addq $24, %rax
  movq %rax, -4008(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4008(%rbp), %rsi
  movq -4000(%rbp), %rdx
  syscall
  movq %rax, -4016(%rbp)
  jmp main_pr_next_0_15
main_pr_enum_0_15:
  movq -3048(%rbp), %rdi
  call lm_enum_to_str
  mov -4024(%rbp), rax
  movq -4024(%rbp), %rax
  addq $8, %rax
  movq %rax, -4032(%rbp)
  movq -4032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4040(%rbp)
  movq -4024(%rbp), %rax
  addq $24, %rax
  movq %rax, -4048(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4048(%rbp), %rsi
  movq -4040(%rbp), %rdx
  syscall
  movq %rax, -4056(%rbp)
  jmp main_pr_next_0_15
main_pr_list_0_15:
  movq -3048(%rbp), %rdi
  call lm_list_to_str
  mov -4064(%rbp), rax
  movq -4064(%rbp), %rax
  addq $8, %rax
  movq %rax, -4072(%rbp)
  movq -4072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4080(%rbp)
  movq -4064(%rbp), %rax
  addq $24, %rax
  movq %rax, -4088(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4088(%rbp), %rsi
  movq -4080(%rbp), %rdx
  syscall
  movq %rax, -4096(%rbp)
  jmp main_pr_next_0_15
main_pr_nonstr_0_15:
  movq -3608(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4104(%rbp)
  movq -4104(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_15
  jmp main_pr_list_0_15
main_assert_pass_18:
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_19(%rip), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4112(%rbp)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4120(%rbp)
  movq -4112(%rbp), %rdi
  movq -4120(%rbp), %rsi
  call lm_key_eq
  mov -4128(%rbp), rax
  movq -4128(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_20(%rip), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4136(%rbp)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4144(%rbp)
  movq -4136(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_21
  jmp main_assert_fail_21
main_assert_fail_18:
  movq -3680(%rbp), %rax
  addq $8, %rax
  movq %rax, -4152(%rbp)
  movq -4152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4160(%rbp)
  movq -3680(%rbp), %rax
  addq $24, %rax
  movq %rax, -4168(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4168(%rbp), %rsi
  movq -4160(%rbp), %rdx
  syscall
  movq %rax, -4176(%rbp)
  movq $50397203, %rax
  movq %rax, -4184(%rbp)
  jmp main_assert_pass_18
main_assert_pass_21:
  movq $0, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_22(%rip), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4192(%rbp)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4200(%rbp)
  movq -4192(%rbp), %rdi
  movq -4200(%rbp), %rsi
  call lm_key_eq
  mov -4208(%rbp), rax
  movq -4208(%rbp), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_23(%rip), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4216(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4224(%rbp)
  movq -4216(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_24
  jmp main_assert_fail_24
main_assert_fail_21:
  movq -4144(%rbp), %rax
  addq $8, %rax
  movq %rax, -4232(%rbp)
  movq -4232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4240(%rbp)
  movq -4144(%rbp), %rax
  addq $24, %rax
  movq %rax, -4248(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4248(%rbp), %rsi
  movq -4240(%rbp), %rdx
  syscall
  movq %rax, -4256(%rbp)
  movq $50397203, %rax
  movq %rax, -4264(%rbp)
  jmp main_assert_pass_21
main_assert_pass_24:
  movq $0, %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4272(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4280(%rbp)
  movq -4280(%rbp), %rax
  addq -4272(%rbp), %rax
  movq %rax, -4288(%rbp)
  movq -4288(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_25(%rip), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4296(%rbp)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4304(%rbp)
  movq -4304(%rbp), %rdi
  call lm_to_string
  mov -4312(%rbp), rax
  movq -4296(%rbp), %rdi
  movq -4312(%rbp), %rsi
  call lm_rt_str_format
  mov -4320(%rbp), rax
  movq -4320(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4328(%rbp)
  movq -4328(%rbp), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4336(%rbp)
  movq -4336(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -4344(%rbp)
  movq -4336(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -4352(%rbp)
  movq -4352(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4360(%rbp)
  movq -4344(%rbp), %rax
  andq -4360(%rbp), %rax
  movq %rax, -4368(%rbp)
  movq -4368(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_26
  jmp main_pr_int_0_26
main_assert_fail_24:
  movq -4224(%rbp), %rax
  addq $8, %rax
  movq %rax, -4376(%rbp)
  movq -4376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4384(%rbp)
  movq -4224(%rbp), %rax
  addq $24, %rax
  movq %rax, -4392(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4392(%rbp), %rsi
  movq -4384(%rbp), %rdx
  syscall
  movq %rax, -4400(%rbp)
  movq $50397203, %rax
  movq %rax, -4408(%rbp)
  jmp main_assert_pass_24
main_pr_ptr_0_26:
  movq -4336(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4416(%rbp)
  movq -4336(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4424(%rbp)
  movq -4416(%rbp), %rax
  orq -4424(%rbp), %rax
  movq %rax, -4432(%rbp)
  movq -4432(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_26
  jmp main_pr_obj_0_26
main_pr_int_0_26:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -4440(%rbp)
  movq $11, %rax
  movq -4440(%rbp), %rdx
  movl %eax, (%rdx)
  movq -4440(%rbp), %rax
  addq $4, %rax
  movq %rax, -4448(%rbp)
  movq $0, %rax
  movq -4448(%rbp), %rdx
  movl %eax, (%rdx)
  movq -4440(%rbp), %rax
  addq $63, %rax
  movq %rax, -4456(%rbp)
  movq $0, %rax
  movq -4456(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4464(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -4456(%rbp), %rax
  movq -4464(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4472(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4480(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -4336(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -4488(%rbp)
  movq -4488(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_8
  jmp main_i2s_pos_8
main_pr_nil_0_26:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4496(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4496(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4504(%rbp)
  jmp main_pr_next_0_26
main_pr_obj_0_26:
  movq -4336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4512(%rbp)
  movq -4512(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -4520(%rbp)
  movq -4520(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4528(%rbp)
  movq -4528(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_26
  jmp main_pr_nonstr_0_26
main_pr_next_0_26:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4536(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4536(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4544(%rbp)
  movq $0, %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_27(%rip), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4552(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4560(%rbp)
  movq -4552(%rbp), %rdi
  movq -4560(%rbp), %rsi
  call lm_key_eq
  mov -4568(%rbp), rax
  movq -4568(%rbp), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_28(%rip), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4576(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4584(%rbp)
  movq -4576(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_29
  jmp main_assert_fail_29
main_i2s_neg_8:
  movq $1, %rax
  movq -4480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4336(%rbp), %rax
  negq %rax
  movq %rax, -4592(%rbp)
  movq -4592(%rbp), %rax
  movq -4472(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_8
main_i2s_pos_8:
  movq $0, %rax
  movq -4480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4336(%rbp), %rax
  movq -4472(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_8
main_i2s_loop_8:
  movq -4472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4600(%rbp)
  movq -4600(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -4608(%rbp)
  movq -4600(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -4616(%rbp)
  movq -4616(%rbp), %rax
  movq -4472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4608(%rbp), %rax
  addq $48, %rax
  movq %rax, -4624(%rbp)
  movq -4464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4632(%rbp)
  movq -4632(%rbp), %rax
  subq $1, %rax
  movq %rax, -4640(%rbp)
  movq -4624(%rbp), %rax
  movq -4640(%rbp), %rdx
  movb %al, (%rdx)
  movq -4640(%rbp), %rax
  movq -4464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4600(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -4648(%rbp)
  movq -4648(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_8
  jmp main_i2s_sign_8
main_i2s_sign_8:
  movq -4480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4656(%rbp)
  movq -4656(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4664(%rbp)
  movq -4664(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_8
  jmp main_i2s_done_8
main_i2s_minus_8:
  movq -4464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4672(%rbp)
  movq -4672(%rbp), %rax
  subq $1, %rax
  movq %rax, -4680(%rbp)
  movq $45, %rax
  movq -4680(%rbp), %rdx
  movb %al, (%rdx)
  movq -4680(%rbp), %rax
  movq -4464(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_8
main_i2s_done_8:
  movq -4464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4688(%rbp)
  movq -4456(%rbp), %rax
  subq -4688(%rbp), %rax
  movq %rax, -4696(%rbp)
  movq -4440(%rbp), %rax
  addq $8, %rax
  movq %rax, -4704(%rbp)
  movq -4696(%rbp), %rax
  movq -4704(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4440(%rbp), %rax
  addq $16, %rax
  movq %rax, -4712(%rbp)
  movq -4696(%rbp), %rax
  movq -4712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4440(%rbp), %rax
  addq $24, %rax
  movq %rax, -4720(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4728(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -4728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4696(%rbp), %rax
  addq $1, %rax
  movq %rax, -4736(%rbp)
  jmp main_d2s_copy_loop_8
main_d2s_copy_loop_8:
  movq -4728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4744(%rbp)
  movq -4744(%rbp), %rax
  cmpq -4736(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -4752(%rbp)
  movq -4752(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_8
  jmp main_d2s_copy_done_8
main_d2s_copy_body_8:
  movq -4688(%rbp), %rax
  addq -4744(%rbp), %rax
  movq %rax, -4760(%rbp)
  movq -4760(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -4768(%rbp)
  movq -4720(%rbp), %rax
  addq -4744(%rbp), %rax
  movq %rax, -4776(%rbp)
  movq -4768(%rbp), %rax
  movq -4776(%rbp), %rdx
  movb %al, (%rdx)
  movq -4744(%rbp), %rax
  addq $1, %rax
  movq %rax, -4784(%rbp)
  movq -4784(%rbp), %rax
  movq -4728(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_8
main_d2s_copy_done_8:
  movq -4440(%rbp), %rax
  addq $24, %rax
  movq %rax, -4792(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -4800(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -4800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4696(%rbp), %rax
  addq $1, %rax
  movq %rax, -4808(%rbp)
  jmp main_i2s_copy_loop_8
main_i2s_copy_loop_8:
  movq -4800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4816(%rbp)
  movq -4816(%rbp), %rax
  cmpq -4808(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -4824(%rbp)
  movq -4824(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_8
  jmp main_i2s_copy_done_8
main_i2s_copy_body_8:
  movq -4688(%rbp), %rax
  addq -4816(%rbp), %rax
  movq %rax, -4832(%rbp)
  movq -4832(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -4840(%rbp)
  movq -4792(%rbp), %rax
  addq -4816(%rbp), %rax
  movq %rax, -4848(%rbp)
  movq -4840(%rbp), %rax
  movq -4848(%rbp), %rdx
  movb %al, (%rdx)
  movq -4816(%rbp), %rax
  addq $1, %rax
  movq %rax, -4856(%rbp)
  movq -4856(%rbp), %rax
  movq -4800(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_8
main_i2s_copy_done_8:
  movq -4440(%rbp), %rax
  addq $8, %rax
  movq %rax, -4864(%rbp)
  movq -4864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4872(%rbp)
  movq -4440(%rbp), %rax
  addq $24, %rax
  movq %rax, -4880(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4880(%rbp), %rsi
  movq -4872(%rbp), %rdx
  syscall
  movq %rax, -4888(%rbp)
  jmp main_pr_next_0_26
main_pr_str_0_26:
  movq -4336(%rbp), %rax
  addq $8, %rax
  movq %rax, -4896(%rbp)
  movq -4896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4904(%rbp)
  movq -4336(%rbp), %rax
  addq $24, %rax
  movq %rax, -4912(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4912(%rbp), %rsi
  movq -4904(%rbp), %rdx
  syscall
  movq %rax, -4920(%rbp)
  jmp main_pr_next_0_26
main_pr_enum_0_26:
  movq -4336(%rbp), %rdi
  call lm_enum_to_str
  mov -4928(%rbp), rax
  movq -4928(%rbp), %rax
  addq $8, %rax
  movq %rax, -4936(%rbp)
  movq -4936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4944(%rbp)
  movq -4928(%rbp), %rax
  addq $24, %rax
  movq %rax, -4952(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4952(%rbp), %rsi
  movq -4944(%rbp), %rdx
  syscall
  movq %rax, -4960(%rbp)
  jmp main_pr_next_0_26
main_pr_list_0_26:
  movq -4336(%rbp), %rdi
  call lm_list_to_str
  mov -4968(%rbp), rax
  movq -4968(%rbp), %rax
  addq $8, %rax
  movq %rax, -4976(%rbp)
  movq -4976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4984(%rbp)
  movq -4968(%rbp), %rax
  addq $24, %rax
  movq %rax, -4992(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4992(%rbp), %rsi
  movq -4984(%rbp), %rdx
  syscall
  movq %rax, -5000(%rbp)
  jmp main_pr_next_0_26
main_pr_nonstr_0_26:
  movq -4512(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5008(%rbp)
  movq -5008(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_26
  jmp main_pr_list_0_26
main_assert_pass_29:
  movq $0, %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5016(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5024(%rbp)
  movq -5024(%rbp), %rax
  imulq -5016(%rbp), %rax
  movq %rax, -5032(%rbp)
  movq -5032(%rbp), %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5040(%rbp)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5048(%rbp)
  movq -5048(%rbp), %rax
  imulq -5040(%rbp), %rax
  movq %rax, -5056(%rbp)
  movq -5056(%rbp), %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_30(%rip), %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5064(%rbp)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5072(%rbp)
  movq -5072(%rbp), %rdi
  call lm_to_string
  mov -5080(%rbp), rax
  movq -5064(%rbp), %rdi
  movq -5080(%rbp), %rsi
  call lm_rt_str_format
  mov -5088(%rbp), rax
  movq -5088(%rbp), %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5096(%rbp)
  movq -5096(%rbp), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5104(%rbp)
  movq -5104(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -5112(%rbp)
  movq -5104(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -5120(%rbp)
  movq -5120(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5128(%rbp)
  movq -5112(%rbp), %rax
  andq -5128(%rbp), %rax
  movq %rax, -5136(%rbp)
  movq -5136(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_31
  jmp main_pr_int_0_31
main_assert_fail_29:
  movq -4584(%rbp), %rax
  addq $8, %rax
  movq %rax, -5144(%rbp)
  movq -5144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5152(%rbp)
  movq -4584(%rbp), %rax
  addq $24, %rax
  movq %rax, -5160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5160(%rbp), %rsi
  movq -5152(%rbp), %rdx
  syscall
  movq %rax, -5168(%rbp)
  movq $50397203, %rax
  movq %rax, -5176(%rbp)
  jmp main_assert_pass_29
main_pr_ptr_0_31:
  movq -5104(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5184(%rbp)
  movq -5104(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5192(%rbp)
  movq -5184(%rbp), %rax
  orq -5192(%rbp), %rax
  movq %rax, -5200(%rbp)
  movq -5200(%rbp), %rax
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
  movq %rax, -5208(%rbp)
  movq $11, %rax
  movq -5208(%rbp), %rdx
  movl %eax, (%rdx)
  movq -5208(%rbp), %rax
  addq $4, %rax
  movq %rax, -5216(%rbp)
  movq $0, %rax
  movq -5216(%rbp), %rdx
  movl %eax, (%rdx)
  movq -5208(%rbp), %rax
  addq $63, %rax
  movq %rax, -5224(%rbp)
  movq $0, %rax
  movq -5224(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -5232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -5224(%rbp), %rax
  movq -5232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -5240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -5248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -5104(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -5256(%rbp)
  movq -5256(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_9
  jmp main_i2s_pos_9
main_pr_nil_0_31:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5264(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5264(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5272(%rbp)
  jmp main_pr_next_0_31
main_pr_obj_0_31:
  movq -5104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5280(%rbp)
  movq -5280(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -5288(%rbp)
  movq -5288(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5296(%rbp)
  movq -5296(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_31
  jmp main_pr_nonstr_0_31
main_pr_next_0_31:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5304(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5304(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5312(%rbp)
  movq $0, %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_32(%rip), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5320(%rbp)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5328(%rbp)
  movq -5320(%rbp), %rdi
  movq -5328(%rbp), %rsi
  call lm_key_eq
  mov -5336(%rbp), rax
  movq -5336(%rbp), %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_33(%rip), %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5344(%rbp)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5352(%rbp)
  movq -5344(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_34
  jmp main_assert_fail_34
main_i2s_neg_9:
  movq $1, %rax
  movq -5248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5104(%rbp), %rax
  negq %rax
  movq %rax, -5360(%rbp)
  movq -5360(%rbp), %rax
  movq -5240(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_9
main_i2s_pos_9:
  movq $0, %rax
  movq -5248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5104(%rbp), %rax
  movq -5240(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_9
main_i2s_loop_9:
  movq -5240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5368(%rbp)
  movq -5368(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -5376(%rbp)
  movq -5368(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -5384(%rbp)
  movq -5384(%rbp), %rax
  movq -5240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5376(%rbp), %rax
  addq $48, %rax
  movq %rax, -5392(%rbp)
  movq -5232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5400(%rbp)
  movq -5400(%rbp), %rax
  subq $1, %rax
  movq %rax, -5408(%rbp)
  movq -5392(%rbp), %rax
  movq -5408(%rbp), %rdx
  movb %al, (%rdx)
  movq -5408(%rbp), %rax
  movq -5232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5368(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -5416(%rbp)
  movq -5416(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_9
  jmp main_i2s_sign_9
main_i2s_sign_9:
  movq -5248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5424(%rbp)
  movq -5424(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5432(%rbp)
  movq -5432(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_9
  jmp main_i2s_done_9
main_i2s_minus_9:
  movq -5232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5440(%rbp)
  movq -5440(%rbp), %rax
  subq $1, %rax
  movq %rax, -5448(%rbp)
  movq $45, %rax
  movq -5448(%rbp), %rdx
  movb %al, (%rdx)
  movq -5448(%rbp), %rax
  movq -5232(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_9
main_i2s_done_9:
  movq -5232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5456(%rbp)
  movq -5224(%rbp), %rax
  subq -5456(%rbp), %rax
  movq %rax, -5464(%rbp)
  movq -5208(%rbp), %rax
  addq $8, %rax
  movq %rax, -5472(%rbp)
  movq -5464(%rbp), %rax
  movq -5472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5208(%rbp), %rax
  addq $16, %rax
  movq %rax, -5480(%rbp)
  movq -5464(%rbp), %rax
  movq -5480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5208(%rbp), %rax
  addq $24, %rax
  movq %rax, -5488(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -5496(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -5496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5464(%rbp), %rax
  addq $1, %rax
  movq %rax, -5504(%rbp)
  jmp main_d2s_copy_loop_9
main_d2s_copy_loop_9:
  movq -5496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5512(%rbp)
  movq -5512(%rbp), %rax
  cmpq -5504(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -5520(%rbp)
  movq -5520(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_9
  jmp main_d2s_copy_done_9
main_d2s_copy_body_9:
  movq -5456(%rbp), %rax
  addq -5512(%rbp), %rax
  movq %rax, -5528(%rbp)
  movq -5528(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -5536(%rbp)
  movq -5488(%rbp), %rax
  addq -5512(%rbp), %rax
  movq %rax, -5544(%rbp)
  movq -5536(%rbp), %rax
  movq -5544(%rbp), %rdx
  movb %al, (%rdx)
  movq -5512(%rbp), %rax
  addq $1, %rax
  movq %rax, -5552(%rbp)
  movq -5552(%rbp), %rax
  movq -5496(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_9
main_d2s_copy_done_9:
  movq -5208(%rbp), %rax
  addq $24, %rax
  movq %rax, -5560(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -5568(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -5568(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5464(%rbp), %rax
  addq $1, %rax
  movq %rax, -5576(%rbp)
  jmp main_i2s_copy_loop_9
main_i2s_copy_loop_9:
  movq -5568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5584(%rbp)
  movq -5584(%rbp), %rax
  cmpq -5576(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -5592(%rbp)
  movq -5592(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_9
  jmp main_i2s_copy_done_9
main_i2s_copy_body_9:
  movq -5456(%rbp), %rax
  addq -5584(%rbp), %rax
  movq %rax, -5600(%rbp)
  movq -5600(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -5608(%rbp)
  movq -5560(%rbp), %rax
  addq -5584(%rbp), %rax
  movq %rax, -5616(%rbp)
  movq -5608(%rbp), %rax
  movq -5616(%rbp), %rdx
  movb %al, (%rdx)
  movq -5584(%rbp), %rax
  addq $1, %rax
  movq %rax, -5624(%rbp)
  movq -5624(%rbp), %rax
  movq -5568(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_9
main_i2s_copy_done_9:
  movq -5208(%rbp), %rax
  addq $8, %rax
  movq %rax, -5632(%rbp)
  movq -5632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5640(%rbp)
  movq -5208(%rbp), %rax
  addq $24, %rax
  movq %rax, -5648(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5648(%rbp), %rsi
  movq -5640(%rbp), %rdx
  syscall
  movq %rax, -5656(%rbp)
  jmp main_pr_next_0_31
main_pr_str_0_31:
  movq -5104(%rbp), %rax
  addq $8, %rax
  movq %rax, -5664(%rbp)
  movq -5664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5672(%rbp)
  movq -5104(%rbp), %rax
  addq $24, %rax
  movq %rax, -5680(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5680(%rbp), %rsi
  movq -5672(%rbp), %rdx
  syscall
  movq %rax, -5688(%rbp)
  jmp main_pr_next_0_31
main_pr_enum_0_31:
  movq -5104(%rbp), %rdi
  call lm_enum_to_str
  mov -5696(%rbp), rax
  movq -5696(%rbp), %rax
  addq $8, %rax
  movq %rax, -5704(%rbp)
  movq -5704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5712(%rbp)
  movq -5696(%rbp), %rax
  addq $24, %rax
  movq %rax, -5720(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5720(%rbp), %rsi
  movq -5712(%rbp), %rdx
  syscall
  movq %rax, -5728(%rbp)
  jmp main_pr_next_0_31
main_pr_list_0_31:
  movq -5104(%rbp), %rdi
  call lm_list_to_str
  mov -5736(%rbp), rax
  movq -5736(%rbp), %rax
  addq $8, %rax
  movq %rax, -5744(%rbp)
  movq -5744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5752(%rbp)
  movq -5736(%rbp), %rax
  addq $24, %rax
  movq %rax, -5760(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5760(%rbp), %rsi
  movq -5752(%rbp), %rdx
  syscall
  movq %rax, -5768(%rbp)
  jmp main_pr_next_0_31
main_pr_nonstr_0_31:
  movq -5280(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5776(%rbp)
  movq -5776(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_31
  jmp main_pr_list_0_31
main_assert_pass_34:
  movq $0, %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_35(%rip), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5784(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5792(%rbp)
  movq -5784(%rbp), %rdi
  movq -5792(%rbp), %rsi
  call lm_rt_str_format
  mov -5800(%rbp), rax
  movq -5800(%rbp), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5808(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5816(%rbp)
  movq -5816(%rbp), %rdi
  call lm_to_string
  mov -5824(%rbp), rax
  movq -5808(%rbp), %rdi
  movq -5824(%rbp), %rsi
  call lm_rt_str_format
  mov -5832(%rbp), rax
  movq -5832(%rbp), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5840(%rbp)
  movq -5840(%rbp), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5848(%rbp)
  movq -5848(%rbp), %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_36(%rip), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5856(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5864(%rbp)
  movq -5856(%rbp), %rdi
  movq -5864(%rbp), %rsi
  call lm_rt_str_format
  mov -5872(%rbp), rax
  movq -5872(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5880(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5888(%rbp)
  movq -5888(%rbp), %rdi
  call lm_to_string
  mov -5896(%rbp), rax
  movq -5880(%rbp), %rdi
  movq -5896(%rbp), %rsi
  call lm_rt_str_format
  mov -5904(%rbp), rax
  movq -5904(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5912(%rbp)
  movq -5912(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5920(%rbp)
  movq -5920(%rbp), %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5928(%rbp)
  movq -5928(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -5936(%rbp)
  movq -5928(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -5944(%rbp)
  movq -5944(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5952(%rbp)
  movq -5936(%rbp), %rax
  andq -5952(%rbp), %rax
  movq %rax, -5960(%rbp)
  movq -5960(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_37
  jmp main_pr_int_0_37
main_assert_fail_34:
  movq -5352(%rbp), %rax
  addq $8, %rax
  movq %rax, -5968(%rbp)
  movq -5968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5976(%rbp)
  movq -5352(%rbp), %rax
  addq $24, %rax
  movq %rax, -5984(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5984(%rbp), %rsi
  movq -5976(%rbp), %rdx
  syscall
  movq %rax, -5992(%rbp)
  movq $50397203, %rax
  movq %rax, -6000(%rbp)
  jmp main_assert_pass_34
main_pr_ptr_0_37:
  movq -5928(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6008(%rbp)
  movq -5928(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6016(%rbp)
  movq -6008(%rbp), %rax
  orq -6016(%rbp), %rax
  movq %rax, -6024(%rbp)
  movq -6024(%rbp), %rax
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
  movq %rax, -6032(%rbp)
  movq $11, %rax
  movq -6032(%rbp), %rdx
  movl %eax, (%rdx)
  movq -6032(%rbp), %rax
  addq $4, %rax
  movq %rax, -6040(%rbp)
  movq $0, %rax
  movq -6040(%rbp), %rdx
  movl %eax, (%rdx)
  movq -6032(%rbp), %rax
  addq $63, %rax
  movq %rax, -6048(%rbp)
  movq $0, %rax
  movq -6048(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6056(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -6048(%rbp), %rax
  movq -6056(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6064(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6072(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -5928(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -6080(%rbp)
  movq -6080(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_10
  jmp main_i2s_pos_10
main_pr_nil_0_37:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6088(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6088(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6096(%rbp)
  jmp main_pr_next_0_37
main_pr_obj_0_37:
  movq -5928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6104(%rbp)
  movq -6104(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -6112(%rbp)
  movq -6112(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6120(%rbp)
  movq -6120(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_37
  jmp main_pr_nonstr_0_37
main_pr_next_0_37:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6128(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6128(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6136(%rbp)
  movq $0, %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6144(%rbp)
  movq -6144(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -6152(%rbp)
  movq -6144(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -6160(%rbp)
  movq -6160(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6168(%rbp)
  movq -6152(%rbp), %rax
  andq -6168(%rbp), %rax
  movq %rax, -6176(%rbp)
  movq -6176(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_38
  jmp main_pr_int_0_38
main_i2s_neg_10:
  movq $1, %rax
  movq -6072(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5928(%rbp), %rax
  negq %rax
  movq %rax, -6184(%rbp)
  movq -6184(%rbp), %rax
  movq -6064(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_10
main_i2s_pos_10:
  movq $0, %rax
  movq -6072(%rbp), %rdx
  movq %rax, (%rdx)
  movq -5928(%rbp), %rax
  movq -6064(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_10
main_i2s_loop_10:
  movq -6064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6192(%rbp)
  movq -6192(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -6200(%rbp)
  movq -6192(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -6208(%rbp)
  movq -6208(%rbp), %rax
  movq -6064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6200(%rbp), %rax
  addq $48, %rax
  movq %rax, -6216(%rbp)
  movq -6056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6224(%rbp)
  movq -6224(%rbp), %rax
  subq $1, %rax
  movq %rax, -6232(%rbp)
  movq -6216(%rbp), %rax
  movq -6232(%rbp), %rdx
  movb %al, (%rdx)
  movq -6232(%rbp), %rax
  movq -6056(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6192(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -6240(%rbp)
  movq -6240(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_10
  jmp main_i2s_sign_10
main_i2s_sign_10:
  movq -6072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6248(%rbp)
  movq -6248(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6256(%rbp)
  movq -6256(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_10
  jmp main_i2s_done_10
main_i2s_minus_10:
  movq -6056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6264(%rbp)
  movq -6264(%rbp), %rax
  subq $1, %rax
  movq %rax, -6272(%rbp)
  movq $45, %rax
  movq -6272(%rbp), %rdx
  movb %al, (%rdx)
  movq -6272(%rbp), %rax
  movq -6056(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_10
main_i2s_done_10:
  movq -6056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6280(%rbp)
  movq -6048(%rbp), %rax
  subq -6280(%rbp), %rax
  movq %rax, -6288(%rbp)
  movq -6032(%rbp), %rax
  addq $8, %rax
  movq %rax, -6296(%rbp)
  movq -6288(%rbp), %rax
  movq -6296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6032(%rbp), %rax
  addq $16, %rax
  movq %rax, -6304(%rbp)
  movq -6288(%rbp), %rax
  movq -6304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6032(%rbp), %rax
  addq $24, %rax
  movq %rax, -6312(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6320(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -6320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6288(%rbp), %rax
  addq $1, %rax
  movq %rax, -6328(%rbp)
  jmp main_d2s_copy_loop_10
main_d2s_copy_loop_10:
  movq -6320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6336(%rbp)
  movq -6336(%rbp), %rax
  cmpq -6328(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -6344(%rbp)
  movq -6344(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_10
  jmp main_d2s_copy_done_10
main_d2s_copy_body_10:
  movq -6280(%rbp), %rax
  addq -6336(%rbp), %rax
  movq %rax, -6352(%rbp)
  movq -6352(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -6360(%rbp)
  movq -6312(%rbp), %rax
  addq -6336(%rbp), %rax
  movq %rax, -6368(%rbp)
  movq -6360(%rbp), %rax
  movq -6368(%rbp), %rdx
  movb %al, (%rdx)
  movq -6336(%rbp), %rax
  addq $1, %rax
  movq %rax, -6376(%rbp)
  movq -6376(%rbp), %rax
  movq -6320(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_10
main_d2s_copy_done_10:
  movq -6032(%rbp), %rax
  addq $24, %rax
  movq %rax, -6384(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6392(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -6392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6288(%rbp), %rax
  addq $1, %rax
  movq %rax, -6400(%rbp)
  jmp main_i2s_copy_loop_10
main_i2s_copy_loop_10:
  movq -6392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6408(%rbp)
  movq -6408(%rbp), %rax
  cmpq -6400(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -6416(%rbp)
  movq -6416(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_10
  jmp main_i2s_copy_done_10
main_i2s_copy_body_10:
  movq -6280(%rbp), %rax
  addq -6408(%rbp), %rax
  movq %rax, -6424(%rbp)
  movq -6424(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -6432(%rbp)
  movq -6384(%rbp), %rax
  addq -6408(%rbp), %rax
  movq %rax, -6440(%rbp)
  movq -6432(%rbp), %rax
  movq -6440(%rbp), %rdx
  movb %al, (%rdx)
  movq -6408(%rbp), %rax
  addq $1, %rax
  movq %rax, -6448(%rbp)
  movq -6448(%rbp), %rax
  movq -6392(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_10
main_i2s_copy_done_10:
  movq -6032(%rbp), %rax
  addq $8, %rax
  movq %rax, -6456(%rbp)
  movq -6456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6464(%rbp)
  movq -6032(%rbp), %rax
  addq $24, %rax
  movq %rax, -6472(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6472(%rbp), %rsi
  movq -6464(%rbp), %rdx
  syscall
  movq %rax, -6480(%rbp)
  jmp main_pr_next_0_37
main_pr_str_0_37:
  movq -5928(%rbp), %rax
  addq $8, %rax
  movq %rax, -6488(%rbp)
  movq -6488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6496(%rbp)
  movq -5928(%rbp), %rax
  addq $24, %rax
  movq %rax, -6504(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6504(%rbp), %rsi
  movq -6496(%rbp), %rdx
  syscall
  movq %rax, -6512(%rbp)
  jmp main_pr_next_0_37
main_pr_enum_0_37:
  movq -5928(%rbp), %rdi
  call lm_enum_to_str
  mov -6520(%rbp), rax
  movq -6520(%rbp), %rax
  addq $8, %rax
  movq %rax, -6528(%rbp)
  movq -6528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6536(%rbp)
  movq -6520(%rbp), %rax
  addq $24, %rax
  movq %rax, -6544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6544(%rbp), %rsi
  movq -6536(%rbp), %rdx
  syscall
  movq %rax, -6552(%rbp)
  jmp main_pr_next_0_37
main_pr_list_0_37:
  movq -5928(%rbp), %rdi
  call lm_list_to_str
  mov -6560(%rbp), rax
  movq -6560(%rbp), %rax
  addq $8, %rax
  movq %rax, -6568(%rbp)
  movq -6568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6576(%rbp)
  movq -6560(%rbp), %rax
  addq $24, %rax
  movq %rax, -6584(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6584(%rbp), %rsi
  movq -6576(%rbp), %rdx
  syscall
  movq %rax, -6592(%rbp)
  jmp main_pr_next_0_37
main_pr_nonstr_0_37:
  movq -6104(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6600(%rbp)
  movq -6600(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_37
  jmp main_pr_list_0_37
main_pr_ptr_0_38:
  movq -6144(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6608(%rbp)
  movq -6144(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6616(%rbp)
  movq -6608(%rbp), %rax
  orq -6616(%rbp), %rax
  movq %rax, -6624(%rbp)
  movq -6624(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_38
  jmp main_pr_obj_0_38
main_pr_int_0_38:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -6632(%rbp)
  movq $11, %rax
  movq -6632(%rbp), %rdx
  movl %eax, (%rdx)
  movq -6632(%rbp), %rax
  addq $4, %rax
  movq %rax, -6640(%rbp)
  movq $0, %rax
  movq -6640(%rbp), %rdx
  movl %eax, (%rdx)
  movq -6632(%rbp), %rax
  addq $63, %rax
  movq %rax, -6648(%rbp)
  movq $0, %rax
  movq -6648(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6656(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -6648(%rbp), %rax
  movq -6656(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6664(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6672(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -6144(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -6680(%rbp)
  movq -6680(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_11
  jmp main_i2s_pos_11
main_pr_nil_0_38:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6688(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6688(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6696(%rbp)
  jmp main_pr_next_0_38
main_pr_obj_0_38:
  movq -6144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6704(%rbp)
  movq -6704(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -6712(%rbp)
  movq -6712(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6720(%rbp)
  movq -6720(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_38
  jmp main_pr_nonstr_0_38
main_pr_next_0_38:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6728(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6728(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6736(%rbp)
  movq $0, %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_39(%rip), %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6744(%rbp)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6752(%rbp)
  movq -6744(%rbp), %rdi
  movq -6752(%rbp), %rsi
  call lm_key_eq
  mov -6760(%rbp), rax
  movq -6760(%rbp), %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_40(%rip), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6768(%rbp)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6776(%rbp)
  movq -6768(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_41
  jmp main_assert_fail_41
main_i2s_neg_11:
  movq $1, %rax
  movq -6672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6144(%rbp), %rax
  negq %rax
  movq %rax, -6784(%rbp)
  movq -6784(%rbp), %rax
  movq -6664(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_11
main_i2s_pos_11:
  movq $0, %rax
  movq -6672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6144(%rbp), %rax
  movq -6664(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_11
main_i2s_loop_11:
  movq -6664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6792(%rbp)
  movq -6792(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -6800(%rbp)
  movq -6792(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -6808(%rbp)
  movq -6808(%rbp), %rax
  movq -6664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6800(%rbp), %rax
  addq $48, %rax
  movq %rax, -6816(%rbp)
  movq -6656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6824(%rbp)
  movq -6824(%rbp), %rax
  subq $1, %rax
  movq %rax, -6832(%rbp)
  movq -6816(%rbp), %rax
  movq -6832(%rbp), %rdx
  movb %al, (%rdx)
  movq -6832(%rbp), %rax
  movq -6656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6792(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -6840(%rbp)
  movq -6840(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_11
  jmp main_i2s_sign_11
main_i2s_sign_11:
  movq -6672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6848(%rbp)
  movq -6848(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6856(%rbp)
  movq -6856(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_11
  jmp main_i2s_done_11
main_i2s_minus_11:
  movq -6656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6864(%rbp)
  movq -6864(%rbp), %rax
  subq $1, %rax
  movq %rax, -6872(%rbp)
  movq $45, %rax
  movq -6872(%rbp), %rdx
  movb %al, (%rdx)
  movq -6872(%rbp), %rax
  movq -6656(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_11
main_i2s_done_11:
  movq -6656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6880(%rbp)
  movq -6648(%rbp), %rax
  subq -6880(%rbp), %rax
  movq %rax, -6888(%rbp)
  movq -6632(%rbp), %rax
  addq $8, %rax
  movq %rax, -6896(%rbp)
  movq -6888(%rbp), %rax
  movq -6896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6632(%rbp), %rax
  addq $16, %rax
  movq %rax, -6904(%rbp)
  movq -6888(%rbp), %rax
  movq -6904(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6632(%rbp), %rax
  addq $24, %rax
  movq %rax, -6912(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6920(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -6920(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6888(%rbp), %rax
  addq $1, %rax
  movq %rax, -6928(%rbp)
  jmp main_d2s_copy_loop_11
main_d2s_copy_loop_11:
  movq -6920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6936(%rbp)
  movq -6936(%rbp), %rax
  cmpq -6928(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -6944(%rbp)
  movq -6944(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_11
  jmp main_d2s_copy_done_11
main_d2s_copy_body_11:
  movq -6880(%rbp), %rax
  addq -6936(%rbp), %rax
  movq %rax, -6952(%rbp)
  movq -6952(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -6960(%rbp)
  movq -6912(%rbp), %rax
  addq -6936(%rbp), %rax
  movq %rax, -6968(%rbp)
  movq -6960(%rbp), %rax
  movq -6968(%rbp), %rdx
  movb %al, (%rdx)
  movq -6936(%rbp), %rax
  addq $1, %rax
  movq %rax, -6976(%rbp)
  movq -6976(%rbp), %rax
  movq -6920(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_11
main_d2s_copy_done_11:
  movq -6632(%rbp), %rax
  addq $24, %rax
  movq %rax, -6984(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -6992(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -6992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -6888(%rbp), %rax
  addq $1, %rax
  movq %rax, -7000(%rbp)
  jmp main_i2s_copy_loop_11
main_i2s_copy_loop_11:
  movq -6992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7008(%rbp)
  movq -7008(%rbp), %rax
  cmpq -7000(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -7016(%rbp)
  movq -7016(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_11
  jmp main_i2s_copy_done_11
main_i2s_copy_body_11:
  movq -6880(%rbp), %rax
  addq -7008(%rbp), %rax
  movq %rax, -7024(%rbp)
  movq -7024(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -7032(%rbp)
  movq -6984(%rbp), %rax
  addq -7008(%rbp), %rax
  movq %rax, -7040(%rbp)
  movq -7032(%rbp), %rax
  movq -7040(%rbp), %rdx
  movb %al, (%rdx)
  movq -7008(%rbp), %rax
  addq $1, %rax
  movq %rax, -7048(%rbp)
  movq -7048(%rbp), %rax
  movq -6992(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_11
main_i2s_copy_done_11:
  movq -6632(%rbp), %rax
  addq $8, %rax
  movq %rax, -7056(%rbp)
  movq -7056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7064(%rbp)
  movq -6632(%rbp), %rax
  addq $24, %rax
  movq %rax, -7072(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7072(%rbp), %rsi
  movq -7064(%rbp), %rdx
  syscall
  movq %rax, -7080(%rbp)
  jmp main_pr_next_0_38
main_pr_str_0_38:
  movq -6144(%rbp), %rax
  addq $8, %rax
  movq %rax, -7088(%rbp)
  movq -7088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7096(%rbp)
  movq -6144(%rbp), %rax
  addq $24, %rax
  movq %rax, -7104(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7104(%rbp), %rsi
  movq -7096(%rbp), %rdx
  syscall
  movq %rax, -7112(%rbp)
  jmp main_pr_next_0_38
main_pr_enum_0_38:
  movq -6144(%rbp), %rdi
  call lm_enum_to_str
  mov -7120(%rbp), rax
  movq -7120(%rbp), %rax
  addq $8, %rax
  movq %rax, -7128(%rbp)
  movq -7128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7136(%rbp)
  movq -7120(%rbp), %rax
  addq $24, %rax
  movq %rax, -7144(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7144(%rbp), %rsi
  movq -7136(%rbp), %rdx
  syscall
  movq %rax, -7152(%rbp)
  jmp main_pr_next_0_38
main_pr_list_0_38:
  movq -6144(%rbp), %rdi
  call lm_list_to_str
  mov -7160(%rbp), rax
  movq -7160(%rbp), %rax
  addq $8, %rax
  movq %rax, -7168(%rbp)
  movq -7168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7176(%rbp)
  movq -7160(%rbp), %rax
  addq $24, %rax
  movq %rax, -7184(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7184(%rbp), %rsi
  movq -7176(%rbp), %rdx
  syscall
  movq %rax, -7192(%rbp)
  jmp main_pr_next_0_38
main_pr_nonstr_0_38:
  movq -6704(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7200(%rbp)
  movq -7200(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_38
  jmp main_pr_list_0_38
main_assert_pass_41:
  movq $0, %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_42(%rip), %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7208(%rbp)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7216(%rbp)
  movq -7208(%rbp), %rdi
  movq -7216(%rbp), %rsi
  call lm_key_eq
  mov -7224(%rbp), rax
  movq -7224(%rbp), %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_43(%rip), %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7232(%rbp)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7240(%rbp)
  movq -7232(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_44
  jmp main_assert_fail_44
main_assert_fail_41:
  movq -6776(%rbp), %rax
  addq $8, %rax
  movq %rax, -7248(%rbp)
  movq -7248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7256(%rbp)
  movq -6776(%rbp), %rax
  addq $24, %rax
  movq %rax, -7264(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7264(%rbp), %rsi
  movq -7256(%rbp), %rdx
  syscall
  movq %rax, -7272(%rbp)
  movq $50397203, %rax
  movq %rax, -7280(%rbp)
  jmp main_assert_pass_41
main_assert_pass_44:
  movq $0, %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_45(%rip), %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7288(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7296(%rbp)
  movq -7288(%rbp), %rdi
  movq -7296(%rbp), %rsi
  call lm_rt_str_format
  mov -7304(%rbp), rax
  movq -7304(%rbp), %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7312(%rbp)
  movq -7312(%rbp), %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_46(%rip), %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  movq -752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7320(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7328(%rbp)
  movq -7328(%rbp), %rdi
  call lm_to_string
  mov -7336(%rbp), rax
  movq -7320(%rbp), %rdi
  movq -7336(%rbp), %rsi
  call lm_rt_str_format
  mov -7344(%rbp), rax
  movq -7344(%rbp), %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7352(%rbp)
  movq -7352(%rbp), %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7360(%rbp)
  movq -7360(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -7368(%rbp)
  movq -7360(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -7376(%rbp)
  movq -7376(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7384(%rbp)
  movq -7368(%rbp), %rax
  andq -7384(%rbp), %rax
  movq %rax, -7392(%rbp)
  movq -7392(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_47
  jmp main_pr_int_0_47
main_assert_fail_44:
  movq -7240(%rbp), %rax
  addq $8, %rax
  movq %rax, -7400(%rbp)
  movq -7400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7408(%rbp)
  movq -7240(%rbp), %rax
  addq $24, %rax
  movq %rax, -7416(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7416(%rbp), %rsi
  movq -7408(%rbp), %rdx
  syscall
  movq %rax, -7424(%rbp)
  movq $50397203, %rax
  movq %rax, -7432(%rbp)
  jmp main_assert_pass_44
main_pr_ptr_0_47:
  movq -7360(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7440(%rbp)
  movq -7360(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7448(%rbp)
  movq -7440(%rbp), %rax
  orq -7448(%rbp), %rax
  movq %rax, -7456(%rbp)
  movq -7456(%rbp), %rax
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
  movq %rax, -7464(%rbp)
  movq $11, %rax
  movq -7464(%rbp), %rdx
  movl %eax, (%rdx)
  movq -7464(%rbp), %rax
  addq $4, %rax
  movq %rax, -7472(%rbp)
  movq $0, %rax
  movq -7472(%rbp), %rdx
  movl %eax, (%rdx)
  movq -7464(%rbp), %rax
  addq $63, %rax
  movq %rax, -7480(%rbp)
  movq $0, %rax
  movq -7480(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -7488(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -7480(%rbp), %rax
  movq -7488(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -7496(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -7504(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -7360(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -7512(%rbp)
  movq -7512(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_12
  jmp main_i2s_pos_12
main_pr_nil_0_47:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7520(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7520(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7528(%rbp)
  jmp main_pr_next_0_47
main_pr_obj_0_47:
  movq -7360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7536(%rbp)
  movq -7536(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -7544(%rbp)
  movq -7544(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7552(%rbp)
  movq -7552(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_47
  jmp main_pr_nonstr_0_47
main_pr_next_0_47:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7560(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7560(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7568(%rbp)
  movq $0, %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7576(%rbp)
  movq -7576(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -7584(%rbp)
  movq -7576(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -7592(%rbp)
  movq -7592(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7600(%rbp)
  movq -7584(%rbp), %rax
  andq -7600(%rbp), %rax
  movq %rax, -7608(%rbp)
  movq -7608(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_48
  jmp main_pr_int_0_48
main_i2s_neg_12:
  movq $1, %rax
  movq -7504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7360(%rbp), %rax
  negq %rax
  movq %rax, -7616(%rbp)
  movq -7616(%rbp), %rax
  movq -7496(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_12
main_i2s_pos_12:
  movq $0, %rax
  movq -7504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7360(%rbp), %rax
  movq -7496(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_12
main_i2s_loop_12:
  movq -7496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7624(%rbp)
  movq -7624(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -7632(%rbp)
  movq -7624(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -7640(%rbp)
  movq -7640(%rbp), %rax
  movq -7496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7632(%rbp), %rax
  addq $48, %rax
  movq %rax, -7648(%rbp)
  movq -7488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7656(%rbp)
  movq -7656(%rbp), %rax
  subq $1, %rax
  movq %rax, -7664(%rbp)
  movq -7648(%rbp), %rax
  movq -7664(%rbp), %rdx
  movb %al, (%rdx)
  movq -7664(%rbp), %rax
  movq -7488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7624(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -7672(%rbp)
  movq -7672(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_12
  jmp main_i2s_sign_12
main_i2s_sign_12:
  movq -7504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7680(%rbp)
  movq -7680(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7688(%rbp)
  movq -7688(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_12
  jmp main_i2s_done_12
main_i2s_minus_12:
  movq -7488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7696(%rbp)
  movq -7696(%rbp), %rax
  subq $1, %rax
  movq %rax, -7704(%rbp)
  movq $45, %rax
  movq -7704(%rbp), %rdx
  movb %al, (%rdx)
  movq -7704(%rbp), %rax
  movq -7488(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_12
main_i2s_done_12:
  movq -7488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7712(%rbp)
  movq -7480(%rbp), %rax
  subq -7712(%rbp), %rax
  movq %rax, -7720(%rbp)
  movq -7464(%rbp), %rax
  addq $8, %rax
  movq %rax, -7728(%rbp)
  movq -7720(%rbp), %rax
  movq -7728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7464(%rbp), %rax
  addq $16, %rax
  movq %rax, -7736(%rbp)
  movq -7720(%rbp), %rax
  movq -7736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7464(%rbp), %rax
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
  movq -7720(%rbp), %rax
  addq $1, %rax
  movq %rax, -7760(%rbp)
  jmp main_d2s_copy_loop_12
main_d2s_copy_loop_12:
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
  jne main_d2s_copy_body_12
  jmp main_d2s_copy_done_12
main_d2s_copy_body_12:
  movq -7712(%rbp), %rax
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
  jmp main_d2s_copy_loop_12
main_d2s_copy_done_12:
  movq -7464(%rbp), %rax
  addq $24, %rax
  movq %rax, -7816(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -7824(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -7824(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7720(%rbp), %rax
  addq $1, %rax
  movq %rax, -7832(%rbp)
  jmp main_i2s_copy_loop_12
main_i2s_copy_loop_12:
  movq -7824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7840(%rbp)
  movq -7840(%rbp), %rax
  cmpq -7832(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -7848(%rbp)
  movq -7848(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_12
  jmp main_i2s_copy_done_12
main_i2s_copy_body_12:
  movq -7712(%rbp), %rax
  addq -7840(%rbp), %rax
  movq %rax, -7856(%rbp)
  movq -7856(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -7864(%rbp)
  movq -7816(%rbp), %rax
  addq -7840(%rbp), %rax
  movq %rax, -7872(%rbp)
  movq -7864(%rbp), %rax
  movq -7872(%rbp), %rdx
  movb %al, (%rdx)
  movq -7840(%rbp), %rax
  addq $1, %rax
  movq %rax, -7880(%rbp)
  movq -7880(%rbp), %rax
  movq -7824(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_12
main_i2s_copy_done_12:
  movq -7464(%rbp), %rax
  addq $8, %rax
  movq %rax, -7888(%rbp)
  movq -7888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7896(%rbp)
  movq -7464(%rbp), %rax
  addq $24, %rax
  movq %rax, -7904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7904(%rbp), %rsi
  movq -7896(%rbp), %rdx
  syscall
  movq %rax, -7912(%rbp)
  jmp main_pr_next_0_47
main_pr_str_0_47:
  movq -7360(%rbp), %rax
  addq $8, %rax
  movq %rax, -7920(%rbp)
  movq -7920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7928(%rbp)
  movq -7360(%rbp), %rax
  addq $24, %rax
  movq %rax, -7936(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7936(%rbp), %rsi
  movq -7928(%rbp), %rdx
  syscall
  movq %rax, -7944(%rbp)
  jmp main_pr_next_0_47
main_pr_enum_0_47:
  movq -7360(%rbp), %rdi
  call lm_enum_to_str
  mov -7952(%rbp), rax
  movq -7952(%rbp), %rax
  addq $8, %rax
  movq %rax, -7960(%rbp)
  movq -7960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7968(%rbp)
  movq -7952(%rbp), %rax
  addq $24, %rax
  movq %rax, -7976(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7976(%rbp), %rsi
  movq -7968(%rbp), %rdx
  syscall
  movq %rax, -7984(%rbp)
  jmp main_pr_next_0_47
main_pr_list_0_47:
  movq -7360(%rbp), %rdi
  call lm_list_to_str
  mov -7992(%rbp), rax
  movq -7992(%rbp), %rax
  addq $8, %rax
  movq %rax, -8000(%rbp)
  movq -8000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8008(%rbp)
  movq -7992(%rbp), %rax
  addq $24, %rax
  movq %rax, -8016(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8016(%rbp), %rsi
  movq -8008(%rbp), %rdx
  syscall
  movq %rax, -8024(%rbp)
  jmp main_pr_next_0_47
main_pr_nonstr_0_47:
  movq -7536(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8032(%rbp)
  movq -8032(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_47
  jmp main_pr_list_0_47
main_pr_ptr_0_48:
  movq -7576(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8040(%rbp)
  movq -7576(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8048(%rbp)
  movq -8040(%rbp), %rax
  orq -8048(%rbp), %rax
  movq %rax, -8056(%rbp)
  movq -8056(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_48
  jmp main_pr_obj_0_48
main_pr_int_0_48:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -8064(%rbp)
  movq $11, %rax
  movq -8064(%rbp), %rdx
  movl %eax, (%rdx)
  movq -8064(%rbp), %rax
  addq $4, %rax
  movq %rax, -8072(%rbp)
  movq $0, %rax
  movq -8072(%rbp), %rdx
  movl %eax, (%rdx)
  movq -8064(%rbp), %rax
  addq $63, %rax
  movq %rax, -8080(%rbp)
  movq $0, %rax
  movq -8080(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -8088(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -8080(%rbp), %rax
  movq -8088(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -8096(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -8104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -7576(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -8112(%rbp)
  movq -8112(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_13
  jmp main_i2s_pos_13
main_pr_nil_0_48:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -8120(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8120(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -8128(%rbp)
  jmp main_pr_next_0_48
main_pr_obj_0_48:
  movq -7576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8136(%rbp)
  movq -8136(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -8144(%rbp)
  movq -8144(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8152(%rbp)
  movq -8152(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_48
  jmp main_pr_nonstr_0_48
main_pr_next_0_48:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -8160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8160(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -8168(%rbp)
  movq $0, %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_49(%rip), %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8176(%rbp)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8184(%rbp)
  movq -8176(%rbp), %rdi
  movq -8184(%rbp), %rsi
  call lm_key_eq
  mov -8192(%rbp), rax
  movq -8192(%rbp), %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_50(%rip), %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8200(%rbp)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8208(%rbp)
  movq -8200(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_51
  jmp main_assert_fail_51
main_i2s_neg_13:
  movq $1, %rax
  movq -8104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7576(%rbp), %rax
  negq %rax
  movq %rax, -8216(%rbp)
  movq -8216(%rbp), %rax
  movq -8096(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_13
main_i2s_pos_13:
  movq $0, %rax
  movq -8104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -7576(%rbp), %rax
  movq -8096(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_13
main_i2s_loop_13:
  movq -8096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8224(%rbp)
  movq -8224(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -8232(%rbp)
  movq -8224(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -8240(%rbp)
  movq -8240(%rbp), %rax
  movq -8096(%rbp), %rdx
  movq %rax, (%rdx)
  movq -8232(%rbp), %rax
  addq $48, %rax
  movq %rax, -8248(%rbp)
  movq -8088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8256(%rbp)
  movq -8256(%rbp), %rax
  subq $1, %rax
  movq %rax, -8264(%rbp)
  movq -8248(%rbp), %rax
  movq -8264(%rbp), %rdx
  movb %al, (%rdx)
  movq -8264(%rbp), %rax
  movq -8088(%rbp), %rdx
  movq %rax, (%rdx)
  movq -8224(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -8272(%rbp)
  movq -8272(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_13
  jmp main_i2s_sign_13
main_i2s_sign_13:
  movq -8104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8280(%rbp)
  movq -8280(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8288(%rbp)
  movq -8288(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_13
  jmp main_i2s_done_13
main_i2s_minus_13:
  movq -8088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8296(%rbp)
  movq -8296(%rbp), %rax
  subq $1, %rax
  movq %rax, -8304(%rbp)
  movq $45, %rax
  movq -8304(%rbp), %rdx
  movb %al, (%rdx)
  movq -8304(%rbp), %rax
  movq -8088(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_13
main_i2s_done_13:
  movq -8088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8312(%rbp)
  movq -8080(%rbp), %rax
  subq -8312(%rbp), %rax
  movq %rax, -8320(%rbp)
  movq -8064(%rbp), %rax
  addq $8, %rax
  movq %rax, -8328(%rbp)
  movq -8320(%rbp), %rax
  movq -8328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -8064(%rbp), %rax
  addq $16, %rax
  movq %rax, -8336(%rbp)
  movq -8320(%rbp), %rax
  movq -8336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -8064(%rbp), %rax
  addq $24, %rax
  movq %rax, -8344(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -8352(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -8352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -8320(%rbp), %rax
  addq $1, %rax
  movq %rax, -8360(%rbp)
  jmp main_d2s_copy_loop_13
main_d2s_copy_loop_13:
  movq -8352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8368(%rbp)
  movq -8368(%rbp), %rax
  cmpq -8360(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -8376(%rbp)
  movq -8376(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_13
  jmp main_d2s_copy_done_13
main_d2s_copy_body_13:
  movq -8312(%rbp), %rax
  addq -8368(%rbp), %rax
  movq %rax, -8384(%rbp)
  movq -8384(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -8392(%rbp)
  movq -8344(%rbp), %rax
  addq -8368(%rbp), %rax
  movq %rax, -8400(%rbp)
  movq -8392(%rbp), %rax
  movq -8400(%rbp), %rdx
  movb %al, (%rdx)
  movq -8368(%rbp), %rax
  addq $1, %rax
  movq %rax, -8408(%rbp)
  movq -8408(%rbp), %rax
  movq -8352(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_13
main_d2s_copy_done_13:
  movq -8064(%rbp), %rax
  addq $24, %rax
  movq %rax, -8416(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -8424(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -8424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -8320(%rbp), %rax
  addq $1, %rax
  movq %rax, -8432(%rbp)
  jmp main_i2s_copy_loop_13
main_i2s_copy_loop_13:
  movq -8424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8440(%rbp)
  movq -8440(%rbp), %rax
  cmpq -8432(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -8448(%rbp)
  movq -8448(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_13
  jmp main_i2s_copy_done_13
main_i2s_copy_body_13:
  movq -8312(%rbp), %rax
  addq -8440(%rbp), %rax
  movq %rax, -8456(%rbp)
  movq -8456(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -8464(%rbp)
  movq -8416(%rbp), %rax
  addq -8440(%rbp), %rax
  movq %rax, -8472(%rbp)
  movq -8464(%rbp), %rax
  movq -8472(%rbp), %rdx
  movb %al, (%rdx)
  movq -8440(%rbp), %rax
  addq $1, %rax
  movq %rax, -8480(%rbp)
  movq -8480(%rbp), %rax
  movq -8424(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_13
main_i2s_copy_done_13:
  movq -8064(%rbp), %rax
  addq $8, %rax
  movq %rax, -8488(%rbp)
  movq -8488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8496(%rbp)
  movq -8064(%rbp), %rax
  addq $24, %rax
  movq %rax, -8504(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8504(%rbp), %rsi
  movq -8496(%rbp), %rdx
  syscall
  movq %rax, -8512(%rbp)
  jmp main_pr_next_0_48
main_pr_str_0_48:
  movq -7576(%rbp), %rax
  addq $8, %rax
  movq %rax, -8520(%rbp)
  movq -8520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8528(%rbp)
  movq -7576(%rbp), %rax
  addq $24, %rax
  movq %rax, -8536(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8536(%rbp), %rsi
  movq -8528(%rbp), %rdx
  syscall
  movq %rax, -8544(%rbp)
  jmp main_pr_next_0_48
main_pr_enum_0_48:
  movq -7576(%rbp), %rdi
  call lm_enum_to_str
  mov -8552(%rbp), rax
  movq -8552(%rbp), %rax
  addq $8, %rax
  movq %rax, -8560(%rbp)
  movq -8560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8568(%rbp)
  movq -8552(%rbp), %rax
  addq $24, %rax
  movq %rax, -8576(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8576(%rbp), %rsi
  movq -8568(%rbp), %rdx
  syscall
  movq %rax, -8584(%rbp)
  jmp main_pr_next_0_48
main_pr_list_0_48:
  movq -7576(%rbp), %rdi
  call lm_list_to_str
  mov -8592(%rbp), rax
  movq -8592(%rbp), %rax
  addq $8, %rax
  movq %rax, -8600(%rbp)
  movq -8600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8608(%rbp)
  movq -8592(%rbp), %rax
  addq $24, %rax
  movq %rax, -8616(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8616(%rbp), %rsi
  movq -8608(%rbp), %rdx
  syscall
  movq %rax, -8624(%rbp)
  jmp main_pr_next_0_48
main_pr_nonstr_0_48:
  movq -8136(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -8632(%rbp)
  movq -8632(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_48
  jmp main_pr_list_0_48
main_assert_pass_51:
  movq $0, %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_52(%rip), %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8640(%rbp)
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8648(%rbp)
  movq -8640(%rbp), %rdi
  movq -8648(%rbp), %rsi
  call lm_key_eq
  mov -8656(%rbp), rax
  movq -8656(%rbp), %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_53(%rip), %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8664(%rbp)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8672(%rbp)
  movq -8664(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_54
  jmp main_assert_fail_54
main_assert_fail_51:
  movq -8208(%rbp), %rax
  addq $8, %rax
  movq %rax, -8680(%rbp)
  movq -8680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8688(%rbp)
  movq -8208(%rbp), %rax
  addq $24, %rax
  movq %rax, -8696(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8696(%rbp), %rsi
  movq -8688(%rbp), %rdx
  syscall
  movq %rax, -8704(%rbp)
  movq $50397203, %rax
  movq %rax, -8712(%rbp)
  jmp main_assert_pass_51
main_assert_pass_54:
  movq $0, %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8720(%rbp)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8728(%rbp)
  movq -8728(%rbp), %rax
  addq -8720(%rbp), %rax
  movq %rax, -8736(%rbp)
  movq -8736(%rbp), %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_55(%rip), %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8744(%rbp)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8752(%rbp)
  movq -8752(%rbp), %rdi
  call lm_to_string
  mov -8760(%rbp), rax
  movq -8744(%rbp), %rdi
  movq -8760(%rbp), %rsi
  call lm_rt_str_format
  mov -8768(%rbp), rax
  movq -8768(%rbp), %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8776(%rbp)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8784(%rbp)
  movq -8784(%rbp), %rdi
  call lm_to_string
  mov -8792(%rbp), rax
  movq -8776(%rbp), %rdi
  movq -8792(%rbp), %rsi
  call lm_rt_str_format
  mov -8800(%rbp), rax
  movq -8800(%rbp), %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  movq -888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8808(%rbp)
  movq -864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8816(%rbp)
  movq -8816(%rbp), %rdi
  call lm_to_string
  mov -8824(%rbp), rax
  movq -8808(%rbp), %rdi
  movq -8824(%rbp), %rsi
  call lm_rt_str_format
  mov -8832(%rbp), rax
  movq -8832(%rbp), %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8840(%rbp)
  movq -8840(%rbp), %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8848(%rbp)
  movq -8848(%rbp), %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8856(%rbp)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8864(%rbp)
  movq -8864(%rbp), %rax
  cmpq -8856(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -8872(%rbp)
  movq -8872(%rbp), %rax
  movq -912(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_56(%rip), %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8880(%rbp)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8888(%rbp)
  movq -8888(%rbp), %rdi
  call lm_to_string
  mov -8896(%rbp), rax
  movq -8880(%rbp), %rdi
  movq -8896(%rbp), %rsi
  call lm_rt_str_format
  mov -8904(%rbp), rax
  movq -8904(%rbp), %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8912(%rbp)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8920(%rbp)
  movq -8920(%rbp), %rdi
  call lm_to_string
  mov -8928(%rbp), rax
  movq -8912(%rbp), %rdi
  movq -8928(%rbp), %rsi
  call lm_rt_str_format
  mov -8936(%rbp), rax
  movq -8936(%rbp), %rax
  movq -936(%rbp), %rdx
  movq %rax, (%rdx)
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8944(%rbp)
  movq -912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8952(%rbp)
  movq -8952(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -8960(%rbp)
  movq -8960(%rbp), %rax
  testq %rax, %rax
  jne main_b2s_t_1
  jmp main_b2s_f_1
main_assert_fail_54:
  movq -8672(%rbp), %rax
  addq $8, %rax
  movq %rax, -8968(%rbp)
  movq -8968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -8976(%rbp)
  movq -8672(%rbp), %rax
  addq $24, %rax
  movq %rax, -8984(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -8984(%rbp), %rsi
  movq -8976(%rbp), %rdx
  syscall
  movq %rax, -8992(%rbp)
  movq $50397203, %rax
  movq %rax, -9000(%rbp)
  jmp main_assert_pass_54
main_b2s_t_1:
  movq str_true(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -9008(%rbp)
  jmp main_b2s_d_1
main_b2s_f_1:
  movq str_false(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -9008(%rbp)
  jmp main_b2s_d_1
main_b2s_d_1:
  movq -8944(%rbp), %rdi
  movq -9008(%rbp), %rsi
  call lm_rt_str_format
  mov -9016(%rbp), rax
  movq -9016(%rbp), %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9024(%rbp)
  movq -9024(%rbp), %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9032(%rbp)
  movq -9032(%rbp), %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9040(%rbp)
  movq -9040(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -9048(%rbp)
  movq -9040(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -9056(%rbp)
  movq -9056(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9064(%rbp)
  movq -9048(%rbp), %rax
  andq -9064(%rbp), %rax
  movq %rax, -9072(%rbp)
  movq -9072(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_57
  jmp main_pr_int_0_57
main_pr_ptr_0_57:
  movq -9040(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9080(%rbp)
  movq -9040(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9088(%rbp)
  movq -9080(%rbp), %rax
  orq -9088(%rbp), %rax
  movq %rax, -9096(%rbp)
  movq -9096(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_57
  jmp main_pr_obj_0_57
main_pr_int_0_57:
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
  movq -9040(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -9152(%rbp)
  movq -9152(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_14
  jmp main_i2s_pos_14
main_pr_nil_0_57:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9160(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9168(%rbp)
  jmp main_pr_next_0_57
main_pr_obj_0_57:
  movq -9040(%rbp), %rax
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
  jne main_pr_str_0_57
  jmp main_pr_nonstr_0_57
main_pr_next_0_57:
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
  movq -960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -952(%rbp), %rax
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
  jne main_pr_ptr_0_58
  jmp main_pr_int_0_58
main_i2s_neg_14:
  movq $1, %rax
  movq -9144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9040(%rbp), %rax
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
  movq -9040(%rbp), %rax
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
  jmp main_pr_next_0_57
main_pr_str_0_57:
  movq -9040(%rbp), %rax
  addq $8, %rax
  movq %rax, -9560(%rbp)
  movq -9560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9568(%rbp)
  movq -9040(%rbp), %rax
  addq $24, %rax
  movq %rax, -9576(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9576(%rbp), %rsi
  movq -9568(%rbp), %rdx
  syscall
  movq %rax, -9584(%rbp)
  jmp main_pr_next_0_57
main_pr_enum_0_57:
  movq -9040(%rbp), %rdi
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
  jmp main_pr_next_0_57
main_pr_list_0_57:
  movq -9040(%rbp), %rdi
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
  jmp main_pr_next_0_57
main_pr_nonstr_0_57:
  movq -9176(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9672(%rbp)
  movq -9672(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_57
  jmp main_pr_list_0_57
main_pr_ptr_0_58:
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
  jne main_pr_nil_0_58
  jmp main_pr_obj_0_58
main_pr_int_0_58:
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
main_pr_nil_0_58:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -9760(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -9760(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -9768(%rbp)
  jmp main_pr_next_0_58
main_pr_obj_0_58:
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
  jne main_pr_str_0_58
  jmp main_pr_nonstr_0_58
main_pr_next_0_58:
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
  movq -968(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_59(%rip), %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9816(%rbp)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9824(%rbp)
  movq -9816(%rbp), %rdi
  movq -9824(%rbp), %rsi
  call lm_key_eq
  mov -9832(%rbp), rax
  movq -9832(%rbp), %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_60(%rip), %rax
  movq -992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9840(%rbp)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9848(%rbp)
  movq -9840(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_61
  jmp main_assert_fail_61
main_i2s_neg_15:
  movq $1, %rax
  movq -9744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9216(%rbp), %rax
  negq %rax
  movq %rax, -9856(%rbp)
  movq -9856(%rbp), %rax
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
  movq %rax, -9864(%rbp)
  movq -9864(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -9872(%rbp)
  movq -9864(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -9880(%rbp)
  movq -9880(%rbp), %rax
  movq -9736(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9872(%rbp), %rax
  addq $48, %rax
  movq %rax, -9888(%rbp)
  movq -9728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9896(%rbp)
  movq -9896(%rbp), %rax
  subq $1, %rax
  movq %rax, -9904(%rbp)
  movq -9888(%rbp), %rax
  movq -9904(%rbp), %rdx
  movb %al, (%rdx)
  movq -9904(%rbp), %rax
  movq -9728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9864(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -9912(%rbp)
  movq -9912(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_15
  jmp main_i2s_sign_15
main_i2s_sign_15:
  movq -9744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9920(%rbp)
  movq -9920(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -9928(%rbp)
  movq -9928(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_15
  jmp main_i2s_done_15
main_i2s_minus_15:
  movq -9728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9936(%rbp)
  movq -9936(%rbp), %rax
  subq $1, %rax
  movq %rax, -9944(%rbp)
  movq $45, %rax
  movq -9944(%rbp), %rdx
  movb %al, (%rdx)
  movq -9944(%rbp), %rax
  movq -9728(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_15
main_i2s_done_15:
  movq -9728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -9952(%rbp)
  movq -9720(%rbp), %rax
  subq -9952(%rbp), %rax
  movq %rax, -9960(%rbp)
  movq -9704(%rbp), %rax
  addq $8, %rax
  movq %rax, -9968(%rbp)
  movq -9960(%rbp), %rax
  movq -9968(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9704(%rbp), %rax
  addq $16, %rax
  movq %rax, -9976(%rbp)
  movq -9960(%rbp), %rax
  movq -9976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9704(%rbp), %rax
  addq $24, %rax
  movq %rax, -9984(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -9992(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -9992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9960(%rbp), %rax
  addq $1, %rax
  movq %rax, -10000(%rbp)
  jmp main_d2s_copy_loop_15
main_d2s_copy_loop_15:
  movq -9992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10008(%rbp)
  movq -10008(%rbp), %rax
  cmpq -10000(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -10016(%rbp)
  movq -10016(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_15
  jmp main_d2s_copy_done_15
main_d2s_copy_body_15:
  movq -9952(%rbp), %rax
  addq -10008(%rbp), %rax
  movq %rax, -10024(%rbp)
  movq -10024(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -10032(%rbp)
  movq -9984(%rbp), %rax
  addq -10008(%rbp), %rax
  movq %rax, -10040(%rbp)
  movq -10032(%rbp), %rax
  movq -10040(%rbp), %rdx
  movb %al, (%rdx)
  movq -10008(%rbp), %rax
  addq $1, %rax
  movq %rax, -10048(%rbp)
  movq -10048(%rbp), %rax
  movq -9992(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_15
main_d2s_copy_done_15:
  movq -9704(%rbp), %rax
  addq $24, %rax
  movq %rax, -10056(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -10064(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -10064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -9960(%rbp), %rax
  addq $1, %rax
  movq %rax, -10072(%rbp)
  jmp main_i2s_copy_loop_15
main_i2s_copy_loop_15:
  movq -10064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10080(%rbp)
  movq -10080(%rbp), %rax
  cmpq -10072(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -10088(%rbp)
  movq -10088(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_15
  jmp main_i2s_copy_done_15
main_i2s_copy_body_15:
  movq -9952(%rbp), %rax
  addq -10080(%rbp), %rax
  movq %rax, -10096(%rbp)
  movq -10096(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -10104(%rbp)
  movq -10056(%rbp), %rax
  addq -10080(%rbp), %rax
  movq %rax, -10112(%rbp)
  movq -10104(%rbp), %rax
  movq -10112(%rbp), %rdx
  movb %al, (%rdx)
  movq -10080(%rbp), %rax
  addq $1, %rax
  movq %rax, -10120(%rbp)
  movq -10120(%rbp), %rax
  movq -10064(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_15
main_i2s_copy_done_15:
  movq -9704(%rbp), %rax
  addq $8, %rax
  movq %rax, -10128(%rbp)
  movq -10128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10136(%rbp)
  movq -9704(%rbp), %rax
  addq $24, %rax
  movq %rax, -10144(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10144(%rbp), %rsi
  movq -10136(%rbp), %rdx
  syscall
  movq %rax, -10152(%rbp)
  jmp main_pr_next_0_58
main_pr_str_0_58:
  movq -9216(%rbp), %rax
  addq $8, %rax
  movq %rax, -10160(%rbp)
  movq -10160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10168(%rbp)
  movq -9216(%rbp), %rax
  addq $24, %rax
  movq %rax, -10176(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10176(%rbp), %rsi
  movq -10168(%rbp), %rdx
  syscall
  movq %rax, -10184(%rbp)
  jmp main_pr_next_0_58
main_pr_enum_0_58:
  movq -9216(%rbp), %rdi
  call lm_enum_to_str
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
  jmp main_pr_next_0_58
main_pr_list_0_58:
  movq -9216(%rbp), %rdi
  call lm_list_to_str
  mov -10232(%rbp), rax
  movq -10232(%rbp), %rax
  addq $8, %rax
  movq %rax, -10240(%rbp)
  movq -10240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10248(%rbp)
  movq -10232(%rbp), %rax
  addq $24, %rax
  movq %rax, -10256(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10256(%rbp), %rsi
  movq -10248(%rbp), %rdx
  syscall
  movq %rax, -10264(%rbp)
  jmp main_pr_next_0_58
main_pr_nonstr_0_58:
  movq -9776(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10272(%rbp)
  movq -10272(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_58
  jmp main_pr_list_0_58
main_assert_pass_61:
  movq $0, %rax
  movq -1000(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_62(%rip), %rax
  movq -1008(%rbp), %rdx
  movq %rax, (%rdx)
  movq -952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10280(%rbp)
  movq -1008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10288(%rbp)
  movq -10280(%rbp), %rdi
  movq -10288(%rbp), %rsi
  call lm_key_eq
  mov -10296(%rbp), rax
  movq -10296(%rbp), %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_63(%rip), %rax
  movq -1024(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10304(%rbp)
  movq -1024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10312(%rbp)
  movq -10304(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_64
  jmp main_assert_fail_64
main_assert_fail_61:
  movq -9848(%rbp), %rax
  addq $8, %rax
  movq %rax, -10320(%rbp)
  movq -10320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10328(%rbp)
  movq -9848(%rbp), %rax
  addq $24, %rax
  movq %rax, -10336(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10336(%rbp), %rsi
  movq -10328(%rbp), %rdx
  syscall
  movq %rax, -10344(%rbp)
  movq $50397203, %rax
  movq %rax, -10352(%rbp)
  jmp main_assert_pass_61
main_assert_pass_64:
  movq $0, %rax
  movq -1032(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10360(%rbp)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10368(%rbp)
  movq -10368(%rbp), %rax
  addq -10360(%rbp), %rax
  movq %rax, -10376(%rbp)
  movq -10376(%rbp), %rax
  movq -1040(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -1048(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10384(%rbp)
  movq -1040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10392(%rbp)
  movq -10392(%rbp), %rax
  imulq -10384(%rbp), %rax
  movq %rax, -10400(%rbp)
  movq -10400(%rbp), %rax
  movq -1056(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10408(%rbp)
  movq -1056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10416(%rbp)
  movq -10416(%rbp), %rax
  subq -10408(%rbp), %rax
  movq %rax, -10424(%rbp)
  movq -10424(%rbp), %rax
  movq -1072(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_65(%rip), %rax
  movq -1088(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10432(%rbp)
  movq -1072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10440(%rbp)
  movq -10440(%rbp), %rdi
  call lm_to_string
  mov -10448(%rbp), rax
  movq -10432(%rbp), %rdi
  movq -10448(%rbp), %rsi
  call lm_rt_str_format
  mov -10456(%rbp), rax
  movq -10456(%rbp), %rax
  movq -1080(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10464(%rbp)
  movq -10464(%rbp), %rax
  movq -1096(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10472(%rbp)
  movq -10472(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -10480(%rbp)
  movq -10472(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -10488(%rbp)
  movq -10488(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10496(%rbp)
  movq -10480(%rbp), %rax
  andq -10496(%rbp), %rax
  movq %rax, -10504(%rbp)
  movq -10504(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_66
  jmp main_pr_int_0_66
main_assert_fail_64:
  movq -10312(%rbp), %rax
  addq $8, %rax
  movq %rax, -10512(%rbp)
  movq -10512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10520(%rbp)
  movq -10312(%rbp), %rax
  addq $24, %rax
  movq %rax, -10528(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10528(%rbp), %rsi
  movq -10520(%rbp), %rdx
  syscall
  movq %rax, -10536(%rbp)
  movq $50397203, %rax
  movq %rax, -10544(%rbp)
  jmp main_assert_pass_64
main_pr_ptr_0_66:
  movq -10472(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10552(%rbp)
  movq -10472(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10560(%rbp)
  movq -10552(%rbp), %rax
  orq -10560(%rbp), %rax
  movq %rax, -10568(%rbp)
  movq -10568(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_66
  jmp main_pr_obj_0_66
main_pr_int_0_66:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -10576(%rbp)
  movq $11, %rax
  movq -10576(%rbp), %rdx
  movl %eax, (%rdx)
  movq -10576(%rbp), %rax
  addq $4, %rax
  movq %rax, -10584(%rbp)
  movq $0, %rax
  movq -10584(%rbp), %rdx
  movl %eax, (%rdx)
  movq -10576(%rbp), %rax
  addq $63, %rax
  movq %rax, -10592(%rbp)
  movq $0, %rax
  movq -10592(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -10600(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -10592(%rbp), %rax
  movq -10600(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -10608(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -10616(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -10472(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -10624(%rbp)
  movq -10624(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_16
  jmp main_i2s_pos_16
main_pr_nil_0_66:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -10632(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10632(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -10640(%rbp)
  jmp main_pr_next_0_66
main_pr_obj_0_66:
  movq -10472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10648(%rbp)
  movq -10648(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -10656(%rbp)
  movq -10656(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10664(%rbp)
  movq -10664(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_66
  jmp main_pr_nonstr_0_66
main_pr_next_0_66:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -10672(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -10672(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -10680(%rbp)
  movq $0, %rax
  movq -1104(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_67(%rip), %rax
  movq -1112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1096(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10688(%rbp)
  movq -1112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10696(%rbp)
  movq -10688(%rbp), %rdi
  movq -10696(%rbp), %rsi
  call lm_key_eq
  mov -10704(%rbp), rax
  movq -10704(%rbp), %rax
  movq -1120(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_68(%rip), %rax
  movq -1128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10712(%rbp)
  movq -1128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10720(%rbp)
  movq -10712(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_69
  jmp main_assert_fail_69
main_i2s_neg_16:
  movq $1, %rax
  movq -10616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -10472(%rbp), %rax
  negq %rax
  movq %rax, -10728(%rbp)
  movq -10728(%rbp), %rax
  movq -10608(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_16
main_i2s_pos_16:
  movq $0, %rax
  movq -10616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -10472(%rbp), %rax
  movq -10608(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_16
main_i2s_loop_16:
  movq -10608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10736(%rbp)
  movq -10736(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -10744(%rbp)
  movq -10736(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -10752(%rbp)
  movq -10752(%rbp), %rax
  movq -10608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -10744(%rbp), %rax
  addq $48, %rax
  movq %rax, -10760(%rbp)
  movq -10600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10768(%rbp)
  movq -10768(%rbp), %rax
  subq $1, %rax
  movq %rax, -10776(%rbp)
  movq -10760(%rbp), %rax
  movq -10776(%rbp), %rdx
  movb %al, (%rdx)
  movq -10776(%rbp), %rax
  movq -10600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -10736(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -10784(%rbp)
  movq -10784(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_16
  jmp main_i2s_sign_16
main_i2s_sign_16:
  movq -10616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10792(%rbp)
  movq -10792(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -10800(%rbp)
  movq -10800(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_16
  jmp main_i2s_done_16
main_i2s_minus_16:
  movq -10600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10808(%rbp)
  movq -10808(%rbp), %rax
  subq $1, %rax
  movq %rax, -10816(%rbp)
  movq $45, %rax
  movq -10816(%rbp), %rdx
  movb %al, (%rdx)
  movq -10816(%rbp), %rax
  movq -10600(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_16
main_i2s_done_16:
  movq -10600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10824(%rbp)
  movq -10592(%rbp), %rax
  subq -10824(%rbp), %rax
  movq %rax, -10832(%rbp)
  movq -10576(%rbp), %rax
  addq $8, %rax
  movq %rax, -10840(%rbp)
  movq -10832(%rbp), %rax
  movq -10840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -10576(%rbp), %rax
  addq $16, %rax
  movq %rax, -10848(%rbp)
  movq -10832(%rbp), %rax
  movq -10848(%rbp), %rdx
  movq %rax, (%rdx)
  movq -10576(%rbp), %rax
  addq $24, %rax
  movq %rax, -10856(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -10864(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -10864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -10832(%rbp), %rax
  addq $1, %rax
  movq %rax, -10872(%rbp)
  jmp main_d2s_copy_loop_16
main_d2s_copy_loop_16:
  movq -10864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10880(%rbp)
  movq -10880(%rbp), %rax
  cmpq -10872(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -10888(%rbp)
  movq -10888(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_16
  jmp main_d2s_copy_done_16
main_d2s_copy_body_16:
  movq -10824(%rbp), %rax
  addq -10880(%rbp), %rax
  movq %rax, -10896(%rbp)
  movq -10896(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -10904(%rbp)
  movq -10856(%rbp), %rax
  addq -10880(%rbp), %rax
  movq %rax, -10912(%rbp)
  movq -10904(%rbp), %rax
  movq -10912(%rbp), %rdx
  movb %al, (%rdx)
  movq -10880(%rbp), %rax
  addq $1, %rax
  movq %rax, -10920(%rbp)
  movq -10920(%rbp), %rax
  movq -10864(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_16
main_d2s_copy_done_16:
  movq -10576(%rbp), %rax
  addq $24, %rax
  movq %rax, -10928(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -10936(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -10936(%rbp), %rdx
  movq %rax, (%rdx)
  movq -10832(%rbp), %rax
  addq $1, %rax
  movq %rax, -10944(%rbp)
  jmp main_i2s_copy_loop_16
main_i2s_copy_loop_16:
  movq -10936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -10952(%rbp)
  movq -10952(%rbp), %rax
  cmpq -10944(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -10960(%rbp)
  movq -10960(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_16
  jmp main_i2s_copy_done_16
main_i2s_copy_body_16:
  movq -10824(%rbp), %rax
  addq -10952(%rbp), %rax
  movq %rax, -10968(%rbp)
  movq -10968(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -10976(%rbp)
  movq -10928(%rbp), %rax
  addq -10952(%rbp), %rax
  movq %rax, -10984(%rbp)
  movq -10976(%rbp), %rax
  movq -10984(%rbp), %rdx
  movb %al, (%rdx)
  movq -10952(%rbp), %rax
  addq $1, %rax
  movq %rax, -10992(%rbp)
  movq -10992(%rbp), %rax
  movq -10936(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_16
main_i2s_copy_done_16:
  movq -10576(%rbp), %rax
  addq $8, %rax
  movq %rax, -11000(%rbp)
  movq -11000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11008(%rbp)
  movq -10576(%rbp), %rax
  addq $24, %rax
  movq %rax, -11016(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11016(%rbp), %rsi
  movq -11008(%rbp), %rdx
  syscall
  movq %rax, -11024(%rbp)
  jmp main_pr_next_0_66
main_pr_str_0_66:
  movq -10472(%rbp), %rax
  addq $8, %rax
  movq %rax, -11032(%rbp)
  movq -11032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11040(%rbp)
  movq -10472(%rbp), %rax
  addq $24, %rax
  movq %rax, -11048(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11048(%rbp), %rsi
  movq -11040(%rbp), %rdx
  syscall
  movq %rax, -11056(%rbp)
  jmp main_pr_next_0_66
main_pr_enum_0_66:
  movq -10472(%rbp), %rdi
  call lm_enum_to_str
  mov -11064(%rbp), rax
  movq -11064(%rbp), %rax
  addq $8, %rax
  movq %rax, -11072(%rbp)
  movq -11072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11080(%rbp)
  movq -11064(%rbp), %rax
  addq $24, %rax
  movq %rax, -11088(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11088(%rbp), %rsi
  movq -11080(%rbp), %rdx
  syscall
  movq %rax, -11096(%rbp)
  jmp main_pr_next_0_66
main_pr_list_0_66:
  movq -10472(%rbp), %rdi
  call lm_list_to_str
  mov -11104(%rbp), rax
  movq -11104(%rbp), %rax
  addq $8, %rax
  movq %rax, -11112(%rbp)
  movq -11112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11120(%rbp)
  movq -11104(%rbp), %rax
  addq $24, %rax
  movq %rax, -11128(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11128(%rbp), %rsi
  movq -11120(%rbp), %rdx
  syscall
  movq %rax, -11136(%rbp)
  jmp main_pr_next_0_66
main_pr_nonstr_0_66:
  movq -10648(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11144(%rbp)
  movq -11144(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_66
  jmp main_pr_list_0_66
main_assert_pass_69:
  movq $0, %rax
  movq -1136(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_70(%rip), %rax
  movq -1152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11152(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11160(%rbp)
  movq -11152(%rbp), %rdi
  movq -11160(%rbp), %rsi
  call lm_rt_str_format
  mov -11168(%rbp), rax
  movq -11168(%rbp), %rax
  movq -1144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11176(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11184(%rbp)
  movq -11184(%rbp), %rdi
  call lm_to_string
  mov -11192(%rbp), rax
  movq -11176(%rbp), %rdi
  movq -11192(%rbp), %rsi
  call lm_rt_str_format
  mov -11200(%rbp), rax
  movq -11200(%rbp), %rax
  movq -1160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11208(%rbp)
  movq -11208(%rbp), %rax
  movq -1144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11216(%rbp)
  movq -11216(%rbp), %rax
  movq -1168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11224(%rbp)
  movq -11224(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -11232(%rbp)
  movq -11224(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -11240(%rbp)
  movq -11240(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11248(%rbp)
  movq -11232(%rbp), %rax
  andq -11248(%rbp), %rax
  movq %rax, -11256(%rbp)
  movq -11256(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_71
  jmp main_pr_int_0_71
main_assert_fail_69:
  movq -10720(%rbp), %rax
  addq $8, %rax
  movq %rax, -11264(%rbp)
  movq -11264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11272(%rbp)
  movq -10720(%rbp), %rax
  addq $24, %rax
  movq %rax, -11280(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11280(%rbp), %rsi
  movq -11272(%rbp), %rdx
  syscall
  movq %rax, -11288(%rbp)
  movq $50397203, %rax
  movq %rax, -11296(%rbp)
  jmp main_assert_pass_69
main_pr_ptr_0_71:
  movq -11224(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11304(%rbp)
  movq -11224(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11312(%rbp)
  movq -11304(%rbp), %rax
  orq -11312(%rbp), %rax
  movq %rax, -11320(%rbp)
  movq -11320(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_71
  jmp main_pr_obj_0_71
main_pr_int_0_71:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -11328(%rbp)
  movq $11, %rax
  movq -11328(%rbp), %rdx
  movl %eax, (%rdx)
  movq -11328(%rbp), %rax
  addq $4, %rax
  movq %rax, -11336(%rbp)
  movq $0, %rax
  movq -11336(%rbp), %rdx
  movl %eax, (%rdx)
  movq -11328(%rbp), %rax
  addq $63, %rax
  movq %rax, -11344(%rbp)
  movq $0, %rax
  movq -11344(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -11352(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -11344(%rbp), %rax
  movq -11352(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -11360(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -11368(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -11224(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -11376(%rbp)
  movq -11376(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_17
  jmp main_i2s_pos_17
main_pr_nil_0_71:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -11384(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11384(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -11392(%rbp)
  jmp main_pr_next_0_71
main_pr_obj_0_71:
  movq -11224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11400(%rbp)
  movq -11400(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -11408(%rbp)
  movq -11408(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11416(%rbp)
  movq -11416(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_71
  jmp main_pr_nonstr_0_71
main_pr_next_0_71:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -11424(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11424(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -11432(%rbp)
  movq $0, %rax
  movq -1176(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_72(%rip), %rax
  movq -1184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11440(%rbp)
  movq -1184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11448(%rbp)
  movq -11440(%rbp), %rdi
  movq -11448(%rbp), %rsi
  call lm_key_eq
  mov -11456(%rbp), rax
  movq -11456(%rbp), %rax
  movq -1192(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_73(%rip), %rax
  movq -1200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11464(%rbp)
  movq -1200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11472(%rbp)
  movq -11464(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_74
  jmp main_assert_fail_74
main_i2s_neg_17:
  movq $1, %rax
  movq -11368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -11224(%rbp), %rax
  negq %rax
  movq %rax, -11480(%rbp)
  movq -11480(%rbp), %rax
  movq -11360(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_17
main_i2s_pos_17:
  movq $0, %rax
  movq -11368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -11224(%rbp), %rax
  movq -11360(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_17
main_i2s_loop_17:
  movq -11360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11488(%rbp)
  movq -11488(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -11496(%rbp)
  movq -11488(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -11504(%rbp)
  movq -11504(%rbp), %rax
  movq -11360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -11496(%rbp), %rax
  addq $48, %rax
  movq %rax, -11512(%rbp)
  movq -11352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11520(%rbp)
  movq -11520(%rbp), %rax
  subq $1, %rax
  movq %rax, -11528(%rbp)
  movq -11512(%rbp), %rax
  movq -11528(%rbp), %rdx
  movb %al, (%rdx)
  movq -11528(%rbp), %rax
  movq -11352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -11488(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -11536(%rbp)
  movq -11536(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_17
  jmp main_i2s_sign_17
main_i2s_sign_17:
  movq -11368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11544(%rbp)
  movq -11544(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11552(%rbp)
  movq -11552(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_17
  jmp main_i2s_done_17
main_i2s_minus_17:
  movq -11352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11560(%rbp)
  movq -11560(%rbp), %rax
  subq $1, %rax
  movq %rax, -11568(%rbp)
  movq $45, %rax
  movq -11568(%rbp), %rdx
  movb %al, (%rdx)
  movq -11568(%rbp), %rax
  movq -11352(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_17
main_i2s_done_17:
  movq -11352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11576(%rbp)
  movq -11344(%rbp), %rax
  subq -11576(%rbp), %rax
  movq %rax, -11584(%rbp)
  movq -11328(%rbp), %rax
  addq $8, %rax
  movq %rax, -11592(%rbp)
  movq -11584(%rbp), %rax
  movq -11592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -11328(%rbp), %rax
  addq $16, %rax
  movq %rax, -11600(%rbp)
  movq -11584(%rbp), %rax
  movq -11600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -11328(%rbp), %rax
  addq $24, %rax
  movq %rax, -11608(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -11616(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -11616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -11584(%rbp), %rax
  addq $1, %rax
  movq %rax, -11624(%rbp)
  jmp main_d2s_copy_loop_17
main_d2s_copy_loop_17:
  movq -11616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11632(%rbp)
  movq -11632(%rbp), %rax
  cmpq -11624(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -11640(%rbp)
  movq -11640(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_17
  jmp main_d2s_copy_done_17
main_d2s_copy_body_17:
  movq -11576(%rbp), %rax
  addq -11632(%rbp), %rax
  movq %rax, -11648(%rbp)
  movq -11648(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -11656(%rbp)
  movq -11608(%rbp), %rax
  addq -11632(%rbp), %rax
  movq %rax, -11664(%rbp)
  movq -11656(%rbp), %rax
  movq -11664(%rbp), %rdx
  movb %al, (%rdx)
  movq -11632(%rbp), %rax
  addq $1, %rax
  movq %rax, -11672(%rbp)
  movq -11672(%rbp), %rax
  movq -11616(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_17
main_d2s_copy_done_17:
  movq -11328(%rbp), %rax
  addq $24, %rax
  movq %rax, -11680(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -11688(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -11688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -11584(%rbp), %rax
  addq $1, %rax
  movq %rax, -11696(%rbp)
  jmp main_i2s_copy_loop_17
main_i2s_copy_loop_17:
  movq -11688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11704(%rbp)
  movq -11704(%rbp), %rax
  cmpq -11696(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -11712(%rbp)
  movq -11712(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_17
  jmp main_i2s_copy_done_17
main_i2s_copy_body_17:
  movq -11576(%rbp), %rax
  addq -11704(%rbp), %rax
  movq %rax, -11720(%rbp)
  movq -11720(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -11728(%rbp)
  movq -11680(%rbp), %rax
  addq -11704(%rbp), %rax
  movq %rax, -11736(%rbp)
  movq -11728(%rbp), %rax
  movq -11736(%rbp), %rdx
  movb %al, (%rdx)
  movq -11704(%rbp), %rax
  addq $1, %rax
  movq %rax, -11744(%rbp)
  movq -11744(%rbp), %rax
  movq -11688(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_17
main_i2s_copy_done_17:
  movq -11328(%rbp), %rax
  addq $8, %rax
  movq %rax, -11752(%rbp)
  movq -11752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11760(%rbp)
  movq -11328(%rbp), %rax
  addq $24, %rax
  movq %rax, -11768(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11768(%rbp), %rsi
  movq -11760(%rbp), %rdx
  syscall
  movq %rax, -11776(%rbp)
  jmp main_pr_next_0_71
main_pr_str_0_71:
  movq -11224(%rbp), %rax
  addq $8, %rax
  movq %rax, -11784(%rbp)
  movq -11784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11792(%rbp)
  movq -11224(%rbp), %rax
  addq $24, %rax
  movq %rax, -11800(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11800(%rbp), %rsi
  movq -11792(%rbp), %rdx
  syscall
  movq %rax, -11808(%rbp)
  jmp main_pr_next_0_71
main_pr_enum_0_71:
  movq -11224(%rbp), %rdi
  call lm_enum_to_str
  mov -11816(%rbp), rax
  movq -11816(%rbp), %rax
  addq $8, %rax
  movq %rax, -11824(%rbp)
  movq -11824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11832(%rbp)
  movq -11816(%rbp), %rax
  addq $24, %rax
  movq %rax, -11840(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11840(%rbp), %rsi
  movq -11832(%rbp), %rdx
  syscall
  movq %rax, -11848(%rbp)
  jmp main_pr_next_0_71
main_pr_list_0_71:
  movq -11224(%rbp), %rdi
  call lm_list_to_str
  mov -11856(%rbp), rax
  movq -11856(%rbp), %rax
  addq $8, %rax
  movq %rax, -11864(%rbp)
  movq -11864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11872(%rbp)
  movq -11856(%rbp), %rax
  addq $24, %rax
  movq %rax, -11880(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11880(%rbp), %rsi
  movq -11872(%rbp), %rdx
  syscall
  movq %rax, -11888(%rbp)
  jmp main_pr_next_0_71
main_pr_nonstr_0_71:
  movq -11400(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11896(%rbp)
  movq -11896(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_71
  jmp main_pr_list_0_71
main_assert_pass_74:
  movq $0, %rax
  movq -1208(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_75(%rip), %rax
  movq -1216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11904(%rbp)
  movq -11904(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -11912(%rbp)
  movq -11904(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -11920(%rbp)
  movq -11920(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11928(%rbp)
  movq -11912(%rbp), %rax
  andq -11928(%rbp), %rax
  movq %rax, -11936(%rbp)
  movq -11936(%rbp), %rax
  testq %rax, %rax
  jne main_pr_ptr_0_76
  jmp main_pr_int_0_76
main_assert_fail_74:
  movq -11472(%rbp), %rax
  addq $8, %rax
  movq %rax, -11944(%rbp)
  movq -11944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -11952(%rbp)
  movq -11472(%rbp), %rax
  addq $24, %rax
  movq %rax, -11960(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -11960(%rbp), %rsi
  movq -11952(%rbp), %rdx
  syscall
  movq %rax, -11968(%rbp)
  movq $50397203, %rax
  movq %rax, -11976(%rbp)
  jmp main_assert_pass_74
main_pr_ptr_0_76:
  movq -11904(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11984(%rbp)
  movq -11904(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -11992(%rbp)
  movq -11984(%rbp), %rax
  orq -11992(%rbp), %rax
  movq %rax, -12000(%rbp)
  movq -12000(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_76
  jmp main_pr_obj_0_76
main_pr_int_0_76:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -12008(%rbp)
  movq $11, %rax
  movq -12008(%rbp), %rdx
  movl %eax, (%rdx)
  movq -12008(%rbp), %rax
  addq $4, %rax
  movq %rax, -12016(%rbp)
  movq $0, %rax
  movq -12016(%rbp), %rdx
  movl %eax, (%rdx)
  movq -12008(%rbp), %rax
  addq $63, %rax
  movq %rax, -12024(%rbp)
  movq $0, %rax
  movq -12024(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -12032(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -12024(%rbp), %rax
  movq -12032(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -12040(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -12048(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -11904(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -12056(%rbp)
  movq -12056(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_18
  jmp main_i2s_pos_18
main_pr_nil_0_76:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -12064(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12064(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -12072(%rbp)
  jmp main_pr_next_0_76
main_pr_obj_0_76:
  movq -11904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12080(%rbp)
  movq -12080(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -12088(%rbp)
  movq -12088(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -12096(%rbp)
  movq -12096(%rbp), %rax
  testq %rax, %rax
  jne main_pr_str_0_76
  jmp main_pr_nonstr_0_76
main_pr_next_0_76:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -12104(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12104(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -12112(%rbp)
  movq $0, %rax
  movq -1224(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp main_epilogue
main_i2s_neg_18:
  movq $1, %rax
  movq -12048(%rbp), %rdx
  movq %rax, (%rdx)
  movq -11904(%rbp), %rax
  negq %rax
  movq %rax, -12120(%rbp)
  movq -12120(%rbp), %rax
  movq -12040(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_18
main_i2s_pos_18:
  movq $0, %rax
  movq -12048(%rbp), %rdx
  movq %rax, (%rdx)
  movq -11904(%rbp), %rax
  movq -12040(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_18
main_i2s_loop_18:
  movq -12040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12128(%rbp)
  movq -12128(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -12136(%rbp)
  movq -12128(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -12144(%rbp)
  movq -12144(%rbp), %rax
  movq -12040(%rbp), %rdx
  movq %rax, (%rdx)
  movq -12136(%rbp), %rax
  addq $48, %rax
  movq %rax, -12152(%rbp)
  movq -12032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12160(%rbp)
  movq -12160(%rbp), %rax
  subq $1, %rax
  movq %rax, -12168(%rbp)
  movq -12152(%rbp), %rax
  movq -12168(%rbp), %rdx
  movb %al, (%rdx)
  movq -12168(%rbp), %rax
  movq -12032(%rbp), %rdx
  movq %rax, (%rdx)
  movq -12128(%rbp), %rax
  cmpq $10, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -12176(%rbp)
  movq -12176(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_18
  jmp main_i2s_sign_18
main_i2s_sign_18:
  movq -12048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12184(%rbp)
  movq -12184(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -12192(%rbp)
  movq -12192(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_18
  jmp main_i2s_done_18
main_i2s_minus_18:
  movq -12032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12200(%rbp)
  movq -12200(%rbp), %rax
  subq $1, %rax
  movq %rax, -12208(%rbp)
  movq $45, %rax
  movq -12208(%rbp), %rdx
  movb %al, (%rdx)
  movq -12208(%rbp), %rax
  movq -12032(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_18
main_i2s_done_18:
  movq -12032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12216(%rbp)
  movq -12024(%rbp), %rax
  subq -12216(%rbp), %rax
  movq %rax, -12224(%rbp)
  movq -12008(%rbp), %rax
  addq $8, %rax
  movq %rax, -12232(%rbp)
  movq -12224(%rbp), %rax
  movq -12232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -12008(%rbp), %rax
  addq $16, %rax
  movq %rax, -12240(%rbp)
  movq -12224(%rbp), %rax
  movq -12240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -12008(%rbp), %rax
  addq $24, %rax
  movq %rax, -12248(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -12256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -12256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -12224(%rbp), %rax
  addq $1, %rax
  movq %rax, -12264(%rbp)
  jmp main_d2s_copy_loop_18
main_d2s_copy_loop_18:
  movq -12256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12272(%rbp)
  movq -12272(%rbp), %rax
  cmpq -12264(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -12280(%rbp)
  movq -12280(%rbp), %rax
  testq %rax, %rax
  jne main_d2s_copy_body_18
  jmp main_d2s_copy_done_18
main_d2s_copy_body_18:
  movq -12216(%rbp), %rax
  addq -12272(%rbp), %rax
  movq %rax, -12288(%rbp)
  movq -12288(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -12296(%rbp)
  movq -12248(%rbp), %rax
  addq -12272(%rbp), %rax
  movq %rax, -12304(%rbp)
  movq -12296(%rbp), %rax
  movq -12304(%rbp), %rdx
  movb %al, (%rdx)
  movq -12272(%rbp), %rax
  addq $1, %rax
  movq %rax, -12312(%rbp)
  movq -12312(%rbp), %rax
  movq -12256(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_d2s_copy_loop_18
main_d2s_copy_done_18:
  movq -12008(%rbp), %rax
  addq $24, %rax
  movq %rax, -12320(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -12328(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -12328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -12224(%rbp), %rax
  addq $1, %rax
  movq %rax, -12336(%rbp)
  jmp main_i2s_copy_loop_18
main_i2s_copy_loop_18:
  movq -12328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12344(%rbp)
  movq -12344(%rbp), %rax
  cmpq -12336(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -12352(%rbp)
  movq -12352(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_copy_body_18
  jmp main_i2s_copy_done_18
main_i2s_copy_body_18:
  movq -12216(%rbp), %rax
  addq -12344(%rbp), %rax
  movq %rax, -12360(%rbp)
  movq -12360(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -12368(%rbp)
  movq -12320(%rbp), %rax
  addq -12344(%rbp), %rax
  movq %rax, -12376(%rbp)
  movq -12368(%rbp), %rax
  movq -12376(%rbp), %rdx
  movb %al, (%rdx)
  movq -12344(%rbp), %rax
  addq $1, %rax
  movq %rax, -12384(%rbp)
  movq -12384(%rbp), %rax
  movq -12328(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_copy_loop_18
main_i2s_copy_done_18:
  movq -12008(%rbp), %rax
  addq $8, %rax
  movq %rax, -12392(%rbp)
  movq -12392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12400(%rbp)
  movq -12008(%rbp), %rax
  addq $24, %rax
  movq %rax, -12408(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12408(%rbp), %rsi
  movq -12400(%rbp), %rdx
  syscall
  movq %rax, -12416(%rbp)
  jmp main_pr_next_0_76
main_pr_str_0_76:
  movq -11904(%rbp), %rax
  addq $8, %rax
  movq %rax, -12424(%rbp)
  movq -12424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12432(%rbp)
  movq -11904(%rbp), %rax
  addq $24, %rax
  movq %rax, -12440(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12440(%rbp), %rsi
  movq -12432(%rbp), %rdx
  syscall
  movq %rax, -12448(%rbp)
  jmp main_pr_next_0_76
main_pr_enum_0_76:
  movq -11904(%rbp), %rdi
  call lm_enum_to_str
  mov -12456(%rbp), rax
  movq -12456(%rbp), %rax
  addq $8, %rax
  movq %rax, -12464(%rbp)
  movq -12464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12472(%rbp)
  movq -12456(%rbp), %rax
  addq $24, %rax
  movq %rax, -12480(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12480(%rbp), %rsi
  movq -12472(%rbp), %rdx
  syscall
  movq %rax, -12488(%rbp)
  jmp main_pr_next_0_76
main_pr_list_0_76:
  movq -11904(%rbp), %rdi
  call lm_list_to_str
  mov -12496(%rbp), rax
  movq -12496(%rbp), %rax
  addq $8, %rax
  movq %rax, -12504(%rbp)
  movq -12504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -12512(%rbp)
  movq -12496(%rbp), %rax
  addq $24, %rax
  movq %rax, -12520(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -12520(%rbp), %rsi
  movq -12512(%rbp), %rdx
  syscall
  movq %rax, -12528(%rbp)
  jmp main_pr_next_0_76
main_pr_nonstr_0_76:
  movq -12080(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -12536(%rbp)
  movq -12536(%rbp), %rax
  testq %rax, %rax
  jne main_pr_enum_0_76
  jmp main_pr_list_0_76
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

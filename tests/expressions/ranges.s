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
  .byte 82
  .byte 97
  .byte 110
  .byte 103
  .byte 101
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
  .byte 82
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 32
  .byte 49
  .byte 46
  .byte 46
  .byte 53
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
  .byte 82
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 32
  .byte 49
  .byte 46
  .byte 46
  .byte 53
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
  .byte 49
  .byte 44
  .byte 50
  .byte 44
  .byte 51
  .byte 44
  .byte 52
  .byte 41
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
  .byte 48
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
  .byte 82
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 32
  .byte 48
  .byte 46
  .byte 46
  .byte 51
  .byte 58
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
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 32
  .byte 48
  .byte 46
  .byte 46
  .byte 51
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
  .byte 48
  .byte 44
  .byte 49
  .byte 44
  .byte 50
  .byte 41
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
  .byte 48
  .byte 43
  .byte 49
  .byte 43
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
  .byte 37
  .byte 115
  .byte 46
  .byte 46
  .byte 37
  .byte 115
  .byte 58
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
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 32
  .byte 53
  .byte 46
  .byte 46
  .byte 56
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
  .byte 53
  .byte 44
  .byte 54
  .byte 44
  .byte 55
  .byte 41
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
  .byte 83
  .byte 117
  .byte 109
  .byte 32
  .byte 111
  .byte 102
  .byte 32
  .byte 53
  .byte 43
  .byte 54
  .byte 43
  .byte 55
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
  .byte 114
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 32
  .byte 37
  .byte 115
  .byte 46
  .byte 46
  .byte 37
  .byte 115
  .byte 58
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
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 32
  .byte 50
  .byte 46
  .byte 46
  .byte 53
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
  .byte 44
  .byte 51
  .byte 44
  .byte 52
  .byte 41
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
str_hdr_21:
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
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 114
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 115
  .byte 58
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
  .byte 79
  .byte 117
  .byte 116
  .byte 101
  .byte 114
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
  .byte 32
  .byte 32
  .byte 73
  .byte 110
  .byte 110
  .byte 101
  .byte 114
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
  .byte 69
  .byte 97
  .byte 99
  .byte 104
  .byte 32
  .byte 105
  .byte 110
  .byte 110
  .byte 101
  .byte 114
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
  .byte 50
  .byte 32
  .byte 116
  .byte 105
  .byte 109
  .byte 101
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
  .byte 79
  .byte 117
  .byte 116
  .byte 101
  .byte 114
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
  .byte 50
  .byte 32
  .byte 116
  .byte 105
  .byte 109
  .byte 101
  .byte 115
  .byte 32
  .byte 40
  .byte 49
  .byte 44
  .byte 50
  .byte 41
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
  .byte 84
  .byte 111
  .byte 116
  .byte 97
  .byte 108
  .byte 32
  .byte 105
  .byte 110
  .byte 110
  .byte 101
  .byte 114
  .byte 32
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
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
  .byte 52
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
  .byte 69
  .byte 109
  .byte 112
  .byte 116
  .byte 121
  .byte 32
  .byte 114
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 32
  .byte 40
  .byte 53
  .byte 46
  .byte 46
  .byte 53
  .byte 41
  .byte 58
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
  .byte 84
  .byte 104
  .byte 105
  .byte 115
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
  .byte 112
  .byte 114
  .byte 105
  .byte 110
  .byte 116
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
  .byte 109
  .byte 112
  .byte 116
  .byte 121
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
  .byte 110
  .byte 111
  .byte 116
  .byte 32
  .byte 105
  .byte 116
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 101
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
  .byte 69
  .byte 109
  .byte 112
  .byte 116
  .byte 121
  .byte 32
  .byte 114
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
  .byte 32
  .byte 99
  .byte 111
  .byte 109
  .byte 112
  .byte 108
  .byte 101
  .byte 116
  .byte 101
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
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 82
  .byte 97
  .byte 110
  .byte 103
  .byte 101
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
  subq $5416, %rsp
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
  jmp main_block_0
main_block_0:
  leaq str_hdr_0(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1392(%rbp)
  movq -1392(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1400(%rbp)
  movq -1400(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9383
  jmp main_pr_str_0_9383
main_block_9:
  movq $5, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1408(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1416(%rbp)
  movq -1416(%rbp), %rax
  cmpq -1408(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1424(%rbp)
  movq -1424(%rbp), %rax
  movq -120(%rbp), %rdx
  movl %eax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1432(%rbp)
  movq -1432(%rbp), %rax
  testq %rax, %rax
  jne main_block_12
  jmp main_block_21
main_block_12:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1440(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -1448(%rbp)
  movq $11, %rax
  movq -1448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1448(%rbp), %rax
  addq $63, %rax
  movq %rax, -1456(%rbp)
  movq $0, %rax
  movq -1456(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1464(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1456(%rbp), %rax
  movq -1464(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1472(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1480(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1440(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1488(%rbp)
  movq -1488(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_1
  jmp main_i2s_pos_1
main_block_17:
  movq $1, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1496(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1504(%rbp)
  movq -1504(%rbp), %rax
  addq -1496(%rbp), %rax
  movq %rax, -1512(%rbp)
  movq -1512(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1520(%rbp)
  movq -1520(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_9
main_block_21:
  movq $4, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1528(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1536(%rbp)
  movq -1536(%rbp), %rax
  cmpq -1528(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1544(%rbp)
  movq -1544(%rbp), %rax
  movq -168(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_2(%rip), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1552(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1560(%rbp)
  movq -1552(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_3
  jmp main_assert_fail_3
main_block_36:
  movq $3, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1568(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1576(%rbp)
  movq -1576(%rbp), %rax
  cmpq -1568(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1584(%rbp)
  movq -1584(%rbp), %rax
  movq -280(%rbp), %rdx
  movl %eax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1592(%rbp)
  movq -1592(%rbp), %rax
  testq %rax, %rax
  jne main_block_39
  jmp main_block_48
main_block_39:
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1600(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -1608(%rbp)
  movq $11, %rax
  movq -1608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1608(%rbp), %rax
  addq $63, %rax
  movq %rax, -1616(%rbp)
  movq $0, %rax
  movq -1616(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1624(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1616(%rbp), %rax
  movq -1624(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1632(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1640(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1600(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1648(%rbp)
  movq -1648(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_2
  jmp main_i2s_pos_2
main_block_44:
  movq $1, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1656(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1664(%rbp)
  movq -1664(%rbp), %rax
  addq -1656(%rbp), %rax
  movq %rax, -1672(%rbp)
  movq -1672(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1680(%rbp)
  movq -1680(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_36
main_block_48:
  movq $3, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1688(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1696(%rbp)
  movq -1696(%rbp), %rax
  cmpq -1688(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1704(%rbp)
  movq -1704(%rbp), %rax
  movq -328(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_7(%rip), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1712(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1720(%rbp)
  movq -1712(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_8
  jmp main_assert_fail_8
main_block_67:
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1728(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1736(%rbp)
  movq -1736(%rbp), %rax
  cmpq -1728(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1744(%rbp)
  movq -1744(%rbp), %rax
  movq -456(%rbp), %rdx
  movl %eax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1752(%rbp)
  movq -1752(%rbp), %rax
  testq %rax, %rax
  jne main_block_69
  jmp main_block_78
main_block_69:
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1760(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -1768(%rbp)
  movq $11, %rax
  movq -1768(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1768(%rbp), %rax
  addq $63, %rax
  movq %rax, -1776(%rbp)
  movq $0, %rax
  movq -1776(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1784(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1776(%rbp), %rax
  movq -1784(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1792(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1800(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1760(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1808(%rbp)
  movq -1808(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_3
  jmp main_i2s_pos_3
main_block_74:
  movq $1, %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1816(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1824(%rbp)
  movq -1824(%rbp), %rax
  addq -1816(%rbp), %rax
  movq %rax, -1832(%rbp)
  movq -1832(%rbp), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1840(%rbp)
  movq -1840(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_67
main_block_78:
  movq $3, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1848(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1856(%rbp)
  movq -1856(%rbp), %rax
  cmpq -1848(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1864(%rbp)
  movq -1864(%rbp), %rax
  movq -504(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_12(%rip), %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1872(%rbp)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1880(%rbp)
  movq -1872(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_13
  jmp main_assert_fail_13
main_block_99:
  movq $3, %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1888(%rbp)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1896(%rbp)
  movq -1896(%rbp), %rax
  addq -1888(%rbp), %rax
  movq %rax, -1904(%rbp)
  movq -1904(%rbp), %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1912(%rbp)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1920(%rbp)
  movq -1920(%rbp), %rax
  cmpq -1912(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1928(%rbp)
  movq -1928(%rbp), %rax
  movq -672(%rbp), %rdx
  movl %eax, (%rdx)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1936(%rbp)
  movq -1936(%rbp), %rax
  testq %rax, %rax
  jne main_block_104
  jmp main_block_113
main_block_104:
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1944(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -1952(%rbp)
  movq $11, %rax
  movq -1952(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1952(%rbp), %rax
  addq $63, %rax
  movq %rax, -1960(%rbp)
  movq $0, %rax
  movq -1960(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1968(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1960(%rbp), %rax
  movq -1968(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1976(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1984(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -1944(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1992(%rbp)
  movq -1992(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_neg_4
  jmp main_i2s_pos_4
main_block_109:
  movq $1, %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2000(%rbp)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2008(%rbp)
  movq -2008(%rbp), %rax
  addq -2000(%rbp), %rax
  movq %rax, -2016(%rbp)
  movq -2016(%rbp), %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2024(%rbp)
  movq -2024(%rbp), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_99
main_block_113:
  movq $3, %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2032(%rbp)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2040(%rbp)
  movq -2040(%rbp), %rax
  cmpq -2032(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2048(%rbp)
  movq -2048(%rbp), %rax
  movq -720(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_17(%rip), %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2056(%rbp)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2064(%rbp)
  movq -2056(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_18
  jmp main_assert_fail_18
main_block_128:
  movq $3, %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2072(%rbp)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2080(%rbp)
  movq -2080(%rbp), %rax
  cmpq -2072(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2088(%rbp)
  movq -2088(%rbp), %rax
  movq -832(%rbp), %rdx
  movl %eax, (%rdx)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2096(%rbp)
  movq -2096(%rbp), %rax
  testq %rax, %rax
  jne main_block_131
  jmp main_block_171
main_block_131:
  leaq str_hdr_22(%rip), %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2104(%rbp)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2112(%rbp)
  movq -2104(%rbp), %rdi
  movq -2112(%rbp), %rsi
  call lm_rt_str_format
  mov -2120(%rbp), rax
  movq -2120(%rbp), %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -840(%rbp), %rax
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
main_block_141:
  movq $10, %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2144(%rbp)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2152(%rbp)
  movq -2152(%rbp), %rax
  imulq -2144(%rbp), %rax
  movq %rax, -2160(%rbp)
  movq -2160(%rbp), %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2168(%rbp)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2176(%rbp)
  movq -2176(%rbp), %rax
  imulq -2168(%rbp), %rax
  movq %rax, -2184(%rbp)
  movq -2184(%rbp), %rax
  movq -936(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2192(%rbp)
  movq -936(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2200(%rbp)
  movq -2200(%rbp), %rax
  addq -2192(%rbp), %rax
  movq %rax, -2208(%rbp)
  movq -2208(%rbp), %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  movq -952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2216(%rbp)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2224(%rbp)
  movq -2224(%rbp), %rax
  cmpq -2216(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2232(%rbp)
  movq -2232(%rbp), %rax
  movq -960(%rbp), %rdx
  movl %eax, (%rdx)
  movq -960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2240(%rbp)
  movq -2240(%rbp), %rax
  testq %rax, %rax
  jne main_block_150
  jmp main_block_162
main_block_150:
  leaq str_hdr_23(%rip), %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2248(%rbp)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2256(%rbp)
  movq -2248(%rbp), %rdi
  movq -2256(%rbp), %rsi
  call lm_rt_str_format
  mov -2264(%rbp), rax
  movq -2264(%rbp), %rax
  movq -968(%rbp), %rdx
  movq %rax, (%rdx)
  movq -968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2272(%rbp)
  movq -2272(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2280(%rbp)
  movq -2280(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_492
  jmp main_pr_str_0_492
main_block_158:
  movq $1, %rax
  movq -1008(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2288(%rbp)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2296(%rbp)
  movq -2296(%rbp), %rax
  addq -2288(%rbp), %rax
  movq %rax, -2304(%rbp)
  movq -2304(%rbp), %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2312(%rbp)
  movq -2312(%rbp), %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_141
main_block_162:
  movq $2, %rax
  movq -1024(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2320(%rbp)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2328(%rbp)
  movq -2328(%rbp), %rax
  cmpq -2320(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2336(%rbp)
  movq -2336(%rbp), %rax
  movq -1032(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_24(%rip), %rax
  movq -1040(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1032(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2344(%rbp)
  movq -1040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2352(%rbp)
  movq -2344(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_25
  jmp main_assert_fail_25
main_block_167:
  movq $1, %rax
  movq -1056(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2360(%rbp)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2368(%rbp)
  movq -2368(%rbp), %rax
  addq -2360(%rbp), %rax
  movq %rax, -2376(%rbp)
  movq -2376(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2384(%rbp)
  movq -2384(%rbp), %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_128
main_block_171:
  movq $2, %rax
  movq -1072(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2392(%rbp)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2400(%rbp)
  movq -2400(%rbp), %rax
  cmpq -2392(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2408(%rbp)
  movq -2408(%rbp), %rax
  movq -1080(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_26(%rip), %rax
  movq -1088(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1080(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2416(%rbp)
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2424(%rbp)
  movq -2416(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_27
  jmp main_assert_fail_27
main_block_185:
  movq $5, %rax
  movq -1176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2432(%rbp)
  movq -1160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2440(%rbp)
  movq -2440(%rbp), %rax
  cmpq -2432(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -2448(%rbp)
  movq -2448(%rbp), %rax
  movq -1184(%rbp), %rdx
  movl %eax, (%rdx)
  movq -1184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2456(%rbp)
  movq -2456(%rbp), %rax
  testq %rax, %rax
  jne main_block_188
  jmp main_block_198
main_block_188:
  leaq str_hdr_31(%rip), %rax
  movq -1200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2464(%rbp)
  movq -1160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2472(%rbp)
  movq -2464(%rbp), %rdi
  movq -2472(%rbp), %rsi
  call lm_rt_str_format
  mov -2480(%rbp), rax
  movq -2480(%rbp), %rax
  movq -1192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2488(%rbp)
  movq -2488(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2496(%rbp)
  movq -2496(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1421
  jmp main_pr_str_0_1421
main_block_194:
  movq $1, %rax
  movq -1224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2504(%rbp)
  movq -1160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2512(%rbp)
  movq -2512(%rbp), %rax
  addq -2504(%rbp), %rax
  movq %rax, -2520(%rbp)
  movq -2520(%rbp), %rax
  movq -1232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2528(%rbp)
  movq -2528(%rbp), %rax
  movq -1160(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_185
main_block_198:
  movq $0, %rax
  movq -1240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2536(%rbp)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2544(%rbp)
  movq -2544(%rbp), %rax
  cmpq -2536(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2552(%rbp)
  movq -2552(%rbp), %rax
  movq -1248(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_32(%rip), %rax
  movq -1256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2560(%rbp)
  movq -1256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2568(%rbp)
  movq -2560(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_33
  jmp main_assert_fail_33
main_pr_nil_0_9383:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2576(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2576(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2584(%rbp)
  jmp main_pr_next_0_9383
main_pr_str_0_9383:
  movq -1392(%rbp), %rax
  addq $8, %rax
  movq %rax, -2592(%rbp)
  movq -2592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2600(%rbp)
  movq -1392(%rbp), %rax
  addq $24, %rax
  movq %rax, -2608(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2608(%rbp), %rsi
  movq -2600(%rbp), %rdx
  syscall
  movq %rax, -2616(%rbp)
  jmp main_pr_next_0_9383
main_pr_next_0_9383:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2624(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2624(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2632(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_1(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2640(%rbp)
  movq -2640(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2648(%rbp)
  movq -2648(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_886
  jmp main_pr_str_0_886
main_pr_nil_0_886:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2656(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2656(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2664(%rbp)
  jmp main_pr_next_0_886
main_pr_str_0_886:
  movq -2640(%rbp), %rax
  addq $8, %rax
  movq %rax, -2672(%rbp)
  movq -2672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2680(%rbp)
  movq -2640(%rbp), %rax
  addq $24, %rax
  movq %rax, -2688(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2688(%rbp), %rsi
  movq -2680(%rbp), %rdx
  syscall
  movq %rax, -2696(%rbp)
  jmp main_pr_next_0_886
main_pr_next_0_886:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2704(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2704(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2712(%rbp)
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
  movq %rax, -2720(%rbp)
  movq -2720(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_9
main_i2s_neg_1:
  movq $1, %rax
  movq -1480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1440(%rbp), %rax
  negq %rax
  movq %rax, -2728(%rbp)
  movq -2728(%rbp), %rax
  movq -1472(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_1
main_i2s_pos_1:
  movq $0, %rax
  movq -1480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1440(%rbp), %rax
  movq -1472(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_1
main_i2s_loop_1:
  movq -1472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2736(%rbp)
  movq -2736(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -2744(%rbp)
  movq -2736(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -2752(%rbp)
  movq -2752(%rbp), %rax
  movq -1472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2744(%rbp), %rax
  addq $48, %rax
  movq %rax, -2760(%rbp)
  movq -1464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2768(%rbp)
  movq -2768(%rbp), %rax
  subq $1, %rax
  movq %rax, -2776(%rbp)
  movq -2760(%rbp), %rax
  movq -2776(%rbp), %rdx
  movb %al, (%rdx)
  movq -2776(%rbp), %rax
  movq -1464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -2752(%rbp), %rax
  cmpq $1, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -2784(%rbp)
  movq -2784(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_1
  jmp main_i2s_sign_1
main_i2s_sign_1:
  movq -1480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2792(%rbp)
  movq -2792(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2800(%rbp)
  movq -2800(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_1
  jmp main_i2s_done_1
main_i2s_minus_1:
  movq -1464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2808(%rbp)
  movq -2808(%rbp), %rax
  subq $1, %rax
  movq %rax, -2816(%rbp)
  movq $45, %rax
  movq -2816(%rbp), %rdx
  movb %al, (%rdx)
  movq -2816(%rbp), %rax
  movq -1464(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_1
main_i2s_done_1:
  movq -1464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2824(%rbp)
  movq -1456(%rbp), %rax
  subq -2824(%rbp), %rax
  movq %rax, -2832(%rbp)
  movq -1448(%rbp), %rax
  addq $8, %rax
  movq %rax, -2840(%rbp)
  movq -2832(%rbp), %rax
  movq -2840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1448(%rbp), %rax
  addq $16, %rax
  movq %rax, -2848(%rbp)
  movq -2832(%rbp), %rax
  movq -2848(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1448(%rbp), %rax
  addq $24, %rax
  movq %rax, -2856(%rbp)
  movq -2832(%rbp), %rax
  addq $1, %rax
  movq %rax, -2864(%rbp)
  movq $184614912, %rax
  movq %rax, -2872(%rbp)
  movq -1448(%rbp), %rax
  addq $8, %rax
  movq %rax, -2880(%rbp)
  movq -2880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2888(%rbp)
  movq -1448(%rbp), %rax
  addq $24, %rax
  movq %rax, -2896(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2896(%rbp), %rsi
  movq -2888(%rbp), %rdx
  syscall
  movq %rax, -2904(%rbp)
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2912(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2912(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2920(%rbp)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2928(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2936(%rbp)
  movq -2936(%rbp), %rax
  addq -2928(%rbp), %rax
  movq %rax, -2944(%rbp)
  movq -2944(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2952(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2960(%rbp)
  movq -2960(%rbp), %rax
  addq -2952(%rbp), %rax
  movq %rax, -2968(%rbp)
  movq -2968(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_17
main_assert_pass_3:
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2976(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2984(%rbp)
  movq -2984(%rbp), %rax
  cmpq -2976(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2992(%rbp)
  movq -2992(%rbp), %rax
  movq -200(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_4(%rip), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3000(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3008(%rbp)
  movq -3000(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_5
  jmp main_assert_fail_5
main_assert_fail_3:
  movq -1560(%rbp), %rax
  addq $8, %rax
  movq %rax, -3016(%rbp)
  movq -3016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3024(%rbp)
  movq -1560(%rbp), %rax
  addq $24, %rax
  movq %rax, -3032(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3032(%rbp), %rsi
  movq -3024(%rbp), %rdx
  syscall
  movq %rax, -3040(%rbp)
  movq $50397203, %rax
  movq %rax, -3048(%rbp)
  jmp main_assert_pass_3
main_assert_pass_5:
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_6(%rip), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3056(%rbp)
  movq -3056(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3064(%rbp)
  movq -3064(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2777
  jmp main_pr_str_0_2777
main_assert_fail_5:
  movq -3008(%rbp), %rax
  addq $8, %rax
  movq %rax, -3072(%rbp)
  movq -3072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3080(%rbp)
  movq -3008(%rbp), %rax
  addq $24, %rax
  movq %rax, -3088(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3088(%rbp), %rsi
  movq -3080(%rbp), %rdx
  syscall
  movq %rax, -3096(%rbp)
  movq $50397203, %rax
  movq %rax, -3104(%rbp)
  jmp main_assert_pass_5
main_pr_nil_0_2777:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3112(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3112(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3120(%rbp)
  jmp main_pr_next_0_2777
main_pr_str_0_2777:
  movq -3056(%rbp), %rax
  addq $8, %rax
  movq %rax, -3128(%rbp)
  movq -3128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3136(%rbp)
  movq -3056(%rbp), %rax
  addq $24, %rax
  movq %rax, -3144(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3144(%rbp), %rsi
  movq -3136(%rbp), %rdx
  syscall
  movq %rax, -3152(%rbp)
  jmp main_pr_next_0_2777
main_pr_next_0_2777:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3160(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3168(%rbp)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3176(%rbp)
  movq -3176(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_36
main_i2s_neg_2:
  movq $1, %rax
  movq -1640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1600(%rbp), %rax
  negq %rax
  movq %rax, -3184(%rbp)
  movq -3184(%rbp), %rax
  movq -1632(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_2
main_i2s_pos_2:
  movq $0, %rax
  movq -1640(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1600(%rbp), %rax
  movq -1632(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_2
main_i2s_loop_2:
  movq -1632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3192(%rbp)
  movq -3192(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -3200(%rbp)
  movq -3192(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -3208(%rbp)
  movq -3208(%rbp), %rax
  movq -1632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3200(%rbp), %rax
  addq $48, %rax
  movq %rax, -3216(%rbp)
  movq -1624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3224(%rbp)
  movq -3224(%rbp), %rax
  subq $1, %rax
  movq %rax, -3232(%rbp)
  movq -3216(%rbp), %rax
  movq -3232(%rbp), %rdx
  movb %al, (%rdx)
  movq -3232(%rbp), %rax
  movq -1624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3208(%rbp), %rax
  cmpq $1, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -3240(%rbp)
  movq -3240(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_2
  jmp main_i2s_sign_2
main_i2s_sign_2:
  movq -1640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3248(%rbp)
  movq -3248(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3256(%rbp)
  movq -3256(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_2
  jmp main_i2s_done_2
main_i2s_minus_2:
  movq -1624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3264(%rbp)
  movq -3264(%rbp), %rax
  subq $1, %rax
  movq %rax, -3272(%rbp)
  movq $45, %rax
  movq -3272(%rbp), %rdx
  movb %al, (%rdx)
  movq -3272(%rbp), %rax
  movq -1624(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_2
main_i2s_done_2:
  movq -1624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3280(%rbp)
  movq -1616(%rbp), %rax
  subq -3280(%rbp), %rax
  movq %rax, -3288(%rbp)
  movq -1608(%rbp), %rax
  addq $8, %rax
  movq %rax, -3296(%rbp)
  movq -3288(%rbp), %rax
  movq -3296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1608(%rbp), %rax
  addq $16, %rax
  movq %rax, -3304(%rbp)
  movq -3288(%rbp), %rax
  movq -3304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1608(%rbp), %rax
  addq $24, %rax
  movq %rax, -3312(%rbp)
  movq -3288(%rbp), %rax
  addq $1, %rax
  movq %rax, -3320(%rbp)
  movq $184614912, %rax
  movq %rax, -3328(%rbp)
  movq -1608(%rbp), %rax
  addq $8, %rax
  movq %rax, -3336(%rbp)
  movq -3336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3344(%rbp)
  movq -1608(%rbp), %rax
  addq $24, %rax
  movq %rax, -3352(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3352(%rbp), %rsi
  movq -3344(%rbp), %rdx
  syscall
  movq %rax, -3360(%rbp)
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3368(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3368(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3376(%rbp)
  movq $0, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3384(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3392(%rbp)
  movq -3392(%rbp), %rax
  addq -3384(%rbp), %rax
  movq %rax, -3400(%rbp)
  movq -3400(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3408(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3416(%rbp)
  movq -3416(%rbp), %rax
  addq -3408(%rbp), %rax
  movq %rax, -3424(%rbp)
  movq -3424(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_44
main_assert_pass_8:
  movq $0, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3432(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3440(%rbp)
  movq -3440(%rbp), %rax
  cmpq -3432(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3448(%rbp)
  movq -3448(%rbp), %rax
  movq -360(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_9(%rip), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3456(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3464(%rbp)
  movq -3456(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_10
  jmp main_assert_fail_10
main_assert_fail_8:
  movq -1720(%rbp), %rax
  addq $8, %rax
  movq %rax, -3472(%rbp)
  movq -3472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3480(%rbp)
  movq -1720(%rbp), %rax
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
  jmp main_assert_pass_8
main_assert_pass_10:
  movq $0, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq $8, %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_11(%rip), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3512(%rbp)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3520(%rbp)
  movq -3512(%rbp), %rdi
  movq -3520(%rbp), %rsi
  call lm_rt_str_format
  mov -3528(%rbp), rax
  movq -3528(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3536(%rbp)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3544(%rbp)
  movq -3536(%rbp), %rdi
  movq -3544(%rbp), %rsi
  call lm_rt_str_format
  mov -3552(%rbp), rax
  movq -3552(%rbp), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3560(%rbp)
  movq -3560(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3568(%rbp)
  movq -3568(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3576(%rbp)
  movq -3576(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6915
  jmp main_pr_str_0_6915
main_assert_fail_10:
  movq -3464(%rbp), %rax
  addq $8, %rax
  movq %rax, -3584(%rbp)
  movq -3584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3592(%rbp)
  movq -3464(%rbp), %rax
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
  jmp main_assert_pass_10
main_pr_nil_0_6915:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3624(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3624(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3632(%rbp)
  jmp main_pr_next_0_6915
main_pr_str_0_6915:
  movq -3568(%rbp), %rax
  addq $8, %rax
  movq %rax, -3640(%rbp)
  movq -3640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3648(%rbp)
  movq -3568(%rbp), %rax
  addq $24, %rax
  movq %rax, -3656(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3656(%rbp), %rsi
  movq -3648(%rbp), %rdx
  syscall
  movq %rax, -3664(%rbp)
  jmp main_pr_next_0_6915
main_pr_next_0_6915:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3672(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3672(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3680(%rbp)
  movq $0, %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3688(%rbp)
  movq -3688(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_67
main_i2s_neg_3:
  movq $1, %rax
  movq -1800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1760(%rbp), %rax
  negq %rax
  movq %rax, -3696(%rbp)
  movq -3696(%rbp), %rax
  movq -1792(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_3
main_i2s_pos_3:
  movq $0, %rax
  movq -1800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1760(%rbp), %rax
  movq -1792(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_3
main_i2s_loop_3:
  movq -1792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3704(%rbp)
  movq -3704(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -3712(%rbp)
  movq -3704(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -3720(%rbp)
  movq -3720(%rbp), %rax
  movq -1792(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3712(%rbp), %rax
  addq $48, %rax
  movq %rax, -3728(%rbp)
  movq -1784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3736(%rbp)
  movq -3736(%rbp), %rax
  subq $1, %rax
  movq %rax, -3744(%rbp)
  movq -3728(%rbp), %rax
  movq -3744(%rbp), %rdx
  movb %al, (%rdx)
  movq -3744(%rbp), %rax
  movq -1784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -3720(%rbp), %rax
  cmpq $1, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -3752(%rbp)
  movq -3752(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_3
  jmp main_i2s_sign_3
main_i2s_sign_3:
  movq -1800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3760(%rbp)
  movq -3760(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3768(%rbp)
  movq -3768(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_3
  jmp main_i2s_done_3
main_i2s_minus_3:
  movq -1784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3776(%rbp)
  movq -3776(%rbp), %rax
  subq $1, %rax
  movq %rax, -3784(%rbp)
  movq $45, %rax
  movq -3784(%rbp), %rdx
  movb %al, (%rdx)
  movq -3784(%rbp), %rax
  movq -1784(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_3
main_i2s_done_3:
  movq -1784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3792(%rbp)
  movq -1776(%rbp), %rax
  subq -3792(%rbp), %rax
  movq %rax, -3800(%rbp)
  movq -1768(%rbp), %rax
  addq $8, %rax
  movq %rax, -3808(%rbp)
  movq -3800(%rbp), %rax
  movq -3808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1768(%rbp), %rax
  addq $16, %rax
  movq %rax, -3816(%rbp)
  movq -3800(%rbp), %rax
  movq -3816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1768(%rbp), %rax
  addq $24, %rax
  movq %rax, -3824(%rbp)
  movq -3800(%rbp), %rax
  addq $1, %rax
  movq %rax, -3832(%rbp)
  movq $184614912, %rax
  movq %rax, -3840(%rbp)
  movq -1768(%rbp), %rax
  addq $8, %rax
  movq %rax, -3848(%rbp)
  movq -3848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3856(%rbp)
  movq -1768(%rbp), %rax
  addq $24, %rax
  movq %rax, -3864(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3864(%rbp), %rsi
  movq -3856(%rbp), %rdx
  syscall
  movq %rax, -3872(%rbp)
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3880(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3880(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3888(%rbp)
  movq $0, %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq -472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3896(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3904(%rbp)
  movq -3904(%rbp), %rax
  addq -3896(%rbp), %rax
  movq %rax, -3912(%rbp)
  movq -3912(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3920(%rbp)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3928(%rbp)
  movq -3928(%rbp), %rax
  addq -3920(%rbp), %rax
  movq %rax, -3936(%rbp)
  movq -3936(%rbp), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_74
main_assert_pass_13:
  movq $0, %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq $18, %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3944(%rbp)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3952(%rbp)
  movq -3952(%rbp), %rax
  cmpq -3944(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3960(%rbp)
  movq -3960(%rbp), %rax
  movq -536(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_14(%rip), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3968(%rbp)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3976(%rbp)
  movq -3968(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_15
  jmp main_assert_fail_15
main_assert_fail_13:
  movq -1880(%rbp), %rax
  addq $8, %rax
  movq %rax, -3984(%rbp)
  movq -3984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3992(%rbp)
  movq -1880(%rbp), %rax
  addq $24, %rax
  movq %rax, -4000(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4000(%rbp), %rsi
  movq -3992(%rbp), %rdx
  syscall
  movq %rax, -4008(%rbp)
  movq $50397203, %rax
  movq %rax, -4016(%rbp)
  jmp main_assert_pass_13
main_assert_pass_15:
  movq $0, %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4024(%rbp)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4032(%rbp)
  movq -4032(%rbp), %rax
  addq -4024(%rbp), %rax
  movq %rax, -4040(%rbp)
  movq -4040(%rbp), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_16(%rip), %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4048(%rbp)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4056(%rbp)
  movq -4048(%rbp), %rdi
  movq -4056(%rbp), %rsi
  call lm_rt_str_format
  mov -4064(%rbp), rax
  movq -4064(%rbp), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4072(%rbp)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4080(%rbp)
  movq -4072(%rbp), %rdi
  movq -4080(%rbp), %rsi
  call lm_rt_str_format
  mov -4088(%rbp), rax
  movq -4088(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4096(%rbp)
  movq -4096(%rbp), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4104(%rbp)
  movq -4104(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4112(%rbp)
  movq -4112(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7793
  jmp main_pr_str_0_7793
main_assert_fail_15:
  movq -3976(%rbp), %rax
  addq $8, %rax
  movq %rax, -4120(%rbp)
  movq -4120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4128(%rbp)
  movq -3976(%rbp), %rax
  addq $24, %rax
  movq %rax, -4136(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4136(%rbp), %rsi
  movq -4128(%rbp), %rdx
  syscall
  movq %rax, -4144(%rbp)
  movq $50397203, %rax
  movq %rax, -4152(%rbp)
  jmp main_assert_pass_15
main_pr_nil_0_7793:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4160(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4168(%rbp)
  jmp main_pr_next_0_7793
main_pr_str_0_7793:
  movq -4104(%rbp), %rax
  addq $8, %rax
  movq %rax, -4176(%rbp)
  movq -4176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4184(%rbp)
  movq -4104(%rbp), %rax
  addq $24, %rax
  movq %rax, -4192(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4192(%rbp), %rsi
  movq -4184(%rbp), %rdx
  syscall
  movq %rax, -4200(%rbp)
  jmp main_pr_next_0_7793
main_pr_next_0_7793:
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
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4224(%rbp)
  movq -4224(%rbp), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_99
main_i2s_neg_4:
  movq $1, %rax
  movq -1984(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1944(%rbp), %rax
  negq %rax
  movq %rax, -4232(%rbp)
  movq -4232(%rbp), %rax
  movq -1976(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_4
main_i2s_pos_4:
  movq $0, %rax
  movq -1984(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1944(%rbp), %rax
  movq -1976(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_loop_4
main_i2s_loop_4:
  movq -1976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4240(%rbp)
  movq -4240(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -4248(%rbp)
  movq -4240(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -4256(%rbp)
  movq -4256(%rbp), %rax
  movq -1976(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4248(%rbp), %rax
  addq $48, %rax
  movq %rax, -4264(%rbp)
  movq -1968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4272(%rbp)
  movq -4272(%rbp), %rax
  subq $1, %rax
  movq %rax, -4280(%rbp)
  movq -4264(%rbp), %rax
  movq -4280(%rbp), %rdx
  movb %al, (%rdx)
  movq -4280(%rbp), %rax
  movq -1968(%rbp), %rdx
  movq %rax, (%rdx)
  movq -4256(%rbp), %rax
  cmpq $1, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -4288(%rbp)
  movq -4288(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_loop_4
  jmp main_i2s_sign_4
main_i2s_sign_4:
  movq -1984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4296(%rbp)
  movq -4296(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4304(%rbp)
  movq -4304(%rbp), %rax
  testq %rax, %rax
  jne main_i2s_minus_4
  jmp main_i2s_done_4
main_i2s_minus_4:
  movq -1968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4312(%rbp)
  movq -4312(%rbp), %rax
  subq $1, %rax
  movq %rax, -4320(%rbp)
  movq $45, %rax
  movq -4320(%rbp), %rdx
  movb %al, (%rdx)
  movq -4320(%rbp), %rax
  movq -1968(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_i2s_done_4
main_i2s_done_4:
  movq -1968(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4328(%rbp)
  movq -1960(%rbp), %rax
  subq -4328(%rbp), %rax
  movq %rax, -4336(%rbp)
  movq -1952(%rbp), %rax
  addq $8, %rax
  movq %rax, -4344(%rbp)
  movq -4336(%rbp), %rax
  movq -4344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1952(%rbp), %rax
  addq $16, %rax
  movq %rax, -4352(%rbp)
  movq -4336(%rbp), %rax
  movq -4352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1952(%rbp), %rax
  addq $24, %rax
  movq %rax, -4360(%rbp)
  movq -4336(%rbp), %rax
  addq $1, %rax
  movq %rax, -4368(%rbp)
  movq $184614912, %rax
  movq %rax, -4376(%rbp)
  movq -1952(%rbp), %rax
  addq $8, %rax
  movq %rax, -4384(%rbp)
  movq -4384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4392(%rbp)
  movq -1952(%rbp), %rax
  addq $24, %rax
  movq %rax, -4400(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4400(%rbp), %rsi
  movq -4392(%rbp), %rdx
  syscall
  movq %rax, -4408(%rbp)
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
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4432(%rbp)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4440(%rbp)
  movq -4440(%rbp), %rax
  addq -4432(%rbp), %rax
  movq %rax, -4448(%rbp)
  movq -4448(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -640(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4456(%rbp)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4464(%rbp)
  movq -4464(%rbp), %rax
  addq -4456(%rbp), %rax
  movq %rax, -4472(%rbp)
  movq -4472(%rbp), %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_109
main_assert_pass_18:
  movq $0, %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  movq $9, %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4480(%rbp)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4488(%rbp)
  movq -4488(%rbp), %rax
  cmpq -4480(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4496(%rbp)
  movq -4496(%rbp), %rax
  movq -752(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_19(%rip), %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq -752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4504(%rbp)
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4512(%rbp)
  movq -4504(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_20
  jmp main_assert_fail_20
main_assert_fail_18:
  movq -2064(%rbp), %rax
  addq $8, %rax
  movq %rax, -4520(%rbp)
  movq -4520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4528(%rbp)
  movq -2064(%rbp), %rax
  addq $24, %rax
  movq %rax, -4536(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4536(%rbp), %rsi
  movq -4528(%rbp), %rdx
  syscall
  movq %rax, -4544(%rbp)
  movq $50397203, %rax
  movq %rax, -4552(%rbp)
  jmp main_assert_pass_18
main_assert_pass_20:
  movq $0, %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_21(%rip), %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  movq -776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4560(%rbp)
  movq -4560(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4568(%rbp)
  movq -4568(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8335
  jmp main_pr_str_0_8335
main_assert_fail_20:
  movq -4512(%rbp), %rax
  addq $8, %rax
  movq %rax, -4576(%rbp)
  movq -4576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4584(%rbp)
  movq -4512(%rbp), %rax
  addq $24, %rax
  movq %rax, -4592(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4592(%rbp), %rsi
  movq -4584(%rbp), %rdx
  syscall
  movq %rax, -4600(%rbp)
  movq $50397203, %rax
  movq %rax, -4608(%rbp)
  jmp main_assert_pass_20
main_pr_nil_0_8335:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4616(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4616(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4624(%rbp)
  jmp main_pr_next_0_8335
main_pr_str_0_8335:
  movq -4560(%rbp), %rax
  addq $8, %rax
  movq %rax, -4632(%rbp)
  movq -4632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4640(%rbp)
  movq -4560(%rbp), %rax
  addq $24, %rax
  movq %rax, -4648(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4648(%rbp), %rsi
  movq -4640(%rbp), %rdx
  syscall
  movq %rax, -4656(%rbp)
  jmp main_pr_next_0_8335
main_pr_next_0_8335:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4664(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4664(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4672(%rbp)
  movq $0, %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4680(%rbp)
  movq -4680(%rbp), %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_128
main_pr_nil_0_5386:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4688(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4688(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4696(%rbp)
  jmp main_pr_next_0_5386
main_pr_str_0_5386:
  movq -2128(%rbp), %rax
  addq $8, %rax
  movq %rax, -4704(%rbp)
  movq -4704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4712(%rbp)
  movq -2128(%rbp), %rax
  addq $24, %rax
  movq %rax, -4720(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4720(%rbp), %rsi
  movq -4712(%rbp), %rdx
  syscall
  movq %rax, -4728(%rbp)
  jmp main_pr_next_0_5386
main_pr_next_0_5386:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4736(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4736(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4744(%rbp)
  movq $0, %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4752(%rbp)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4760(%rbp)
  movq -4760(%rbp), %rax
  addq -4752(%rbp), %rax
  movq %rax, -4768(%rbp)
  movq -4768(%rbp), %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  movq -888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4776(%rbp)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4784(%rbp)
  movq -4784(%rbp), %rax
  imulq -4776(%rbp), %rax
  movq %rax, -4792(%rbp)
  movq -4792(%rbp), %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4800(%rbp)
  movq -4800(%rbp), %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_141
main_pr_nil_0_492:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4808(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4808(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4816(%rbp)
  jmp main_pr_next_0_492
main_pr_str_0_492:
  movq -2272(%rbp), %rax
  addq $8, %rax
  movq %rax, -4824(%rbp)
  movq -4824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4832(%rbp)
  movq -2272(%rbp), %rax
  addq $24, %rax
  movq %rax, -4840(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4840(%rbp), %rsi
  movq -4832(%rbp), %rdx
  syscall
  movq %rax, -4848(%rbp)
  jmp main_pr_next_0_492
main_pr_next_0_492:
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
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4872(%rbp)
  movq -872(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4880(%rbp)
  movq -4880(%rbp), %rax
  addq -4872(%rbp), %rax
  movq %rax, -4888(%rbp)
  movq -4888(%rbp), %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1000(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4896(%rbp)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4904(%rbp)
  movq -4904(%rbp), %rax
  addq -4896(%rbp), %rax
  movq %rax, -4912(%rbp)
  movq -4912(%rbp), %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_158
main_assert_pass_25:
  movq $0, %rax
  movq -1048(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_167
main_assert_fail_25:
  movq -2352(%rbp), %rax
  addq $8, %rax
  movq %rax, -4920(%rbp)
  movq -4920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4928(%rbp)
  movq -2352(%rbp), %rax
  addq $24, %rax
  movq %rax, -4936(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4936(%rbp), %rsi
  movq -4928(%rbp), %rdx
  syscall
  movq %rax, -4944(%rbp)
  movq $50397203, %rax
  movq %rax, -4952(%rbp)
  jmp main_assert_pass_25
main_assert_pass_27:
  movq $0, %rax
  movq -1096(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4, %rax
  movq -1104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4960(%rbp)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4968(%rbp)
  movq -4968(%rbp), %rax
  cmpq -4960(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4976(%rbp)
  movq -4976(%rbp), %rax
  movq -1112(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_28(%rip), %rax
  movq -1120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4984(%rbp)
  movq -1120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4992(%rbp)
  movq -4984(%rbp), %rax
  testq %rax, %rax
  jne main_assert_pass_29
  jmp main_assert_fail_29
main_assert_fail_27:
  movq -2424(%rbp), %rax
  addq $8, %rax
  movq %rax, -5000(%rbp)
  movq -5000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5008(%rbp)
  movq -2424(%rbp), %rax
  addq $24, %rax
  movq %rax, -5016(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5016(%rbp), %rsi
  movq -5008(%rbp), %rdx
  syscall
  movq %rax, -5024(%rbp)
  movq $50397203, %rax
  movq %rax, -5032(%rbp)
  jmp main_assert_pass_27
main_assert_pass_29:
  movq $0, %rax
  movq -1128(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_30(%rip), %rax
  movq -1136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5040(%rbp)
  movq -5040(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5048(%rbp)
  movq -5048(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6649
  jmp main_pr_str_0_6649
main_assert_fail_29:
  movq -4992(%rbp), %rax
  addq $8, %rax
  movq %rax, -5056(%rbp)
  movq -5056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5064(%rbp)
  movq -4992(%rbp), %rax
  addq $24, %rax
  movq %rax, -5072(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5072(%rbp), %rsi
  movq -5064(%rbp), %rdx
  syscall
  movq %rax, -5080(%rbp)
  movq $50397203, %rax
  movq %rax, -5088(%rbp)
  jmp main_assert_pass_29
main_pr_nil_0_6649:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5096(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5096(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5104(%rbp)
  jmp main_pr_next_0_6649
main_pr_str_0_6649:
  movq -5040(%rbp), %rax
  addq $8, %rax
  movq %rax, -5112(%rbp)
  movq -5112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5120(%rbp)
  movq -5040(%rbp), %rax
  addq $24, %rax
  movq %rax, -5128(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5128(%rbp), %rsi
  movq -5120(%rbp), %rdx
  syscall
  movq %rax, -5136(%rbp)
  jmp main_pr_next_0_6649
main_pr_next_0_6649:
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
  movq -1144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -1168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5160(%rbp)
  movq -5160(%rbp), %rax
  movq -1160(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_185
main_pr_nil_0_1421:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5168(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5168(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5176(%rbp)
  jmp main_pr_next_0_1421
main_pr_str_0_1421:
  movq -2488(%rbp), %rax
  addq $8, %rax
  movq %rax, -5184(%rbp)
  movq -5184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5192(%rbp)
  movq -2488(%rbp), %rax
  addq $24, %rax
  movq %rax, -5200(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5200(%rbp), %rsi
  movq -5192(%rbp), %rdx
  syscall
  movq %rax, -5208(%rbp)
  jmp main_pr_next_0_1421
main_pr_next_0_1421:
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
  movq -1208(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -1216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5232(%rbp)
  movq -1152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5240(%rbp)
  movq -5240(%rbp), %rax
  addq -5232(%rbp), %rax
  movq %rax, -5248(%rbp)
  movq -5248(%rbp), %rax
  movq -1152(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_194
main_assert_pass_33:
  movq $0, %rax
  movq -1264(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_34(%rip), %rax
  movq -1272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5256(%rbp)
  movq -5256(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5264(%rbp)
  movq -5264(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2362
  jmp main_pr_str_0_2362
main_assert_fail_33:
  movq -2568(%rbp), %rax
  addq $8, %rax
  movq %rax, -5272(%rbp)
  movq -5272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5280(%rbp)
  movq -2568(%rbp), %rax
  addq $24, %rax
  movq %rax, -5288(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5288(%rbp), %rsi
  movq -5280(%rbp), %rdx
  syscall
  movq %rax, -5296(%rbp)
  movq $50397203, %rax
  movq %rax, -5304(%rbp)
  jmp main_assert_pass_33
main_pr_nil_0_2362:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5312(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5312(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5320(%rbp)
  jmp main_pr_next_0_2362
main_pr_str_0_2362:
  movq -5256(%rbp), %rax
  addq $8, %rax
  movq %rax, -5328(%rbp)
  movq -5328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5336(%rbp)
  movq -5256(%rbp), %rax
  addq $24, %rax
  movq %rax, -5344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5344(%rbp), %rsi
  movq -5336(%rbp), %rdx
  syscall
  movq %rax, -5352(%rbp)
  jmp main_pr_next_0_2362
main_pr_next_0_2362:
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
  movq -1280(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_35(%rip), %rax
  movq -1288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5376(%rbp)
  movq -5376(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5384(%rbp)
  movq -5384(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_27
  jmp main_pr_str_0_27
main_pr_nil_0_27:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5392(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5392(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5400(%rbp)
  jmp main_pr_next_0_27
main_pr_str_0_27:
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
  jmp main_pr_next_0_27
main_pr_next_0_27:
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
  movq -1296(%rbp), %rdx
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
  jne lm_enum_to_str_i2s_neg_5
  jmp lm_enum_to_str_i2s_pos_5
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
lm_enum_to_str_i2s_neg_5:
  movq $1, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  negq %rax
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_5
lm_enum_to_str_i2s_pos_5:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_5
lm_enum_to_str_i2s_loop_5:
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
  jne lm_enum_to_str_i2s_loop_5
  jmp lm_enum_to_str_i2s_sign_5
lm_enum_to_str_i2s_sign_5:
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
  jne lm_enum_to_str_i2s_minus_5
  jmp lm_enum_to_str_i2s_done_5
lm_enum_to_str_i2s_minus_5:
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
  jmp lm_enum_to_str_i2s_done_5
lm_enum_to_str_i2s_done_5:
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
  jne lm_enum_to_str_i2s_neg_6
  jmp lm_enum_to_str_i2s_pos_6
lm_enum_to_str_i2s_neg_6:
  movq $1, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  negq %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_6
lm_enum_to_str_i2s_pos_6:
  movq $0, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_6
lm_enum_to_str_i2s_loop_6:
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
  jne lm_enum_to_str_i2s_loop_6
  jmp lm_enum_to_str_i2s_sign_6
lm_enum_to_str_i2s_sign_6:
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
  jne lm_enum_to_str_i2s_minus_6
  jmp lm_enum_to_str_i2s_done_6
lm_enum_to_str_i2s_minus_6:
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
  jmp lm_enum_to_str_i2s_done_6
lm_enum_to_str_i2s_done_6:
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
  jne lm_list_to_str_i2s_neg_7
  jmp lm_list_to_str_i2s_pos_7
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
lm_list_to_str_i2s_neg_7:
  movq $1, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  negq %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_i2s_loop_7
lm_list_to_str_i2s_pos_7:
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_i2s_loop_7
lm_list_to_str_i2s_loop_7:
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
  jne lm_list_to_str_i2s_loop_7
  jmp lm_list_to_str_i2s_sign_7
lm_list_to_str_i2s_sign_7:
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
  jne lm_list_to_str_i2s_minus_7
  jmp lm_list_to_str_i2s_done_7
lm_list_to_str_i2s_minus_7:
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
  jmp lm_list_to_str_i2s_done_7
lm_list_to_str_i2s_done_7:
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

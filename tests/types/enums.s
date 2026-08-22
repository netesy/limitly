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
  .byte 69
  .byte 110
  .byte 117
  .byte 109
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
  .byte 69
  .byte 110
  .byte 117
  .byte 109
  .byte 32
  .byte 68
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
  .byte 32
  .byte 45
  .byte 45
  .byte 45
  .byte 0
.align 8
vname_Red:
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
  .byte 82
  .byte 101
  .byte 100
  .byte 0
.align 8
vname_Green:
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
  .byte 71
  .byte 114
  .byte 101
  .byte 101
  .byte 110
  .byte 0
.align 8
vname_Blue:
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
  .byte 66
  .byte 108
  .byte 117
  .byte 101
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
  .byte 108
  .byte 111
  .byte 114
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
  .byte 108
  .byte 111
  .byte 114
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
  .byte 108
  .byte 111
  .byte 114
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
  .byte 50
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
  .byte 65
  .byte 115
  .byte 115
  .byte 111
  .byte 99
  .byte 105
  .byte 97
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 86
  .byte 97
  .byte 108
  .byte 117
  .byte 101
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
  .byte 79
  .byte 112
  .byte 101
  .byte 114
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
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
  .byte 0
.align 8
vname_Success:
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
  .byte 83
  .byte 117
  .byte 99
  .byte 99
  .byte 101
  .byte 115
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
  .byte 83
  .byte 111
  .byte 109
  .byte 101
  .byte 116
  .byte 104
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 119
  .byte 101
  .byte 110
  .byte 116
  .byte 32
  .byte 119
  .byte 114
  .byte 111
  .byte 110
  .byte 103
  .byte 0
.align 8
vname_Error:
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
  .byte 69
  .byte 114
  .byte 114
  .byte 111
  .byte 114
  .byte 0
.align 8
vname_Pending:
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
  .byte 80
  .byte 101
  .byte 110
  .byte 100
  .byte 105
  .byte 110
  .byte 103
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
str_hdr_9:
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
str_hdr_10:
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
  .byte 51
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 51
  .byte 58
  .byte 32
  .byte 69
  .byte 110
  .byte 117
  .byte 109
  .byte 32
  .byte 80
  .byte 97
  .byte 116
  .byte 116
  .byte 101
  .byte 114
  .byte 110
  .byte 32
  .byte 77
  .byte 97
  .byte 116
  .byte 99
  .byte 104
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 68
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
  .byte 49
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
  .byte 68
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
  .byte 50
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
  .byte 68
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
  .byte 51
  .byte 58
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
  .byte 52
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
  .byte 86
  .byte 97
  .byte 114
  .byte 105
  .byte 97
  .byte 110
  .byte 116
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
  .byte 0
.align 8
vname_Active:
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
  .byte 65
  .byte 99
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 0
.align 8
vname_Archived:
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
  .byte 65
  .byte 114
  .byte 99
  .byte 104
  .byte 105
  .byte 118
  .byte 101
  .byte 100
  .byte 0
.align 8
vname_Inactive:
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
  .byte 73
  .byte 110
  .byte 97
  .byte 99
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 0
.align 8
vname_Deleted:
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
  .byte 68
  .byte 101
  .byte 108
  .byte 101
  .byte 116
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
  .byte 83
  .byte 116
  .byte 97
  .byte 116
  .byte 117
  .byte 115
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
  .byte 83
  .byte 116
  .byte 97
  .byte 116
  .byte 117
  .byte 115
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
  .byte 116
  .byte 97
  .byte 116
  .byte 117
  .byte 115
  .byte 32
  .byte 51
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
  .byte 116
  .byte 97
  .byte 116
  .byte 117
  .byte 115
  .byte 32
  .byte 52
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
  .byte 116
  .byte 97
  .byte 116
  .byte 117
  .byte 115
  .byte 32
  .byte 53
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
  .byte 53
  .byte 58
  .byte 32
  .byte 69
  .byte 110
  .byte 117
  .byte 109
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
  .byte 65
  .byte 99
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 49
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
  .byte 65
  .byte 99
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 50
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
  .byte 65
  .byte 99
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 51
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
  .byte 78
  .byte 117
  .byte 109
  .byte 101
  .byte 114
  .byte 105
  .byte 99
  .byte 32
  .byte 65
  .byte 115
  .byte 115
  .byte 111
  .byte 99
  .byte 105
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
vname_Low:
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
  .byte 76
  .byte 111
  .byte 119
  .byte 0
.align 8
vname_Medium:
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
  .byte 77
  .byte 101
  .byte 100
  .byte 105
  .byte 117
  .byte 109
  .byte 0
.align 8
vname_High:
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
  .byte 72
  .byte 105
  .byte 103
  .byte 104
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
  .byte 105
  .byte 111
  .byte 114
  .byte 105
  .byte 116
  .byte 121
  .byte 32
  .byte 49
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
  .byte 105
  .byte 111
  .byte 114
  .byte 105
  .byte 116
  .byte 121
  .byte 32
  .byte 50
  .byte 58
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
  .byte 105
  .byte 111
  .byte 114
  .byte 105
  .byte 116
  .byte 121
  .byte 32
  .byte 51
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
  .byte 55
  .byte 58
  .byte 32
  .byte 69
  .byte 110
  .byte 117
  .byte 109
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
  .byte 67
  .byte 111
  .byte 108
  .byte 111
  .byte 114
  .byte 32
  .byte 118
  .byte 97
  .byte 114
  .byte 105
  .byte 97
  .byte 98
  .byte 108
  .byte 101
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
  .byte 97
  .byte 116
  .byte 117
  .byte 115
  .byte 32
  .byte 118
  .byte 97
  .byte 114
  .byte 105
  .byte 97
  .byte 98
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
  .byte 56
  .byte 58
  .byte 32
  .byte 69
  .byte 110
  .byte 117
  .byte 109
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
str_hdr_33:
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
  .byte 67
  .byte 111
  .byte 108
  .byte 111
  .byte 114
  .byte 115
  .byte 32
  .byte 108
  .byte 105
  .byte 115
  .byte 116
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
  .byte 116
  .byte 97
  .byte 116
  .byte 117
  .byte 115
  .byte 101
  .byte 115
  .byte 32
  .byte 108
  .byte 105
  .byte 115
  .byte 116
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
  .byte 57
  .byte 58
  .byte 32
  .byte 69
  .byte 110
  .byte 117
  .byte 109
  .byte 32
  .byte 69
  .byte 120
  .byte 104
  .byte 97
  .byte 117
  .byte 115
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 110
  .byte 101
  .byte 115
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
  .byte 67
  .byte 111
  .byte 109
  .byte 112
  .byte 108
  .byte 101
  .byte 120
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
  .byte 105
  .byte 120
  .byte 101
  .byte 100
  .byte 32
  .byte 86
  .byte 97
  .byte 114
  .byte 105
  .byte 97
  .byte 110
  .byte 116
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
  .byte 0
.align 8
vname_Quit:
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
  .byte 81
  .byte 117
  .byte 105
  .byte 116
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
str_hdr_37:
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
vname_Write:
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
  .byte 114
  .byte 105
  .byte 116
  .byte 101
  .byte 0
.align 8
vname_ChangeColor:
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
  .byte 104
  .byte 97
  .byte 110
  .byte 103
  .byte 101
  .byte 67
  .byte 111
  .byte 108
  .byte 111
  .byte 114
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
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 69
  .byte 110
  .byte 117
  .byte 109
  .byte 32
  .byte 85
  .byte 115
  .byte 97
  .byte 103
  .byte 101
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
vname_Visible:
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
  .byte 86
  .byte 105
  .byte 115
  .byte 105
  .byte 98
  .byte 108
  .byte 101
  .byte 0
.align 8
vname_Hidden:
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
  .byte 72
  .byte 105
  .byte 100
  .byte 100
  .byte 101
  .byte 110
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
  .byte 57
  .byte 58
  .byte 32
  .byte 69
  .byte 110
  .byte 117
  .byte 109
  .byte 32
  .byte 65
  .byte 109
  .byte 98
  .byte 105
  .byte 103
  .byte 117
  .byte 105
  .byte 116
  .byte 121
  .byte 32
  .byte 72
  .byte 97
  .byte 110
  .byte 100
  .byte 108
  .byte 105
  .byte 110
  .byte 103
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
  .byte 83
  .byte 116
  .byte 97
  .byte 116
  .byte 101
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
  .byte 116
  .byte 97
  .byte 116
  .byte 117
  .byte 115
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
  .byte 117
  .byte 108
  .byte 116
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
  .byte 48
  .byte 58
  .byte 32
  .byte 87
  .byte 105
  .byte 108
  .byte 100
  .byte 99
  .byte 97
  .byte 114
  .byte 100
  .byte 115
  .byte 32
  .byte 105
  .byte 110
  .byte 32
  .byte 77
  .byte 97
  .byte 116
  .byte 99
  .byte 104
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 10
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 69
  .byte 110
  .byte 117
  .byte 109
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
str_hdr_45:
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
  .byte 83
  .byte 104
  .byte 97
  .byte 112
  .byte 101
  .byte 32
  .byte 105
  .byte 115
  .byte 32
  .byte 104
  .byte 105
  .byte 100
  .byte 100
  .byte 101
  .byte 110
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
  .byte 86
  .byte 105
  .byte 115
  .byte 105
  .byte 98
  .byte 108
  .byte 101
  .byte 32
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
  .byte 119
  .byte 105
  .byte 116
  .byte 104
  .byte 32
  .byte 37
  .byte 115
  .byte 120
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
  .byte 105
  .byte 115
  .byte 105
  .byte 98
  .byte 108
  .byte 101
  .byte 32
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
str_hdr_48:
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
  .byte 67
  .byte 104
  .byte 97
  .byte 110
  .byte 103
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 99
  .byte 111
  .byte 108
  .byte 111
  .byte 114
  .byte 32
  .byte 116
  .byte 111
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
str_hdr_49:
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
  .byte 87
  .byte 114
  .byte 105
  .byte 116
  .byte 105
  .byte 110
  .byte 103
  .byte 58
  .byte 32
  .byte 37
  .byte 115
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
  .byte 111
  .byte 118
  .byte 105
  .byte 110
  .byte 103
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
str_hdr_51:
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
  .byte 81
  .byte 117
  .byte 105
  .byte 116
  .byte 116
  .byte 105
  .byte 110
  .byte 103
  .byte 46
  .byte 46
  .byte 46
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
  .byte 84
  .byte 104
  .byte 101
  .byte 32
  .byte 99
  .byte 111
  .byte 108
  .byte 111
  .byte 114
  .byte 32
  .byte 98
  .byte 108
  .byte 117
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
  .byte 104
  .byte 101
  .byte 32
  .byte 99
  .byte 111
  .byte 108
  .byte 111
  .byte 114
  .byte 32
  .byte 103
  .byte 114
  .byte 101
  .byte 101
  .byte 110
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
  .byte 84
  .byte 104
  .byte 101
  .byte 32
  .byte 99
  .byte 111
  .byte 108
  .byte 111
  .byte 114
  .byte 32
  .byte 114
  .byte 101
  .byte 100
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
  .byte 78
  .byte 111
  .byte 116
  .byte 32
  .byte 97
  .byte 99
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 40
  .byte 37
  .byte 115
  .byte 41
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
  .byte 110
  .byte 110
  .byte 101
  .byte 99
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 97
  .byte 110
  .byte 100
  .byte 32
  .byte 97
  .byte 99
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
  subq $7352, %rsp
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
  jmp main_block_0
main_block_0:
  leaq str_hdr_0(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2032(%rbp)
  movq -2032(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2040(%rbp)
  movq -2040(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9383
  jmp main_pr_str_0_9383
main_pr_nil_0_9383:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2048(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2048(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2056(%rbp)
  jmp main_pr_next_0_9383
main_pr_str_0_9383:
  movq -2032(%rbp), %rax
  addq $8, %rax
  movq %rax, -2064(%rbp)
  movq -2064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2072(%rbp)
  movq -2032(%rbp), %rax
  addq $24, %rax
  movq %rax, -2080(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2080(%rbp), %rsi
  movq -2072(%rbp), %rdx
  syscall
  movq %rax, -2088(%rbp)
  jmp main_pr_next_0_9383
main_pr_next_0_9383:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2096(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2096(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2104(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_1(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2112(%rbp)
  movq -2112(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2120(%rbp)
  movq -2120(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_886
  jmp main_pr_str_0_886
main_pr_nil_0_886:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2128(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2128(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2136(%rbp)
  jmp main_pr_next_0_886
main_pr_str_0_886:
  movq -2112(%rbp), %rax
  addq $8, %rax
  movq %rax, -2144(%rbp)
  movq -2144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2152(%rbp)
  movq -2112(%rbp), %rax
  addq $24, %rax
  movq %rax, -2160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2160(%rbp), %rsi
  movq -2152(%rbp), %rdx
  syscall
  movq %rax, -2168(%rbp)
  jmp main_pr_next_0_886
main_pr_next_0_886:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2176(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2176(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2184(%rbp)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  movq $0, %rsi
  leaq vname_Red(%rip), %rdx
  call lm_enum_new
  mov -2192(%rbp), rax
  movq -2192(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2200(%rbp)
  movq -2200(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rdi
  movq $0, %rsi
  leaq vname_Green(%rip), %rdx
  call lm_enum_new
  mov -2208(%rbp), rax
  movq -2208(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2216(%rbp)
  movq -2216(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  movq $0, %rsi
  leaq vname_Blue(%rip), %rdx
  call lm_enum_new
  mov -2224(%rbp), rax
  movq -2224(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2232(%rbp)
  movq -2232(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_2(%rip), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2240(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2248(%rbp)
  movq -2240(%rbp), %rdi
  movq -2248(%rbp), %rsi
  call lm_rt_str_format
  mov -2256(%rbp), rax
  movq -2256(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2264(%rbp)
  movq -2264(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2272(%rbp)
  movq -2272(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2777
  jmp main_pr_str_0_2777
main_pr_nil_0_2777:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2280(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2280(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2288(%rbp)
  jmp main_pr_next_0_2777
main_pr_str_0_2777:
  movq -2264(%rbp), %rax
  addq $8, %rax
  movq %rax, -2296(%rbp)
  movq -2296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2304(%rbp)
  movq -2264(%rbp), %rax
  addq $24, %rax
  movq %rax, -2312(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2312(%rbp), %rsi
  movq -2304(%rbp), %rdx
  syscall
  movq %rax, -2320(%rbp)
  jmp main_pr_next_0_2777
main_pr_next_0_2777:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2328(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2328(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2336(%rbp)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_3(%rip), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2344(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2352(%rbp)
  movq -2344(%rbp), %rdi
  movq -2352(%rbp), %rsi
  call lm_rt_str_format
  mov -2360(%rbp), rax
  movq -2360(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2368(%rbp)
  movq -2368(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2376(%rbp)
  movq -2376(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6915
  jmp main_pr_str_0_6915
main_pr_nil_0_6915:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2384(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2384(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2392(%rbp)
  jmp main_pr_next_0_6915
main_pr_str_0_6915:
  movq -2368(%rbp), %rax
  addq $8, %rax
  movq %rax, -2400(%rbp)
  movq -2400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2408(%rbp)
  movq -2368(%rbp), %rax
  addq $24, %rax
  movq %rax, -2416(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2416(%rbp), %rsi
  movq -2408(%rbp), %rdx
  syscall
  movq %rax, -2424(%rbp)
  jmp main_pr_next_0_6915
main_pr_next_0_6915:
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
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_4(%rip), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2448(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2456(%rbp)
  movq -2448(%rbp), %rdi
  movq -2456(%rbp), %rsi
  call lm_rt_str_format
  mov -2464(%rbp), rax
  movq -2464(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2472(%rbp)
  movq -2472(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2480(%rbp)
  movq -2480(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7793
  jmp main_pr_str_0_7793
main_pr_nil_0_7793:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2488(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2488(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2496(%rbp)
  jmp main_pr_next_0_7793
main_pr_str_0_7793:
  movq -2472(%rbp), %rax
  addq $8, %rax
  movq %rax, -2504(%rbp)
  movq -2504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2512(%rbp)
  movq -2472(%rbp), %rax
  addq $24, %rax
  movq %rax, -2520(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2520(%rbp), %rsi
  movq -2512(%rbp), %rdx
  syscall
  movq %rax, -2528(%rbp)
  jmp main_pr_next_0_7793
main_pr_next_0_7793:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2536(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2536(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2544(%rbp)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_5(%rip), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2552(%rbp)
  movq -2552(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2560(%rbp)
  movq -2560(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8335
  jmp main_pr_str_0_8335
main_pr_nil_0_8335:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2568(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2568(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2576(%rbp)
  jmp main_pr_next_0_8335
main_pr_str_0_8335:
  movq -2552(%rbp), %rax
  addq $8, %rax
  movq %rax, -2584(%rbp)
  movq -2584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2592(%rbp)
  movq -2552(%rbp), %rax
  addq $24, %rax
  movq %rax, -2600(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2600(%rbp), %rsi
  movq -2592(%rbp), %rdx
  syscall
  movq %rax, -2608(%rbp)
  jmp main_pr_next_0_8335
main_pr_next_0_8335:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2616(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2616(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2624(%rbp)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_6(%rip), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2632(%rbp)
  movq $0, %rdi
  movq -2632(%rbp), %rsi
  leaq vname_Success(%rip), %rdx
  call lm_enum_new
  mov -2640(%rbp), rax
  movq -2640(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2648(%rbp)
  movq -2648(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_7(%rip), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2656(%rbp)
  movq $1, %rdi
  movq -2656(%rbp), %rsi
  leaq vname_Error(%rip), %rdx
  call lm_enum_new
  mov -2664(%rbp), rax
  movq -2664(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2672(%rbp)
  movq -2672(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  movq $0, %rsi
  leaq vname_Pending(%rip), %rdx
  call lm_enum_new
  mov -2680(%rbp), rax
  movq -2680(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2688(%rbp)
  movq -2688(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_8(%rip), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2696(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2704(%rbp)
  movq -2696(%rbp), %rdi
  movq -2704(%rbp), %rsi
  call lm_rt_str_format
  mov -2712(%rbp), rax
  movq -2712(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2720(%rbp)
  movq -2720(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2728(%rbp)
  movq -2728(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5386
  jmp main_pr_str_0_5386
main_pr_nil_0_5386:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2736(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2736(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2744(%rbp)
  jmp main_pr_next_0_5386
main_pr_str_0_5386:
  movq -2720(%rbp), %rax
  addq $8, %rax
  movq %rax, -2752(%rbp)
  movq -2752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2760(%rbp)
  movq -2720(%rbp), %rax
  addq $24, %rax
  movq %rax, -2768(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2768(%rbp), %rsi
  movq -2760(%rbp), %rdx
  syscall
  movq %rax, -2776(%rbp)
  jmp main_pr_next_0_5386
main_pr_next_0_5386:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2784(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2784(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2792(%rbp)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_9(%rip), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2800(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2808(%rbp)
  movq -2800(%rbp), %rdi
  movq -2808(%rbp), %rsi
  call lm_rt_str_format
  mov -2816(%rbp), rax
  movq -2816(%rbp), %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2824(%rbp)
  movq -2824(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2832(%rbp)
  movq -2832(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_492
  jmp main_pr_str_0_492
main_pr_nil_0_492:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2840(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2840(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2848(%rbp)
  jmp main_pr_next_0_492
main_pr_str_0_492:
  movq -2824(%rbp), %rax
  addq $8, %rax
  movq %rax, -2856(%rbp)
  movq -2856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2864(%rbp)
  movq -2824(%rbp), %rax
  addq $24, %rax
  movq %rax, -2872(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2872(%rbp), %rsi
  movq -2864(%rbp), %rdx
  syscall
  movq %rax, -2880(%rbp)
  jmp main_pr_next_0_492
main_pr_next_0_492:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2888(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2888(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -2896(%rbp)
  movq $0, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_10(%rip), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2904(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2912(%rbp)
  movq -2904(%rbp), %rdi
  movq -2912(%rbp), %rsi
  call lm_rt_str_format
  mov -2920(%rbp), rax
  movq -2920(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2928(%rbp)
  movq -2928(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -2936(%rbp)
  movq -2936(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6649
  jmp main_pr_str_0_6649
main_pr_nil_0_6649:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -2944(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2944(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -2952(%rbp)
  jmp main_pr_next_0_6649
main_pr_str_0_6649:
  movq -2928(%rbp), %rax
  addq $8, %rax
  movq %rax, -2960(%rbp)
  movq -2960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -2968(%rbp)
  movq -2928(%rbp), %rax
  addq $24, %rax
  movq %rax, -2976(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2976(%rbp), %rsi
  movq -2968(%rbp), %rdx
  syscall
  movq %rax, -2984(%rbp)
  jmp main_pr_next_0_6649
main_pr_next_0_6649:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -2992(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -2992(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3000(%rbp)
  movq $0, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_11(%rip), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3008(%rbp)
  movq -3008(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3016(%rbp)
  movq -3016(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1421
  jmp main_pr_str_0_1421
main_pr_nil_0_1421:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3024(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3024(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3032(%rbp)
  jmp main_pr_next_0_1421
main_pr_str_0_1421:
  movq -3008(%rbp), %rax
  addq $8, %rax
  movq %rax, -3040(%rbp)
  movq -3040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3048(%rbp)
  movq -3008(%rbp), %rax
  addq $24, %rax
  movq %rax, -3056(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3056(%rbp), %rsi
  movq -3048(%rbp), %rdx
  syscall
  movq %rax, -3064(%rbp)
  jmp main_pr_next_0_1421
main_pr_next_0_1421:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3072(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3072(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3080(%rbp)
  movq $0, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  movq $0, %rsi
  leaq vname_Red(%rip), %rdx
  call lm_enum_new
  mov -3088(%rbp), rax
  movq -3088(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3096(%rbp)
  movq -3096(%rbp), %rdi
  call describeColor
  mov -3104(%rbp), rax
  movq -3104(%rbp), %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3112(%rbp)
  movq -3112(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rdi
  movq $0, %rsi
  leaq vname_Green(%rip), %rdx
  call lm_enum_new
  mov -3120(%rbp), rax
  movq -3120(%rbp), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3128(%rbp)
  movq -3128(%rbp), %rdi
  call describeColor
  mov -3136(%rbp), rax
  movq -3136(%rbp), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3144(%rbp)
  movq -3144(%rbp), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  movq $0, %rsi
  leaq vname_Blue(%rip), %rdx
  call lm_enum_new
  mov -3152(%rbp), rax
  movq -3152(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3160(%rbp)
  movq -3160(%rbp), %rdi
  call describeColor
  mov -3168(%rbp), rax
  movq -3168(%rbp), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3176(%rbp)
  movq -3176(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_12(%rip), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3184(%rbp)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3192(%rbp)
  movq -3184(%rbp), %rdi
  movq -3192(%rbp), %rsi
  call lm_rt_str_format
  mov -3200(%rbp), rax
  movq -3200(%rbp), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3208(%rbp)
  movq -3208(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3216(%rbp)
  movq -3216(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2362
  jmp main_pr_str_0_2362
main_pr_nil_0_2362:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3224(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3224(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3232(%rbp)
  jmp main_pr_next_0_2362
main_pr_str_0_2362:
  movq -3208(%rbp), %rax
  addq $8, %rax
  movq %rax, -3240(%rbp)
  movq -3240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3248(%rbp)
  movq -3208(%rbp), %rax
  addq $24, %rax
  movq %rax, -3256(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3256(%rbp), %rsi
  movq -3248(%rbp), %rdx
  syscall
  movq %rax, -3264(%rbp)
  jmp main_pr_next_0_2362
main_pr_next_0_2362:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3272(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3272(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3280(%rbp)
  movq $0, %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_13(%rip), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3288(%rbp)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3296(%rbp)
  movq -3288(%rbp), %rdi
  movq -3296(%rbp), %rsi
  call lm_rt_str_format
  mov -3304(%rbp), rax
  movq -3304(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3312(%rbp)
  movq -3312(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3320(%rbp)
  movq -3320(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_27
  jmp main_pr_str_0_27
main_pr_nil_0_27:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3328(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3328(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3336(%rbp)
  jmp main_pr_next_0_27
main_pr_str_0_27:
  movq -3312(%rbp), %rax
  addq $8, %rax
  movq %rax, -3344(%rbp)
  movq -3344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3352(%rbp)
  movq -3312(%rbp), %rax
  addq $24, %rax
  movq %rax, -3360(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3360(%rbp), %rsi
  movq -3352(%rbp), %rdx
  syscall
  movq %rax, -3368(%rbp)
  jmp main_pr_next_0_27
main_pr_next_0_27:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3376(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3376(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3384(%rbp)
  movq $0, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_14(%rip), %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3392(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3400(%rbp)
  movq -3392(%rbp), %rdi
  movq -3400(%rbp), %rsi
  call lm_rt_str_format
  mov -3408(%rbp), rax
  movq -3408(%rbp), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3416(%rbp)
  movq -3416(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3424(%rbp)
  movq -3424(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8690
  jmp main_pr_str_0_8690
main_pr_nil_0_8690:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3432(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3432(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3440(%rbp)
  jmp main_pr_next_0_8690
main_pr_str_0_8690:
  movq -3416(%rbp), %rax
  addq $8, %rax
  movq %rax, -3448(%rbp)
  movq -3448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3456(%rbp)
  movq -3416(%rbp), %rax
  addq $24, %rax
  movq %rax, -3464(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3464(%rbp), %rsi
  movq -3456(%rbp), %rdx
  syscall
  movq %rax, -3472(%rbp)
  jmp main_pr_next_0_8690
main_pr_next_0_8690:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3480(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3480(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3488(%rbp)
  movq $0, %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_15(%rip), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3496(%rbp)
  movq -3496(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3504(%rbp)
  movq -3504(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_59
  jmp main_pr_str_0_59
main_pr_nil_0_59:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3512(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3512(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3520(%rbp)
  jmp main_pr_next_0_59
main_pr_str_0_59:
  movq -3496(%rbp), %rax
  addq $8, %rax
  movq %rax, -3528(%rbp)
  movq -3528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3536(%rbp)
  movq -3496(%rbp), %rax
  addq $24, %rax
  movq %rax, -3544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3544(%rbp), %rsi
  movq -3536(%rbp), %rdx
  syscall
  movq %rax, -3552(%rbp)
  jmp main_pr_next_0_59
main_pr_next_0_59:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3560(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3560(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3568(%rbp)
  movq $0, %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  movq $0, %rsi
  leaq vname_Active(%rip), %rdx
  call lm_enum_new
  mov -3576(%rbp), rax
  movq -3576(%rbp), %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3584(%rbp)
  movq -3584(%rbp), %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  movq $0, %rsi
  leaq vname_Pending(%rip), %rdx
  call lm_enum_new
  mov -3592(%rbp), rax
  movq -3592(%rbp), %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3600(%rbp)
  movq -3600(%rbp), %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rdi
  movq $0, %rsi
  leaq vname_Archived(%rip), %rdx
  call lm_enum_new
  mov -3608(%rbp), rax
  movq -3608(%rbp), %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3616(%rbp)
  movq -3616(%rbp), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rdi
  movq $0, %rsi
  leaq vname_Inactive(%rip), %rdx
  call lm_enum_new
  mov -3624(%rbp), rax
  movq -3624(%rbp), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3632(%rbp)
  movq -3632(%rbp), %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4, %rdi
  movq $0, %rsi
  leaq vname_Deleted(%rip), %rdx
  call lm_enum_new
  mov -3640(%rbp), rax
  movq -3640(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3648(%rbp)
  movq -3648(%rbp), %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_16(%rip), %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3656(%rbp)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3664(%rbp)
  movq -3656(%rbp), %rdi
  movq -3664(%rbp), %rsi
  call lm_rt_str_format
  mov -3672(%rbp), rax
  movq -3672(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -624(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3680(%rbp)
  movq -3680(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3688(%rbp)
  movq -3688(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7763
  jmp main_pr_str_0_7763
main_pr_nil_0_7763:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3696(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3696(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3704(%rbp)
  jmp main_pr_next_0_7763
main_pr_str_0_7763:
  movq -3680(%rbp), %rax
  addq $8, %rax
  movq %rax, -3712(%rbp)
  movq -3712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3720(%rbp)
  movq -3680(%rbp), %rax
  addq $24, %rax
  movq %rax, -3728(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3728(%rbp), %rsi
  movq -3720(%rbp), %rdx
  syscall
  movq %rax, -3736(%rbp)
  jmp main_pr_next_0_7763
main_pr_next_0_7763:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3744(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3744(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3752(%rbp)
  movq $0, %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_17(%rip), %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3760(%rbp)
  movq -568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3768(%rbp)
  movq -3760(%rbp), %rdi
  movq -3768(%rbp), %rsi
  call lm_rt_str_format
  mov -3776(%rbp), rax
  movq -3776(%rbp), %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3784(%rbp)
  movq -3784(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3792(%rbp)
  movq -3792(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3926
  jmp main_pr_str_0_3926
main_pr_nil_0_3926:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3800(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3800(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3808(%rbp)
  jmp main_pr_next_0_3926
main_pr_str_0_3926:
  movq -3784(%rbp), %rax
  addq $8, %rax
  movq %rax, -3816(%rbp)
  movq -3816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3824(%rbp)
  movq -3784(%rbp), %rax
  addq $24, %rax
  movq %rax, -3832(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3832(%rbp), %rsi
  movq -3824(%rbp), %rdx
  syscall
  movq %rax, -3840(%rbp)
  jmp main_pr_next_0_3926
main_pr_next_0_3926:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3848(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3848(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3856(%rbp)
  movq $0, %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_18(%rip), %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3864(%rbp)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3872(%rbp)
  movq -3864(%rbp), %rdi
  movq -3872(%rbp), %rsi
  call lm_rt_str_format
  mov -3880(%rbp), rax
  movq -3880(%rbp), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3888(%rbp)
  movq -3888(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -3896(%rbp)
  movq -3896(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_540
  jmp main_pr_str_0_540
main_pr_nil_0_540:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -3904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3904(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -3912(%rbp)
  jmp main_pr_next_0_540
main_pr_str_0_540:
  movq -3888(%rbp), %rax
  addq $8, %rax
  movq %rax, -3920(%rbp)
  movq -3920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3928(%rbp)
  movq -3888(%rbp), %rax
  addq $24, %rax
  movq %rax, -3936(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3936(%rbp), %rsi
  movq -3928(%rbp), %rdx
  syscall
  movq %rax, -3944(%rbp)
  jmp main_pr_next_0_540
main_pr_next_0_540:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -3952(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -3952(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -3960(%rbp)
  movq $0, %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_19(%rip), %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3968(%rbp)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3976(%rbp)
  movq -3968(%rbp), %rdi
  movq -3976(%rbp), %rsi
  call lm_rt_str_format
  mov -3984(%rbp), rax
  movq -3984(%rbp), %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -3992(%rbp)
  movq -3992(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4000(%rbp)
  movq -4000(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3426
  jmp main_pr_str_0_3426
main_pr_nil_0_3426:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4008(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4008(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4016(%rbp)
  jmp main_pr_next_0_3426
main_pr_str_0_3426:
  movq -3992(%rbp), %rax
  addq $8, %rax
  movq %rax, -4024(%rbp)
  movq -4024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4032(%rbp)
  movq -3992(%rbp), %rax
  addq $24, %rax
  movq %rax, -4040(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4040(%rbp), %rsi
  movq -4032(%rbp), %rdx
  syscall
  movq %rax, -4048(%rbp)
  jmp main_pr_next_0_3426
main_pr_next_0_3426:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4056(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4056(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4064(%rbp)
  movq $0, %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_20(%rip), %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4072(%rbp)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4080(%rbp)
  movq -4072(%rbp), %rdi
  movq -4080(%rbp), %rsi
  call lm_rt_str_format
  mov -4088(%rbp), rax
  movq -4088(%rbp), %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4096(%rbp)
  movq -4096(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4104(%rbp)
  movq -4104(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9172
  jmp main_pr_str_0_9172
main_pr_nil_0_9172:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4112(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4112(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4120(%rbp)
  jmp main_pr_next_0_9172
main_pr_str_0_9172:
  movq -4096(%rbp), %rax
  addq $8, %rax
  movq %rax, -4128(%rbp)
  movq -4128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4136(%rbp)
  movq -4096(%rbp), %rax
  addq $24, %rax
  movq %rax, -4144(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4144(%rbp), %rsi
  movq -4136(%rbp), %rdx
  syscall
  movq %rax, -4152(%rbp)
  jmp main_pr_next_0_9172
main_pr_next_0_9172:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4160(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4168(%rbp)
  movq $0, %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_21(%rip), %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4176(%rbp)
  movq -4176(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4184(%rbp)
  movq -4184(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5736
  jmp main_pr_str_0_5736
main_pr_nil_0_5736:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4192(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4192(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4200(%rbp)
  jmp main_pr_next_0_5736
main_pr_str_0_5736:
  movq -4176(%rbp), %rax
  addq $8, %rax
  movq %rax, -4208(%rbp)
  movq -4208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4216(%rbp)
  movq -4176(%rbp), %rax
  addq $24, %rax
  movq %rax, -4224(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4224(%rbp), %rsi
  movq -4216(%rbp), %rdx
  syscall
  movq %rax, -4232(%rbp)
  jmp main_pr_next_0_5736
main_pr_next_0_5736:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4240(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4240(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4248(%rbp)
  movq $0, %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  movq $0, %rsi
  leaq vname_Active(%rip), %rdx
  call lm_enum_new
  mov -4256(%rbp), rax
  movq -4256(%rbp), %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  movq -760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4264(%rbp)
  movq -4264(%rbp), %rdi
  call isActive
  mov -4272(%rbp), rax
  movq -4272(%rbp), %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4280(%rbp)
  movq -4280(%rbp), %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rdi
  movq $0, %rsi
  leaq vname_Inactive(%rip), %rdx
  call lm_enum_new
  mov -4288(%rbp), rax
  movq -4288(%rbp), %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4296(%rbp)
  movq -4296(%rbp), %rdi
  call isActive
  mov -4304(%rbp), rax
  movq -4304(%rbp), %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4312(%rbp)
  movq -4312(%rbp), %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  movq $0, %rsi
  leaq vname_Pending(%rip), %rdx
  call lm_enum_new
  mov -4320(%rbp), rax
  movq -4320(%rbp), %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4328(%rbp)
  movq -4328(%rbp), %rdi
  call isActive
  mov -4336(%rbp), rax
  movq -4336(%rbp), %rax
  movq -816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4344(%rbp)
  movq -4344(%rbp), %rax
  movq -824(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_22(%rip), %rax
  movq -840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4352(%rbp)
  movq -776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4360(%rbp)
  movq -4360(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -4368(%rbp)
  movq -4368(%rbp), %rax
  testq %rax, %rax
  jne main_b2s_t_1
  jmp main_b2s_f_1
main_b2s_t_1:
  movq str_true(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -4376(%rbp)
  jmp main_b2s_d_1
main_b2s_f_1:
  movq str_false(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -4376(%rbp)
  jmp main_b2s_d_1
main_b2s_d_1:
  movq -4352(%rbp), %rdi
  movq -4376(%rbp), %rsi
  call lm_rt_str_format
  mov -4384(%rbp), rax
  movq -4384(%rbp), %rax
  movq -832(%rbp), %rdx
  movq %rax, (%rdx)
  movq -832(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4392(%rbp)
  movq -4392(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4400(%rbp)
  movq -4400(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5211
  jmp main_pr_str_0_5211
main_pr_nil_0_5211:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4408(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4408(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4416(%rbp)
  jmp main_pr_next_0_5211
main_pr_str_0_5211:
  movq -4392(%rbp), %rax
  addq $8, %rax
  movq %rax, -4424(%rbp)
  movq -4424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4432(%rbp)
  movq -4392(%rbp), %rax
  addq $24, %rax
  movq %rax, -4440(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4440(%rbp), %rsi
  movq -4432(%rbp), %rdx
  syscall
  movq %rax, -4448(%rbp)
  jmp main_pr_next_0_5211
main_pr_next_0_5211:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4456(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4456(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4464(%rbp)
  movq $0, %rax
  movq -848(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_23(%rip), %rax
  movq -864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4472(%rbp)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4480(%rbp)
  movq -4480(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -4488(%rbp)
  movq -4488(%rbp), %rax
  testq %rax, %rax
  jne main_b2s_t_2
  jmp main_b2s_f_2
main_b2s_t_2:
  movq str_true(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -4496(%rbp)
  jmp main_b2s_d_2
main_b2s_f_2:
  movq str_false(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -4496(%rbp)
  jmp main_b2s_d_2
main_b2s_d_2:
  movq -4472(%rbp), %rdi
  movq -4496(%rbp), %rsi
  call lm_rt_str_format
  mov -4504(%rbp), rax
  movq -4504(%rbp), %rax
  movq -856(%rbp), %rdx
  movq %rax, (%rdx)
  movq -856(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4512(%rbp)
  movq -4512(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4520(%rbp)
  movq -4520(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5368
  jmp main_pr_str_0_5368
main_pr_nil_0_5368:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4528(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4528(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4536(%rbp)
  jmp main_pr_next_0_5368
main_pr_str_0_5368:
  movq -4512(%rbp), %rax
  addq $8, %rax
  movq %rax, -4544(%rbp)
  movq -4544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4552(%rbp)
  movq -4512(%rbp), %rax
  addq $24, %rax
  movq %rax, -4560(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4560(%rbp), %rsi
  movq -4552(%rbp), %rdx
  syscall
  movq %rax, -4568(%rbp)
  jmp main_pr_next_0_5368
main_pr_next_0_5368:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4576(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4576(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4584(%rbp)
  movq $0, %rax
  movq -872(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_24(%rip), %rax
  movq -888(%rbp), %rdx
  movq %rax, (%rdx)
  movq -888(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4592(%rbp)
  movq -824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4600(%rbp)
  movq -4600(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -4608(%rbp)
  movq -4608(%rbp), %rax
  testq %rax, %rax
  jne main_b2s_t_3
  jmp main_b2s_f_3
main_b2s_t_3:
  movq str_true(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -4616(%rbp)
  jmp main_b2s_d_3
main_b2s_f_3:
  movq str_false(%rip), %rax
  pushq %rax
  popq %rax
  movq %rax, -4616(%rbp)
  jmp main_b2s_d_3
main_b2s_d_3:
  movq -4592(%rbp), %rdi
  movq -4616(%rbp), %rsi
  call lm_rt_str_format
  mov -4624(%rbp), rax
  movq -4624(%rbp), %rax
  movq -880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4632(%rbp)
  movq -4632(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4640(%rbp)
  movq -4640(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2567
  jmp main_pr_str_0_2567
main_pr_nil_0_2567:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4648(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4648(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4656(%rbp)
  jmp main_pr_next_0_2567
main_pr_str_0_2567:
  movq -4632(%rbp), %rax
  addq $8, %rax
  movq %rax, -4664(%rbp)
  movq -4664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4672(%rbp)
  movq -4632(%rbp), %rax
  addq $24, %rax
  movq %rax, -4680(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4680(%rbp), %rsi
  movq -4672(%rbp), %rdx
  syscall
  movq %rax, -4688(%rbp)
  jmp main_pr_next_0_2567
main_pr_next_0_2567:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4696(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4696(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4704(%rbp)
  movq $0, %rax
  movq -896(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_25(%rip), %rax
  movq -904(%rbp), %rdx
  movq %rax, (%rdx)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4712(%rbp)
  movq -4712(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4720(%rbp)
  movq -4720(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6429
  jmp main_pr_str_0_6429
main_pr_nil_0_6429:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4728(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4728(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4736(%rbp)
  jmp main_pr_next_0_6429
main_pr_str_0_6429:
  movq -4712(%rbp), %rax
  addq $8, %rax
  movq %rax, -4744(%rbp)
  movq -4744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4752(%rbp)
  movq -4712(%rbp), %rax
  addq $24, %rax
  movq %rax, -4760(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4760(%rbp), %rsi
  movq -4752(%rbp), %rdx
  syscall
  movq %rax, -4768(%rbp)
  jmp main_pr_next_0_6429
main_pr_next_0_6429:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4776(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4776(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4784(%rbp)
  movq $0, %rax
  movq -912(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -920(%rbp), %rdx
  movq %rax, (%rdx)
  movq -920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4792(%rbp)
  movq $0, %rdi
  movq -4792(%rbp), %rsi
  leaq vname_Low(%rip), %rdx
  call lm_enum_new
  mov -4800(%rbp), rax
  movq -4800(%rbp), %rax
  movq -928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4808(%rbp)
  movq -4808(%rbp), %rax
  movq -944(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -952(%rbp), %rdx
  movq %rax, (%rdx)
  movq -952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4816(%rbp)
  movq $1, %rdi
  movq -4816(%rbp), %rsi
  leaq vname_Medium(%rip), %rdx
  call lm_enum_new
  mov -4824(%rbp), rax
  movq -4824(%rbp), %rax
  movq -960(%rbp), %rdx
  movq %rax, (%rdx)
  movq -960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4832(%rbp)
  movq -4832(%rbp), %rax
  movq -976(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -984(%rbp), %rdx
  movq %rax, (%rdx)
  movq -984(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4840(%rbp)
  movq $2, %rdi
  movq -4840(%rbp), %rsi
  leaq vname_High(%rip), %rdx
  call lm_enum_new
  mov -4848(%rbp), rax
  movq -4848(%rbp), %rax
  movq -992(%rbp), %rdx
  movq %rax, (%rdx)
  movq -992(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4856(%rbp)
  movq -4856(%rbp), %rax
  movq -1008(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_26(%rip), %rax
  movq -1024(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4864(%rbp)
  movq -944(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4872(%rbp)
  movq -4864(%rbp), %rdi
  movq -4872(%rbp), %rsi
  call lm_rt_str_format
  mov -4880(%rbp), rax
  movq -4880(%rbp), %rax
  movq -1016(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1016(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4888(%rbp)
  movq -4888(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -4896(%rbp)
  movq -4896(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5782
  jmp main_pr_str_0_5782
main_pr_nil_0_5782:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -4904(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4904(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -4912(%rbp)
  jmp main_pr_next_0_5782
main_pr_str_0_5782:
  movq -4888(%rbp), %rax
  addq $8, %rax
  movq %rax, -4920(%rbp)
  movq -4920(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4928(%rbp)
  movq -4888(%rbp), %rax
  addq $24, %rax
  movq %rax, -4936(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4936(%rbp), %rsi
  movq -4928(%rbp), %rdx
  syscall
  movq %rax, -4944(%rbp)
  jmp main_pr_next_0_5782
main_pr_next_0_5782:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -4952(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -4952(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -4960(%rbp)
  movq $0, %rax
  movq -1032(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_27(%rip), %rax
  movq -1048(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1048(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4968(%rbp)
  movq -976(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4976(%rbp)
  movq -4968(%rbp), %rdi
  movq -4976(%rbp), %rsi
  call lm_rt_str_format
  mov -4984(%rbp), rax
  movq -4984(%rbp), %rax
  movq -1040(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1040(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -4992(%rbp)
  movq -4992(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5000(%rbp)
  movq -5000(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1530
  jmp main_pr_str_0_1530
main_pr_nil_0_1530:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5008(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5008(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5016(%rbp)
  jmp main_pr_next_0_1530
main_pr_str_0_1530:
  movq -4992(%rbp), %rax
  addq $8, %rax
  movq %rax, -5024(%rbp)
  movq -5024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5032(%rbp)
  movq -4992(%rbp), %rax
  addq $24, %rax
  movq %rax, -5040(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5040(%rbp), %rsi
  movq -5032(%rbp), %rdx
  syscall
  movq %rax, -5048(%rbp)
  jmp main_pr_next_0_1530
main_pr_next_0_1530:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5056(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5056(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5064(%rbp)
  movq $0, %rax
  movq -1056(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_28(%rip), %rax
  movq -1072(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1072(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5072(%rbp)
  movq -1008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5080(%rbp)
  movq -5072(%rbp), %rdi
  movq -5080(%rbp), %rsi
  call lm_rt_str_format
  mov -5088(%rbp), rax
  movq -5088(%rbp), %rax
  movq -1064(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1064(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5096(%rbp)
  movq -5096(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5104(%rbp)
  movq -5104(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2862
  jmp main_pr_str_0_2862
main_pr_nil_0_2862:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5112(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5112(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5120(%rbp)
  jmp main_pr_next_0_2862
main_pr_str_0_2862:
  movq -5096(%rbp), %rax
  addq $8, %rax
  movq %rax, -5128(%rbp)
  movq -5128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5136(%rbp)
  movq -5096(%rbp), %rax
  addq $24, %rax
  movq %rax, -5144(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5144(%rbp), %rsi
  movq -5136(%rbp), %rdx
  syscall
  movq %rax, -5152(%rbp)
  jmp main_pr_next_0_2862
main_pr_next_0_2862:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5160(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5160(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5168(%rbp)
  movq $0, %rax
  movq -1080(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_29(%rip), %rax
  movq -1088(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5176(%rbp)
  movq -5176(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5184(%rbp)
  movq -5184(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5123
  jmp main_pr_str_0_5123
main_pr_nil_0_5123:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5192(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5192(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5200(%rbp)
  jmp main_pr_next_0_5123
main_pr_str_0_5123:
  movq -5176(%rbp), %rax
  addq $8, %rax
  movq %rax, -5208(%rbp)
  movq -5208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5216(%rbp)
  movq -5176(%rbp), %rax
  addq $24, %rax
  movq %rax, -5224(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5224(%rbp), %rsi
  movq -5216(%rbp), %rdx
  syscall
  movq %rax, -5232(%rbp)
  jmp main_pr_next_0_5123
main_pr_next_0_5123:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5240(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5240(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5248(%rbp)
  movq $0, %rax
  movq -1096(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  movq $0, %rsi
  leaq vname_Red(%rip), %rdx
  call lm_enum_new
  mov -5256(%rbp), rax
  movq -5256(%rbp), %rax
  movq -1104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5264(%rbp)
  movq -5264(%rbp), %rax
  movq -1112(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  movq $0, %rsi
  leaq vname_Active(%rip), %rdx
  call lm_enum_new
  mov -5272(%rbp), rax
  movq -5272(%rbp), %rax
  movq -1120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5280(%rbp)
  movq -5280(%rbp), %rax
  movq -1128(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_30(%rip), %rax
  movq -1144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5288(%rbp)
  movq -1112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5296(%rbp)
  movq -5288(%rbp), %rdi
  movq -5296(%rbp), %rsi
  call lm_rt_str_format
  mov -5304(%rbp), rax
  movq -5304(%rbp), %rax
  movq -1136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5312(%rbp)
  movq -5312(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5320(%rbp)
  movq -5320(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_4067
  jmp main_pr_str_0_4067
main_pr_nil_0_4067:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5328(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5328(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5336(%rbp)
  jmp main_pr_next_0_4067
main_pr_str_0_4067:
  movq -5312(%rbp), %rax
  addq $8, %rax
  movq %rax, -5344(%rbp)
  movq -5344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5352(%rbp)
  movq -5312(%rbp), %rax
  addq $24, %rax
  movq %rax, -5360(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5360(%rbp), %rsi
  movq -5352(%rbp), %rdx
  syscall
  movq %rax, -5368(%rbp)
  jmp main_pr_next_0_4067
main_pr_next_0_4067:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5376(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5376(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5384(%rbp)
  movq $0, %rax
  movq -1152(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_31(%rip), %rax
  movq -1168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5392(%rbp)
  movq -1128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5400(%rbp)
  movq -5392(%rbp), %rdi
  movq -5400(%rbp), %rsi
  call lm_rt_str_format
  mov -5408(%rbp), rax
  movq -5408(%rbp), %rax
  movq -1160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5416(%rbp)
  movq -5416(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5424(%rbp)
  movq -5424(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3135
  jmp main_pr_str_0_3135
main_pr_nil_0_3135:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5432(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5432(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5440(%rbp)
  jmp main_pr_next_0_3135
main_pr_str_0_3135:
  movq -5416(%rbp), %rax
  addq $8, %rax
  movq %rax, -5448(%rbp)
  movq -5448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5456(%rbp)
  movq -5416(%rbp), %rax
  addq $24, %rax
  movq %rax, -5464(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5464(%rbp), %rsi
  movq -5456(%rbp), %rdx
  syscall
  movq %rax, -5472(%rbp)
  jmp main_pr_next_0_3135
main_pr_next_0_3135:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5480(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5480(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5488(%rbp)
  movq $0, %rax
  movq -1176(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_32(%rip), %rax
  movq -1184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5496(%rbp)
  movq -5496(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5504(%rbp)
  movq -5504(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3929
  jmp main_pr_str_0_3929
main_pr_nil_0_3929:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5512(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5512(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5520(%rbp)
  jmp main_pr_next_0_3929
main_pr_str_0_3929:
  movq -5496(%rbp), %rax
  addq $8, %rax
  movq %rax, -5528(%rbp)
  movq -5528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5536(%rbp)
  movq -5496(%rbp), %rax
  addq $24, %rax
  movq %rax, -5544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5544(%rbp), %rsi
  movq -5536(%rbp), %rdx
  syscall
  movq %rax, -5552(%rbp)
  jmp main_pr_next_0_3929
main_pr_next_0_3929:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5560(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5560(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5568(%rbp)
  movq $0, %rax
  movq -1192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -5576(%rbp), rax
  movq -5576(%rbp), %rax
  movq -1200(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  movq $0, %rsi
  leaq vname_Red(%rip), %rdx
  call lm_enum_new
  mov -5584(%rbp), rax
  movq -5584(%rbp), %rax
  movq -1208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5592(%rbp)
  movq -1208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5600(%rbp)
  movq -5592(%rbp), %rdi
  movq -5600(%rbp), %rsi
  call lm_list_append
  mov -5608(%rbp), rax
  movq $1, %rdi
  movq $0, %rsi
  leaq vname_Green(%rip), %rdx
  call lm_enum_new
  mov -5616(%rbp), rax
  movq -5616(%rbp), %rax
  movq -1224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5624(%rbp)
  movq -1224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5632(%rbp)
  movq -5624(%rbp), %rdi
  movq -5632(%rbp), %rsi
  call lm_list_append
  mov -5640(%rbp), rax
  movq $2, %rdi
  movq $0, %rsi
  leaq vname_Blue(%rip), %rdx
  call lm_enum_new
  mov -5648(%rbp), rax
  movq -5648(%rbp), %rax
  movq -1240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5656(%rbp)
  movq -1240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5664(%rbp)
  movq -5656(%rbp), %rdi
  movq -5664(%rbp), %rsi
  call lm_list_append
  mov -5672(%rbp), rax
  movq $0, %rdi
  movq $0, %rsi
  leaq vname_Red(%rip), %rdx
  call lm_enum_new
  mov -5680(%rbp), rax
  movq -5680(%rbp), %rax
  movq -1256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5688(%rbp)
  movq -1256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5696(%rbp)
  movq -5688(%rbp), %rdi
  movq -5696(%rbp), %rsi
  call lm_list_append
  mov -5704(%rbp), rax
  movq $1, %rdi
  movq $0, %rsi
  leaq vname_Green(%rip), %rdx
  call lm_enum_new
  mov -5712(%rbp), rax
  movq -5712(%rbp), %rax
  movq -1272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5720(%rbp)
  movq -1272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5728(%rbp)
  movq -5720(%rbp), %rdi
  movq -5728(%rbp), %rsi
  call lm_list_append
  mov -5736(%rbp), rax
  movq -1200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5744(%rbp)
  movq -5744(%rbp), %rax
  movq -1288(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  call lm_list_new
  mov -5752(%rbp), rax
  movq -5752(%rbp), %rax
  movq -1296(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  movq $0, %rsi
  leaq vname_Active(%rip), %rdx
  call lm_enum_new
  mov -5760(%rbp), rax
  movq -5760(%rbp), %rax
  movq -1304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5768(%rbp)
  movq -1304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5776(%rbp)
  movq -5768(%rbp), %rdi
  movq -5776(%rbp), %rsi
  call lm_list_append
  mov -5784(%rbp), rax
  movq $1, %rdi
  movq $0, %rsi
  leaq vname_Inactive(%rip), %rdx
  call lm_enum_new
  mov -5792(%rbp), rax
  movq -5792(%rbp), %rax
  movq -1320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5800(%rbp)
  movq -1320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5808(%rbp)
  movq -5800(%rbp), %rdi
  movq -5808(%rbp), %rsi
  call lm_list_append
  mov -5816(%rbp), rax
  movq $2, %rdi
  movq $0, %rsi
  leaq vname_Pending(%rip), %rdx
  call lm_enum_new
  mov -5824(%rbp), rax
  movq -5824(%rbp), %rax
  movq -1336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5832(%rbp)
  movq -1336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5840(%rbp)
  movq -5832(%rbp), %rdi
  movq -5840(%rbp), %rsi
  call lm_list_append
  mov -5848(%rbp), rax
  movq $0, %rdi
  movq $0, %rsi
  leaq vname_Active(%rip), %rdx
  call lm_enum_new
  mov -5856(%rbp), rax
  movq -5856(%rbp), %rax
  movq -1352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5864(%rbp)
  movq -1352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5872(%rbp)
  movq -5864(%rbp), %rdi
  movq -5872(%rbp), %rsi
  call lm_list_append
  mov -5880(%rbp), rax
  movq -1296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5888(%rbp)
  movq -5888(%rbp), %rax
  movq -1368(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_33(%rip), %rax
  movq -1384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5896(%rbp)
  movq -1288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5904(%rbp)
  movq -5896(%rbp), %rdi
  movq -5904(%rbp), %rsi
  call lm_rt_str_format
  mov -5912(%rbp), rax
  movq -5912(%rbp), %rax
  movq -1376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5920(%rbp)
  movq -5920(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -5928(%rbp)
  movq -5928(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9802
  jmp main_pr_str_0_9802
main_pr_nil_0_9802:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -5936(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5936(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -5944(%rbp)
  jmp main_pr_next_0_9802
main_pr_str_0_9802:
  movq -5920(%rbp), %rax
  addq $8, %rax
  movq %rax, -5952(%rbp)
  movq -5952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -5960(%rbp)
  movq -5920(%rbp), %rax
  addq $24, %rax
  movq %rax, -5968(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5968(%rbp), %rsi
  movq -5960(%rbp), %rdx
  syscall
  movq %rax, -5976(%rbp)
  jmp main_pr_next_0_9802
main_pr_next_0_9802:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -5984(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -5984(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -5992(%rbp)
  movq $0, %rax
  movq -1392(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_34(%rip), %rax
  movq -1408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6000(%rbp)
  movq -1368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6008(%rbp)
  movq -6000(%rbp), %rdi
  movq -6008(%rbp), %rsi
  call lm_rt_str_format
  mov -6016(%rbp), rax
  movq -6016(%rbp), %rax
  movq -1400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6024(%rbp)
  movq -6024(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6032(%rbp)
  movq -6032(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_4022
  jmp main_pr_str_0_4022
main_pr_nil_0_4022:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6040(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6040(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6048(%rbp)
  jmp main_pr_next_0_4022
main_pr_str_0_4022:
  movq -6024(%rbp), %rax
  addq $8, %rax
  movq %rax, -6056(%rbp)
  movq -6056(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6064(%rbp)
  movq -6024(%rbp), %rax
  addq $24, %rax
  movq %rax, -6072(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6072(%rbp), %rsi
  movq -6064(%rbp), %rdx
  syscall
  movq %rax, -6080(%rbp)
  jmp main_pr_next_0_4022
main_pr_next_0_4022:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6088(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6088(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6096(%rbp)
  movq $0, %rax
  movq -1416(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_35(%rip), %rax
  movq -1424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6104(%rbp)
  movq -6104(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6112(%rbp)
  movq -6112(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3058
  jmp main_pr_str_0_3058
main_pr_nil_0_3058:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6120(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6120(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6128(%rbp)
  jmp main_pr_next_0_3058
main_pr_str_0_3058:
  movq -6104(%rbp), %rax
  addq $8, %rax
  movq %rax, -6136(%rbp)
  movq -6136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6144(%rbp)
  movq -6104(%rbp), %rax
  addq $24, %rax
  movq %rax, -6152(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6152(%rbp), %rsi
  movq -6144(%rbp), %rdx
  syscall
  movq %rax, -6160(%rbp)
  jmp main_pr_next_0_3058
main_pr_next_0_3058:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6168(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6168(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6176(%rbp)
  movq $0, %rax
  movq -1432(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_36(%rip), %rax
  movq -1440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6184(%rbp)
  movq -6184(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6192(%rbp)
  movq -6192(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_3069
  jmp main_pr_str_0_3069
main_pr_nil_0_3069:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6200(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6200(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6208(%rbp)
  jmp main_pr_next_0_3069
main_pr_str_0_3069:
  movq -6184(%rbp), %rax
  addq $8, %rax
  movq %rax, -6216(%rbp)
  movq -6216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6224(%rbp)
  movq -6184(%rbp), %rax
  addq $24, %rax
  movq %rax, -6232(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6232(%rbp), %rsi
  movq -6224(%rbp), %rdx
  syscall
  movq %rax, -6240(%rbp)
  jmp main_pr_next_0_3069
main_pr_next_0_3069:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6248(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6248(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6256(%rbp)
  movq $0, %rax
  movq -1448(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  movq $0, %rsi
  leaq vname_Quit(%rip), %rdx
  call lm_enum_new
  mov -6264(%rbp), rax
  movq -6264(%rbp), %rax
  movq -1456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6272(%rbp)
  movq -6272(%rbp), %rdi
  call processMessage
  mov -6280(%rbp), rax
  movq -6280(%rbp), %rax
  movq -1464(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -1472(%rbp), %rdx
  movq %rax, (%rdx)
  movq $20, %rax
  movq -1480(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  call lm_tuple_new
  mov -6288(%rbp), rax
  movq -6288(%rbp), %rax
  movq -1496(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6296(%rbp)
  movq -1504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6304(%rbp)
  movq -1472(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6312(%rbp)
  movq -6296(%rbp), %rdi
  movq -6304(%rbp), %rsi
  movq -6312(%rbp), %rdx
  call lm_tuple_set
  mov -6320(%rbp), rax
  movq $1, %rax
  movq -1512(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6328(%rbp)
  movq -1512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6336(%rbp)
  movq -1480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6344(%rbp)
  movq -6328(%rbp), %rdi
  movq -6336(%rbp), %rsi
  movq -6344(%rbp), %rdx
  call lm_tuple_set
  mov -6352(%rbp), rax
  movq -1496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6360(%rbp)
  movq $1, %rdi
  movq -6360(%rbp), %rsi
  leaq vname_Move(%rip), %rdx
  call lm_enum_new
  mov -6368(%rbp), rax
  movq -6368(%rbp), %rax
  movq -1488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6376(%rbp)
  movq -6376(%rbp), %rdi
  call processMessage
  mov -6384(%rbp), rax
  movq -6384(%rbp), %rax
  movq -1520(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_37(%rip), %rax
  movq -1528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6392(%rbp)
  movq $2, %rdi
  movq -6392(%rbp), %rsi
  leaq vname_Write(%rip), %rdx
  call lm_enum_new
  mov -6400(%rbp), rax
  movq -6400(%rbp), %rax
  movq -1536(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1536(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6408(%rbp)
  movq -6408(%rbp), %rdi
  call processMessage
  mov -6416(%rbp), rax
  movq -6416(%rbp), %rax
  movq -1552(%rbp), %rdx
  movq %rax, (%rdx)
  movq $255, %rax
  movq -1560(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1568(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1576(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rdi
  call lm_tuple_new
  mov -6424(%rbp), rax
  movq -6424(%rbp), %rax
  movq -1592(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -1600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6432(%rbp)
  movq -1600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6440(%rbp)
  movq -1560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6448(%rbp)
  movq -6432(%rbp), %rdi
  movq -6440(%rbp), %rsi
  movq -6448(%rbp), %rdx
  call lm_tuple_set
  mov -6456(%rbp), rax
  movq $1, %rax
  movq -1608(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6464(%rbp)
  movq -1608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6472(%rbp)
  movq -1568(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6480(%rbp)
  movq -6464(%rbp), %rdi
  movq -6472(%rbp), %rsi
  movq -6480(%rbp), %rdx
  call lm_tuple_set
  mov -6488(%rbp), rax
  movq $2, %rax
  movq -1616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6496(%rbp)
  movq -1616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6504(%rbp)
  movq -1576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6512(%rbp)
  movq -6496(%rbp), %rdi
  movq -6504(%rbp), %rsi
  movq -6512(%rbp), %rdx
  call lm_tuple_set
  mov -6520(%rbp), rax
  movq -1592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6528(%rbp)
  movq $3, %rdi
  movq -6528(%rbp), %rsi
  leaq vname_ChangeColor(%rip), %rdx
  call lm_enum_new
  mov -6536(%rbp), rax
  movq -6536(%rbp), %rax
  movq -1584(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6544(%rbp)
  movq -6544(%rbp), %rdi
  call processMessage
  mov -6552(%rbp), rax
  movq -6552(%rbp), %rax
  movq -1624(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_38(%rip), %rax
  movq -1632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6560(%rbp)
  movq -6560(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6568(%rbp)
  movq -6568(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8167
  jmp main_pr_str_0_8167
main_pr_nil_0_8167:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6576(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6576(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6584(%rbp)
  jmp main_pr_next_0_8167
main_pr_str_0_8167:
  movq -6560(%rbp), %rax
  addq $8, %rax
  movq %rax, -6592(%rbp)
  movq -6592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6600(%rbp)
  movq -6560(%rbp), %rax
  addq $24, %rax
  movq %rax, -6608(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6608(%rbp), %rsi
  movq -6600(%rbp), %rdx
  syscall
  movq %rax, -6616(%rbp)
  jmp main_pr_next_0_8167
main_pr_next_0_8167:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6624(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6624(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6632(%rbp)
  movq $0, %rax
  movq -1640(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4617315517961601024, %rax
  movq -1648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6640(%rbp)
  movq $0, %rdi
  movq -6640(%rbp), %rsi
  leaq vname_Circle(%rip), %rdx
  call lm_enum_new
  mov -6648(%rbp), rax
  movq -6648(%rbp), %rax
  movq -1656(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1656(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6656(%rbp)
  movq $0, %rdi
  movq -6656(%rbp), %rsi
  leaq vname_Visible(%rip), %rdx
  call lm_enum_new
  mov -6664(%rbp), rax
  movq -6664(%rbp), %rax
  movq -1672(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6672(%rbp)
  movq -6672(%rbp), %rax
  movq -1688(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rdi
  movq $0, %rsi
  leaq vname_Hidden(%rip), %rdx
  call lm_enum_new
  mov -6680(%rbp), rax
  movq -6680(%rbp), %rax
  movq -1696(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6688(%rbp)
  movq -6688(%rbp), %rax
  movq -1704(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6696(%rbp)
  movq -6696(%rbp), %rdi
  call describeShapeStatus
  mov -6704(%rbp), rax
  movq -6704(%rbp), %rax
  movq -1712(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_39(%rip), %rax
  movq -1728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6712(%rbp)
  movq -6712(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6720(%rbp)
  movq -6720(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1393
  jmp main_pr_str_0_1393
main_pr_nil_0_1393:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6728(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6728(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6736(%rbp)
  jmp main_pr_next_0_1393
main_pr_str_0_1393:
  movq -6712(%rbp), %rax
  addq $8, %rax
  movq %rax, -6744(%rbp)
  movq -6744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6752(%rbp)
  movq -6712(%rbp), %rax
  addq $24, %rax
  movq %rax, -6760(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6760(%rbp), %rsi
  movq -6752(%rbp), %rdx
  syscall
  movq %rax, -6768(%rbp)
  jmp main_pr_next_0_1393
main_pr_next_0_1393:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6776(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6776(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6784(%rbp)
  movq $0, %rax
  movq -1736(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  movq $0, %rsi
  leaq vname_Pending(%rip), %rdx
  call lm_enum_new
  mov -6792(%rbp), rax
  movq -6792(%rbp), %rax
  movq -1744(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6800(%rbp)
  movq -6800(%rbp), %rax
  movq -1752(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  movq $0, %rsi
  leaq vname_Pending(%rip), %rdx
  call lm_enum_new
  mov -6808(%rbp), rax
  movq -6808(%rbp), %rax
  movq -1760(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1760(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6816(%rbp)
  movq -6816(%rbp), %rax
  movq -1768(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rdi
  movq $0, %rsi
  leaq vname_Pending(%rip), %rdx
  call lm_enum_new
  mov -6824(%rbp), rax
  movq -6824(%rbp), %rax
  movq -1776(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1776(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6832(%rbp)
  movq -6832(%rbp), %rax
  movq -1784(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_40(%rip), %rax
  movq -1800(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6840(%rbp)
  movq -1752(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6848(%rbp)
  movq -6840(%rbp), %rdi
  movq -6848(%rbp), %rsi
  call lm_rt_str_format
  mov -6856(%rbp), rax
  movq -6856(%rbp), %rax
  movq -1792(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6864(%rbp)
  movq -6864(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6872(%rbp)
  movq -6872(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8456
  jmp main_pr_str_0_8456
main_pr_nil_0_8456:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6880(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6880(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6888(%rbp)
  jmp main_pr_next_0_8456
main_pr_str_0_8456:
  movq -6864(%rbp), %rax
  addq $8, %rax
  movq %rax, -6896(%rbp)
  movq -6896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6904(%rbp)
  movq -6864(%rbp), %rax
  addq $24, %rax
  movq %rax, -6912(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6912(%rbp), %rsi
  movq -6904(%rbp), %rdx
  syscall
  movq %rax, -6920(%rbp)
  jmp main_pr_next_0_8456
main_pr_next_0_8456:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -6928(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6928(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -6936(%rbp)
  movq $0, %rax
  movq -1808(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_41(%rip), %rax
  movq -1824(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1824(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6944(%rbp)
  movq -1768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6952(%rbp)
  movq -6944(%rbp), %rdi
  movq -6952(%rbp), %rsi
  call lm_rt_str_format
  mov -6960(%rbp), rax
  movq -6960(%rbp), %rax
  movq -1816(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1816(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -6968(%rbp)
  movq -6968(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -6976(%rbp)
  movq -6976(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5011
  jmp main_pr_str_0_5011
main_pr_nil_0_5011:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -6984(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -6984(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -6992(%rbp)
  jmp main_pr_next_0_5011
main_pr_str_0_5011:
  movq -6968(%rbp), %rax
  addq $8, %rax
  movq %rax, -7000(%rbp)
  movq -7000(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7008(%rbp)
  movq -6968(%rbp), %rax
  addq $24, %rax
  movq %rax, -7016(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7016(%rbp), %rsi
  movq -7008(%rbp), %rdx
  syscall
  movq %rax, -7024(%rbp)
  jmp main_pr_next_0_5011
main_pr_next_0_5011:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7032(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7032(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7040(%rbp)
  movq $0, %rax
  movq -1832(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_42(%rip), %rax
  movq -1848(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7048(%rbp)
  movq -1784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7056(%rbp)
  movq -7048(%rbp), %rdi
  movq -7056(%rbp), %rsi
  call lm_rt_str_format
  mov -7064(%rbp), rax
  movq -7064(%rbp), %rax
  movq -1840(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1840(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7072(%rbp)
  movq -7072(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7080(%rbp)
  movq -7080(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8042
  jmp main_pr_str_0_8042
main_pr_nil_0_8042:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7088(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7088(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7096(%rbp)
  jmp main_pr_next_0_8042
main_pr_str_0_8042:
  movq -7072(%rbp), %rax
  addq $8, %rax
  movq %rax, -7104(%rbp)
  movq -7104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7112(%rbp)
  movq -7072(%rbp), %rax
  addq $24, %rax
  movq %rax, -7120(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7120(%rbp), %rsi
  movq -7112(%rbp), %rdx
  syscall
  movq %rax, -7128(%rbp)
  jmp main_pr_next_0_8042
main_pr_next_0_8042:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7136(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7136(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7144(%rbp)
  movq $0, %rax
  movq -1856(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_43(%rip), %rax
  movq -1864(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1864(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7152(%rbp)
  movq -7152(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7160(%rbp)
  movq -7160(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6229
  jmp main_pr_str_0_6229
main_pr_nil_0_6229:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7168(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7168(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7176(%rbp)
  jmp main_pr_next_0_6229
main_pr_str_0_6229:
  movq -7152(%rbp), %rax
  addq $8, %rax
  movq %rax, -7184(%rbp)
  movq -7184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7192(%rbp)
  movq -7152(%rbp), %rax
  addq $24, %rax
  movq %rax, -7200(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7200(%rbp), %rsi
  movq -7192(%rbp), %rdx
  syscall
  movq %rax, -7208(%rbp)
  jmp main_pr_next_0_6229
main_pr_next_0_6229:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7216(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7216(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7224(%rbp)
  movq $0, %rax
  movq -1872(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rdi
  movq $0, %rsi
  leaq vname_Active(%rip), %rdx
  call lm_enum_new
  mov -7232(%rbp), rax
  movq -7232(%rbp), %rax
  movq -1880(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1880(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7240(%rbp)
  movq -7240(%rbp), %rdi
  call checkConnectivity
  mov -7248(%rbp), rax
  movq -7248(%rbp), %rax
  movq -1888(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rdi
  movq $0, %rsi
  leaq vname_Inactive(%rip), %rdx
  call lm_enum_new
  mov -7256(%rbp), rax
  movq -7256(%rbp), %rax
  movq -1896(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1896(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7264(%rbp)
  movq -7264(%rbp), %rdi
  call checkConnectivity
  mov -7272(%rbp), rax
  movq -7272(%rbp), %rax
  movq -1904(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4, %rdi
  movq $0, %rsi
  leaq vname_Deleted(%rip), %rdx
  call lm_enum_new
  mov -7280(%rbp), rax
  movq -7280(%rbp), %rax
  movq -1912(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1912(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7288(%rbp)
  movq -7288(%rbp), %rdi
  call checkConnectivity
  mov -7296(%rbp), rax
  movq -7296(%rbp), %rax
  movq -1920(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_44(%rip), %rax
  movq -1928(%rbp), %rdx
  movq %rax, (%rdx)
  movq -1928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7304(%rbp)
  movq -7304(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -7312(%rbp)
  movq -7312(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7373
  jmp main_pr_str_0_7373
main_pr_nil_0_7373:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -7320(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7320(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -7328(%rbp)
  jmp main_pr_next_0_7373
main_pr_str_0_7373:
  movq -7304(%rbp), %rax
  addq $8, %rax
  movq %rax, -7336(%rbp)
  movq -7336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -7344(%rbp)
  movq -7304(%rbp), %rax
  addq $24, %rax
  movq %rax, -7352(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7352(%rbp), %rsi
  movq -7344(%rbp), %rdx
  syscall
  movq %rax, -7360(%rbp)
  jmp main_pr_next_0_7373
main_pr_next_0_7373:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -7368(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -7368(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -7376(%rbp)
  movq $0, %rax
  movq -1936(%rbp), %rdx
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

.globl describeShapeStatus
describeShapeStatus:
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
  subq $1096, %rsp
  movq %rdi, -48(%rbp)
describeShapeStatus_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp describeShapeStatus_block_0
describeShapeStatus_block_0:
  jmp describeShapeStatus_block_1
describeShapeStatus_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rdi
  call lm_enum_tag
  mov -432(%rbp), rax
  movq -432(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  cmpq -440(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  testq %rax, %rax
  jne describeShapeStatus_block_5
  jmp describeShapeStatus_block_7
describeShapeStatus_block_5:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rdi
  call lm_enum_payload
  mov -480(%rbp), rax
  movq -480(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  jmp describeShapeStatus_block_15
describeShapeStatus_block_7:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rdi
  call lm_enum_tag
  mov -496(%rbp), rax
  movq -496(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  cmpq -504(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  movq -320(%rbp), %rdx
  movl %eax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rax
  testq %rax, %rax
  jne describeShapeStatus_block_11
  jmp describeShapeStatus_block_50
describeShapeStatus_block_11:
  jmp describeShapeStatus_block_12
describeShapeStatus_block_12:
  leaq str_hdr_45(%rip), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -536(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  testq %rax, %rax
  jne describeShapeStatus_pr_nil_0_4421
  jmp describeShapeStatus_pr_str_0_4421
describeShapeStatus_block_15:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rdi
  call lm_enum_payload
  mov -560(%rbp), rax
  movq -560(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp describeShapeStatus_block_17
describeShapeStatus_block_17:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rdi
  call lm_enum_tag
  mov -576(%rbp), rax
  movq -576(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  cmpq -584(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  movq -120(%rbp), %rdx
  movl %eax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  testq %rax, %rax
  jne describeShapeStatus_block_21
  jmp describeShapeStatus_block_23
describeShapeStatus_block_21:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rdi
  call lm_enum_payload
  mov -624(%rbp), rax
  movq -624(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  jmp describeShapeStatus_block_44
describeShapeStatus_block_23:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -632(%rbp), %rdi
  call lm_enum_tag
  mov -640(%rbp), rax
  movq -640(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  cmpq -648(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  movq -184(%rbp), %rdx
  movl %eax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -672(%rbp), %rax
  testq %rax, %rax
  jne describeShapeStatus_block_27
  jmp describeShapeStatus_block_49
describeShapeStatus_block_27:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rdi
  call lm_enum_payload
  mov -688(%rbp), rax
  movq -688(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -696(%rbp), %rdi
  movq -704(%rbp), %rsi
  call lm_tuple_get
  mov -712(%rbp), rax
  movq -712(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -720(%rbp), %rdi
  movq -728(%rbp), %rsi
  call lm_tuple_get
  mov -736(%rbp), rax
  movq -736(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp describeShapeStatus_block_33
describeShapeStatus_block_33:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rdi
  call lm_enum_payload
  mov -752(%rbp), rax
  movq -752(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -760(%rbp), %rdi
  movq -768(%rbp), %rsi
  call lm_tuple_get
  mov -776(%rbp), rax
  movq -776(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -784(%rbp), %rdi
  movq -792(%rbp), %rsi
  call lm_tuple_get
  mov -800(%rbp), rax
  movq -800(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_46(%rip), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -808(%rbp), %rdi
  movq -816(%rbp), %rsi
  call lm_rt_str_format
  mov -824(%rbp), rax
  movq -824(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -832(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -832(%rbp), %rdi
  movq -840(%rbp), %rsi
  call lm_rt_str_format
  mov -848(%rbp), rax
  movq -848(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -856(%rbp)
  movq -856(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -864(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -872(%rbp)
  movq -872(%rbp), %rax
  testq %rax, %rax
  jne describeShapeStatus_pr_nil_0_4919
  jmp describeShapeStatus_pr_str_0_4919
describeShapeStatus_block_44:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -880(%rbp), %rdi
  call lm_enum_payload
  mov -888(%rbp), rax
  movq -888(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_47(%rip), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -896(%rbp), %rdi
  movq -904(%rbp), %rsi
  call lm_rt_str_format
  mov -912(%rbp), rax
  movq -912(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -920(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -928(%rbp)
  movq -928(%rbp), %rax
  testq %rax, %rax
  jne describeShapeStatus_pr_nil_0_3784
  jmp describeShapeStatus_pr_str_0_3784
describeShapeStatus_block_49:
  jmp describeShapeStatus_block_50
describeShapeStatus_block_50:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -936(%rbp), %rax
  jmp describeShapeStatus_epilogue
describeShapeStatus_pr_nil_0_4421:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -944(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -944(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -952(%rbp)
  jmp describeShapeStatus_pr_next_0_4421
describeShapeStatus_pr_str_0_4421:
  movq -536(%rbp), %rax
  addq $8, %rax
  movq %rax, -960(%rbp)
  movq -960(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -536(%rbp), %rax
  addq $24, %rax
  movq %rax, -976(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -976(%rbp), %rsi
  movq -968(%rbp), %rdx
  syscall
  movq %rax, -984(%rbp)
  jmp describeShapeStatus_pr_next_0_4421
describeShapeStatus_pr_next_0_4421:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -992(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -992(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1000(%rbp)
  movq $0, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  jmp describeShapeStatus_block_50
describeShapeStatus_pr_nil_0_4919:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1008(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1008(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1016(%rbp)
  jmp describeShapeStatus_pr_next_0_4919
describeShapeStatus_pr_str_0_4919:
  movq -864(%rbp), %rax
  addq $8, %rax
  movq %rax, -1024(%rbp)
  movq -1024(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1032(%rbp)
  movq -864(%rbp), %rax
  addq $24, %rax
  movq %rax, -1040(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1040(%rbp), %rsi
  movq -1032(%rbp), %rdx
  syscall
  movq %rax, -1048(%rbp)
  jmp describeShapeStatus_pr_next_0_4919
describeShapeStatus_pr_next_0_4919:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1056(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1056(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1064(%rbp)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  jmp describeShapeStatus_block_49
describeShapeStatus_pr_nil_0_3784:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1072(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1072(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1080(%rbp)
  jmp describeShapeStatus_pr_next_0_3784
describeShapeStatus_pr_str_0_3784:
  movq -920(%rbp), %rax
  addq $8, %rax
  movq %rax, -1088(%rbp)
  movq -1088(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -920(%rbp), %rax
  addq $24, %rax
  movq %rax, -1104(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1104(%rbp), %rsi
  movq -1096(%rbp), %rdx
  syscall
  movq %rax, -1112(%rbp)
  jmp describeShapeStatus_pr_next_0_3784
describeShapeStatus_pr_next_0_3784:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1120(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1120(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1128(%rbp)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  jmp describeShapeStatus_block_49
describeShapeStatus_epilogue:
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
.Lfunc_end_describeShapeStatus:

.globl processMessage
processMessage:
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
  subq $1544, %rsp
  movq %rdi, -48(%rbp)
processMessage_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp processMessage_block_0
processMessage_block_0:
  jmp processMessage_block_1
processMessage_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rdi
  call lm_enum_tag
  mov -568(%rbp), rax
  movq -568(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -584(%rbp), %rax
  cmpq -576(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  testq %rax, %rax
  jne processMessage_block_5
  jmp processMessage_block_6
processMessage_block_5:
  jmp processMessage_block_64
processMessage_block_6:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rdi
  call lm_enum_tag
  mov -616(%rbp), rax
  movq -616(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -632(%rbp), %rax
  cmpq -624(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -640(%rbp)
  movq -640(%rbp), %rax
  movq -120(%rbp), %rdx
  movl %eax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  testq %rax, %rax
  jne processMessage_block_10
  jmp processMessage_block_16
processMessage_block_10:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rdi
  call lm_enum_payload
  mov -664(%rbp), rax
  movq -664(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -672(%rbp), %rdi
  movq -680(%rbp), %rsi
  call lm_tuple_get
  mov -688(%rbp), rax
  movq -688(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -696(%rbp), %rdi
  movq -704(%rbp), %rsi
  call lm_tuple_get
  mov -712(%rbp), rax
  movq -712(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  jmp processMessage_block_53
processMessage_block_16:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -720(%rbp), %rdi
  call lm_enum_tag
  mov -728(%rbp), rax
  movq -728(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rax
  cmpq -736(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rax
  movq -256(%rbp), %rdx
  movl %eax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -760(%rbp), %rax
  testq %rax, %rax
  jne processMessage_block_20
  jmp processMessage_block_22
processMessage_block_20:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -768(%rbp), %rdi
  call lm_enum_payload
  mov -776(%rbp), rax
  movq -776(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  jmp processMessage_block_48
processMessage_block_22:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -784(%rbp), %rdi
  call lm_enum_tag
  mov -792(%rbp), rax
  movq -792(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -808(%rbp), %rax
  cmpq -800(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -816(%rbp)
  movq -816(%rbp), %rax
  movq -320(%rbp), %rdx
  movl %eax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -824(%rbp), %rax
  testq %rax, %rax
  jne processMessage_block_26
  jmp processMessage_block_67
processMessage_block_26:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -832(%rbp)
  movq -832(%rbp), %rdi
  call lm_enum_payload
  mov -840(%rbp), rax
  movq -840(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -856(%rbp)
  movq -848(%rbp), %rdi
  movq -856(%rbp), %rsi
  call lm_tuple_get
  mov -864(%rbp), rax
  movq -864(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -872(%rbp), %rdi
  movq -880(%rbp), %rsi
  call lm_tuple_get
  mov -888(%rbp), rax
  movq -888(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -896(%rbp), %rdi
  movq -904(%rbp), %rsi
  call lm_tuple_get
  mov -912(%rbp), rax
  movq -912(%rbp), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  jmp processMessage_block_34
processMessage_block_34:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -920(%rbp), %rdi
  call lm_enum_payload
  mov -928(%rbp), rax
  movq -928(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -936(%rbp), %rdi
  movq -944(%rbp), %rsi
  call lm_tuple_get
  mov -952(%rbp), rax
  movq -952(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -960(%rbp)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -960(%rbp), %rdi
  movq -968(%rbp), %rsi
  call lm_tuple_get
  mov -976(%rbp), rax
  movq -976(%rbp), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -984(%rbp)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -984(%rbp), %rdi
  movq -992(%rbp), %rsi
  call lm_tuple_get
  mov -1000(%rbp), rax
  movq -1000(%rbp), %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_48(%rip), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1008(%rbp)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1016(%rbp)
  movq -1008(%rbp), %rdi
  movq -1016(%rbp), %rsi
  call lm_rt_str_format
  mov -1024(%rbp), rax
  movq -1024(%rbp), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1032(%rbp)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1040(%rbp)
  movq -1032(%rbp), %rdi
  movq -1040(%rbp), %rsi
  call lm_rt_str_format
  mov -1048(%rbp), rax
  movq -1048(%rbp), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -456(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1056(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1064(%rbp)
  movq -1056(%rbp), %rdi
  movq -1064(%rbp), %rsi
  call lm_rt_str_format
  mov -1072(%rbp), rax
  movq -1072(%rbp), %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1080(%rbp)
  movq -1080(%rbp), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1088(%rbp)
  movq -1088(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1096(%rbp)
  movq -1096(%rbp), %rax
  testq %rax, %rax
  jne processMessage_pr_nil_0_8537
  jmp processMessage_pr_str_0_8537
processMessage_block_48:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1104(%rbp)
  movq -1104(%rbp), %rdi
  call lm_enum_payload
  mov -1112(%rbp), rax
  movq -1112(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_49(%rip), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1120(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1128(%rbp)
  movq -1120(%rbp), %rdi
  movq -1128(%rbp), %rsi
  call lm_rt_str_format
  mov -1136(%rbp), rax
  movq -1136(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1144(%rbp)
  movq -1144(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1152(%rbp)
  movq -1152(%rbp), %rax
  testq %rax, %rax
  jne processMessage_pr_nil_0_5198
  jmp processMessage_pr_str_0_5198
processMessage_block_53:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1160(%rbp)
  movq -1160(%rbp), %rdi
  call lm_enum_payload
  mov -1168(%rbp), rax
  movq -1168(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1176(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1184(%rbp)
  movq -1176(%rbp), %rdi
  movq -1184(%rbp), %rsi
  call lm_tuple_get
  mov -1192(%rbp), rax
  movq -1192(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1200(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1208(%rbp)
  movq -1200(%rbp), %rdi
  movq -1208(%rbp), %rsi
  call lm_tuple_get
  mov -1216(%rbp), rax
  movq -1216(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_50(%rip), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1224(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1232(%rbp)
  movq -1224(%rbp), %rdi
  movq -1232(%rbp), %rsi
  call lm_rt_str_format
  mov -1240(%rbp), rax
  movq -1240(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1248(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1256(%rbp)
  movq -1248(%rbp), %rdi
  movq -1256(%rbp), %rsi
  call lm_rt_str_format
  mov -1264(%rbp), rax
  movq -1264(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1272(%rbp)
  movq -1272(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1280(%rbp)
  movq -1280(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1288(%rbp)
  movq -1288(%rbp), %rax
  testq %rax, %rax
  jne processMessage_pr_nil_0_4324
  jmp processMessage_pr_str_0_4324
processMessage_block_64:
  leaq str_hdr_51(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1296(%rbp)
  movq -1296(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1304(%rbp)
  movq -1304(%rbp), %rax
  testq %rax, %rax
  jne processMessage_pr_nil_0_8315
  jmp processMessage_pr_str_0_8315
processMessage_block_67:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1312(%rbp)
  movq -1312(%rbp), %rax
  jmp processMessage_epilogue
processMessage_pr_nil_0_8537:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1320(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1320(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1328(%rbp)
  jmp processMessage_pr_next_0_8537
processMessage_pr_str_0_8537:
  movq -1088(%rbp), %rax
  addq $8, %rax
  movq %rax, -1336(%rbp)
  movq -1336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1344(%rbp)
  movq -1088(%rbp), %rax
  addq $24, %rax
  movq %rax, -1352(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1352(%rbp), %rsi
  movq -1344(%rbp), %rdx
  syscall
  movq %rax, -1360(%rbp)
  jmp processMessage_pr_next_0_8537
processMessage_pr_next_0_8537:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1368(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1368(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1376(%rbp)
  movq $0, %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  jmp processMessage_block_67
processMessage_pr_nil_0_5198:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1384(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1384(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1392(%rbp)
  jmp processMessage_pr_next_0_5198
processMessage_pr_str_0_5198:
  movq -1144(%rbp), %rax
  addq $8, %rax
  movq %rax, -1400(%rbp)
  movq -1400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1408(%rbp)
  movq -1144(%rbp), %rax
  addq $24, %rax
  movq %rax, -1416(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1416(%rbp), %rsi
  movq -1408(%rbp), %rdx
  syscall
  movq %rax, -1424(%rbp)
  jmp processMessage_pr_next_0_5198
processMessage_pr_next_0_5198:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1432(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1432(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1440(%rbp)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  jmp processMessage_block_67
processMessage_pr_nil_0_4324:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1448(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1448(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1456(%rbp)
  jmp processMessage_pr_next_0_4324
processMessage_pr_str_0_4324:
  movq -1280(%rbp), %rax
  addq $8, %rax
  movq %rax, -1464(%rbp)
  movq -1464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1472(%rbp)
  movq -1280(%rbp), %rax
  addq $24, %rax
  movq %rax, -1480(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1480(%rbp), %rsi
  movq -1472(%rbp), %rdx
  syscall
  movq %rax, -1488(%rbp)
  jmp processMessage_pr_next_0_4324
processMessage_pr_next_0_4324:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1496(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1496(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1504(%rbp)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  jmp processMessage_block_67
processMessage_pr_nil_0_8315:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1512(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1512(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1520(%rbp)
  jmp processMessage_pr_next_0_8315
processMessage_pr_str_0_8315:
  movq -1296(%rbp), %rax
  addq $8, %rax
  movq %rax, -1528(%rbp)
  movq -1528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1536(%rbp)
  movq -1296(%rbp), %rax
  addq $24, %rax
  movq %rax, -1544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1544(%rbp), %rsi
  movq -1536(%rbp), %rdx
  syscall
  movq %rax, -1552(%rbp)
  jmp processMessage_pr_next_0_8315
processMessage_pr_next_0_8315:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1560(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1560(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1568(%rbp)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp processMessage_block_67
processMessage_epilogue:
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
.Lfunc_end_processMessage:

.globl getColorCode
getColorCode:
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
  subq $376, %rsp
  movq %rdi, -48(%rbp)
getColorCode_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp getColorCode_block_0
getColorCode_block_0:
  jmp getColorCode_block_1
getColorCode_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -240(%rbp)
  movq -240(%rbp), %rdi
  call lm_enum_tag
  mov -248(%rbp), rax
  movq -248(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -256(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rax
  cmpq -256(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -272(%rbp)
  movq -272(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -280(%rbp)
  movq -280(%rbp), %rax
  testq %rax, %rax
  jne getColorCode_block_5
  jmp getColorCode_block_6
getColorCode_block_5:
  jmp getColorCode_block_21
getColorCode_block_6:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rdi
  call lm_enum_tag
  mov -296(%rbp), rax
  movq -296(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -304(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -312(%rbp)
  movq -312(%rbp), %rax
  cmpq -304(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rax
  movq -112(%rbp), %rdx
  movl %eax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  testq %rax, %rax
  jne getColorCode_block_10
  jmp getColorCode_block_11
getColorCode_block_10:
  jmp getColorCode_block_19
getColorCode_block_11:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rdi
  call lm_enum_tag
  mov -344(%rbp), rax
  movq -344(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -352(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -360(%rbp), %rax
  cmpq -352(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rax
  movq -144(%rbp), %rdx
  movl %eax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -376(%rbp)
  movq -376(%rbp), %rax
  testq %rax, %rax
  jne getColorCode_block_15
  jmp getColorCode_block_16
getColorCode_block_15:
  jmp getColorCode_block_17
getColorCode_block_16:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -384(%rbp)
  movq -384(%rbp), %rax
  jmp getColorCode_epilogue
getColorCode_block_17:
  movq $64, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rax
  jmp getColorCode_epilogue
getColorCode_block_19:
  movq $128, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  jmp getColorCode_epilogue
getColorCode_block_21:
  movq $255, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -408(%rbp), %rax
  jmp getColorCode_epilogue
getColorCode_epilogue:
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
.Lfunc_end_getColorCode:

.globl describeColor
describeColor:
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
  subq $376, %rsp
  movq %rdi, -48(%rbp)
describeColor_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp describeColor_block_0
describeColor_block_0:
  jmp describeColor_block_1
describeColor_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -240(%rbp)
  movq -240(%rbp), %rdi
  call lm_enum_tag
  mov -248(%rbp), rax
  movq -248(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -256(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rax
  cmpq -256(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -272(%rbp)
  movq -272(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -280(%rbp)
  movq -280(%rbp), %rax
  testq %rax, %rax
  jne describeColor_block_5
  jmp describeColor_block_6
describeColor_block_5:
  jmp describeColor_block_21
describeColor_block_6:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rdi
  call lm_enum_tag
  mov -296(%rbp), rax
  movq -296(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -304(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -312(%rbp)
  movq -312(%rbp), %rax
  cmpq -304(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rax
  movq -112(%rbp), %rdx
  movl %eax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  testq %rax, %rax
  jne describeColor_block_10
  jmp describeColor_block_11
describeColor_block_10:
  jmp describeColor_block_19
describeColor_block_11:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rdi
  call lm_enum_tag
  mov -344(%rbp), rax
  movq -344(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -352(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -360(%rbp), %rax
  cmpq -352(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rax
  movq -144(%rbp), %rdx
  movl %eax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -376(%rbp)
  movq -376(%rbp), %rax
  testq %rax, %rax
  jne describeColor_block_15
  jmp describeColor_block_16
describeColor_block_15:
  jmp describeColor_block_17
describeColor_block_16:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -384(%rbp)
  movq -384(%rbp), %rax
  jmp describeColor_epilogue
describeColor_block_17:
  leaq str_hdr_52(%rip), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rax
  jmp describeColor_epilogue
describeColor_block_19:
  leaq str_hdr_53(%rip), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  jmp describeColor_epilogue
describeColor_block_21:
  leaq str_hdr_54(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -408(%rbp), %rax
  jmp describeColor_epilogue
describeColor_epilogue:
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
.Lfunc_end_describeColor:

.globl checkConnectivity
checkConnectivity:
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
checkConnectivity_entry:
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
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp checkConnectivity_block_0
checkConnectivity_block_0:
  jmp checkConnectivity_block_1
checkConnectivity_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -208(%rbp)
  movq -208(%rbp), %rdi
  call lm_enum_tag
  mov -216(%rbp), rax
  movq -216(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -224(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -232(%rbp)
  movq -232(%rbp), %rax
  cmpq -224(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -240(%rbp)
  movq -240(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -248(%rbp)
  movq -248(%rbp), %rax
  testq %rax, %rax
  jne checkConnectivity_block_5
  jmp checkConnectivity_block_6
checkConnectivity_block_5:
  jmp checkConnectivity_block_11
checkConnectivity_block_6:
  jmp checkConnectivity_block_7
checkConnectivity_block_7:
  leaq str_hdr_55(%rip), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -256(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -264(%rbp)
  movq -256(%rbp), %rdi
  movq -264(%rbp), %rsi
  call lm_rt_str_format
  mov -272(%rbp), rax
  movq -272(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -280(%rbp)
  movq -280(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rax
  testq %rax, %rax
  jne checkConnectivity_pr_nil_0_4370
  jmp checkConnectivity_pr_str_0_4370
checkConnectivity_block_11:
  leaq str_hdr_56(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -296(%rbp)
  movq -296(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -304(%rbp)
  movq -304(%rbp), %rax
  testq %rax, %rax
  jne checkConnectivity_pr_nil_0_6413
  jmp checkConnectivity_pr_str_0_6413
checkConnectivity_block_14:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -312(%rbp)
  movq -312(%rbp), %rax
  jmp checkConnectivity_epilogue
checkConnectivity_pr_nil_0_4370:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -320(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -320(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -328(%rbp)
  jmp checkConnectivity_pr_next_0_4370
checkConnectivity_pr_str_0_4370:
  movq -280(%rbp), %rax
  addq $8, %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -344(%rbp)
  movq -280(%rbp), %rax
  addq $24, %rax
  movq %rax, -352(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -352(%rbp), %rsi
  movq -344(%rbp), %rdx
  syscall
  movq %rax, -360(%rbp)
  jmp checkConnectivity_pr_next_0_4370
checkConnectivity_pr_next_0_4370:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -368(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -368(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -376(%rbp)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  jmp checkConnectivity_block_14
checkConnectivity_pr_nil_0_6413:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -384(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -384(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -392(%rbp)
  jmp checkConnectivity_pr_next_0_6413
checkConnectivity_pr_str_0_6413:
  movq -296(%rbp), %rax
  addq $8, %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -296(%rbp), %rax
  addq $24, %rax
  movq %rax, -416(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -416(%rbp), %rsi
  movq -408(%rbp), %rdx
  syscall
  movq %rax, -424(%rbp)
  jmp checkConnectivity_pr_next_0_6413
checkConnectivity_pr_next_0_6413:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -432(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -432(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -440(%rbp)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp checkConnectivity_block_14
checkConnectivity_epilogue:
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
.Lfunc_end_checkConnectivity:

.globl isActive
isActive:
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
isActive_entry:
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
  jmp isActive_block_0
isActive_block_0:
  jmp isActive_block_1
isActive_block_1:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rdi
  call lm_enum_tag
  mov -192(%rbp), rax
  movq -192(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -200(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -208(%rbp)
  movq -208(%rbp), %rax
  cmpq -200(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -216(%rbp)
  movq -216(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -224(%rbp)
  movq -224(%rbp), %rax
  testq %rax, %rax
  jne isActive_block_5
  jmp isActive_block_6
isActive_block_5:
  jmp isActive_block_9
isActive_block_6:
  jmp isActive_block_7
isActive_block_7:
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -232(%rbp)
  movq -232(%rbp), %rax
  jmp isActive_epilogue
isActive_block_9:
  movq $1, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -240(%rbp)
  movq -240(%rbp), %rax
  jmp isActive_epilogue
isActive_epilogue:
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
.Lfunc_end_isActive:

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

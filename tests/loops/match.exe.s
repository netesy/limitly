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
str_const_0:
  .string "=== Match Statement Tests ==="
.align 8
str_const_1:
  .string "
--- Test 1: Literal Integer Patterns ---"
.align 8
str_const_2:
  .string "x is something else"
.align 8
str_const_3:
  .string "x is ten"
.align 8
str_const_4:
  .string "x is five"
.align 8
str_const_5:
  .string "
--- Test 2: Variable Binding Patterns ---"
.align 8
str_const_6:
  .string "The value is: %s"
.align 8
str_const_7:
  .string "
--- Test 3: Enum Pattern Matching ---"
.align 8
str_const_8:
  .string "Unknown status"
.align 8
str_const_9:
  .string "Status is Pending"
.align 8
str_const_10:
  .string "Status is Inactive"
.align 8
str_const_11:
  .string "Status is Active"
.align 8
str_const_12:
  .string "
--- Test 4: Enum with Associated Values ---"
.align 8
str_const_13:
  .string "Operation completed"
.align 8
str_const_14:
  .string "Something went wrong"
.align 8
str_const_15:
  .string "
--- Test 5: Frame Pattern Matching ---"
.align 8
str_const_16:
  .string "Point at (%s, %s)"
.align 8
str_const_17:
  .string "
--- Test 6: Wildcard Patterns ---"
.align 8
str_const_18:
  .string "hello"
.align 8
str_const_19:
  .string "Matched anything: %s"
.align 8
str_const_20:
  .string "
--- Test 7: Nested Match Statements ---"
.align 8
str_const_21:
  .string "Unknown color square"
.align 8
str_const_22:
  .string "Blue square"
.align 8
str_const_23:
  .string "Green square"
.align 8
str_const_24:
  .string "Red square"
.align 8
str_const_25:
  .string "Unknown color circle"
.align 8
str_const_26:
  .string "Blue circle"
.align 8
str_const_27:
  .string "Green circle"
.align 8
str_const_28:
  .string "Red circle"
.align 8
str_const_29:
  .string "
--- Test 8: Match with Return Values ---"
.align 8
str_const_30:
  .string "Monday"
.align 8
str_const_31:
  .string "Day 1 should be Monday"
.align 8
str_const_32:
  .string "Friday"
.align 8
str_const_33:
  .string "Day 5 should be Friday"
.align 8
str_const_34:
  .string "Invalid day"
.align 8
str_const_35:
  .string "Day 10 should be Invalid day"
.align 8
str_const_36:
  .string "Day 1: %s"
.align 8
str_const_37:
  .string "Day 5: %s"
.align 8
str_const_38:
  .string "Day 10: %s"
.align 8
str_const_39:
  .string "
--- Test 9: Multiple Match Cases ---"
.align 8
str_const_40:
  .string "Hello, World!"
.align 8
str_const_41:
  .string "Quitting application..."
.align 8
str_const_42:
  .string "Quit message failed"
.align 8
str_const_43:
  .string "Moving to position (10, 20)"
.align 8
str_const_44:
  .string "Move message failed"
.align 8
str_const_45:
  .string "Writing message: Hello, World!"
.align 8
str_const_46:
  .string "Write message failed"
.align 8
str_const_47:
  .string "Message 1: %s"
.align 8
str_const_48:
  .string "Message 2: %s"
.align 8
str_const_49:
  .string "Message 3: %s"
.align 8
str_const_50:
  .string "
--- Test 10: Guard Clauses ---"
.align 8
str_const_51:
  .string "exactly 10"
.align 8
str_const_52:
  .string "Guard clause test for 10 failed"
.align 8
str_const_53:
  .string "greater than 10"
.align 8
str_const_54:
  .string "Guard clause test for 15 failed"
.align 8
str_const_55:
  .string "less than 10"
.align 8
str_const_56:
  .string "Guard clause test for 5 failed"
.align 8
str_const_57:
  .string "Value 10: %s"
.align 8
str_const_58:
  .string "Value 15: %s"
.align 8
str_const_59:
  .string "Value 5: %s"
.align 8
str_const_60:
  .string "
=== Match Statement Tests Complete ==="
.align 8
str_const_61:
  .string "greater than 10"
.align 8
str_const_62:
  .string "less than 10"
.align 8
str_const_63:
  .string "exactly 10"
.align 8
str_const_64:
  .string "Invalid day"
.align 8
str_const_65:
  .string "Sunday"
.align 8
str_const_66:
  .string "Saturday"
.align 8
str_const_67:
  .string "Friday"
.align 8
str_const_68:
  .string "Thursday"
.align 8
str_const_69:
  .string "Wednesday"
.align 8
str_const_70:
  .string "Tuesday"
.align 8
str_const_71:
  .string "Monday"
.align 8
str_const_72:
  .string "Operation is pending"
.align 8
str_const_73:
  .string "Error Result: %s"
.align 8
str_const_74:
  .string "Success: %s"
.align 8
str_const_75:
  .string "Writing message: %s"
.align 8
str_const_76:
  .string "Moving to position (%s, %s)"
.align 8
str_const_77:
  .string "Quitting application..."
.align 8
nl:
  .string "
"
.align 8
assert_fail:
  .string "Assertion failed
"
.text
.globl main
.globl _start
_start:
  and %rsp, -16
  and rsp, -16
  subq $32, %rsp
  call main
  addq $32, %rsp
  mov rcx, rax
  subq $32, %rsp
  call ExitProcess
  addq $32, %rsp

.globl main
main:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 1800
main_entry:
main_block_0:
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  addq $16, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  mov rax, [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  call lm_print_str
  jmp main_block_6
main_block_6:
  movq $81, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne main_block_9
  jmp main_block_10
main_block_9:
  jmp main_block_9
  jmp main_block_21
main_block_10:
  movq $81, rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne main_block_13
  jmp main_block_14
main_block_13:
  jmp main_block_13
  jmp main_block_18
main_block_14:
  jmp main_block_15
main_block_15:
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  addq $16, rax
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  mov rax, [rax]
  movq rax, [rbp + -168]
  movq [rbp + -168], rcx
  call lm_print_str
  jmp main_block_24
main_block_18:
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  addq $16, rax
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  mov rax, [rax]
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  call lm_print_str
  jmp main_block_24
main_block_21:
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  addq $16, rax
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  mov rax, [rax]
  movq rax, [rbp + -232]
  movq [rbp + -232], rcx
  call lm_print_str
  jmp main_block_24
main_block_24:
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  addq $16, rax
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  mov rax, [rax]
  movq rax, [rbp + -264]
  movq [rbp + -264], rcx
  call lm_print_str
  jmp main_block_28
main_block_28:
  jmp main_block_29
main_block_29:
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -272], rcx
  movq $337, rdx
  call lm_rt_str_format
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  addq $16, rax
  movq rax, [rbp + -288]
  movq [rbp + -288], rax
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  mov rax, [rax]
  movq rax, [rbp + -304]
  movq [rbp + -304], rcx
  call lm_print_str
  jmp main_block_33
main_block_33:
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -312], rax
  addq $16, rax
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  mov rax, [rax]
  movq rax, [rbp + -336]
  movq [rbp + -336], rcx
  call lm_print_str
  jmp main_block_38
main_block_38:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  testq rax, rax
  jne main_block_42
  jmp main_block_43
main_block_42:
  jmp main_block_42
  jmp main_block_63
main_block_43:
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  testq rax, rax
  jne main_block_47
  jmp main_block_48
main_block_47:
  jmp main_block_47
  jmp main_block_60
main_block_48:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rbp + -360], rax
  testq rax, rax
  jne main_block_52
  jmp main_block_53
main_block_52:
  jmp main_block_52
  jmp main_block_57
main_block_53:
  jmp main_block_54
main_block_54:
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -368], rax
  addq $16, rax
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  movq rax, [rbp + -384]
  movq [rbp + -384], rax
  mov rax, [rax]
  movq rax, [rbp + -392]
  movq [rbp + -392], rcx
  call lm_print_str
  jmp main_block_66
main_block_57:
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  addq $16, rax
  movq rax, [rbp + -408]
  movq [rbp + -408], rax
  movq rax, [rbp + -416]
  movq [rbp + -416], rax
  mov rax, [rax]
  movq rax, [rbp + -424]
  movq [rbp + -424], rcx
  call lm_print_str
  jmp main_block_66
main_block_60:
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -432], rax
  addq $16, rax
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  mov rax, [rax]
  movq rax, [rbp + -456]
  movq [rbp + -456], rcx
  call lm_print_str
  jmp main_block_66
main_block_63:
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rbp + -464], rax
  addq $16, rax
  movq rax, [rbp + -472]
  movq [rbp + -472], rax
  movq rax, [rbp + -480]
  movq [rbp + -480], rax
  mov rax, [rax]
  movq rax, [rbp + -488]
  movq [rbp + -488], rcx
  call lm_print_str
  jmp main_block_66
main_block_66:
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  addq $16, rax
  movq rax, [rbp + -504]
  movq [rbp + -504], rax
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  mov rax, [rax]
  movq rax, [rbp + -520]
  movq [rbp + -520], rcx
  call lm_print_str
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -536]
  movq $0, rcx
  call describeResult
  movq $0, rcx
  call describeResult
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  addq $16, rax
  movq rax, [rbp + -552]
  movq [rbp + -552], rax
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  mov rax, [rax]
  movq rax, [rbp + -568]
  movq [rbp + -568], rcx
  call lm_print_str
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -576], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -576], rax
  addq $0, rax
  movq rax, [rbp + -584]
  movq [rbp + -64], rax
  movq [rbp + -584], rdx
  mov [rdx], rax
  movq [rbp + -576], rax
  addq $0, rax
  movq rax, [rbp + -592]
  movq $r1, rax
  movq [rbp + -592], rdx
  mov [rdx], rax
  jmp main_block_85
main_block_85:
  jmp main_block_86
main_block_86:
  movq [rbp + -576], rax
  addq $0, rax
  movq rax, [rbp + -600]
  movq [rbp + -600], rax
  mov rax, [rax]
  movq rax, [rbp + -608]
  movq [rbp + -576], rax
  addq $0, rax
  movq rax, [rbp + -616]
  movq [rbp + -616], rax
  mov rax, [rax]
  movq rax, [rbp + -624]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq [rbp + -632], rcx
  movq [rbp + -608], rdx
  call lm_rt_str_format
  movq rax, [rbp + -640]
  movq [rbp + -640], rcx
  movq [rbp + -624], rdx
  call lm_rt_str_format
  movq rax, [rbp + -648]
  movq [rbp + -648], rax
  addq $16, rax
  movq rax, [rbp + -656]
  movq [rbp + -656], rax
  movq rax, [rbp + -664]
  movq [rbp + -664], rax
  mov rax, [rax]
  movq rax, [rbp + -672]
  movq [rbp + -672], rcx
  call lm_print_str
  jmp main_block_94
main_block_94:
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -680]
  movq [rbp + -680], rax
  addq $16, rax
  movq rax, [rbp + -688]
  movq [rbp + -688], rax
  movq rax, [rbp + -696]
  movq [rbp + -696], rax
  mov rax, [rax]
  movq rax, [rbp + -704]
  movq [rbp + -704], rcx
  call lm_print_str
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -712]
  jmp main_block_98
main_block_98:
  jmp main_block_99
main_block_99:
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -720]
  movq [rbp + -720], rcx
  movq [rbp + -712], rdx
  call lm_rt_str_format
  movq rax, [rbp + -728]
  movq [rbp + -728], rax
  addq $16, rax
  movq rax, [rbp + -736]
  movq [rbp + -736], rax
  movq rax, [rbp + -744]
  movq [rbp + -744], rax
  mov rax, [rax]
  movq rax, [rbp + -752]
  movq [rbp + -752], rcx
  call lm_print_str
  jmp main_block_103
main_block_103:
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -760]
  movq [rbp + -760], rax
  addq $16, rax
  movq rax, [rbp + -768]
  movq [rbp + -768], rax
  movq rax, [rbp + -776]
  movq [rbp + -776], rax
  mov rax, [rax]
  movq rax, [rbp + -784]
  movq [rbp + -784], rcx
  call lm_print_str
  jmp main_block_109
main_block_109:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -792]
  movq [rbp + -792], rax
  testq rax, rax
  jne main_block_113
  jmp main_block_115
main_block_113:
  jmp main_block_113
  jmp main_block_152
main_block_115:
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -800]
  movq [rbp + -800], rax
  testq rax, rax
  jne main_block_119
  jmp main_block_183
main_block_119:
  jmp main_block_119
  jmp main_block_121
main_block_121:
  jmp main_block_123
main_block_123:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -808]
  movq [rbp + -808], rax
  testq rax, rax
  jne main_block_127
  jmp main_block_128
main_block_127:
  jmp main_block_127
  jmp main_block_148
main_block_128:
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -816]
  movq [rbp + -816], rax
  testq rax, rax
  jne main_block_132
  jmp main_block_133
main_block_132:
  jmp main_block_132
  jmp main_block_145
main_block_133:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -824]
  movq [rbp + -824], rax
  testq rax, rax
  jne main_block_137
  jmp main_block_138
main_block_137:
  jmp main_block_137
  jmp main_block_142
main_block_138:
  jmp main_block_139
main_block_139:
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -832]
  movq [rbp + -832], rax
  addq $16, rax
  movq rax, [rbp + -840]
  movq [rbp + -840], rax
  movq rax, [rbp + -848]
  movq [rbp + -848], rax
  mov rax, [rax]
  movq rax, [rbp + -856]
  movq [rbp + -856], rcx
  call lm_print_str
  jmp main_block_151
main_block_142:
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -864]
  movq [rbp + -864], rax
  addq $16, rax
  movq rax, [rbp + -872]
  movq [rbp + -872], rax
  movq rax, [rbp + -880]
  movq [rbp + -880], rax
  mov rax, [rax]
  movq rax, [rbp + -888]
  movq [rbp + -888], rcx
  call lm_print_str
  jmp main_block_151
main_block_145:
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -896]
  movq [rbp + -896], rax
  addq $16, rax
  movq rax, [rbp + -904]
  movq [rbp + -904], rax
  movq rax, [rbp + -912]
  movq [rbp + -912], rax
  mov rax, [rax]
  movq rax, [rbp + -920]
  movq [rbp + -920], rcx
  call lm_print_str
  jmp main_block_151
main_block_148:
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -928]
  movq [rbp + -928], rax
  addq $16, rax
  movq rax, [rbp + -936]
  movq [rbp + -936], rax
  movq rax, [rbp + -944]
  movq [rbp + -944], rax
  mov rax, [rax]
  movq rax, [rbp + -952]
  movq [rbp + -952], rcx
  call lm_print_str
  jmp main_block_151
main_block_151:
  jmp main_block_183
main_block_152:
  jmp main_block_154
main_block_154:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -960]
  movq [rbp + -960], rax
  testq rax, rax
  jne main_block_158
  jmp main_block_159
main_block_158:
  jmp main_block_158
  jmp main_block_179
main_block_159:
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -968]
  movq [rbp + -968], rax
  testq rax, rax
  jne main_block_163
  jmp main_block_164
main_block_163:
  jmp main_block_163
  jmp main_block_176
main_block_164:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -976]
  movq [rbp + -976], rax
  testq rax, rax
  jne main_block_168
  jmp main_block_169
main_block_168:
  jmp main_block_168
  jmp main_block_173
main_block_169:
  jmp main_block_170
main_block_170:
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -984]
  movq [rbp + -984], rax
  addq $16, rax
  movq rax, [rbp + -992]
  movq [rbp + -992], rax
  movq rax, [rbp + -1000]
  movq [rbp + -1000], rax
  mov rax, [rax]
  movq rax, [rbp + -1008]
  movq [rbp + -1008], rcx
  call lm_print_str
  jmp main_block_182
main_block_173:
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -1016]
  movq [rbp + -1016], rax
  addq $16, rax
  movq rax, [rbp + -1024]
  movq [rbp + -1024], rax
  movq rax, [rbp + -1032]
  movq [rbp + -1032], rax
  mov rax, [rax]
  movq rax, [rbp + -1040]
  movq [rbp + -1040], rcx
  call lm_print_str
  jmp main_block_182
main_block_176:
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -1048]
  movq [rbp + -1048], rax
  addq $16, rax
  movq rax, [rbp + -1056]
  movq [rbp + -1056], rax
  movq rax, [rbp + -1064]
  movq [rbp + -1064], rax
  mov rax, [rax]
  movq rax, [rbp + -1072]
  movq [rbp + -1072], rcx
  call lm_print_str
  jmp main_block_182
main_block_179:
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -1080]
  movq [rbp + -1080], rax
  addq $16, rax
  movq rax, [rbp + -1088]
  movq [rbp + -1088], rax
  movq rax, [rbp + -1096]
  movq [rbp + -1096], rax
  mov rax, [rax]
  movq rax, [rbp + -1104]
  movq [rbp + -1104], rcx
  call lm_print_str
  jmp main_block_182
main_block_182:
  jmp main_block_183
main_block_183:
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -1112]
  movq [rbp + -1112], rax
  addq $16, rax
  movq rax, [rbp + -1120]
  movq [rbp + -1120], rax
  movq rax, [rbp + -1128]
  movq [rbp + -1128], rax
  mov rax, [rax]
  movq rax, [rbp + -1136]
  movq [rbp + -1136], rcx
  call lm_print_str
  movq $9, rcx
  call getDayName
  movq $41, rcx
  call getDayName
  movq $81, rcx
  call getDayName
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -1144]
  movq $r125, rax
  cmpq [rbp + -1144], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1152]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -1160]
  movq [rbp + -1152], rcx
  movq [rbp + -1160], rdx
  call lm_assert
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -1168]
  movq $r128, rax
  cmpq [rbp + -1168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1176]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -1184]
  movq [rbp + -1176], rcx
  movq [rbp + -1184], rdx
  call lm_assert
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -1192]
  movq $r131, rax
  cmpq [rbp + -1192], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1200]
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -1208]
  movq [rbp + -1200], rcx
  movq [rbp + -1208], rdx
  call lm_assert
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -1216]
  movq [rbp + -1216], rcx
  movq $r125, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1224]
  movq [rbp + -1224], rax
  addq $16, rax
  movq rax, [rbp + -1232]
  movq [rbp + -1232], rax
  movq rax, [rbp + -1240]
  movq [rbp + -1240], rax
  mov rax, [rax]
  movq rax, [rbp + -1248]
  movq [rbp + -1248], rcx
  call lm_print_str
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -1256]
  movq [rbp + -1256], rcx
  movq $r128, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1264]
  movq [rbp + -1264], rax
  addq $16, rax
  movq rax, [rbp + -1272]
  movq [rbp + -1272], rax
  movq rax, [rbp + -1280]
  movq [rbp + -1280], rax
  mov rax, [rax]
  movq rax, [rbp + -1288]
  movq [rbp + -1288], rcx
  call lm_print_str
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -1296]
  movq [rbp + -1296], rcx
  movq $r131, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1304]
  movq [rbp + -1304], rax
  addq $16, rax
  movq rax, [rbp + -1312]
  movq [rbp + -1312], rax
  movq rax, [rbp + -1320]
  movq [rbp + -1320], rax
  mov rax, [rax]
  movq rax, [rbp + -1328]
  movq [rbp + -1328], rcx
  call lm_print_str
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -1336]
  movq [rbp + -1336], rax
  addq $16, rax
  movq rax, [rbp + -1344]
  movq [rbp + -1344], rax
  movq rax, [rbp + -1352]
  movq [rbp + -1352], rax
  mov rax, [rax]
  movq rax, [rbp + -1360]
  movq [rbp + -1360], rcx
  call lm_print_str
  movq $0, rcx
  call processMessage
  movq $0, rcx
  call processMessage
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -1368]
  movq $0, rcx
  call processMessage
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -1376]
  movq $r157, rax
  cmpq [rbp + -1376], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1384]
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -1392]
  movq [rbp + -1384], rcx
  movq [rbp + -1392], rdx
  call lm_assert
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -1400]
  movq $r165, rax
  cmpq [rbp + -1400], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1408]
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -1416]
  movq [rbp + -1408], rcx
  movq [rbp + -1416], rdx
  call lm_assert
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -1424]
  movq $r170, rax
  cmpq [rbp + -1424], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1432]
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -1440]
  movq [rbp + -1432], rcx
  movq [rbp + -1440], rdx
  call lm_assert
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -1448]
  movq [rbp + -1448], rcx
  movq $r157, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1456]
  movq [rbp + -1456], rax
  addq $16, rax
  movq rax, [rbp + -1464]
  movq [rbp + -1464], rax
  movq rax, [rbp + -1472]
  movq [rbp + -1472], rax
  mov rax, [rax]
  movq rax, [rbp + -1480]
  movq [rbp + -1480], rcx
  call lm_print_str
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -1488]
  movq [rbp + -1488], rcx
  movq $r165, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1496]
  movq [rbp + -1496], rax
  addq $16, rax
  movq rax, [rbp + -1504]
  movq [rbp + -1504], rax
  movq rax, [rbp + -1512]
  movq [rbp + -1512], rax
  mov rax, [rax]
  movq rax, [rbp + -1520]
  movq [rbp + -1520], rcx
  call lm_print_str
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -1528]
  movq [rbp + -1528], rcx
  movq $r170, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1536]
  movq [rbp + -1536], rax
  addq $16, rax
  movq rax, [rbp + -1544]
  movq [rbp + -1544], rax
  movq rax, [rbp + -1552]
  movq [rbp + -1552], rax
  mov rax, [rax]
  movq rax, [rbp + -1560]
  movq [rbp + -1560], rcx
  call lm_print_str
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -1568]
  movq [rbp + -1568], rax
  addq $16, rax
  movq rax, [rbp + -1576]
  movq [rbp + -1576], rax
  movq rax, [rbp + -1584]
  movq [rbp + -1584], rax
  mov rax, [rax]
  movq rax, [rbp + -1592]
  movq [rbp + -1592], rcx
  call lm_print_str
  movq $81, rcx
  call getGuard
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -1600]
  movq $r196, rax
  cmpq [rbp + -1600], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1608]
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -1616]
  movq [rbp + -1608], rcx
  movq [rbp + -1616], rdx
  call lm_assert
  movq $121, rcx
  call getGuard
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -1624]
  movq $r203, rax
  cmpq [rbp + -1624], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1632]
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -1640]
  movq [rbp + -1632], rcx
  movq [rbp + -1640], rdx
  call lm_assert
  movq $41, rcx
  call getGuard
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -1648]
  movq $r210, rax
  cmpq [rbp + -1648], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1656]
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -1664]
  movq [rbp + -1656], rcx
  movq [rbp + -1664], rdx
  call lm_assert
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -1672]
  movq [rbp + -1672], rcx
  movq $r196, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1680]
  movq [rbp + -1680], rax
  addq $16, rax
  movq rax, [rbp + -1688]
  movq [rbp + -1688], rax
  movq rax, [rbp + -1696]
  movq [rbp + -1696], rax
  mov rax, [rax]
  movq rax, [rbp + -1704]
  movq [rbp + -1704], rcx
  call lm_print_str
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -1712]
  movq [rbp + -1712], rcx
  movq $r203, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1720]
  movq [rbp + -1720], rax
  addq $16, rax
  movq rax, [rbp + -1728]
  movq [rbp + -1728], rax
  movq rax, [rbp + -1736]
  movq [rbp + -1736], rax
  mov rax, [rax]
  movq rax, [rbp + -1744]
  movq [rbp + -1744], rcx
  call lm_print_str
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -1752]
  movq [rbp + -1752], rcx
  movq $r210, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1760]
  movq [rbp + -1760], rax
  addq $16, rax
  movq rax, [rbp + -1768]
  movq [rbp + -1768], rax
  movq rax, [rbp + -1776]
  movq [rbp + -1776], rax
  mov rax, [rax]
  movq rax, [rbp + -1784]
  movq [rbp + -1784], rcx
  call lm_print_str
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -1792]
  movq [rbp + -1792], rax
  addq $16, rax
  movq rax, [rbp + -1800]
  movq [rbp + -1800], rax
  movq rax, [rbp + -1808]
  movq [rbp + -1808], rax
  mov rax, [rax]
  movq rax, [rbp + -1816]
  movq [rbp + -1816], rcx
  call lm_print_str
  movq $0, rax
  jmp main_epilogue
main_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_main:

.globl getGuard
getGuard:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
getGuard_entry:
getGuard_block_0:
  jmp getGuard_block_1
getGuard_block_1:
  movq [rbp + -64], rax
  cmpq $81, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne getGuard_block_4
  jmp getGuard_block_6
getGuard_block_4:
  jmp getGuard_block_4
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp getGuard_epilogue
getGuard_block_6:
  movq [rbp + -64], rax
  cmpq $81, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne getGuard_block_9
  jmp getGuard_block_11
getGuard_block_9:
  jmp getGuard_block_9
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp getGuard_epilogue
getGuard_block_11:
  jmp getGuard_block_12
getGuard_block_12:
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp getGuard_epilogue
getGuard_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_getGuard:

.globl getDayName
getDayName:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 168
  mov [rbp + -64], rcx
getDayName_entry:
getDayName_block_0:
  jmp getDayName_block_1
getDayName_block_1:
  movq [rbp + -64], rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne getDayName_block_4
  jmp getDayName_block_5
getDayName_block_4:
  jmp getDayName_block_4
  jmp getDayName_block_44
getDayName_block_5:
  movq [rbp + -64], rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne getDayName_block_8
  jmp getDayName_block_9
getDayName_block_8:
  jmp getDayName_block_8
  jmp getDayName_block_42
getDayName_block_9:
  movq [rbp + -64], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne getDayName_block_12
  jmp getDayName_block_13
getDayName_block_12:
  jmp getDayName_block_12
  jmp getDayName_block_40
getDayName_block_13:
  movq [rbp + -64], rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne getDayName_block_16
  jmp getDayName_block_17
getDayName_block_16:
  jmp getDayName_block_16
  jmp getDayName_block_38
getDayName_block_17:
  movq [rbp + -64], rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne getDayName_block_20
  jmp getDayName_block_21
getDayName_block_20:
  jmp getDayName_block_20
  jmp getDayName_block_36
getDayName_block_21:
  movq [rbp + -64], rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne getDayName_block_24
  jmp getDayName_block_25
getDayName_block_24:
  jmp getDayName_block_24
  jmp getDayName_block_34
getDayName_block_25:
  movq [rbp + -64], rax
  cmpq $57, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne getDayName_block_28
  jmp getDayName_block_29
getDayName_block_28:
  jmp getDayName_block_28
  jmp getDayName_block_32
getDayName_block_29:
  jmp getDayName_block_30
getDayName_block_30:
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  jmp getDayName_epilogue
getDayName_block_32:
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp getDayName_epilogue
getDayName_block_34:
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  jmp getDayName_epilogue
getDayName_block_36:
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  jmp getDayName_epilogue
getDayName_block_38:
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  jmp getDayName_epilogue
getDayName_block_40:
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  jmp getDayName_epilogue
getDayName_block_42:
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  jmp getDayName_epilogue
getDayName_block_44:
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  jmp getDayName_epilogue
getDayName_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_getDayName:

.globl describeResult
describeResult:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 184
  mov [rbp + -64], rcx
describeResult_entry:
describeResult_block_0:
  jmp describeResult_block_1
describeResult_block_1:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne describeResult_block_5
  jmp describeResult_block_7
describeResult_block_5:
  jmp describeResult_block_5
  jmp describeResult_block_26
describeResult_block_7:
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne describeResult_block_11
  jmp describeResult_block_13
describeResult_block_11:
  jmp describeResult_block_11
  jmp describeResult_block_21
describeResult_block_13:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne describeResult_block_17
  jmp describeResult_block_31
describeResult_block_17:
  jmp describeResult_block_17
  jmp describeResult_block_18
describeResult_block_18:
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  addq $16, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  mov rax, [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  call lm_print_str
  jmp describeResult_block_31
describeResult_block_21:
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  addq $16, rax
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  mov rax, [rax]
  movq rax, [rbp + -160]
  movq [rbp + -160], rcx
  call lm_print_str
  jmp describeResult_block_31
describeResult_block_26:
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -168], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  addq $16, rax
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  mov rax, [rax]
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  call lm_print_str
  jmp describeResult_block_31
describeResult_block_31:
  movq $0, rax
  jmp describeResult_epilogue
describeResult_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_describeResult:

.globl processMessage
processMessage:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 120
  mov [rbp + -64], rcx
processMessage_entry:
processMessage_block_0:
  jmp processMessage_block_1
processMessage_block_1:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne processMessage_block_5
  jmp processMessage_block_6
processMessage_block_5:
  jmp processMessage_block_5
  jmp processMessage_block_37
processMessage_block_6:
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne processMessage_block_10
  jmp processMessage_block_16
processMessage_block_10:
  jmp processMessage_block_10
  jmp processMessage_block_27
processMessage_block_16:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne processMessage_block_20
  jmp processMessage_block_22
processMessage_block_20:
  jmp processMessage_block_20
  jmp processMessage_block_23
processMessage_block_22:
  movq $0, rax
  jmp processMessage_epilogue
processMessage_block_23:
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp processMessage_epilogue
processMessage_block_27:
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  jmp processMessage_epilogue
processMessage_block_37:
  movq [rel str_const_77], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp processMessage_epilogue
processMessage_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_processMessage:

.globl lm_box_string
lm_box_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
lm_box_string_entry:
  # Bump Allocation: 24 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 24
  mov [rel heap_ptr], rax
  movq $2, rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  addq $8, rax
  movq rax, [rbp + -80]
  movq $3, rax
  movq [rbp + -80], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  addq $16, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  jmp lm_box_string_epilogue
lm_box_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_lm_box_string:

.globl lm_print_str
lm_print_str:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 136
  mov [rbp + -64], rcx
lm_print_str_entry:
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 8
  mov [rel heap_ptr], rax
  movq $0, rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  jmp lm_print_str_loop
lm_print_str_loop:
  movq [rbp + -72], rax
  mov rax, [rax]
  movq rax, [rbp + -80]
  movq [rbp + -64], rax
  addq [rbp + -80], rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  cmpq $0, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -80], rax
  addq $1, rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  testq rax, rax
  jne lm_print_str_done
  jmp lm_print_str_loop
lm_print_str_done:
  movq [rbp + -72], rax
  mov rax, [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  subq $1, rax
  movq rax, [rbp + -128]
  subq $32, %rsp
  movq $1, rcx
  movq [rbp + -64], rdx
  movq [rbp + -128], r8
  call _write
  addq $32, %rsp
  subq $32, %rsp
  movq $1, rcx
  movq [rel nl], rdx
  movq $1, r8
  call _write
  addq $32, %rsp
  movq $0, rax
  jmp lm_print_str_epilogue
lm_print_str_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_lm_print_str:

.globl lm_assert
lm_assert:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
lm_assert_entry:
  movq [rbp + -64], rax
  testq rax, rax
  jne lm_assert_pass
  jmp lm_assert_fail
lm_assert_fail:
  subq $32, %rsp
  movq $1, rcx
  movq [rel assert_fail], rdx
  movq $17, r8
  call _write
  addq $32, %rsp
  movq $50397203, rax
  movq rax, [rbp + -88]
  movq $0, rax
  jmp lm_assert_epilogue
lm_assert_pass:
  movq $0, rax
  jmp lm_assert_epilogue
lm_assert_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_lm_assert:

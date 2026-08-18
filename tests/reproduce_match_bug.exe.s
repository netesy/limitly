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
  .string "--- Test 1: Enum with associated values ---"
.align 8
nl:
  .string "
"
.align 8
str_const_1:
  .string "Operation completed"
.align 8
str_const_2:
  .string "Something went wrong"
.align 8
str_const_3:
  .string "Success: Operation completed"
.align 8
str_const_4:
  .string "describeResult(Success) failed"
.align 8
str_const_5:
  .string "Error: Something went wrong"
.align 8
str_const_6:
  .string "describeResult(Error) failed"
.align 8
str_const_7:
  .string "
--- Test 2: Enum with tuple payload ---"
.align 8
str_const_8:
  .string "Hello"
.align 8
str_const_9:
  .string "Quitting application..."
.align 8
str_const_10:
  .string "Quit failed"
.align 8
str_const_11:
  .string "Moving to position (10, 20)"
.align 8
str_const_12:
  .string "Move failed"
.align 8
str_const_13:
  .string "Writing message: Hello"
.align 8
str_const_14:
  .string "Write failed"
.align 8
str_const_15:
  .string "
--- Test 3: Nested enum dispatch ---"
.align 8
str_const_16:
  .string "Red circle"
.align 8
str_const_17:
  .string "Circle(Red) failed"
.align 8
str_const_18:
  .string "Red square"
.align 8
str_const_19:
  .string "Square(Red) failed"
.align 8
str_const_20:
  .string "
=== All tests passed ==="
.align 8
str_const_21:
  .string "Error: "
.align 8
str_const_22:
  .string "Success: "
.align 8
str_const_23:
  .string "Writing message: "
.align 8
str_const_24:
  .string "Moving to position (%s, %s)"
.align 8
str_const_25:
  .string "Quitting application..."
.align 8
str_const_26:
  .string "Other square"
.align 8
str_const_27:
  .string "Red square"
.align 8
str_const_28:
  .string "Unknown color circle"
.align 8
str_const_29:
  .string "Blue circle"
.align 8
str_const_30:
  .string "Green circle"
.align 8
str_const_31:
  .string "Red circle"
.align 8
assert_fail:
  .string "Assertion failed
"
.text
.globl main
.globl _start
_start:
  and rsp, -16
  sub rsp, 32
  call main
  add rsp, 32
  mov rcx, rax
  sub rsp, 32
  call ExitProcess
  add rsp, 32

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
  sub rsp, 56
main_entry:
main_block_0:
  call test
  mov [rbp + -64], rax
  mov rax, 0
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

.globl test
test:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 1128
test_entry:
test_block_0:
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -64]
  mov [rdx], rax
  jmp test_ps_loop_1
test_ps_loop_1:
  mov rax, [rbp + -64]
  mov rax, [rax]
  mov [rbp + -72], rax
  lea rax, [rel str_const_0]
  add rax, [rbp + -72]
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  movzx rax, byte ptr [rax]
  mov [rbp + -88], rax
  mov rax, [rbp + -88]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -96], rax
  mov rax, [rbp + -72]
  add rax, 1
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  mov rdx, [rbp + -64]
  mov [rdx], rax
  mov rax, [rbp + -96]
  test rax, rax
  jne test_ps_done_1
  jmp test_ps_loop_1
test_ps_done_1:
  mov rax, [rbp + -64]
  mov rax, [rax]
  mov [rbp + -112], rax
  mov rax, [rbp + -112]
  sub rax, 1
  mov [rbp + -120], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_0]
  mov r8d, dword ptr [rbp + -120]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -128], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel nl]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -136], rax
  mov rcx, 0
  call describeResult
  mov [rbp + -144], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -152], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -152]
  mov [rdx], rax
  jmp test_ps_loop_2
test_ps_loop_2:
  mov rax, [rbp + -152]
  mov rax, [rax]
  mov [rbp + -160], rax
  mov rax, [rbp + -144]
  add rax, [rbp + -160]
  mov [rbp + -168], rax
  mov rax, [rbp + -168]
  movzx rax, byte ptr [rax]
  mov [rbp + -176], rax
  mov rax, [rbp + -176]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -184], rax
  mov rax, [rbp + -160]
  add rax, 1
  mov [rbp + -192], rax
  mov rax, [rbp + -192]
  mov rdx, [rbp + -152]
  mov [rdx], rax
  mov rax, [rbp + -184]
  test rax, rax
  jne test_ps_done_2
  jmp test_ps_loop_2
test_ps_done_2:
  mov rax, [rbp + -152]
  mov rax, [rax]
  mov [rbp + -200], rax
  mov rax, [rbp + -200]
  sub rax, 1
  mov [rbp + -208], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -144]
  mov r8d, dword ptr [rbp + -208]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -216], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel nl]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -224], rax
  mov rcx, 0
  call describeResult
  mov [rbp + -232], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -240], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -240]
  mov [rdx], rax
  jmp test_ps_loop_3
test_ps_loop_3:
  mov rax, [rbp + -240]
  mov rax, [rax]
  mov [rbp + -248], rax
  mov rax, [rbp + -232]
  add rax, [rbp + -248]
  mov [rbp + -256], rax
  mov rax, [rbp + -256]
  movzx rax, byte ptr [rax]
  mov [rbp + -264], rax
  mov rax, [rbp + -264]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -272], rax
  mov rax, [rbp + -248]
  add rax, 1
  mov [rbp + -280], rax
  mov rax, [rbp + -280]
  mov rdx, [rbp + -240]
  mov [rdx], rax
  mov rax, [rbp + -272]
  test rax, rax
  jne test_ps_done_3
  jmp test_ps_loop_3
test_ps_done_3:
  mov rax, [rbp + -240]
  mov rax, [rax]
  mov [rbp + -288], rax
  mov rax, [rbp + -288]
  sub rax, 1
  mov [rbp + -296], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -232]
  mov r8d, dword ptr [rbp + -296]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -304], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel nl]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -312], rax
  mov rcx, 0
  call describeResult
  mov [rbp + -320], rax
  mov rax, [rbp + -320]
  cmp rax, [rel str_const_3]
  sete al
  movzx eax, al
  mov [rbp + -328], rax
  mov rcx, [rbp + -328]
  lea rdx, [rel str_const_4]
  call lm_assert
  mov [rbp + -336], rax
  mov rcx, 0
  call describeResult
  mov [rbp + -344], rax
  mov rax, [rbp + -344]
  cmp rax, [rel str_const_5]
  sete al
  movzx eax, al
  mov [rbp + -352], rax
  mov rcx, [rbp + -352]
  lea rdx, [rel str_const_6]
  call lm_assert
  mov [rbp + -360], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -368], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -368]
  mov [rdx], rax
  jmp test_ps_loop_4
test_ps_loop_4:
  mov rax, [rbp + -368]
  mov rax, [rax]
  mov [rbp + -376], rax
  lea rax, [rel str_const_7]
  add rax, [rbp + -376]
  mov [rbp + -384], rax
  mov rax, [rbp + -384]
  movzx rax, byte ptr [rax]
  mov [rbp + -392], rax
  mov rax, [rbp + -392]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -400], rax
  mov rax, [rbp + -376]
  add rax, 1
  mov [rbp + -408], rax
  mov rax, [rbp + -408]
  mov rdx, [rbp + -368]
  mov [rdx], rax
  mov rax, [rbp + -400]
  test rax, rax
  jne test_ps_done_4
  jmp test_ps_loop_4
test_ps_done_4:
  mov rax, [rbp + -368]
  mov rax, [rax]
  mov [rbp + -416], rax
  mov rax, [rbp + -416]
  sub rax, 1
  mov [rbp + -424], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_7]
  mov r8d, dword ptr [rbp + -424]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -432], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel nl]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -440], rax
  mov rcx, 0
  call processMessage
  mov [rbp + -448], rax
  mov rcx, 2
  call lm_tuple_new
  mov [rbp + -456], rax
  mov rcx, [rbp + -456]
  mov rdx, 0
  mov r8, 10
  call lm_tuple_set
  mov [rbp + -464], rax
  mov rcx, [rbp + -456]
  mov rdx, 1
  mov r8, 20
  call lm_tuple_set
  mov [rbp + -472], rax
  mov rcx, 0
  call processMessage
  mov [rbp + -480], rax
  mov rcx, 0
  call processMessage
  mov [rbp + -488], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -496], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -496]
  mov [rdx], rax
  jmp test_ps_loop_5
test_ps_loop_5:
  mov rax, [rbp + -496]
  mov rax, [rax]
  mov [rbp + -504], rax
  mov rax, [rbp + -448]
  add rax, [rbp + -504]
  mov [rbp + -512], rax
  mov rax, [rbp + -512]
  movzx rax, byte ptr [rax]
  mov [rbp + -520], rax
  mov rax, [rbp + -520]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -528], rax
  mov rax, [rbp + -504]
  add rax, 1
  mov [rbp + -536], rax
  mov rax, [rbp + -536]
  mov rdx, [rbp + -496]
  mov [rdx], rax
  mov rax, [rbp + -528]
  test rax, rax
  jne test_ps_done_5
  jmp test_ps_loop_5
test_ps_done_5:
  mov rax, [rbp + -496]
  mov rax, [rax]
  mov [rbp + -544], rax
  mov rax, [rbp + -544]
  sub rax, 1
  mov [rbp + -552], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -448]
  mov r8d, dword ptr [rbp + -552]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -560], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel nl]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -568], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -576], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -576]
  mov [rdx], rax
  jmp test_ps_loop_6
test_ps_loop_6:
  mov rax, [rbp + -576]
  mov rax, [rax]
  mov [rbp + -584], rax
  mov rax, [rbp + -480]
  add rax, [rbp + -584]
  mov [rbp + -592], rax
  mov rax, [rbp + -592]
  movzx rax, byte ptr [rax]
  mov [rbp + -600], rax
  mov rax, [rbp + -600]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -608], rax
  mov rax, [rbp + -584]
  add rax, 1
  mov [rbp + -616], rax
  mov rax, [rbp + -616]
  mov rdx, [rbp + -576]
  mov [rdx], rax
  mov rax, [rbp + -608]
  test rax, rax
  jne test_ps_done_6
  jmp test_ps_loop_6
test_ps_done_6:
  mov rax, [rbp + -576]
  mov rax, [rax]
  mov [rbp + -624], rax
  mov rax, [rbp + -624]
  sub rax, 1
  mov [rbp + -632], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -480]
  mov r8d, dword ptr [rbp + -632]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -640], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel nl]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -648], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -656], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -656]
  mov [rdx], rax
  jmp test_ps_loop_7
test_ps_loop_7:
  mov rax, [rbp + -656]
  mov rax, [rax]
  mov [rbp + -664], rax
  mov rax, [rbp + -488]
  add rax, [rbp + -664]
  mov [rbp + -672], rax
  mov rax, [rbp + -672]
  movzx rax, byte ptr [rax]
  mov [rbp + -680], rax
  mov rax, [rbp + -680]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -688], rax
  mov rax, [rbp + -664]
  add rax, 1
  mov [rbp + -696], rax
  mov rax, [rbp + -696]
  mov rdx, [rbp + -656]
  mov [rdx], rax
  mov rax, [rbp + -688]
  test rax, rax
  jne test_ps_done_7
  jmp test_ps_loop_7
test_ps_done_7:
  mov rax, [rbp + -656]
  mov rax, [rax]
  mov [rbp + -704], rax
  mov rax, [rbp + -704]
  sub rax, 1
  mov [rbp + -712], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -488]
  mov r8d, dword ptr [rbp + -712]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -720], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel nl]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -728], rax
  mov rax, [rbp + -448]
  cmp rax, [rel str_const_9]
  sete al
  movzx eax, al
  mov [rbp + -736], rax
  mov rcx, [rbp + -736]
  lea rdx, [rel str_const_10]
  call lm_assert
  mov [rbp + -744], rax
  mov rax, [rbp + -480]
  cmp rax, [rel str_const_11]
  sete al
  movzx eax, al
  mov [rbp + -752], rax
  mov rcx, [rbp + -752]
  lea rdx, [rel str_const_12]
  call lm_assert
  mov [rbp + -760], rax
  mov rax, [rbp + -488]
  cmp rax, [rel str_const_13]
  sete al
  movzx eax, al
  mov [rbp + -768], rax
  mov rcx, [rbp + -768]
  lea rdx, [rel str_const_14]
  call lm_assert
  mov [rbp + -776], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -784], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -784]
  mov [rdx], rax
  jmp test_ps_loop_8
test_ps_loop_8:
  mov rax, [rbp + -784]
  mov rax, [rax]
  mov [rbp + -792], rax
  lea rax, [rel str_const_15]
  add rax, [rbp + -792]
  mov [rbp + -800], rax
  mov rax, [rbp + -800]
  movzx rax, byte ptr [rax]
  mov [rbp + -808], rax
  mov rax, [rbp + -808]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -816], rax
  mov rax, [rbp + -792]
  add rax, 1
  mov [rbp + -824], rax
  mov rax, [rbp + -824]
  mov rdx, [rbp + -784]
  mov [rdx], rax
  mov rax, [rbp + -816]
  test rax, rax
  jne test_ps_done_8
  jmp test_ps_loop_8
test_ps_done_8:
  mov rax, [rbp + -784]
  mov rax, [rax]
  mov [rbp + -832], rax
  mov rax, [rbp + -832]
  sub rax, 1
  mov [rbp + -840], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_15]
  mov r8d, dword ptr [rbp + -840]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -848], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel nl]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -856], rax
  mov rcx, 0
  call describeShape
  mov [rbp + -864], rax
  mov rcx, 0
  call describeShape
  mov [rbp + -872], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -880], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -880]
  mov [rdx], rax
  jmp test_ps_loop_9
test_ps_loop_9:
  mov rax, [rbp + -880]
  mov rax, [rax]
  mov [rbp + -888], rax
  mov rax, [rbp + -864]
  add rax, [rbp + -888]
  mov [rbp + -896], rax
  mov rax, [rbp + -896]
  movzx rax, byte ptr [rax]
  mov [rbp + -904], rax
  mov rax, [rbp + -904]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -912], rax
  mov rax, [rbp + -888]
  add rax, 1
  mov [rbp + -920], rax
  mov rax, [rbp + -920]
  mov rdx, [rbp + -880]
  mov [rdx], rax
  mov rax, [rbp + -912]
  test rax, rax
  jne test_ps_done_9
  jmp test_ps_loop_9
test_ps_done_9:
  mov rax, [rbp + -880]
  mov rax, [rax]
  mov [rbp + -928], rax
  mov rax, [rbp + -928]
  sub rax, 1
  mov [rbp + -936], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -864]
  mov r8d, dword ptr [rbp + -936]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -944], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel nl]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -952], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -960], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -960]
  mov [rdx], rax
  jmp test_ps_loop_10
test_ps_loop_10:
  mov rax, [rbp + -960]
  mov rax, [rax]
  mov [rbp + -968], rax
  mov rax, [rbp + -872]
  add rax, [rbp + -968]
  mov [rbp + -976], rax
  mov rax, [rbp + -976]
  movzx rax, byte ptr [rax]
  mov [rbp + -984], rax
  mov rax, [rbp + -984]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -992], rax
  mov rax, [rbp + -968]
  add rax, 1
  mov [rbp + -1000], rax
  mov rax, [rbp + -1000]
  mov rdx, [rbp + -960]
  mov [rdx], rax
  mov rax, [rbp + -992]
  test rax, rax
  jne test_ps_done_10
  jmp test_ps_loop_10
test_ps_done_10:
  mov rax, [rbp + -960]
  mov rax, [rax]
  mov [rbp + -1008], rax
  mov rax, [rbp + -1008]
  sub rax, 1
  mov [rbp + -1016], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -872]
  mov r8d, dword ptr [rbp + -1016]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -1024], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel nl]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -1032], rax
  mov rax, [rbp + -864]
  cmp rax, [rel str_const_16]
  sete al
  movzx eax, al
  mov [rbp + -1040], rax
  mov rcx, [rbp + -1040]
  lea rdx, [rel str_const_17]
  call lm_assert
  mov [rbp + -1048], rax
  mov rax, [rbp + -872]
  cmp rax, [rel str_const_18]
  sete al
  movzx eax, al
  mov [rbp + -1056], rax
  mov rcx, [rbp + -1056]
  lea rdx, [rel str_const_19]
  call lm_assert
  mov [rbp + -1064], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -1072], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -1072]
  mov [rdx], rax
  jmp test_ps_loop_11
test_ps_loop_11:
  mov rax, [rbp + -1072]
  mov rax, [rax]
  mov [rbp + -1080], rax
  lea rax, [rel str_const_20]
  add rax, [rbp + -1080]
  mov [rbp + -1088], rax
  mov rax, [rbp + -1088]
  movzx rax, byte ptr [rax]
  mov [rbp + -1096], rax
  mov rax, [rbp + -1096]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -1104], rax
  mov rax, [rbp + -1080]
  add rax, 1
  mov [rbp + -1112], rax
  mov rax, [rbp + -1112]
  mov rdx, [rbp + -1072]
  mov [rdx], rax
  mov rax, [rbp + -1104]
  test rax, rax
  jne test_ps_done_11
  jmp test_ps_loop_11
test_ps_done_11:
  mov rax, [rbp + -1072]
  mov rax, [rax]
  mov [rbp + -1120], rax
  mov rax, [rbp + -1120]
  sub rax, 1
  mov [rbp + -1128], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_20]
  mov r8d, dword ptr [rbp + -1128]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -1136], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel nl]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -1144], rax
  mov rax, 0
  jmp test_epilogue
test_epilogue:
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
.Lfunc_end_test:

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
  sub rsp, 88
  mov [rbp + -64], rcx
describeResult_entry:
describeResult_block_0:
  jmp describeResult_block_1
describeResult_block_1:
  mov rax, 0
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -72], rax
  mov rax, [rbp + -72]
  test rax, rax
  jne describeResult_block_5
  jmp describeResult_block_7
describeResult_block_5:
  jmp describeResult_block_5
  jmp describeResult_block_18
describeResult_block_7:
  mov rax, 0
  cmp rax, 1
  sete al
  movzx eax, al
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  test rax, rax
  jne describeResult_block_11
  jmp describeResult_block_13
describeResult_block_11:
  jmp describeResult_block_11
  jmp describeResult_block_14
describeResult_block_13:
  mov rax, 0
  jmp describeResult_epilogue
describeResult_block_14:
  lea rcx, [rel str_const_21]
  mov rdx, 0
  call lm_str_concat
  mov [rbp + -88], rax
  mov rax, [rbp + -88]
  jmp describeResult_epilogue
describeResult_block_18:
  lea rcx, [rel str_const_22]
  mov rdx, 0
  call lm_str_concat
  mov [rbp + -96], rax
  mov rax, [rbp + -96]
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
  sub rsp, 136
  mov [rbp + -64], rcx
processMessage_entry:
processMessage_block_0:
  jmp processMessage_block_1
processMessage_block_1:
  mov rax, 0
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -72], rax
  mov rax, [rbp + -72]
  test rax, rax
  jne processMessage_block_5
  jmp processMessage_block_6
processMessage_block_5:
  jmp processMessage_block_5
  jmp processMessage_block_37
processMessage_block_6:
  mov rax, 0
  cmp rax, 1
  sete al
  movzx eax, al
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  test rax, rax
  jne processMessage_block_10
  jmp processMessage_block_16
processMessage_block_10:
  jmp processMessage_block_10
  mov rcx, 0
  mov rdx, 0
  call lm_tuple_get
  mov [rbp + -88], rax
  mov rcx, 0
  mov rdx, 1
  call lm_tuple_get
  mov [rbp + -96], rax
  jmp processMessage_block_27
processMessage_block_16:
  mov rax, 0
  cmp rax, 2
  sete al
  movzx eax, al
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  test rax, rax
  jne processMessage_block_20
  jmp processMessage_block_22
processMessage_block_20:
  jmp processMessage_block_20
  jmp processMessage_block_23
processMessage_block_22:
  mov rax, 0
  jmp processMessage_epilogue
processMessage_block_23:
  lea rcx, [rel str_const_23]
  mov rdx, 0
  call lm_str_concat
  mov [rbp + -112], rax
  mov rax, [rbp + -112]
  jmp processMessage_epilogue
processMessage_block_27:
  mov rcx, 0
  mov rdx, 0
  call lm_tuple_get
  mov [rbp + -120], rax
  mov rcx, 0
  mov rdx, 1
  call lm_tuple_get
  mov [rbp + -128], rax
  lea rcx, [rel str_const_24]
  mov rdx, [rbp + -120]
  call lm_rt_str_format
  mov [rbp + -136], rax
  mov rcx, [rbp + -136]
  mov rdx, [rbp + -128]
  call lm_rt_str_format
  mov [rbp + -144], rax
  mov rax, [rbp + -144]
  jmp processMessage_epilogue
processMessage_block_37:
  mov rax, [rel str_const_25]
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

.globl describeShape
describeShape:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
  mov [rbp + -64], rcx
describeShape_entry:
describeShape_block_0:
  jmp describeShape_block_1
describeShape_block_1:
  mov rax, 0
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -72], rax
  mov rax, [rbp + -72]
  test rax, rax
  jne describeShape_block_5
  jmp describeShape_block_7
describeShape_block_5:
  jmp describeShape_block_5
  jmp describeShape_block_26
describeShape_block_7:
  mov rax, 0
  cmp rax, 1
  sete al
  movzx eax, al
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  test rax, rax
  jne describeShape_block_11
  jmp describeShape_block_13
describeShape_block_11:
  jmp describeShape_block_11
  jmp describeShape_block_14
describeShape_block_13:
  mov rax, 0
  jmp describeShape_epilogue
describeShape_block_14:
  jmp describeShape_block_16
describeShape_block_16:
  mov rax, 0
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -88], rax
  mov rax, [rbp + -88]
  test rax, rax
  jne describeShape_block_20
  jmp describeShape_block_21
describeShape_block_20:
  jmp describeShape_block_20
  jmp describeShape_block_24
describeShape_block_21:
  jmp describeShape_block_22
describeShape_block_22:
  mov rax, [rel str_const_26]
  jmp describeShape_epilogue
describeShape_block_24:
  mov rax, [rel str_const_27]
  jmp describeShape_epilogue
describeShape_block_26:
  jmp describeShape_block_28
describeShape_block_28:
  mov rax, 0
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -96], rax
  mov rax, [rbp + -96]
  test rax, rax
  jne describeShape_block_32
  jmp describeShape_block_33
describeShape_block_32:
  jmp describeShape_block_32
  jmp describeShape_block_50
describeShape_block_33:
  mov rax, 0
  cmp rax, 1
  sete al
  movzx eax, al
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  test rax, rax
  jne describeShape_block_37
  jmp describeShape_block_38
describeShape_block_37:
  jmp describeShape_block_37
  jmp describeShape_block_48
describeShape_block_38:
  mov rax, 0
  cmp rax, 2
  sete al
  movzx eax, al
  mov [rbp + -112], rax
  mov rax, [rbp + -112]
  test rax, rax
  jne describeShape_block_42
  jmp describeShape_block_43
describeShape_block_42:
  jmp describeShape_block_42
  jmp describeShape_block_46
describeShape_block_43:
  jmp describeShape_block_44
describeShape_block_44:
  mov rax, [rel str_const_28]
  jmp describeShape_epilogue
describeShape_block_46:
  mov rax, [rel str_const_29]
  jmp describeShape_epilogue
describeShape_block_48:
  mov rax, [rel str_const_30]
  jmp describeShape_epilogue
describeShape_block_50:
  mov rax, [rel str_const_31]
  jmp describeShape_epilogue
describeShape_epilogue:
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
.Lfunc_end_describeShape:

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
  mov rax, [rbp + -64]
  test rax, rax
  jne lm_assert_pass
  jmp lm_assert_fail
lm_assert_fail:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel assert_fail]
  mov r8d, dword ptr 17
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -80], rax
  movq $50397203, rax
  movq rax, [rbp + -88]
  mov rax, 0
  jmp lm_assert_epilogue
lm_assert_pass:
  mov rax, 0
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

.globl lm_tuple_new
lm_tuple_new:
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
lm_tuple_new_entry:
  mov rax, [rbp + -64]
  add rax, 1
  mov [rbp + -72], rax
  mov rax, [rbp + -72]
  imul rax, 8
  mov [rbp + -80], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, [rbp + -80]
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -88], rax
  add rsp, 48
  mov [rbp + -88], rax
  mov rax, [rbp + -64]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  mov rax, [rbp + -88]
  jmp lm_tuple_new_epilogue
lm_tuple_new_epilogue:
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
.Lfunc_end_lm_tuple_new:

.globl lm_tuple_set
lm_tuple_set:
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
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
lm_tuple_set_entry:
  mov rax, [rbp + -72]
  add rax, 1
  mov [rbp + -88], rax
  mov rax, [rbp + -88]
  imul rax, 8
  mov [rbp + -96], rax
  mov rax, [rbp + -64]
  add rax, [rbp + -96]
  mov [rbp + -104], rax
  mov rax, [rbp + -80]
  mov rdx, [rbp + -104]
  mov [rdx], rax
  mov rax, 0
  jmp lm_tuple_set_epilogue
lm_tuple_set_epilogue:
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
.Lfunc_end_lm_tuple_set:

.globl lm_str_concat
lm_str_concat:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 408
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
lm_str_concat_entry:
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -80]
  mov [rdx], rax
  mov rax, 0
  mov rdx, [rbp + -88]
  mov [rdx], rax
  jmp lm_str_concat_l1
lm_str_concat_l1:
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -96], rax
  mov rax, [rbp + -64]
  add rax, [rbp + -96]
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  movzx rax, byte ptr [rax]
  mov [rbp + -112], rax
  mov rax, [rbp + -96]
  add rax, 1
  mov [rbp + -120], rax
  mov rax, [rbp + -120]
  mov rdx, [rbp + -80]
  mov [rdx], rax
  mov rax, [rbp + -112]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -128], rax
  mov rax, [rbp + -128]
  test rax, rax
  jne lm_str_concat_l1d
  jmp lm_str_concat_l1
lm_str_concat_l1d:
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -136], rax
  mov rax, [rbp + -136]
  sub rax, 1
  mov [rbp + -144], rax
  mov rax, [rbp + -144]
  mov rdx, [rbp + -80]
  mov [rdx], rax
  jmp lm_str_concat_l2
lm_str_concat_l2:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -152], rax
  mov rax, [rbp + -72]
  add rax, [rbp + -152]
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  movzx rax, byte ptr [rax]
  mov [rbp + -168], rax
  mov rax, [rbp + -152]
  add rax, 1
  mov [rbp + -176], rax
  mov rax, [rbp + -176]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  mov rax, [rbp + -168]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -184], rax
  mov rax, [rbp + -184]
  test rax, rax
  jne lm_str_concat_l2d
  jmp lm_str_concat_l2
lm_str_concat_l2d:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -192], rax
  mov rax, [rbp + -192]
  sub rax, 1
  mov [rbp + -200], rax
  mov rax, [rbp + -200]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  jmp lm_str_concat_alloc
lm_str_concat_alloc:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -208], rax
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -216], rax
  mov rax, [rbp + -216]
  add rax, [rbp + -208]
  mov [rbp + -224], rax
  mov rax, [rbp + -224]
  add rax, 1
  mov [rbp + -232], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, [rbp + -232]
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -240], rax
  add rsp, 48
  mov [rbp + -240], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -248], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -248]
  mov [rdx], rax
  jmp lm_str_concat_c1c
lm_str_concat_c1c:
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -256], rax
  mov rax, [rbp + -248]
  mov rax, [rax]
  mov [rbp + -264], rax
  mov rax, [rbp + -264]
  cmp rax, [rbp + -256]
  sete al
  movzx eax, al
  mov [rbp + -272], rax
  mov rax, [rbp + -272]
  test rax, rax
  jne lm_str_concat_c2i
  jmp lm_str_concat_c1a
lm_str_concat_c1a:
  mov rax, [rbp + -248]
  mov rax, [rax]
  mov [rbp + -280], rax
  mov rax, [rbp + -240]
  add rax, [rbp + -280]
  mov [rbp + -288], rax
  mov rax, [rbp + -64]
  add rax, [rbp + -280]
  mov [rbp + -296], rax
  mov rax, [rbp + -296]
  movzx rax, byte ptr [rax]
  mov [rbp + -304], rax
  mov rax, [rbp + -304]
  mov rdx, [rbp + -288]
  mov byte ptr [rdx], al
  mov rax, [rbp + -280]
  add rax, 1
  mov [rbp + -312], rax
  mov rax, [rbp + -312]
  mov rdx, [rbp + -248]
  mov [rdx], rax
  jmp lm_str_concat_c1c
lm_str_concat_c2i:
  mov rax, 0
  mov rdx, [rbp + -248]
  mov [rdx], rax
  jmp lm_str_concat_c2c
lm_str_concat_c2c:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -320], rax
  mov rax, [rbp + -248]
  mov rax, [rax]
  mov [rbp + -328], rax
  mov rax, [rbp + -328]
  cmp rax, [rbp + -320]
  sete al
  movzx eax, al
  mov [rbp + -336], rax
  mov rax, [rbp + -336]
  test rax, rax
  jne lm_str_concat_done
  jmp lm_str_concat_c2a
lm_str_concat_c2a:
  mov rax, [rbp + -248]
  mov rax, [rax]
  mov [rbp + -344], rax
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -352], rax
  mov rax, [rbp + -352]
  add rax, [rbp + -344]
  mov [rbp + -360], rax
  mov rax, [rbp + -240]
  add rax, [rbp + -360]
  mov [rbp + -368], rax
  mov rax, [rbp + -72]
  add rax, [rbp + -344]
  mov [rbp + -376], rax
  mov rax, [rbp + -376]
  movzx rax, byte ptr [rax]
  mov [rbp + -384], rax
  mov rax, [rbp + -384]
  mov rdx, [rbp + -368]
  mov byte ptr [rdx], al
  mov rax, [rbp + -344]
  add rax, 1
  mov [rbp + -392], rax
  mov rax, [rbp + -392]
  mov rdx, [rbp + -248]
  mov [rdx], rax
  jmp lm_str_concat_c2c
lm_str_concat_done:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -400], rax
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -408], rax
  mov rax, [rbp + -408]
  add rax, [rbp + -400]
  mov [rbp + -416], rax
  mov rax, [rbp + -240]
  add rax, [rbp + -416]
  mov [rbp + -424], rax
  mov rax, 0
  mov rdx, [rbp + -424]
  mov byte ptr [rdx], al
  mov rax, [rbp + -240]
  jmp lm_str_concat_epilogue
lm_str_concat_epilogue:
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
.Lfunc_end_lm_str_concat:

.globl lm_tuple_get
lm_tuple_get:
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
  mov [rbp + -72], rdx
lm_tuple_get_entry:
  mov rax, [rbp + -72]
  add rax, 1
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  imul rax, 8
  mov [rbp + -88], rax
  mov rax, [rbp + -64]
  add rax, [rbp + -88]
  mov [rbp + -96], rax
  mov rax, [rbp + -96]
  mov rax, [rax]
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  jmp lm_tuple_get_epilogue
lm_tuple_get_epilogue:
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
.Lfunc_end_lm_tuple_get:

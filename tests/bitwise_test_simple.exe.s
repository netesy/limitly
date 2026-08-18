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
  .string "a: "
.align 8
nl:
  .string "
"
.align 8
str_const_1:
  .string "b: "
.align 8
str_const_2:
  .string "a | b: "
.align 8
str_const_3:
  .string "a & b: "
.align 8
str_const_4:
  .string "a ^ 255: "
.align 8
str_const_5:
  .string "1 << 4: "
.align 8
str_const_6:
  .string "16 >> 2: "
.align 8
str_const_7:
  .string "~0: "
.align 8
str_const_8:
  .string "0x1234: "
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
  sub rsp, 808
main_entry:
main_block_0:
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -64]
  mov [rdx], rax
  jmp main_ps_loop_1
main_ps_loop_1:
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
  jne main_ps_done_1
  jmp main_ps_loop_1
main_ps_done_1:
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
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -144], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -144]
  mov [rdx], rax
  jmp main_ps_loop_2
main_ps_loop_2:
  mov rax, [rbp + -144]
  mov rax, [rax]
  mov [rbp + -152], rax
  lea rax, [rel str_const_1]
  add rax, [rbp + -152]
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  movzx rax, byte ptr [rax]
  mov [rbp + -168], rax
  mov rax, [rbp + -168]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -176], rax
  mov rax, [rbp + -152]
  add rax, 1
  mov [rbp + -184], rax
  mov rax, [rbp + -184]
  mov rdx, [rbp + -144]
  mov [rdx], rax
  mov rax, [rbp + -176]
  test rax, rax
  jne main_ps_done_2
  jmp main_ps_loop_2
main_ps_done_2:
  mov rax, [rbp + -144]
  mov rax, [rax]
  mov [rbp + -192], rax
  mov rax, [rbp + -192]
  sub rax, 1
  mov [rbp + -200], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_1]
  mov r8d, dword ptr [rbp + -200]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -208], rax
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
  mov [rbp + -216], rax
  mov rax, 15
  or rax, 240
  mov [rbp + -224], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -232], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -232]
  mov [rdx], rax
  jmp main_ps_loop_3
main_ps_loop_3:
  mov rax, [rbp + -232]
  mov rax, [rax]
  mov [rbp + -240], rax
  lea rax, [rel str_const_2]
  add rax, [rbp + -240]
  mov [rbp + -248], rax
  mov rax, [rbp + -248]
  movzx rax, byte ptr [rax]
  mov [rbp + -256], rax
  mov rax, [rbp + -256]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -264], rax
  mov rax, [rbp + -240]
  add rax, 1
  mov [rbp + -272], rax
  mov rax, [rbp + -272]
  mov rdx, [rbp + -232]
  mov [rdx], rax
  mov rax, [rbp + -264]
  test rax, rax
  jne main_ps_done_3
  jmp main_ps_loop_3
main_ps_done_3:
  mov rax, [rbp + -232]
  mov rax, [rax]
  mov [rbp + -280], rax
  mov rax, [rbp + -280]
  sub rax, 1
  mov [rbp + -288], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_2]
  mov r8d, dword ptr [rbp + -288]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -296], rax
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
  mov [rbp + -304], rax
  mov rax, 15
  and rax, 240
  mov [rbp + -312], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -320], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -320]
  mov [rdx], rax
  jmp main_ps_loop_4
main_ps_loop_4:
  mov rax, [rbp + -320]
  mov rax, [rax]
  mov [rbp + -328], rax
  lea rax, [rel str_const_3]
  add rax, [rbp + -328]
  mov [rbp + -336], rax
  mov rax, [rbp + -336]
  movzx rax, byte ptr [rax]
  mov [rbp + -344], rax
  mov rax, [rbp + -344]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -352], rax
  mov rax, [rbp + -328]
  add rax, 1
  mov [rbp + -360], rax
  mov rax, [rbp + -360]
  mov rdx, [rbp + -320]
  mov [rdx], rax
  mov rax, [rbp + -352]
  test rax, rax
  jne main_ps_done_4
  jmp main_ps_loop_4
main_ps_done_4:
  mov rax, [rbp + -320]
  mov rax, [rax]
  mov [rbp + -368], rax
  mov rax, [rbp + -368]
  sub rax, 1
  mov [rbp + -376], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_3]
  mov r8d, dword ptr [rbp + -376]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -384], rax
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
  mov [rbp + -392], rax
  mov rax, 15
  xor rax, 255
  mov [rbp + -400], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -408], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -408]
  mov [rdx], rax
  jmp main_ps_loop_5
main_ps_loop_5:
  mov rax, [rbp + -408]
  mov rax, [rax]
  mov [rbp + -416], rax
  lea rax, [rel str_const_4]
  add rax, [rbp + -416]
  mov [rbp + -424], rax
  mov rax, [rbp + -424]
  movzx rax, byte ptr [rax]
  mov [rbp + -432], rax
  mov rax, [rbp + -432]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -440], rax
  mov rax, [rbp + -416]
  add rax, 1
  mov [rbp + -448], rax
  mov rax, [rbp + -448]
  mov rdx, [rbp + -408]
  mov [rdx], rax
  mov rax, [rbp + -440]
  test rax, rax
  jne main_ps_done_5
  jmp main_ps_loop_5
main_ps_done_5:
  mov rax, [rbp + -408]
  mov rax, [rax]
  mov [rbp + -456], rax
  mov rax, [rbp + -456]
  sub rax, 1
  mov [rbp + -464], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_4]
  mov r8d, dword ptr [rbp + -464]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -472], rax
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
  mov [rbp + -480], rax
  movq 1, rax
  movq 4, rcx
  shlq %cl, rax
  movq rax, [rbp + -488]
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -496], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -496]
  mov [rdx], rax
  jmp main_ps_loop_6
main_ps_loop_6:
  mov rax, [rbp + -496]
  mov rax, [rax]
  mov [rbp + -504], rax
  lea rax, [rel str_const_5]
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
  jne main_ps_done_6
  jmp main_ps_loop_6
main_ps_done_6:
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
  lea rdx, [rel str_const_5]
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
  movq 16, rax
  movq 2, rcx
  shrq %cl, rax
  movq rax, [rbp + -576]
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -584], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -584]
  mov [rdx], rax
  jmp main_ps_loop_7
main_ps_loop_7:
  mov rax, [rbp + -584]
  mov rax, [rax]
  mov [rbp + -592], rax
  lea rax, [rel str_const_6]
  add rax, [rbp + -592]
  mov [rbp + -600], rax
  mov rax, [rbp + -600]
  movzx rax, byte ptr [rax]
  mov [rbp + -608], rax
  mov rax, [rbp + -608]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -616], rax
  mov rax, [rbp + -592]
  add rax, 1
  mov [rbp + -624], rax
  mov rax, [rbp + -624]
  mov rdx, [rbp + -584]
  mov [rdx], rax
  mov rax, [rbp + -616]
  test rax, rax
  jne main_ps_done_7
  jmp main_ps_loop_7
main_ps_done_7:
  mov rax, [rbp + -584]
  mov rax, [rax]
  mov [rbp + -632], rax
  mov rax, [rbp + -632]
  sub rax, 1
  mov [rbp + -640], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_6]
  mov r8d, dword ptr [rbp + -640]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -648], rax
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
  mov [rbp + -656], rax
  mov rax, 0
  xor rax, 18446744073709551615
  mov [rbp + -664], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -672], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -672]
  mov [rdx], rax
  jmp main_ps_loop_8
main_ps_loop_8:
  mov rax, [rbp + -672]
  mov rax, [rax]
  mov [rbp + -680], rax
  lea rax, [rel str_const_7]
  add rax, [rbp + -680]
  mov [rbp + -688], rax
  mov rax, [rbp + -688]
  movzx rax, byte ptr [rax]
  mov [rbp + -696], rax
  mov rax, [rbp + -696]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -704], rax
  mov rax, [rbp + -680]
  add rax, 1
  mov [rbp + -712], rax
  mov rax, [rbp + -712]
  mov rdx, [rbp + -672]
  mov [rdx], rax
  mov rax, [rbp + -704]
  test rax, rax
  jne main_ps_done_8
  jmp main_ps_loop_8
main_ps_done_8:
  mov rax, [rbp + -672]
  mov rax, [rax]
  mov [rbp + -720], rax
  mov rax, [rbp + -720]
  sub rax, 1
  mov [rbp + -728], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_7]
  mov r8d, dword ptr [rbp + -728]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -736], rax
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
  mov [rbp + -744], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -752], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -752]
  mov [rdx], rax
  jmp main_ps_loop_9
main_ps_loop_9:
  mov rax, [rbp + -752]
  mov rax, [rax]
  mov [rbp + -760], rax
  lea rax, [rel str_const_8]
  add rax, [rbp + -760]
  mov [rbp + -768], rax
  mov rax, [rbp + -768]
  movzx rax, byte ptr [rax]
  mov [rbp + -776], rax
  mov rax, [rbp + -776]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -784], rax
  mov rax, [rbp + -760]
  add rax, 1
  mov [rbp + -792], rax
  mov rax, [rbp + -792]
  mov rdx, [rbp + -752]
  mov [rdx], rax
  mov rax, [rbp + -784]
  test rax, rax
  jne main_ps_done_9
  jmp main_ps_loop_9
main_ps_done_9:
  mov rax, [rbp + -752]
  mov rax, [rax]
  mov [rbp + -800], rax
  mov rax, [rbp + -800]
  sub rax, 1
  mov [rbp + -808], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_8]
  mov r8d, dword ptr [rbp + -808]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -816], rax
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
  mov [rbp + -824], rax
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

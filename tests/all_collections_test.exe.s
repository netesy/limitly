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
str_minus:
  .string "-"
.align 8
str_const_0:
  .string "one"
.align 8
str_const_1:
  .string "two"
.align 8
str_const_2:
  .string "one"
.align 8
str_const_3:
  .string "two"
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
  sub rsp, 1192
main_entry:
main_block_0:
  mov rcx, 2
  call lm_tuple_new
  mov [rbp + -64], rax
  mov rcx, [rbp + -64]
  mov rdx, 0
  mov r8, 10
  call lm_tuple_set
  mov [rbp + -72], rax
  mov rcx, [rbp + -64]
  mov rdx, 1
  mov r8, 20
  call lm_tuple_set
  mov [rbp + -80], rax
  mov rcx, [rbp + -64]
  mov rdx, 0
  call lm_tuple_get
  mov [rbp + -88], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -96], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -96]
  add rax, 31
  mov [rbp + -104], rax
  mov rax, 10
  mov rdx, [rbp + -104]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -112], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -120], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -104]
  mov rdx, [rbp + -120]
  mov [rdx], rax
  mov rax, [rbp + -88]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -128], rax
  mov rax, [rbp + -128]
  test rax, rax
  jne main_pi_neg_1
  jmp main_pi_abs_1
main_pi_neg_1:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_minus]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -136], rax
  mov rax, [rbp + -88]
  neg rax
  mov [rbp + -144], rax
  mov rax, [rbp + -144]
  mov rdx, [rbp + -112]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_abs_1:
  mov rax, [rbp + -88]
  mov rdx, [rbp + -112]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_loop_1:
  mov rax, [rbp + -112]
  mov rax, [rax]
  mov [rbp + -152], rax
  mov rax, [rbp + -152]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -160], rax
  mov rax, [rbp + -152]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -168], rdx
  mov rax, [rbp + -168]
  add rax, 48
  mov [rbp + -176], rax
  mov rax, [rbp + -120]
  mov rax, [rax]
  mov [rbp + -184], rax
  mov rax, [rbp + -184]
  sub rax, 1
  mov [rbp + -192], rax
  mov rax, [rbp + -176]
  mov rdx, [rbp + -192]
  mov byte ptr [rdx], al
  mov rax, [rbp + -160]
  mov rdx, [rbp + -112]
  mov [rdx], rax
  mov rax, [rbp + -192]
  mov rdx, [rbp + -120]
  mov [rdx], rax
  mov rax, [rbp + -160]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -200], rax
  mov rax, [rbp + -200]
  test rax, rax
  jne main_pi_loop_1
  jmp main_pi_emit_1
main_pi_emit_1:
  mov rax, [rbp + -120]
  mov rax, [rax]
  mov [rbp + -208], rax
  mov rax, [rbp + -96]
  add rax, 32
  mov [rbp + -216], rax
  mov rax, [rbp + -216]
  sub rax, [rbp + -208]
  mov [rbp + -224], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -208]
  mov r8d, dword ptr [rbp + -224]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -232], rax
  mov rcx, [rbp + -64]
  mov rdx, 1
  call lm_tuple_get
  mov [rbp + -240], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -248], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -248]
  add rax, 31
  mov [rbp + -256], rax
  mov rax, 10
  mov rdx, [rbp + -256]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -264], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -272], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -256]
  mov rdx, [rbp + -272]
  mov [rdx], rax
  mov rax, [rbp + -240]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -280], rax
  mov rax, [rbp + -280]
  test rax, rax
  jne main_pi_neg_2
  jmp main_pi_abs_2
main_pi_neg_2:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_minus]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -288], rax
  mov rax, [rbp + -240]
  neg rax
  mov [rbp + -296], rax
  mov rax, [rbp + -296]
  mov rdx, [rbp + -264]
  mov [rdx], rax
  jmp main_pi_loop_2
main_pi_abs_2:
  mov rax, [rbp + -240]
  mov rdx, [rbp + -264]
  mov [rdx], rax
  jmp main_pi_loop_2
main_pi_loop_2:
  mov rax, [rbp + -264]
  mov rax, [rax]
  mov [rbp + -304], rax
  mov rax, [rbp + -304]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -312], rax
  mov rax, [rbp + -304]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -320], rdx
  mov rax, [rbp + -320]
  add rax, 48
  mov [rbp + -328], rax
  mov rax, [rbp + -272]
  mov rax, [rax]
  mov [rbp + -336], rax
  mov rax, [rbp + -336]
  sub rax, 1
  mov [rbp + -344], rax
  mov rax, [rbp + -328]
  mov rdx, [rbp + -344]
  mov byte ptr [rdx], al
  mov rax, [rbp + -312]
  mov rdx, [rbp + -264]
  mov [rdx], rax
  mov rax, [rbp + -344]
  mov rdx, [rbp + -272]
  mov [rdx], rax
  mov rax, [rbp + -312]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -352], rax
  mov rax, [rbp + -352]
  test rax, rax
  jne main_pi_loop_2
  jmp main_pi_emit_2
main_pi_emit_2:
  mov rax, [rbp + -272]
  mov rax, [rax]
  mov [rbp + -360], rax
  mov rax, [rbp + -248]
  add rax, 32
  mov [rbp + -368], rax
  mov rax, [rbp + -368]
  sub rax, [rbp + -360]
  mov [rbp + -376], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -360]
  mov r8d, dword ptr [rbp + -376]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -384], rax
  mov rcx, 0
  call lm_list_new
  mov [rbp + -392], rax
  mov rcx, [rbp + -392]
  mov rdx, 100
  call lm_list_append
  mov [rbp + -400], rax
  mov rcx, [rbp + -392]
  mov rdx, 200
  call lm_list_append
  mov [rbp + -408], rax
  mov rcx, [rbp + -392]
  mov rdx, 300
  call lm_list_append
  mov [rbp + -416], rax
  mov rcx, [rbp + -392]
  mov rdx, 0
  call lm_list_get
  mov [rbp + -424], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -432], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -432]
  add rax, 31
  mov [rbp + -440], rax
  mov rax, 10
  mov rdx, [rbp + -440]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -448], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -456], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -440]
  mov rdx, [rbp + -456]
  mov [rdx], rax
  mov rax, [rbp + -424]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -464], rax
  mov rax, [rbp + -464]
  test rax, rax
  jne main_pi_neg_3
  jmp main_pi_abs_3
main_pi_neg_3:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_minus]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -472], rax
  mov rax, [rbp + -424]
  neg rax
  mov [rbp + -480], rax
  mov rax, [rbp + -480]
  mov rdx, [rbp + -448]
  mov [rdx], rax
  jmp main_pi_loop_3
main_pi_abs_3:
  mov rax, [rbp + -424]
  mov rdx, [rbp + -448]
  mov [rdx], rax
  jmp main_pi_loop_3
main_pi_loop_3:
  mov rax, [rbp + -448]
  mov rax, [rax]
  mov [rbp + -488], rax
  mov rax, [rbp + -488]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -496], rax
  mov rax, [rbp + -488]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -504], rdx
  mov rax, [rbp + -504]
  add rax, 48
  mov [rbp + -512], rax
  mov rax, [rbp + -456]
  mov rax, [rax]
  mov [rbp + -520], rax
  mov rax, [rbp + -520]
  sub rax, 1
  mov [rbp + -528], rax
  mov rax, [rbp + -512]
  mov rdx, [rbp + -528]
  mov byte ptr [rdx], al
  mov rax, [rbp + -496]
  mov rdx, [rbp + -448]
  mov [rdx], rax
  mov rax, [rbp + -528]
  mov rdx, [rbp + -456]
  mov [rdx], rax
  mov rax, [rbp + -496]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -536], rax
  mov rax, [rbp + -536]
  test rax, rax
  jne main_pi_loop_3
  jmp main_pi_emit_3
main_pi_emit_3:
  mov rax, [rbp + -456]
  mov rax, [rax]
  mov [rbp + -544], rax
  mov rax, [rbp + -432]
  add rax, 32
  mov [rbp + -552], rax
  mov rax, [rbp + -552]
  sub rax, [rbp + -544]
  mov [rbp + -560], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -544]
  mov r8d, dword ptr [rbp + -560]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -568], rax
  mov rcx, [rbp + -392]
  mov rdx, 1
  call lm_list_get
  mov [rbp + -576], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -584], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -584]
  add rax, 31
  mov [rbp + -592], rax
  mov rax, 10
  mov rdx, [rbp + -592]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -600], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -608], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -592]
  mov rdx, [rbp + -608]
  mov [rdx], rax
  mov rax, [rbp + -576]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -616], rax
  mov rax, [rbp + -616]
  test rax, rax
  jne main_pi_neg_4
  jmp main_pi_abs_4
main_pi_neg_4:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_minus]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -624], rax
  mov rax, [rbp + -576]
  neg rax
  mov [rbp + -632], rax
  mov rax, [rbp + -632]
  mov rdx, [rbp + -600]
  mov [rdx], rax
  jmp main_pi_loop_4
main_pi_abs_4:
  mov rax, [rbp + -576]
  mov rdx, [rbp + -600]
  mov [rdx], rax
  jmp main_pi_loop_4
main_pi_loop_4:
  mov rax, [rbp + -600]
  mov rax, [rax]
  mov [rbp + -640], rax
  mov rax, [rbp + -640]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -648], rax
  mov rax, [rbp + -640]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -656], rdx
  mov rax, [rbp + -656]
  add rax, 48
  mov [rbp + -664], rax
  mov rax, [rbp + -608]
  mov rax, [rax]
  mov [rbp + -672], rax
  mov rax, [rbp + -672]
  sub rax, 1
  mov [rbp + -680], rax
  mov rax, [rbp + -664]
  mov rdx, [rbp + -680]
  mov byte ptr [rdx], al
  mov rax, [rbp + -648]
  mov rdx, [rbp + -600]
  mov [rdx], rax
  mov rax, [rbp + -680]
  mov rdx, [rbp + -608]
  mov [rdx], rax
  mov rax, [rbp + -648]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -688], rax
  mov rax, [rbp + -688]
  test rax, rax
  jne main_pi_loop_4
  jmp main_pi_emit_4
main_pi_emit_4:
  mov rax, [rbp + -608]
  mov rax, [rax]
  mov [rbp + -696], rax
  mov rax, [rbp + -584]
  add rax, 32
  mov [rbp + -704], rax
  mov rax, [rbp + -704]
  sub rax, [rbp + -696]
  mov [rbp + -712], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -696]
  mov r8d, dword ptr [rbp + -712]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -720], rax
  mov rcx, [rbp + -392]
  mov rdx, 2
  call lm_list_get
  mov [rbp + -728], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -736], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -736]
  add rax, 31
  mov [rbp + -744], rax
  mov rax, 10
  mov rdx, [rbp + -744]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -752], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -760], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -744]
  mov rdx, [rbp + -760]
  mov [rdx], rax
  mov rax, [rbp + -728]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -768], rax
  mov rax, [rbp + -768]
  test rax, rax
  jne main_pi_neg_5
  jmp main_pi_abs_5
main_pi_neg_5:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_minus]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -776], rax
  mov rax, [rbp + -728]
  neg rax
  mov [rbp + -784], rax
  mov rax, [rbp + -784]
  mov rdx, [rbp + -752]
  mov [rdx], rax
  jmp main_pi_loop_5
main_pi_abs_5:
  mov rax, [rbp + -728]
  mov rdx, [rbp + -752]
  mov [rdx], rax
  jmp main_pi_loop_5
main_pi_loop_5:
  mov rax, [rbp + -752]
  mov rax, [rax]
  mov [rbp + -792], rax
  mov rax, [rbp + -792]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -800], rax
  mov rax, [rbp + -792]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -808], rdx
  mov rax, [rbp + -808]
  add rax, 48
  mov [rbp + -816], rax
  mov rax, [rbp + -760]
  mov rax, [rax]
  mov [rbp + -824], rax
  mov rax, [rbp + -824]
  sub rax, 1
  mov [rbp + -832], rax
  mov rax, [rbp + -816]
  mov rdx, [rbp + -832]
  mov byte ptr [rdx], al
  mov rax, [rbp + -800]
  mov rdx, [rbp + -752]
  mov [rdx], rax
  mov rax, [rbp + -832]
  mov rdx, [rbp + -760]
  mov [rdx], rax
  mov rax, [rbp + -800]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -840], rax
  mov rax, [rbp + -840]
  test rax, rax
  jne main_pi_loop_5
  jmp main_pi_emit_5
main_pi_emit_5:
  mov rax, [rbp + -760]
  mov rax, [rax]
  mov [rbp + -848], rax
  mov rax, [rbp + -736]
  add rax, 32
  mov [rbp + -856], rax
  mov rax, [rbp + -856]
  sub rax, [rbp + -848]
  mov [rbp + -864], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -848]
  mov r8d, dword ptr [rbp + -864]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -872], rax
  call lm_dict_new
  mov [rbp + -880], rax
  mov rcx, [rbp + -880]
  lea rdx, [rel str_const_0]
  mov r8, 1
  call lm_dict_set
  mov [rbp + -888], rax
  mov rcx, [rbp + -880]
  lea rdx, [rel str_const_1]
  mov r8, 2
  call lm_dict_set
  mov [rbp + -896], rax
  mov rcx, [rbp + -880]
  lea rdx, [rel str_const_2]
  call lm_dict_get
  mov [rbp + -904], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -912], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -912]
  add rax, 31
  mov [rbp + -920], rax
  mov rax, 10
  mov rdx, [rbp + -920]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -928], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -936], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -920]
  mov rdx, [rbp + -936]
  mov [rdx], rax
  mov rax, [rbp + -904]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -944], rax
  mov rax, [rbp + -944]
  test rax, rax
  jne main_pi_neg_6
  jmp main_pi_abs_6
main_pi_neg_6:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_minus]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -952], rax
  mov rax, [rbp + -904]
  neg rax
  mov [rbp + -960], rax
  mov rax, [rbp + -960]
  mov rdx, [rbp + -928]
  mov [rdx], rax
  jmp main_pi_loop_6
main_pi_abs_6:
  mov rax, [rbp + -904]
  mov rdx, [rbp + -928]
  mov [rdx], rax
  jmp main_pi_loop_6
main_pi_loop_6:
  mov rax, [rbp + -928]
  mov rax, [rax]
  mov [rbp + -968], rax
  mov rax, [rbp + -968]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -976], rax
  mov rax, [rbp + -968]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -984], rdx
  mov rax, [rbp + -984]
  add rax, 48
  mov [rbp + -992], rax
  mov rax, [rbp + -936]
  mov rax, [rax]
  mov [rbp + -1000], rax
  mov rax, [rbp + -1000]
  sub rax, 1
  mov [rbp + -1008], rax
  mov rax, [rbp + -992]
  mov rdx, [rbp + -1008]
  mov byte ptr [rdx], al
  mov rax, [rbp + -976]
  mov rdx, [rbp + -928]
  mov [rdx], rax
  mov rax, [rbp + -1008]
  mov rdx, [rbp + -936]
  mov [rdx], rax
  mov rax, [rbp + -976]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -1016], rax
  mov rax, [rbp + -1016]
  test rax, rax
  jne main_pi_loop_6
  jmp main_pi_emit_6
main_pi_emit_6:
  mov rax, [rbp + -936]
  mov rax, [rax]
  mov [rbp + -1024], rax
  mov rax, [rbp + -912]
  add rax, 32
  mov [rbp + -1032], rax
  mov rax, [rbp + -1032]
  sub rax, [rbp + -1024]
  mov [rbp + -1040], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -1024]
  mov r8d, dword ptr [rbp + -1040]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -1048], rax
  mov rcx, [rbp + -880]
  lea rdx, [rel str_const_3]
  call lm_dict_get
  mov [rbp + -1056], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -1064], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -1064]
  add rax, 31
  mov [rbp + -1072], rax
  mov rax, 10
  mov rdx, [rbp + -1072]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -1080], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -1088], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -1072]
  mov rdx, [rbp + -1088]
  mov [rdx], rax
  mov rax, [rbp + -1056]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -1096], rax
  mov rax, [rbp + -1096]
  test rax, rax
  jne main_pi_neg_7
  jmp main_pi_abs_7
main_pi_neg_7:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_minus]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -1104], rax
  mov rax, [rbp + -1056]
  neg rax
  mov [rbp + -1112], rax
  mov rax, [rbp + -1112]
  mov rdx, [rbp + -1080]
  mov [rdx], rax
  jmp main_pi_loop_7
main_pi_abs_7:
  mov rax, [rbp + -1056]
  mov rdx, [rbp + -1080]
  mov [rdx], rax
  jmp main_pi_loop_7
main_pi_loop_7:
  mov rax, [rbp + -1080]
  mov rax, [rax]
  mov [rbp + -1120], rax
  mov rax, [rbp + -1120]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -1128], rax
  mov rax, [rbp + -1120]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -1136], rdx
  mov rax, [rbp + -1136]
  add rax, 48
  mov [rbp + -1144], rax
  mov rax, [rbp + -1088]
  mov rax, [rax]
  mov [rbp + -1152], rax
  mov rax, [rbp + -1152]
  sub rax, 1
  mov [rbp + -1160], rax
  mov rax, [rbp + -1144]
  mov rdx, [rbp + -1160]
  mov byte ptr [rdx], al
  mov rax, [rbp + -1128]
  mov rdx, [rbp + -1080]
  mov [rdx], rax
  mov rax, [rbp + -1160]
  mov rdx, [rbp + -1088]
  mov [rdx], rax
  mov rax, [rbp + -1128]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -1168], rax
  mov rax, [rbp + -1168]
  test rax, rax
  jne main_pi_loop_7
  jmp main_pi_emit_7
main_pi_emit_7:
  mov rax, [rbp + -1088]
  mov rax, [rax]
  mov [rbp + -1176], rax
  mov rax, [rbp + -1064]
  add rax, 32
  mov [rbp + -1184], rax
  mov rax, [rbp + -1184]
  sub rax, [rbp + -1176]
  mov [rbp + -1192], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -1176]
  mov r8d, dword ptr [rbp + -1192]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -1200], rax
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

.globl lm_list_new
lm_list_new:
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
lm_list_new_entry:
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -64]
  mov rdx, [rbp + -72]
  mov [rdx], rax
  mov rax, [rbp + -64]
  cmp rax, 0
  setle al
  movzx eax, al
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  test rax, rax
  jne lm_list_new_def_cap
  jmp lm_list_new_alloc
lm_list_new_def_cap:
  mov rax, 8
  mov rdx, [rbp + -72]
  mov [rdx], rax
  jmp lm_list_new_alloc
lm_list_new_alloc:
  mov rax, [rbp + -72]
  mov rax, [rax]
  mov [rbp + -88], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, 24
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -96], rax
  add rsp, 48
  mov [rbp + -96], rax
  mov rax, [rbp + -88]
  imul rax, 8
  mov [rbp + -104], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, [rbp + -104]
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -112], rax
  add rsp, 48
  mov [rbp + -112], rax
  mov rax, 0
  mov rdx, [rbp + -96]
  mov [rdx], rax
  mov rax, [rbp + -96]
  add rax, 8
  mov [rbp + -120], rax
  mov rax, [rbp + -88]
  mov rdx, [rbp + -120]
  mov [rdx], rax
  mov rax, [rbp + -96]
  add rax, 16
  mov [rbp + -128], rax
  mov rax, [rbp + -112]
  mov rdx, [rbp + -128]
  mov [rdx], rax
  mov rax, [rbp + -96]
  jmp lm_list_new_epilogue
lm_list_new_epilogue:
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
.Lfunc_end_lm_list_new:

.globl lm_list_append
lm_list_append:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 248
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
lm_list_append_entry:
  mov rax, [rbp + -64]
  mov rax, [rax]
  mov [rbp + -80], rax
  mov rax, [rbp + -64]
  add rax, 8
  mov [rbp + -88], rax
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -96], rax
  mov rax, [rbp + -80]
  cmp rax, [rbp + -96]
  setge al
  movzx eax, al
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  test rax, rax
  jne lm_list_append_realloc
  jmp lm_list_append_insert
lm_list_append_realloc:
  mov rax, [rbp + -96]
  imul rax, 2
  mov [rbp + -112], rax
  mov rax, [rbp + -112]
  imul rax, 8
  mov [rbp + -120], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, [rbp + -120]
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -128], rax
  add rsp, 48
  mov [rbp + -128], rax
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -136], rax
  mov rax, [rbp + -136]
  mov rax, [rax]
  mov [rbp + -144], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -152], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -152]
  mov [rdx], rax
  jmp lm_list_append_copy_loop
lm_list_append_copy_loop:
  mov rax, [rbp + -152]
  mov rax, [rax]
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  cmp rax, [rbp + -80]
  setl al
  movzx eax, al
  mov [rbp + -168], rax
  mov rax, [rbp + -168]
  test rax, rax
  jne lm_list_append_copy_body
  jmp lm_list_append_copy_done
lm_list_append_copy_body:
  mov rax, [rbp + -160]
  imul rax, 8
  mov [rbp + -176], rax
  mov rax, [rbp + -144]
  add rax, [rbp + -176]
  mov [rbp + -184], rax
  mov rax, [rbp + -184]
  mov rax, [rax]
  mov [rbp + -192], rax
  mov rax, [rbp + -128]
  add rax, [rbp + -176]
  mov [rbp + -200], rax
  mov rax, [rbp + -192]
  mov rdx, [rbp + -200]
  mov [rdx], rax
  mov rax, [rbp + -160]
  add rax, 1
  mov [rbp + -208], rax
  mov rax, [rbp + -208]
  mov rdx, [rbp + -152]
  mov [rdx], rax
  jmp lm_list_append_copy_loop
lm_list_append_copy_done:
  mov rax, [rbp + -112]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  mov rax, [rbp + -128]
  mov rdx, [rbp + -136]
  mov [rdx], rax
  jmp lm_list_append_insert
lm_list_append_insert:
  mov rax, [rbp + -64]
  mov rax, [rax]
  mov [rbp + -216], rax
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -224], rax
  mov rax, [rbp + -224]
  mov rax, [rax]
  mov [rbp + -232], rax
  mov rax, [rbp + -216]
  imul rax, 8
  mov [rbp + -240], rax
  mov rax, [rbp + -232]
  add rax, [rbp + -240]
  mov [rbp + -248], rax
  mov rax, [rbp + -72]
  mov rdx, [rbp + -248]
  mov [rdx], rax
  mov rax, [rbp + -216]
  add rax, 1
  mov [rbp + -256], rax
  mov rax, [rbp + -256]
  mov rdx, [rbp + -64]
  mov [rdx], rax
  mov rax, 0
  jmp lm_list_append_epilogue
lm_list_append_epilogue:
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
.Lfunc_end_lm_list_append:

.globl lm_list_get
lm_list_get:
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
  mov [rbp + -72], rdx
lm_list_get_entry:
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -88], rax
  mov rax, [rbp + -72]
  imul rax, 8
  mov [rbp + -96], rax
  mov rax, [rbp + -88]
  add rax, [rbp + -96]
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  mov rax, [rax]
  mov [rbp + -112], rax
  mov rax, [rbp + -112]
  jmp lm_list_get_epilogue
lm_list_get_epilogue:
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
.Lfunc_end_lm_list_get:

.globl lm_dict_new
lm_dict_new:
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
lm_dict_new_entry:
  sub rsp, 48
  mov rcx, 0
  mov rdx, 32
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -64], rax
  add rsp, 48
  mov [rbp + -64], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, 256
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -72], rax
  add rsp, 48
  mov [rbp + -72], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, 256
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -80], rax
  add rsp, 48
  mov [rbp + -80], rax
  mov rax, 0
  mov rdx, [rbp + -64]
  mov [rdx], rax
  mov rax, [rbp + -64]
  add rax, 8
  mov [rbp + -88], rax
  mov rax, 32
  mov rdx, [rbp + -88]
  mov [rdx], rax
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -96], rax
  mov rax, [rbp + -72]
  mov rdx, [rbp + -96]
  mov [rdx], rax
  mov rax, [rbp + -64]
  add rax, 24
  mov [rbp + -104], rax
  mov rax, [rbp + -80]
  mov rdx, [rbp + -104]
  mov [rdx], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -112], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -112]
  mov [rdx], rax
  jmp lm_dict_new_init_loop
lm_dict_new_init_loop:
  mov rax, [rbp + -112]
  mov rax, [rax]
  mov [rbp + -120], rax
  mov rax, [rbp + -120]
  cmp rax, 32
  setl al
  movzx eax, al
  mov [rbp + -128], rax
  mov rax, [rbp + -128]
  test rax, rax
  jne lm_dict_new_init_body
  jmp lm_dict_new_init_done
lm_dict_new_init_body:
  mov rax, [rbp + -120]
  imul rax, 8
  mov [rbp + -136], rax
  mov rax, [rbp + -72]
  add rax, [rbp + -136]
  mov [rbp + -144], rax
  mov rax, 0
  mov rdx, [rbp + -144]
  mov [rdx], rax
  mov rax, [rbp + -120]
  add rax, 1
  mov [rbp + -152], rax
  mov rax, [rbp + -152]
  mov rdx, [rbp + -112]
  mov [rdx], rax
  jmp lm_dict_new_init_loop
lm_dict_new_init_done:
  mov rax, [rbp + -64]
  jmp lm_dict_new_epilogue
lm_dict_new_epilogue:
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
.Lfunc_end_lm_dict_new:

.globl lm_dict_set
lm_dict_set:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 200
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
lm_dict_set_entry:
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -88], rax
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -96], rax
  mov rax, [rbp + -64]
  add rax, 24
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  mov rax, [rax]
  mov [rbp + -112], rax
  mov rax, [rbp + -64]
  add rax, 8
  mov [rbp + -120], rax
  mov rax, [rbp + -120]
  mov rax, [rax]
  mov [rbp + -128], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -136], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -136]
  mov [rdx], rax
  jmp lm_dict_set_loop
lm_dict_set_loop:
  mov rax, [rbp + -136]
  mov rax, [rax]
  mov [rbp + -144], rax
  mov rax, [rbp + -144]
  cmp rax, [rbp + -128]
  setl al
  movzx eax, al
  mov [rbp + -152], rax
  mov rax, [rbp + -152]
  test rax, rax
  jne lm_dict_set_check
  jmp lm_dict_set_done
lm_dict_set_check:
  mov rax, [rbp + -144]
  imul rax, 8
  mov [rbp + -160], rax
  mov rax, [rbp + -96]
  add rax, [rbp + -160]
  mov [rbp + -168], rax
  mov rax, [rbp + -168]
  mov rax, [rax]
  mov [rbp + -176], rax
  mov rcx, [rbp + -176]
  mov rdx, [rbp + -72]
  call lm_key_eq
  mov [rbp + -184], rax
  mov rax, [rbp + -176]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -192], rax
  mov rax, [rbp + -184]
  or rax, [rbp + -192]
  mov [rbp + -200], rax
  mov rax, [rbp + -200]
  test rax, rax
  jne lm_dict_set_store
  jmp lm_dict_set_next
lm_dict_set_store:
  mov rax, [rbp + -72]
  mov rdx, [rbp + -168]
  mov [rdx], rax
  mov rax, [rbp + -112]
  add rax, [rbp + -160]
  mov [rbp + -208], rax
  mov rax, [rbp + -80]
  mov rdx, [rbp + -208]
  mov [rdx], rax
  mov rax, 0
  jmp lm_dict_set_epilogue
lm_dict_set_next:
  mov rax, [rbp + -144]
  add rax, 1
  mov [rbp + -216], rax
  mov rax, [rbp + -216]
  mov rdx, [rbp + -136]
  mov [rdx], rax
  jmp lm_dict_set_loop
lm_dict_set_done:
  mov rax, 0
  jmp lm_dict_set_epilogue
lm_dict_set_epilogue:
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
.Lfunc_end_lm_dict_set:

.globl lm_dict_get
lm_dict_get:
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
  mov [rbp + -72], rdx
lm_dict_get_entry:
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -88], rax
  mov rax, [rbp + -64]
  add rax, 24
  mov [rbp + -96], rax
  mov rax, [rbp + -96]
  mov rax, [rax]
  mov [rbp + -104], rax
  mov rax, [rbp + -64]
  add rax, 8
  mov [rbp + -112], rax
  mov rax, [rbp + -112]
  mov rax, [rax]
  mov [rbp + -120], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -128], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -128]
  mov [rdx], rax
  jmp lm_dict_get_loop
lm_dict_get_loop:
  mov rax, [rbp + -128]
  mov rax, [rax]
  mov [rbp + -136], rax
  mov rax, [rbp + -136]
  cmp rax, [rbp + -120]
  setl al
  movzx eax, al
  mov [rbp + -144], rax
  mov rax, [rbp + -144]
  test rax, rax
  jne lm_dict_get_check
  jmp lm_dict_get_not_found
lm_dict_get_check:
  mov rax, [rbp + -136]
  imul rax, 8
  mov [rbp + -152], rax
  mov rax, [rbp + -88]
  add rax, [rbp + -152]
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  mov rax, [rax]
  mov [rbp + -168], rax
  mov rcx, [rbp + -168]
  mov rdx, [rbp + -72]
  call lm_key_eq
  mov [rbp + -176], rax
  mov rax, [rbp + -176]
  test rax, rax
  jne lm_dict_get_found
  jmp lm_dict_get_next
lm_dict_get_found:
  mov rax, [rbp + -104]
  add rax, [rbp + -152]
  mov [rbp + -184], rax
  mov rax, [rbp + -184]
  mov rax, [rax]
  mov [rbp + -192], rax
  mov rax, [rbp + -192]
  jmp lm_dict_get_epilogue
lm_dict_get_next:
  mov rax, [rbp + -136]
  add rax, 1
  mov [rbp + -200], rax
  mov rax, [rbp + -200]
  mov rdx, [rbp + -128]
  mov [rdx], rax
  jmp lm_dict_get_loop
lm_dict_get_not_found:
  mov rax, 0
  jmp lm_dict_get_epilogue
lm_dict_get_epilogue:
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
.Lfunc_end_lm_dict_get:

.globl lm_list_len
lm_list_len:
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
  mov [rbp + -64], rcx
lm_list_len_entry:
  mov rax, [rbp + -64]
  mov rax, [rax]
  mov [rbp + -72], rax
  mov rax, [rbp + -72]
  jmp lm_list_len_epilogue
lm_list_len_epilogue:
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
.Lfunc_end_lm_list_len:

.globl lm_list_set
lm_list_set:
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
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
lm_list_set_entry:
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -88], rax
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -96], rax
  mov rax, [rbp + -72]
  imul rax, 8
  mov [rbp + -104], rax
  mov rax, [rbp + -96]
  add rax, [rbp + -104]
  mov [rbp + -112], rax
  mov rax, [rbp + -80]
  mov rdx, [rbp + -112]
  mov [rdx], rax
  mov rax, 0
  jmp lm_list_set_epilogue
lm_list_set_epilogue:
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
.Lfunc_end_lm_list_set:

.globl lm_key_eq
lm_key_eq:
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
  mov [rbp + -72], rdx
lm_key_eq_entry:
  mov rax, [rbp + -64]
  cmp rax, [rbp + -72]
  sete al
  movzx eax, al
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  test rax, rax
  jne lm_key_eq_ret_true
  jmp lm_key_eq_ptrcmp
lm_key_eq_ptrcmp:
  mov rax, [rbp + -64]
  cmp rax, 65536
  setl al
  movzx eax, al
  mov [rbp + -88], rax
  mov rax, [rbp + -72]
  cmp rax, 65536
  setl al
  movzx eax, al
  mov [rbp + -96], rax
  mov rax, [rbp + -88]
  or rax, [rbp + -96]
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  test rax, rax
  jne lm_key_eq_ret_false
  jmp lm_key_eq_loop_init
lm_key_eq_loop_init:
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -112], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -112]
  mov [rdx], rax
  jmp lm_key_eq_loop_cond
lm_key_eq_loop_cond:
  mov rax, [rbp + -112]
  mov rax, [rax]
  mov [rbp + -120], rax
  mov rax, [rbp + -64]
  add rax, [rbp + -120]
  mov [rbp + -128], rax
  mov rax, [rbp + -72]
  add rax, [rbp + -120]
  mov [rbp + -136], rax
  mov rax, [rbp + -128]
  movzx rax, byte ptr [rax]
  mov [rbp + -144], rax
  mov rax, [rbp + -136]
  movzx rax, byte ptr [rax]
  mov [rbp + -152], rax
  mov rax, [rbp + -144]
  cmp rax, [rbp + -152]
  setne al
  movzx eax, al
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  test rax, rax
  jne lm_key_eq_ret_false
  jmp lm_key_eq_check_end
lm_key_eq_check_end:
  mov rax, [rbp + -144]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -168], rax
  mov rax, [rbp + -168]
  test rax, rax
  jne lm_key_eq_ret_true
  jmp lm_key_eq_advance
lm_key_eq_advance:
  mov rax, [rbp + -120]
  add rax, 1
  mov [rbp + -176], rax
  mov rax, [rbp + -176]
  mov rdx, [rbp + -112]
  mov [rdx], rax
  jmp lm_key_eq_loop_cond
lm_key_eq_ret_true:
  mov rax, 1
  jmp lm_key_eq_epilogue
lm_key_eq_ret_false:
  mov rax, 0
  jmp lm_key_eq_epilogue
lm_key_eq_epilogue:
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
.Lfunc_end_lm_key_eq:

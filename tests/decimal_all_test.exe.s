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
  sub rsp, 1128
main_entry:
main_block_0:
  # Bump Allocation: 64 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 64
  mov [rel heap_ptr], rax
  mov rax, [rbp + -64]
  add rax, 63
  mov [rbp + -72], rax
  mov rax, 10
  mov rdx, [rbp + -72]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -72]
  mov rdx, [rbp + -80]
  mov [rdx], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -96], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -104], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 1234
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -112], rax
  mov rax, [rbp + -112]
  test rax, rax
  jne main_pd_neg_1
  jmp main_pd_abs_1
main_pd_neg_1:
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
  mov [rbp + -120], rax
  mov rax, 1234
  neg rax
  mov [rbp + -128], rax
  mov rax, [rbp + -128]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  jmp main_pd_prep_1
main_pd_abs_1:
  mov rax, 1234
  mov rdx, [rbp + -88]
  mov [rdx], rax
  jmp main_pd_prep_1
main_pd_prep_1:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -136], rax
  mov rax, [rbp + -136]
  cqo
  mov rcx, 100
  idiv rcx
  mov [rbp + -144], rax
  mov rax, [rbp + -136]
  cqo
  mov rcx, 100
  idiv rcx
  mov [rbp + -152], rdx
  mov rax, [rbp + -144]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  mov rax, [rbp + -152]
  mov rdx, [rbp + -96]
  mov [rdx], rax
  mov rax, 2
  mov rdx, [rbp + -104]
  mov [rdx], rax
  jmp main_pd_frac_loop_1
main_pd_frac_loop_1:
  mov rax, [rbp + -96]
  mov rax, [rax]
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -168], rdx
  mov rax, [rbp + -160]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -176], rax
  mov rax, [rbp + -176]
  mov rdx, [rbp + -96]
  mov [rdx], rax
  mov rax, [rbp + -168]
  add rax, 48
  mov [rbp + -184], rax
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -192], rax
  mov rax, [rbp + -192]
  sub rax, 1
  mov [rbp + -200], rax
  mov rax, [rbp + -184]
  mov rdx, [rbp + -200]
  mov byte ptr [rdx], al
  mov rax, [rbp + -200]
  mov rdx, [rbp + -80]
  mov [rdx], rax
  mov rax, [rbp + -104]
  mov rax, [rax]
  mov [rbp + -208], rax
  mov rax, [rbp + -208]
  sub rax, 1
  mov [rbp + -216], rax
  mov rax, [rbp + -216]
  mov rdx, [rbp + -104]
  mov [rdx], rax
  mov rax, [rbp + -216]
  cmp rax, 0
  setg al
  movzx eax, al
  mov [rbp + -224], rax
  mov rax, [rbp + -224]
  test rax, rax
  jne main_pd_frac_loop_1
  jmp main_pd_dot_1
main_pd_dot_1:
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -232], rax
  mov rax, [rbp + -232]
  sub rax, 1
  mov [rbp + -240], rax
  mov rax, 46
  mov rdx, [rbp + -240]
  mov byte ptr [rdx], al
  mov rax, [rbp + -240]
  mov rdx, [rbp + -80]
  mov [rdx], rax
  jmp main_pd_whole_loop_1
main_pd_whole_loop_1:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -248], rax
  mov rax, [rbp + -248]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -256], rdx
  mov rax, [rbp + -248]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -264], rax
  mov rax, [rbp + -264]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  mov rax, [rbp + -256]
  add rax, 48
  mov [rbp + -272], rax
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -280], rax
  mov rax, [rbp + -280]
  sub rax, 1
  mov [rbp + -288], rax
  mov rax, [rbp + -272]
  mov rdx, [rbp + -288]
  mov byte ptr [rdx], al
  mov rax, [rbp + -288]
  mov rdx, [rbp + -80]
  mov [rdx], rax
  mov rax, [rbp + -264]
  cmp rax, 1
  setge al
  movzx eax, al
  mov [rbp + -296], rax
  mov rax, [rbp + -296]
  test rax, rax
  jne main_pd_whole_loop_1
  jmp main_pd_emit_1
main_pd_emit_1:
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -304], rax
  mov rax, [rbp + -64]
  add rax, 64
  mov [rbp + -312], rax
  mov rax, [rbp + -312]
  sub rax, [rbp + -304]
  mov [rbp + -320], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -304]
  mov r8d, dword ptr [rbp + -320]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -328], rax
  # Bump Allocation: 64 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -336], rax
  add rax, 64
  mov [rel heap_ptr], rax
  mov rax, [rbp + -336]
  add rax, 63
  mov [rbp + -344], rax
  mov rax, 10
  mov rdx, [rbp + -344]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -352], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -344]
  mov rdx, [rbp + -352]
  mov [rdx], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -360], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -368], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -376], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 123458
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -384], rax
  mov rax, [rbp + -384]
  test rax, rax
  jne main_pd_neg_2
  jmp main_pd_abs_2
main_pd_neg_2:
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
  mov [rbp + -392], rax
  mov rax, 123458
  neg rax
  mov [rbp + -400], rax
  mov rax, [rbp + -400]
  mov rdx, [rbp + -360]
  mov [rdx], rax
  jmp main_pd_prep_2
main_pd_abs_2:
  mov rax, 123458
  mov rdx, [rbp + -360]
  mov [rdx], rax
  jmp main_pd_prep_2
main_pd_prep_2:
  mov rax, [rbp + -360]
  mov rax, [rax]
  mov [rbp + -408], rax
  mov rax, [rbp + -408]
  cqo
  mov rcx, 10000
  idiv rcx
  mov [rbp + -416], rax
  mov rax, [rbp + -408]
  cqo
  mov rcx, 10000
  idiv rcx
  mov [rbp + -424], rdx
  mov rax, [rbp + -416]
  mov rdx, [rbp + -360]
  mov [rdx], rax
  mov rax, [rbp + -424]
  mov rdx, [rbp + -368]
  mov [rdx], rax
  mov rax, 4
  mov rdx, [rbp + -376]
  mov [rdx], rax
  jmp main_pd_frac_loop_2
main_pd_frac_loop_2:
  mov rax, [rbp + -368]
  mov rax, [rax]
  mov [rbp + -432], rax
  mov rax, [rbp + -432]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -440], rdx
  mov rax, [rbp + -432]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -448], rax
  mov rax, [rbp + -448]
  mov rdx, [rbp + -368]
  mov [rdx], rax
  mov rax, [rbp + -440]
  add rax, 48
  mov [rbp + -456], rax
  mov rax, [rbp + -352]
  mov rax, [rax]
  mov [rbp + -464], rax
  mov rax, [rbp + -464]
  sub rax, 1
  mov [rbp + -472], rax
  mov rax, [rbp + -456]
  mov rdx, [rbp + -472]
  mov byte ptr [rdx], al
  mov rax, [rbp + -472]
  mov rdx, [rbp + -352]
  mov [rdx], rax
  mov rax, [rbp + -376]
  mov rax, [rax]
  mov [rbp + -480], rax
  mov rax, [rbp + -480]
  sub rax, 1
  mov [rbp + -488], rax
  mov rax, [rbp + -488]
  mov rdx, [rbp + -376]
  mov [rdx], rax
  mov rax, [rbp + -488]
  cmp rax, 0
  setg al
  movzx eax, al
  mov [rbp + -496], rax
  mov rax, [rbp + -496]
  test rax, rax
  jne main_pd_frac_loop_2
  jmp main_pd_dot_2
main_pd_dot_2:
  mov rax, [rbp + -352]
  mov rax, [rax]
  mov [rbp + -504], rax
  mov rax, [rbp + -504]
  sub rax, 1
  mov [rbp + -512], rax
  mov rax, 46
  mov rdx, [rbp + -512]
  mov byte ptr [rdx], al
  mov rax, [rbp + -512]
  mov rdx, [rbp + -352]
  mov [rdx], rax
  jmp main_pd_whole_loop_2
main_pd_whole_loop_2:
  mov rax, [rbp + -360]
  mov rax, [rax]
  mov [rbp + -520], rax
  mov rax, [rbp + -520]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -528], rdx
  mov rax, [rbp + -520]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -536], rax
  mov rax, [rbp + -536]
  mov rdx, [rbp + -360]
  mov [rdx], rax
  mov rax, [rbp + -528]
  add rax, 48
  mov [rbp + -544], rax
  mov rax, [rbp + -352]
  mov rax, [rax]
  mov [rbp + -552], rax
  mov rax, [rbp + -552]
  sub rax, 1
  mov [rbp + -560], rax
  mov rax, [rbp + -544]
  mov rdx, [rbp + -560]
  mov byte ptr [rdx], al
  mov rax, [rbp + -560]
  mov rdx, [rbp + -352]
  mov [rdx], rax
  mov rax, [rbp + -536]
  cmp rax, 1
  setge al
  movzx eax, al
  mov [rbp + -568], rax
  mov rax, [rbp + -568]
  test rax, rax
  jne main_pd_whole_loop_2
  jmp main_pd_emit_2
main_pd_emit_2:
  mov rax, [rbp + -352]
  mov rax, [rax]
  mov [rbp + -576], rax
  mov rax, [rbp + -336]
  add rax, 64
  mov [rbp + -584], rax
  mov rax, [rbp + -584]
  sub rax, [rbp + -576]
  mov [rbp + -592], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -576]
  mov r8d, dword ptr [rbp + -592]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -600], rax
  # Bump Allocation: 64 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -608], rax
  add rax, 64
  mov [rel heap_ptr], rax
  mov rax, [rbp + -608]
  add rax, 63
  mov [rbp + -616], rax
  mov rax, 10
  mov rdx, [rbp + -616]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -624], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -616]
  mov rdx, [rbp + -624]
  mov [rdx], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -632], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -640], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -648], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 12345678
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -656], rax
  mov rax, [rbp + -656]
  test rax, rax
  jne main_pd_neg_3
  jmp main_pd_abs_3
main_pd_neg_3:
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
  mov [rbp + -664], rax
  mov rax, 12345678
  neg rax
  mov [rbp + -672], rax
  mov rax, [rbp + -672]
  mov rdx, [rbp + -632]
  mov [rdx], rax
  jmp main_pd_prep_3
main_pd_abs_3:
  mov rax, 12345678
  mov rdx, [rbp + -632]
  mov [rdx], rax
  jmp main_pd_prep_3
main_pd_prep_3:
  mov rax, [rbp + -632]
  mov rax, [rax]
  mov [rbp + -680], rax
  mov rax, [rbp + -680]
  cqo
  mov rcx, 1000000
  idiv rcx
  mov [rbp + -688], rax
  mov rax, [rbp + -680]
  cqo
  mov rcx, 1000000
  idiv rcx
  mov [rbp + -696], rdx
  mov rax, [rbp + -688]
  mov rdx, [rbp + -632]
  mov [rdx], rax
  mov rax, [rbp + -696]
  mov rdx, [rbp + -640]
  mov [rdx], rax
  mov rax, 6
  mov rdx, [rbp + -648]
  mov [rdx], rax
  jmp main_pd_frac_loop_3
main_pd_frac_loop_3:
  mov rax, [rbp + -640]
  mov rax, [rax]
  mov [rbp + -704], rax
  mov rax, [rbp + -704]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -712], rdx
  mov rax, [rbp + -704]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -720], rax
  mov rax, [rbp + -720]
  mov rdx, [rbp + -640]
  mov [rdx], rax
  mov rax, [rbp + -712]
  add rax, 48
  mov [rbp + -728], rax
  mov rax, [rbp + -624]
  mov rax, [rax]
  mov [rbp + -736], rax
  mov rax, [rbp + -736]
  sub rax, 1
  mov [rbp + -744], rax
  mov rax, [rbp + -728]
  mov rdx, [rbp + -744]
  mov byte ptr [rdx], al
  mov rax, [rbp + -744]
  mov rdx, [rbp + -624]
  mov [rdx], rax
  mov rax, [rbp + -648]
  mov rax, [rax]
  mov [rbp + -752], rax
  mov rax, [rbp + -752]
  sub rax, 1
  mov [rbp + -760], rax
  mov rax, [rbp + -760]
  mov rdx, [rbp + -648]
  mov [rdx], rax
  mov rax, [rbp + -760]
  cmp rax, 0
  setg al
  movzx eax, al
  mov [rbp + -768], rax
  mov rax, [rbp + -768]
  test rax, rax
  jne main_pd_frac_loop_3
  jmp main_pd_dot_3
main_pd_dot_3:
  mov rax, [rbp + -624]
  mov rax, [rax]
  mov [rbp + -776], rax
  mov rax, [rbp + -776]
  sub rax, 1
  mov [rbp + -784], rax
  mov rax, 46
  mov rdx, [rbp + -784]
  mov byte ptr [rdx], al
  mov rax, [rbp + -784]
  mov rdx, [rbp + -624]
  mov [rdx], rax
  jmp main_pd_whole_loop_3
main_pd_whole_loop_3:
  mov rax, [rbp + -632]
  mov rax, [rax]
  mov [rbp + -792], rax
  mov rax, [rbp + -792]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -800], rdx
  mov rax, [rbp + -792]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -808], rax
  mov rax, [rbp + -808]
  mov rdx, [rbp + -632]
  mov [rdx], rax
  mov rax, [rbp + -800]
  add rax, 48
  mov [rbp + -816], rax
  mov rax, [rbp + -624]
  mov rax, [rax]
  mov [rbp + -824], rax
  mov rax, [rbp + -824]
  sub rax, 1
  mov [rbp + -832], rax
  mov rax, [rbp + -816]
  mov rdx, [rbp + -832]
  mov byte ptr [rdx], al
  mov rax, [rbp + -832]
  mov rdx, [rbp + -624]
  mov [rdx], rax
  mov rax, [rbp + -808]
  cmp rax, 1
  setge al
  movzx eax, al
  mov [rbp + -840], rax
  mov rax, [rbp + -840]
  test rax, rax
  jne main_pd_whole_loop_3
  jmp main_pd_emit_3
main_pd_emit_3:
  mov rax, [rbp + -624]
  mov rax, [rax]
  mov [rbp + -848], rax
  mov rax, [rbp + -608]
  add rax, 64
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
  # Bump Allocation: 64 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -880], rax
  add rax, 64
  mov [rel heap_ptr], rax
  mov rax, [rbp + -880]
  add rax, 63
  mov [rbp + -888], rax
  mov rax, 10
  mov rdx, [rbp + -888]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -896], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -888]
  mov rdx, [rbp + -896]
  mov [rdx], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -904], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -912], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -920], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 9988
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -928], rax
  mov rax, [rbp + -928]
  test rax, rax
  jne main_pd_neg_4
  jmp main_pd_abs_4
main_pd_neg_4:
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
  mov [rbp + -936], rax
  mov rax, 9988
  neg rax
  mov [rbp + -944], rax
  mov rax, [rbp + -944]
  mov rdx, [rbp + -904]
  mov [rdx], rax
  jmp main_pd_prep_4
main_pd_abs_4:
  mov rax, 9988
  mov rdx, [rbp + -904]
  mov [rdx], rax
  jmp main_pd_prep_4
main_pd_prep_4:
  mov rax, [rbp + -904]
  mov rax, [rax]
  mov [rbp + -952], rax
  mov rax, [rbp + -952]
  cqo
  mov rcx, 100
  idiv rcx
  mov [rbp + -960], rax
  mov rax, [rbp + -952]
  cqo
  mov rcx, 100
  idiv rcx
  mov [rbp + -968], rdx
  mov rax, [rbp + -960]
  mov rdx, [rbp + -904]
  mov [rdx], rax
  mov rax, [rbp + -968]
  mov rdx, [rbp + -912]
  mov [rdx], rax
  mov rax, 2
  mov rdx, [rbp + -920]
  mov [rdx], rax
  jmp main_pd_frac_loop_4
main_pd_frac_loop_4:
  mov rax, [rbp + -912]
  mov rax, [rax]
  mov [rbp + -976], rax
  mov rax, [rbp + -976]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -984], rdx
  mov rax, [rbp + -976]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -992], rax
  mov rax, [rbp + -992]
  mov rdx, [rbp + -912]
  mov [rdx], rax
  mov rax, [rbp + -984]
  add rax, 48
  mov [rbp + -1000], rax
  mov rax, [rbp + -896]
  mov rax, [rax]
  mov [rbp + -1008], rax
  mov rax, [rbp + -1008]
  sub rax, 1
  mov [rbp + -1016], rax
  mov rax, [rbp + -1000]
  mov rdx, [rbp + -1016]
  mov byte ptr [rdx], al
  mov rax, [rbp + -1016]
  mov rdx, [rbp + -896]
  mov [rdx], rax
  mov rax, [rbp + -920]
  mov rax, [rax]
  mov [rbp + -1024], rax
  mov rax, [rbp + -1024]
  sub rax, 1
  mov [rbp + -1032], rax
  mov rax, [rbp + -1032]
  mov rdx, [rbp + -920]
  mov [rdx], rax
  mov rax, [rbp + -1032]
  cmp rax, 0
  setg al
  movzx eax, al
  mov [rbp + -1040], rax
  mov rax, [rbp + -1040]
  test rax, rax
  jne main_pd_frac_loop_4
  jmp main_pd_dot_4
main_pd_dot_4:
  mov rax, [rbp + -896]
  mov rax, [rax]
  mov [rbp + -1048], rax
  mov rax, [rbp + -1048]
  sub rax, 1
  mov [rbp + -1056], rax
  mov rax, 46
  mov rdx, [rbp + -1056]
  mov byte ptr [rdx], al
  mov rax, [rbp + -1056]
  mov rdx, [rbp + -896]
  mov [rdx], rax
  jmp main_pd_whole_loop_4
main_pd_whole_loop_4:
  mov rax, [rbp + -904]
  mov rax, [rax]
  mov [rbp + -1064], rax
  mov rax, [rbp + -1064]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -1072], rdx
  mov rax, [rbp + -1064]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -1080], rax
  mov rax, [rbp + -1080]
  mov rdx, [rbp + -904]
  mov [rdx], rax
  mov rax, [rbp + -1072]
  add rax, 48
  mov [rbp + -1088], rax
  mov rax, [rbp + -896]
  mov rax, [rax]
  mov [rbp + -1096], rax
  mov rax, [rbp + -1096]
  sub rax, 1
  mov [rbp + -1104], rax
  mov rax, [rbp + -1088]
  mov rdx, [rbp + -1104]
  mov byte ptr [rdx], al
  mov rax, [rbp + -1104]
  mov rdx, [rbp + -896]
  mov [rdx], rax
  mov rax, [rbp + -1080]
  cmp rax, 1
  setge al
  movzx eax, al
  mov [rbp + -1112], rax
  mov rax, [rbp + -1112]
  test rax, rax
  jne main_pd_whole_loop_4
  jmp main_pd_emit_4
main_pd_emit_4:
  mov rax, [rbp + -896]
  mov rax, [rax]
  mov [rbp + -1120], rax
  mov rax, [rbp + -880]
  add rax, 64
  mov [rbp + -1128], rax
  mov rax, [rbp + -1128]
  sub rax, [rbp + -1120]
  mov [rbp + -1136], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -1120]
  mov r8d, dword ptr [rbp + -1136]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -1144], rax
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

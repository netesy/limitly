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
  .string "=== Crypto Hash Tests ==="
.align 8
str_const_1:
  .string "Created."
.align 8
nl:
  .string "
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
  sub rsp, 104
main_entry:
main_block_0:
  call std.resource.__init__
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
  call std.resource.create_hash_engine
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

.globl std.resource.__init__
std.resource.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.resource.__init___entry:
  movq $0, rax
  jmp std.resource.__init___epilogue
std.resource.__init___epilogue:
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
.Lfunc_end_std.resource.__init__:

.globl std.resource._call
std.resource._call:
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
  mov [rbp + -80], r8
std.resource._call_entry:
std.resource._call_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.internal.runtime.call
  movq $r3, rax
  jmp std.resource._call_epilogue
std.resource._call_epilogue:
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
.Lfunc_end_std.resource._call:

.globl std.resource.adopt_socket
std.resource.adopt_socket:
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
std.resource.adopt_socket_entry:
std.resource.adopt_socket_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -72], rax
  jmp std.resource.adopt_socket_epilogue
std.resource.adopt_socket_epilogue:
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
.Lfunc_end_std.resource.adopt_socket:

.globl std.resource.create_entropy
std.resource.create_entropy:
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
std.resource.create_entropy_entry:
std.resource.create_entropy_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_entropy_block_8
  jmp std.resource.create_entropy_block_10
std.resource.create_entropy_block_8:
  jmp std.resource.create_entropy_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_entropy_epilogue
std.resource.create_entropy_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_entropy_epilogue
std.resource.create_entropy_epilogue:
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
.Lfunc_end_std.resource.create_entropy:

.globl std.resource.create_websocket
std.resource.create_websocket:
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
std.resource.create_websocket_entry:
std.resource.create_websocket_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_websocket_block_8
  jmp std.resource.create_websocket_block_10
std.resource.create_websocket_block_8:
  jmp std.resource.create_websocket_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_websocket_epilogue
std.resource.create_websocket_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_websocket_epilogue
std.resource.create_websocket_epilogue:
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
.Lfunc_end_std.resource.create_websocket:

.globl std.resource.create_fs_resource
std.resource.create_fs_resource:
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
std.resource.create_fs_resource_entry:
std.resource.create_fs_resource_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_fs_resource_block_8
  jmp std.resource.create_fs_resource_block_10
std.resource.create_fs_resource_block_8:
  jmp std.resource.create_fs_resource_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_fs_resource_epilogue
std.resource.create_fs_resource_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_fs_resource_epilogue
std.resource.create_fs_resource_epilogue:
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
.Lfunc_end_std.resource.create_fs_resource:

.globl std.resource.create_dns_resolver
std.resource.create_dns_resolver:
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
std.resource.create_dns_resolver_entry:
std.resource.create_dns_resolver_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_dns_resolver_block_8
  jmp std.resource.create_dns_resolver_block_10
std.resource.create_dns_resolver_block_8:
  jmp std.resource.create_dns_resolver_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_dns_resolver_epilogue
std.resource.create_dns_resolver_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_dns_resolver_epilogue
std.resource.create_dns_resolver_epilogue:
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
.Lfunc_end_std.resource.create_dns_resolver:

.globl std.resource.Accepter.init
std.resource.Accepter.init:
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
  mov [rbp + -72], rdx
std.resource.Accepter.init_entry:
  movq $0, rax
  jmp std.resource.Accepter.init_epilogue
std.resource.Accepter.init_epilogue:
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
.Lfunc_end_std.resource.Accepter.init:

.globl std.resource.Listener.init
std.resource.Listener.init:
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
  mov [rbp + -72], rdx
std.resource.Listener.init_entry:
  movq $0, rax
  jmp std.resource.Listener.init_epilogue
std.resource.Listener.init_epilogue:
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
.Lfunc_end_std.resource.Listener.init:

.globl std.resource.Listener.listen
std.resource.Listener.listen:
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
  mov [rbp + -72], rdx
std.resource.Listener.listen_entry:
  movq $0, rax
  jmp std.resource.Listener.listen_epilogue
std.resource.Listener.listen_epilogue:
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
.Lfunc_end_std.resource.Listener.listen:

.globl std.resource.Binder.init
std.resource.Binder.init:
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
  mov [rbp + -72], rdx
std.resource.Binder.init_entry:
  movq $0, rax
  jmp std.resource.Binder.init_epilogue
std.resource.Binder.init_epilogue:
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
.Lfunc_end_std.resource.Binder.init:

.globl std.resource.create_hash_engine
std.resource.create_hash_engine:
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
std.resource.create_hash_engine_entry:
std.resource.create_hash_engine_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_hash_engine_block_8
  jmp std.resource.create_hash_engine_block_10
std.resource.create_hash_engine_block_8:
  jmp std.resource.create_hash_engine_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_hash_engine_epilogue
std.resource.create_hash_engine_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_hash_engine_epilogue
std.resource.create_hash_engine_epilogue:
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
.Lfunc_end_std.resource.create_hash_engine:

.globl std.resource.Binder.bind
std.resource.Binder.bind:
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
  mov [rbp + -72], rdx
std.resource.Binder.bind_entry:
  movq $0, rax
  jmp std.resource.Binder.bind_epilogue
std.resource.Binder.bind_epilogue:
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
.Lfunc_end_std.resource.Binder.bind:

.globl std.resource.Connector.init
std.resource.Connector.init:
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
  mov [rbp + -72], rdx
std.resource.Connector.init_entry:
  movq $0, rax
  jmp std.resource.Connector.init_epilogue
std.resource.Connector.init_epilogue:
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
.Lfunc_end_std.resource.Connector.init:

.globl std.resource.create_socket
std.resource.create_socket:
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
std.resource.create_socket_entry:
std.resource.create_socket_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_socket_block_8
  jmp std.resource.create_socket_block_10
std.resource.create_socket_block_8:
  jmp std.resource.create_socket_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_socket_epilogue
std.resource.create_socket_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_socket_epilogue
std.resource.create_socket_epilogue:
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
.Lfunc_end_std.resource.create_socket:

.globl std.resource.Accepter.accept
std.resource.Accepter.accept:
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
std.resource.Accepter.accept_entry:
  movq $0, rax
  jmp std.resource.Accepter.accept_epilogue
std.resource.Accepter.accept_epilogue:
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
.Lfunc_end_std.resource.Accepter.accept:

.globl std.resource.Connector.connect
std.resource.Connector.connect:
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
  mov [rbp + -72], rdx
std.resource.Connector.connect_entry:
  movq $0, rax
  jmp std.resource.Connector.connect_epilogue
std.resource.Connector.connect_epilogue:
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
.Lfunc_end_std.resource.Connector.connect:

.globl std.resource.Poller.init
std.resource.Poller.init:
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
  mov [rbp + -72], rdx
std.resource.Poller.init_entry:
  movq $0, rax
  jmp std.resource.Poller.init_epilogue
std.resource.Poller.init_epilogue:
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
.Lfunc_end_std.resource.Poller.init:

.globl std.internal.runtime.__init__
std.internal.runtime.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.internal.runtime.__init___entry:
  movq $0, rax
  jmp std.internal.runtime.__init___epilogue
std.internal.runtime.__init___epilogue:
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
.Lfunc_end_std.internal.runtime.__init__:

.globl std.resource.Pollable.poll
std.resource.Pollable.poll:
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
std.resource.Pollable.poll_entry:
  movq $0, rax
  jmp std.resource.Pollable.poll_epilogue
std.resource.Pollable.poll_epilogue:
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
.Lfunc_end_std.resource.Pollable.poll:

.globl std.resource.open_file
std.resource.open_file:
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
std.resource.open_file_entry:
std.resource.open_file_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r3, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -80]
  movq $r4, rax
  cmpq [rbp + -80], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.resource.open_file_block_8
  jmp std.resource.open_file_block_10
std.resource.open_file_block_8:
  jmp std.resource.open_file_block_8
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp std.resource.open_file_epilogue
std.resource.open_file_block_10:
  movq $0, rcx
  call lm_list_new
  movq $r12, rcx
  movq [rbp + -64], rdx
  call lm_list_append
  movq $r12, rcx
  movq [rbp + -72], rdx
  call lm_list_append
  movq $r4, rcx
  movq $0, rdx
  movq $r12, r8
  call std.internal.runtime.call
  movq $r15, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.resource.open_file_block_19
  jmp std.resource.open_file_block_22
std.resource.open_file_block_19:
  jmp std.resource.open_file_block_19
  movq $r4, rcx
  call std.internal.runtime.destroy
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.resource.open_file_epilogue
std.resource.open_file_block_22:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -120], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -120], rcx
  movq $r4, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -120], rax
  jmp std.resource.open_file_epilogue
std.resource.open_file_epilogue:
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
.Lfunc_end_std.resource.open_file:

.globl std.resource.Poller.poll
std.resource.Poller.poll:
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
std.resource.Poller.poll_entry:
  movq $0, rax
  jmp std.resource.Poller.poll_epilogue
std.resource.Poller.poll_epilogue:
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
.Lfunc_end_std.resource.Poller.poll:

.globl std.resource.Pollable.init
std.resource.Pollable.init:
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
  mov [rbp + -72], rdx
std.resource.Pollable.init_entry:
  movq $0, rax
  jmp std.resource.Pollable.init_epilogue
std.resource.Pollable.init_epilogue:
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
.Lfunc_end_std.resource.Pollable.init:

.globl std.internal.runtime.create
std.internal.runtime.create:
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
  mov [rbp + -72], rdx
std.internal.runtime.create_entry:
std.internal.runtime.create_block_0:
  movq $0, rax
  jmp std.internal.runtime.create_epilogue
std.internal.runtime.create_epilogue:
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
.Lfunc_end_std.internal.runtime.create:

.globl std.resource.create_udp_socket
std.resource.create_udp_socket:
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
std.resource.create_udp_socket_entry:
std.resource.create_udp_socket_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_udp_socket_block_8
  jmp std.resource.create_udp_socket_block_10
std.resource.create_udp_socket_block_8:
  jmp std.resource.create_udp_socket_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_udp_socket_epilogue
std.resource.create_udp_socket_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_udp_socket_epilogue
std.resource.create_udp_socket_epilogue:
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
.Lfunc_end_std.resource.create_udp_socket:

.globl std.internal.runtime.call
std.internal.runtime.call:
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
  mov [rbp + -80], r8
std.internal.runtime.call_entry:
std.internal.runtime.call_block_0:
  movq $0, rax
  jmp std.internal.runtime.call_epilogue
std.internal.runtime.call_epilogue:
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
.Lfunc_end_std.internal.runtime.call:

.globl std.resource.Resource.init
std.resource.Resource.init:
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
  mov [rbp + -80], r8
std.resource.Resource.init_entry:
  movq $0, rax
  jmp std.resource.Resource.init_epilogue
std.resource.Resource.init_epilogue:
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
.Lfunc_end_std.resource.Resource.init:

.globl std.internal.runtime.destroy
std.internal.runtime.destroy:
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
std.internal.runtime.destroy_entry:
std.internal.runtime.destroy_block_0:
  movq $0, rax
  jmp std.internal.runtime.destroy_epilogue
std.internal.runtime.destroy_epilogue:
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
.Lfunc_end_std.internal.runtime.destroy:

.globl std.resource.Resource.is_open
std.resource.Resource.is_open:
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
std.resource.Resource.is_open_entry:
  movq $0, rax
  jmp std.resource.Resource.is_open_epilogue
std.resource.Resource.is_open_epilogue:
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
.Lfunc_end_std.resource.Resource.is_open:

.globl std.resource.create
std.resource.create:
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
std.resource.create_entry:
std.resource.create_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -80]
  movq $r2, rax
  cmpq [rbp + -80], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.resource.create_block_6
  jmp std.resource.create_block_8
std.resource.create_block_6:
  jmp std.resource.create_block_6
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp std.resource.create_epilogue
std.resource.create_block_8:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -104], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -104], rcx
  movq $r2, rdx
  movq [rbp + -64], r8
  call std.resource.Resource.init
  movq [rbp + -104], rax
  jmp std.resource.create_epilogue
std.resource.create_epilogue:
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
.Lfunc_end_std.resource.create:

.globl std.resource.ResourceReader.init
std.resource.ResourceReader.init:
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
  mov [rbp + -72], rdx
std.resource.ResourceReader.init_entry:
  movq $0, rax
  jmp std.resource.ResourceReader.init_epilogue
std.resource.ResourceReader.init_epilogue:
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
.Lfunc_end_std.resource.ResourceReader.init:

.globl std.resource.Resource.close
std.resource.Resource.close:
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
std.resource.Resource.close_entry:
  movq $0, rax
  jmp std.resource.Resource.close_epilogue
std.resource.Resource.close_epilogue:
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
.Lfunc_end_std.resource.Resource.close:

.globl std.resource.Resource._handle
std.resource.Resource._handle:
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
std.resource.Resource._handle_entry:
  movq $0, rax
  jmp std.resource.Resource._handle_epilogue
std.resource.Resource._handle_epilogue:
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
.Lfunc_end_std.resource.Resource._handle:

.globl std.resource.ResourceReader.read
std.resource.ResourceReader.read:
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
  mov [rbp + -72], rdx
std.resource.ResourceReader.read_entry:
  movq $0, rax
  jmp std.resource.ResourceReader.read_epilogue
std.resource.ResourceReader.read_epilogue:
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
.Lfunc_end_std.resource.ResourceReader.read:

.globl std.resource.ResourceWriter.write
std.resource.ResourceWriter.write:
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
  mov [rbp + -72], rdx
std.resource.ResourceWriter.write_entry:
  movq $0, rax
  jmp std.resource.ResourceWriter.write_epilogue
std.resource.ResourceWriter.write_epilogue:
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
.Lfunc_end_std.resource.ResourceWriter.write:

.globl std.resource.ResourceWriter.init
std.resource.ResourceWriter.init:
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
  mov [rbp + -72], rdx
std.resource.ResourceWriter.init_entry:
  movq $0, rax
  jmp std.resource.ResourceWriter.init_epilogue
std.resource.ResourceWriter.init_epilogue:
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
.Lfunc_end_std.resource.ResourceWriter.init:

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

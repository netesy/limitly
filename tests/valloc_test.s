	.file	"valloc_test.cpp"
	.text
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB7455:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	call	__main
	xorl	%ecx, %ecx
	movl	$4, %r9d
	movl	$12288, %r8d
	movl	$12, %edx
	call	*__imp_VirtualAlloc(%rip)
	testq	%rax, %rax
	sete	%al
	movzbl	%al, %eax
	addq	$40, %rsp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"

	.file	"1.c"
	.text
.globl main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$1819043176, -16(%rbp)
	movw	$111, -12(%rbp)
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	puts
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Gentoo 4.5.4 p1.0, pie-0.4.7) 4.5.4"
	.section	.note.GNU-stack,"",@progbits

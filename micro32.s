	.file	"micro32.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"r"
.LC1:
	.string	"bootloader"
	.text
	.globl	bootLoader
	.type	bootLoader, @function
bootLoader:
.LFB51:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$32, %rsp
	.cfi_def_cfa_offset 80
	movq	%rdi, %r14
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	call	fopen@PLT
	movq	%rax, %r12
	movq	$0, 8(%rsp)
	movq	$0, 16(%rsp)
	movl	$0, %r13d
	leaq	16(%rsp), %rbp
	leaq	8(%rsp), %rbx
	jmp	.L2
.L8:
	movl	$2, %edx
	movl	$0, %esi
	call	strtol@PLT
	movslq	%r13d, %rdx
	movl	%eax, (%r14,%rdx,4)
	leal	1(%r13), %r13d
.L3:
	movq	$0, 8(%rsp)
	movq	$0, 16(%rsp)
.L2:
	movq	%r12, %rdx
	movq	%rbp, %rsi
	movq	%rbx, %rdi
	call	getline@PLT
	testq	%rax, %rax
	jle	.L7
	movq	8(%rsp), %rdi
	movzbl	(%rdi), %eax
	cmpb	$10, %al
	je	.L3
	cmpb	$35, %al
	je	.L3
	jmp	.L8
.L7:
	movq	24(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L9
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
.L9:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE51:
	.size	bootLoader, .-bootLoader
	.section	.rodata.str1.1
.LC2:
	.string	"PC: %d\n\n"
.LC3:
	.string	"COMMAND: "
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC4:
	.string	"ALUF: %d, ALUN: %d, JUMP: %d, JFLG: %d, MS: %d, RDWR: %d\n"
	.section	.rodata.str1.1
.LC5:
	.string	"ASEL: %d, BSEL: %d, SSEL: %d\n"
.LC6:
	.string	"REG %d: %d\n"
.LC7:
	.string	"MBR: %d\n"
.LC8:
	.string	"MAR: %d\n"
.LC9:
	.string	"JR: %d\n"
	.section	.rodata.str1.8
	.align 8
.LC10:
	.string	"------------------------------------------------------------------------\n"
	.text
	.globl	printStatus
	.type	printStatus, @function
printStatus:
.LFB52:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movq	%rdi, %rbp
	movl	%edx, %ebx
	movl	%ecx, %r14d
	movl	%r8d, %r13d
	movl	%r9d, %r12d
	movl	%esi, %edx
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	movl	%ebx, %r9d
	shrl	$26, %r9d
	movl	%ebx, %r8d
	shrl	$28, %r8d
	movl	%ebx, %ecx
	shrl	$29, %ecx
	andl	$1, %ecx
	movl	%ebx, %edx
	shrl	$30, %edx
	movl	%ebx, %eax
	shrl	$24, %eax
	andl	$1, %eax
	pushq	%rax
	.cfi_def_cfa_offset 72
	movl	%ebx, %eax
	shrl	$25, %eax
	andl	$1, %eax
	pushq	%rax
	.cfi_def_cfa_offset 80
	andl	$3, %r9d
	andl	$1, %r8d
	leaq	.LC4(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movzbl	%bh, %ecx
	movl	%ebx, %edx
	shrl	$16, %edx
	movzbl	%dl, %edx
	movzbl	%bl, %r8d
	leaq	.LC5(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$10, %edi
	call	putchar@PLT
	addq	$16, %rsp
	.cfi_def_cfa_offset 64
	movl	$2, %ebx
	leaq	.LC6(%rip), %r15
.L11:
	movl	0(%rbp,%rbx,4), %ecx
	movl	%ebx, %edx
	movq	%r15, %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	addq	$1, %rbx
	cmpq	$8, %rbx
	jne	.L11
	movl	$10, %edi
	call	putchar@PLT
	movl	%r14d, %edx
	leaq	.LC7(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	%r13d, %edx
	leaq	.LC8(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	%r12d, %edx
	leaq	.LC9(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$10, %edi
	call	putchar@PLT
	leaq	.LC10(%rip), %rdi
	call	puts@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE52:
	.size	printStatus, .-printStatus
	.globl	main
	.type	main, @function
main:
.LFB50:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$263192, %rsp
	.cfi_def_cfa_offset 263216
	movq	%fs:40, %rax
	movq	%rax, 263176(%rsp)
	xorl	%eax, %eax
	leaq	1024(%rsp), %rbp
	movl	$65536, %edx
	movl	$0, %esi
	movq	%rbp, %rdi
	call	memset@PLT
	movq	%rsp, %rdx
	movl	$32, %ecx
	movl	$0, %eax
	movq	%rdx, %rdi
	rep stosq
	movq	%rbp, %rdi
	call	bootLoader
	movl	$0, (%rsp)
	movl	$1, 4(%rsp)
	movl	$-1, 1020(%rsp)
	movl	1016(%rsp), %esi
	cmpl	$4094, %esi
	ja	.L15
	movl	%esi, %eax
	movl	1024(%rsp,%rax,4), %edx
	testl	%edx, %edx
	je	.L15
	movq	%rsp, %rbp
	jmp	.L16
.L17:
	movl	%ecx, %ebx
	andl	%edi, %ebx
	jmp	.L18
.L19:
	movl	%ecx, %ebx
	orl	%edi, %ebx
	jmp	.L18
.L31:
	movl	%ecx, %ebx
	jmp	.L18
.L35:
	movl	%eax, %eax
	movl	%ebx, (%rsp,%rax,4)
	jmp	.L22
.L24:
	movl	1008(%rsp), %eax
	movl	1004(%rsp), %ecx
	movl	%ecx, 1024(%rsp,%rax,4)
	jmp	.L23
.L26:
	movl	1012(%rsp), %eax
	movl	%eax, 1016(%rsp)
.L25:
	movl	1012(%rsp), %r9d
	movl	1008(%rsp), %r8d
	movl	1004(%rsp), %ecx
	movq	%rbp, %rdi
	call	printStatus
	movl	1016(%rsp), %esi
	cmpl	$4094, %esi
	ja	.L15
	movl	%esi, %eax
	movl	1024(%rsp,%rax,4), %edx
	testl	%edx, %edx
	je	.L15
.L16:
	leal	1(%rsi), %eax
	movl	%eax, 1016(%rsp)
	movl	%edx, %eax
	shrl	$16, %eax
	movzbl	%al, %eax
	movl	(%rsp,%rax,4), %ecx
	movzbl	%dh, %eax
	movl	(%rsp,%rax,4), %edi
	movl	%edx, %eax
	shrl	$30, %eax
	cmpl	$1, %eax
	je	.L17
	testl	%eax, %eax
	je	.L31
	cmpl	$2, %eax
	je	.L19
	addl	%edi, %ecx
	cmpl	$3, %eax
	cmove	%ecx, %ebx
.L18:
	movl	%edx, %ecx
	andl	$536870912, %ecx
	movl	%ebx, %eax
	notl	%eax
	cmovne	%eax, %ebx
	testb	$-2, %dl
	je	.L22
	movzbl	%dl, %eax
	leal	-254(%rax), %ecx
	cmpl	$1, %ecx
	ja	.L35
.L22:
	testl	$33554432, %edx
	je	.L23
	testl	$16777216, %edx
	je	.L24
	movl	1008(%rsp), %eax
	movl	1024(%rsp,%rax,4), %eax
	movl	%eax, 1004(%rsp)
.L23:
	testl	$268435456, %edx
	je	.L25
	movl	%edx, %eax
	shrl	$26, %eax
	andl	$3, %eax
	je	.L26
	testl	%ebx, %ebx
	jne	.L32
	cmpl	$1, %eax
	je	.L26
.L32:
	testl	%ebx, %ebx
	je	.L33
	cmpl	$2, %eax
	je	.L26
.L33:
	testl	%ebx, %ebx
	jns	.L25
	cmpl	$3, %eax
	jne	.L25
	jmp	.L26
.L15:
	movl	$0, %edi
	call	exit@PLT
	.cfi_endproc
.LFE50:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 8.3.0-6ubuntu1) 8.3.0"
	.section	.note.GNU-stack,"",@progbits

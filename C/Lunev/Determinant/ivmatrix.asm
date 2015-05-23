	.file	"ivmatrix.c"
	.intel_syntax noprefix
	.text
.Ltext0:
	.globl	iv_msgs
	.section	.rodata
.LC0:
	.string	"Argumented pointer is null"
.LC1:
	.string	"Failed to open the file"
.LC2:
	.string	"Invalid pid"
.LC3:
	.string	"Size is below zero"
.LC4:
	.string	"Invalid number of arguments"
.LC5:
	.string	"Memory allocation failed"
	.data
	.align 32
	.type	iv_msgs, @object
	.size	iv_msgs, 48
iv_msgs:
	.quad	.LC0
	.quad	.LC1
	.quad	.LC2
	.quad	.LC3
	.quad	.LC4
	.quad	.LC5
	.globl	GLOBAL_COUNTER
	.bss
	.align 8
	.type	GLOBAL_COUNTER, @object
	.size	GLOBAL_COUNTER, 8
GLOBAL_COUNTER:
	.zero	8
	.section	.rodata
.LC6:
	.string	"ivmatrix.c"
	.align 8
.LC7:
	.string	"File:     %s\nLine:     %d\nFunction: %s\n"
	.align 8
.LC8:
	.string	"Invalid number of arguments. Need name of a file AND number of threads\n"
.LC9:
	.string	"Message : %s\n"
.LC10:
	.string	"ERRNO\t"
	.align 8
.LC11:
	.string	"Failed to get number from second argument"
	.align 8
.LC12:
	.string	"Invalid number of expecting threads to be created"
.LC13:
	.string	"r"
.LC14:
	.string	"Failed to open matrix file"
	.text
	.globl	proceed_arguments
	.type	proceed_arguments, @function
proceed_arguments:
.LFB0:
	.file 1 "ivmatrix.c"
	.loc 1 17 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	call	mcount
	mov	DWORD PTR [rbp-20], edi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	QWORD PTR [rbp-48], rcx
	.loc 1 18 0
	cmp	DWORD PTR [rbp-20], 3
	je	.L2
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip], rax
	.loc 1 18 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4458
	mov	ecx, 18
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+16], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+24]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+24], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC8
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+32]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+32], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+40]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+40], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+48]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+48], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.proceed_arguments[rip+56]
	add	rdx, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+56], rdx
	jmp	.L3
.L2:
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+8], rax
	.loc 1 20 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rax+8]
	mov	QWORD PTR [rbp-8], rax
	.loc 1 22 0
	mov	rax, QWORD PTR [rbp-48]
	mov	QWORD PTR [rax], 0
	.loc 1 23 0
	mov	rax, QWORD PTR [rbp-32]
	add	rax, 16
	mov	rdx, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-48]
	mov	rsi, rdx
	mov	rdi, rax
	call	get_long
	mov	DWORD PTR [rbp-12], eax
	.loc 1 25 0
	cmp	DWORD PTR [rbp-12], 0
	je	.L4
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+64]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+64], rax
	.loc 1 25 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4458
	mov	ecx, 25
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+72]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+72], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+80]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+80], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC11
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+88]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+88], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+96]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+96], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+104]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+104], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.proceed_arguments[rip+112]
	add	rdx, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+112], rdx
	jmp	.L3
.L4:
	.loc 1 27 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-48]
	mov	rax, QWORD PTR [rax]
	test	rax, rax
	jg	.L5
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+120]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+120], rax
	.loc 1 27 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4458
	mov	ecx, 27
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+136]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+136], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+144]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+144], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC12
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+152]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+152], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+160]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+160], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+168]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+168], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.proceed_arguments[rip+176]
	add	rdx, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+176], rdx
	jmp	.L3
.L5:
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+128]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+128], rax
	.loc 1 29 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-8]
	mov	esi, OFFSET FLAT:.LC13
	mov	rdi, rax
	call	fopen
	mov	rdx, QWORD PTR [rbp-40]
	mov	QWORD PTR [rdx], rax
	.loc 1 30 0
	mov	rax, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rax]
	test	rax, rax
	jne	.L6
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+184]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+184], rax
	.loc 1 30 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4458
	mov	ecx, 30
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+192]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+192], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+200]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+200], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC14
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+208]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+208], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+216]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+216], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.proceed_arguments[rip+224]
	add	rax, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+224], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.proceed_arguments[rip+232]
	add	rdx, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+232], rdx
	jmp	.L3
.L6:
	.loc 1 31 0 is_stmt 1
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.proceed_arguments[rip+240]
	add	rdx, 1
	mov	QWORD PTR __gcov0.proceed_arguments[rip+240], rdx
.L3:
	.loc 1 32 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	proceed_arguments, .-proceed_arguments
	.section	.rodata
.LC15:
	.string	"Failed to get arguments"
	.align 8
.LC16:
	.string	"Failed to read matrix from file\n"
	.align 8
.LC18:
	.string	"Failed to calculate matrix determinant"
.LC19:
	.string	"Determinant is %lg\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.loc 1 38 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 112
	call	mcount
	mov	DWORD PTR [rbp-84], edi
	mov	QWORD PTR [rbp-96], rsi
	mov	rax, QWORD PTR __gcov0.main[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip], rax
	.loc 1 43 0
	mov	QWORD PTR [rbp-72], 0
	.loc 1 44 0
	mov	QWORD PTR [rbp-64], 0
	.loc 1 45 0
	lea	rcx, [rbp-64]
	lea	rdx, [rbp-72]
	mov	rsi, QWORD PTR [rbp-96]
	mov	eax, DWORD PTR [rbp-84]
	mov	edi, eax
	call	proceed_arguments
	mov	DWORD PTR [rbp-76], eax
	.loc 1 50 0
	cmp	DWORD PTR [rbp-76], 0
	je	.L8
	mov	rax, QWORD PTR __gcov0.main[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+8], rax
	.loc 1 50 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4470
	mov	ecx, 50
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.main[rip+24]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+24], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.main[rip+32]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+32], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC15
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.main[rip+40]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+40], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.main[rip+48]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+48], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.main[rip+56]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+56], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	rax, QWORD PTR __gcov0.main[rip+64]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+64], rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	fclose
	mov	eax, -1
	jmp	.L12
.L8:
	mov	rax, QWORD PTR __gcov0.main[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+16], rax
	.loc 1 51 0 is_stmt 1
	mov	DWORD PTR [rbp-16], 0
	mov	QWORD PTR [rbp-8], 0
	.loc 1 55 0
	mov	rax, QWORD PTR [rbp-72]
	lea	rdx, [rbp-16]
	mov	rsi, rdx
	mov	rdi, rax
	call	get_matrix
	mov	DWORD PTR [rbp-76], eax
	mov	rax, QWORD PTR __gcov0.main[rip+72]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+72], rax
	.loc 1 57 0
	lea	rax, [rbp-48]
	mov	esi, 0
	mov	rdi, rax
	call	gettimeofday
	.loc 1 62 0
	cmp	DWORD PTR [rbp-76], -1
	jne	.L10
	mov	rax, QWORD PTR __gcov0.main[rip+80]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+80], rax
	.loc 1 62 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4470
	mov	ecx, 62
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.main[rip+96]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+96], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.main[rip+104]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+104], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC16
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.main[rip+112]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+112], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.main[rip+120]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+120], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.main[rip+128]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+128], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	rax, QWORD PTR __gcov0.main[rip+136]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+136], rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	fclose
	mov	rax, QWORD PTR __gcov0.main[rip+144]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+144], rax
	lea	rax, [rbp-16]
	mov	rdi, rax
	call	matrix_kill
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.main[rip+152]
	add	rdx, 1
	mov	QWORD PTR __gcov0.main[rip+152], rdx
	jmp	.L12
.L10:
	mov	rax, QWORD PTR __gcov0.main[rip+88]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+88], rax
	.loc 1 64 0 is_stmt 1
	mov	eax, 0
	mov	QWORD PTR [rbp-56], rax
	.loc 1 65 0
	mov	rcx, QWORD PTR [rbp-64]
	lea	rdx, [rbp-56]
	lea	rax, [rbp-16]
	mov	rsi, rcx
	mov	rdi, rax
	call	get_matrix_determinant
	mov	DWORD PTR [rbp-76], eax
	.loc 1 66 0
	cmp	DWORD PTR [rbp-76], 0
	je	.L11
	mov	rax, QWORD PTR __gcov0.main[rip+160]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+160], rax
	.loc 1 66 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4470
	mov	ecx, 66
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.main[rip+176]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+176], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.main[rip+184]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+184], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC18
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.main[rip+192]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+192], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.main[rip+200]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+200], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.main[rip+208]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+208], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	rax, QWORD PTR __gcov0.main[rip+216]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+216], rax
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	fclose
	mov	rax, QWORD PTR __gcov0.main[rip+224]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+224], rax
	lea	rax, [rbp-16]
	mov	rdi, rax
	call	matrix_kill
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.main[rip+232]
	add	rdx, 1
	mov	QWORD PTR __gcov0.main[rip+232], rdx
	jmp	.L12
.L11:
	mov	rax, QWORD PTR __gcov0.main[rip+168]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+168], rax
	.loc 1 67 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-56]
	mov	QWORD PTR [rbp-104], rax
	movsd	xmm0, QWORD PTR [rbp-104]
	mov	edi, OFFSET FLAT:.LC19
	mov	eax, 1
	call	printf
	mov	rax, QWORD PTR __gcov0.main[rip+240]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+240], rax
	.loc 1 69 0
	mov	rax, QWORD PTR [rbp-72]
	mov	rdi, rax
	call	fclose
	mov	rax, QWORD PTR __gcov0.main[rip+248]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+248], rax
	.loc 1 70 0
	lea	rax, [rbp-16]
	mov	rdi, rax
	call	matrix_kill
	mov	rax, QWORD PTR __gcov0.main[rip+256]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+256], rax
	.loc 1 71 0
	lea	rax, [rbp-32]
	mov	esi, 0
	mov	rdi, rax
	call	gettimeofday
	mov	rax, QWORD PTR __gcov0.main[rip+264]
	add	rax, 1
	mov	QWORD PTR __gcov0.main[rip+264], rax
	.loc 1 73 0
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	mov	rdi, QWORD PTR [rbp-48]
	mov	rsi, QWORD PTR [rbp-40]
	mov	rcx, rdx
	mov	rdx, rax
	call	print_diff
	.loc 1 74 0
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.main[rip+272]
	add	rdx, 1
	mov	QWORD PTR __gcov0.main[rip+272], rdx
.L12:
	mov	rdx, QWORD PTR __gcov0.main[rip+280]
	add	rdx, 1
	mov	QWORD PTR __gcov0.main[rip+280], rdx
	.loc 1 75 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.section	.rodata
.LC20:
	.string	"save"
	.text
	.globl	get_long
	.type	get_long, @function
get_long:
.LFB2:
	.loc 1 82 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	call	mcount
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	.loc 1 83 0
	cmp	QWORD PTR [rbp-40], 0
	jne	.L14
	mov	rax, QWORD PTR __gcov0.get_long[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_long[rip], rax
	.loc 1 83 0 is_stmt 0 discriminator 1
	mov	ecx, OFFSET FLAT:__PRETTY_FUNCTION__.4477
	mov	edx, 83
	mov	esi, OFFSET FLAT:.LC6
	mov	edi, OFFSET FLAT:.LC20
	call	__assert_fail
.L14:
	mov	rax, QWORD PTR __gcov0.get_long[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_long[rip+8], rax
	.loc 1 84 0 is_stmt 1
	mov	DWORD PTR [rbp-20], 10
	.loc 1 85 0
	mov	QWORD PTR [rbp-16], 0
	.loc 1 87 0
	mov	edx, DWORD PTR [rbp-20]
	lea	rcx, [rbp-16]
	mov	rax, QWORD PTR [rbp-48]
	mov	rsi, rcx
	mov	rdi, rax
	call	strtol
	mov	QWORD PTR [rbp-8], rax
	mov	rax, QWORD PTR __gcov0.get_long[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_long[rip+16], rax
	.loc 1 90 0
	call	__errno_location
	mov	rdx, QWORD PTR __gcov0.get_long[rip+24]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_long[rip+24], rdx
	mov	eax, DWORD PTR [rax]
	cmp	eax, 34
	jne	.L15
	mov	rax, QWORD PTR __gcov0.get_long[rip+32]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_long[rip+32], rax
	.loc 1 90 0 is_stmt 0 discriminator 1
	movabs	rax, 9223372036854775807
	cmp	QWORD PTR [rbp-8], rax
	je	.L16
	mov	rax, QWORD PTR __gcov0.get_long[rip+40]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_long[rip+40], rax
	movabs	rax, -9223372036854775808
	cmp	QWORD PTR [rbp-8], rax
	je	.L16
.L15:
	.loc 1 91 0 is_stmt 1
	call	__errno_location
	mov	rdx, QWORD PTR __gcov0.get_long[rip+48]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_long[rip+48], rdx
	mov	eax, DWORD PTR [rax]
	test	eax, eax
	je	.L17
	mov	rax, QWORD PTR __gcov0.get_long[rip+56]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_long[rip+56], rax
	.loc 1 91 0 is_stmt 0 discriminator 1
	cmp	QWORD PTR [rbp-8], 0
	je	.L16
.L17:
	.loc 1 92 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-16]
	cmp	rax, QWORD PTR [rbp-48]
	jne	.L18
	mov	rax, QWORD PTR __gcov0.get_long[rip+64]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_long[rip+64], rax
.L16:
	.loc 1 93 0
	mov	eax, -1
	jmp	.L20
.L18:
	.loc 1 98 0
	mov	rax, QWORD PTR [rbp-40]
	mov	rdx, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	.loc 1 99 0
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.get_long[rip+72]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_long[rip+72], rdx
.L20:
	mov	rdx, QWORD PTR __gcov0.get_long[rip+80]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_long[rip+80], rdx
	.loc 1 100 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	get_long, .-get_long
	.globl	matrix_kill
	.type	matrix_kill, @function
matrix_kill:
.LFB3:
	.loc 1 106 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	call	mcount
	mov	QWORD PTR [rbp-8], rdi
	.loc 1 107 0
	cmp	QWORD PTR [rbp-8], 0
	jne	.L22
	mov	rax, QWORD PTR __gcov0.matrix_kill[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.matrix_kill[rip], rax
	.loc 1 108 0
	jmp	.L21
.L22:
	.loc 1 109 0
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+8]
	test	rax, rax
	je	.L24
	.loc 1 111 0
	mov	rax, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rax+8]
	mov	rdi, rax
	call	free
	.loc 1 112 0
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax+8], 0
	mov	rax, QWORD PTR __gcov0.matrix_kill[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.matrix_kill[rip+8], rax
.L24:
	.loc 1 114 0
	mov	rax, QWORD PTR [rbp-8]
	mov	DWORD PTR [rax], 0
	mov	rax, QWORD PTR __gcov0.matrix_kill[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.matrix_kill[rip+16], rax
.L21:
	.loc 1 115 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	matrix_kill, .-matrix_kill
	.section	.rodata
.LC21:
	.string	"%u"
	.align 8
.LC22:
	.string	"Failed to get matrix size number, that must first in matrix definition"
.LC23:
	.string	"Too big size of matrix"
.LC24:
	.string	"%lg"
.LC25:
	.string	"Failed to read element"
	.text
	.globl	get_matrix
	.type	get_matrix, @function
get_matrix:
.LFB4:
	.loc 1 120 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	call	mcount
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	.loc 1 121 0
	cmp	QWORD PTR [rbp-40], 0
	jne	.L26
	mov	rax, QWORD PTR __gcov0.get_matrix[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip], rax
	.loc 1 121 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4488
	mov	ecx, 121
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+8], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+16], rax
	mov	rdx, QWORD PTR iv_msgs[rip]
	mov	rax, QWORD PTR stdout[rip]
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+24]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+24], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+32]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+32], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+40]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+40], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	jmp	.L35
.L26:
	.loc 1 122 0 is_stmt 1
	cmp	QWORD PTR [rbp-48], 0
	jne	.L28
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+48]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+48], rax
	.loc 1 122 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4488
	mov	ecx, 122
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+64]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+64], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+72]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+72], rax
	mov	rdx, QWORD PTR iv_msgs[rip]
	mov	rax, QWORD PTR stdout[rip]
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+80]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+80], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+88]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+88], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+96]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+96], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.get_matrix[rip+104]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+104], rdx
	jmp	.L35
.L28:
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+56]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+56], rax
	.loc 1 124 0 is_stmt 1
	mov	DWORD PTR [rbp-24], 0
	.loc 1 125 0
	lea	rdx, [rbp-24]
	mov	rax, QWORD PTR [rbp-40]
	mov	esi, OFFSET FLAT:.LC21
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_fscanf
	mov	DWORD PTR [rbp-16], eax
	.loc 1 126 0
	cmp	DWORD PTR [rbp-16], 1
	je	.L29
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+112]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+112], rax
	.loc 1 126 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4488
	mov	ecx, 126
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+120]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+120], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+128]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+128], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC22
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+136]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+136], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+144]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+144], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+152]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+152], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.get_matrix[rip+160]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+160], rdx
	jmp	.L35
.L29:
	.loc 1 127 0 is_stmt 1
	mov	eax, DWORD PTR [rbp-24]
	mov	edx, eax
	mov	eax, DWORD PTR [rbp-24]
	mov	eax, eax
	imul	rdx, rax
	mov	eax, 4294967294
	cmp	rdx, rax
	jbe	.L30
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+168]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+168], rax
	.loc 1 127 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4488
	mov	ecx, 128
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+176]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+176], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+184]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+184], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC23
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+192]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+192], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+200]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+200], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+208]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+208], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.get_matrix[rip+216]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+216], rdx
	jmp	.L35
.L30:
	.loc 1 129 0 is_stmt 1
	mov	edx, DWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rbp-24]
	imul	eax, edx
	mov	eax, eax
	mov	esi, 8
	mov	rdi, rax
	call	calloc
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-48]
	mov	QWORD PTR [rax+8], rdx
	.loc 1 130 0
	mov	rax, QWORD PTR [rbp-48]
	mov	rax, QWORD PTR [rax+8]
	test	rax, rax
	jne	.L31
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+224]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+224], rax
	.loc 1 130 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4488
	mov	ecx, 130
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+232]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+232], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+240]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+240], rax
	mov	rdx, QWORD PTR iv_msgs[rip+40]
	mov	rax, QWORD PTR stdout[rip]
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+248]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+248], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+256]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+256], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+264]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+264], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.get_matrix[rip+272]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+272], rdx
	jmp	.L35
.L31:
	.loc 1 132 0 is_stmt 1
	mov	edx, DWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rbp-24]
	imul	eax, edx
	mov	DWORD PTR [rbp-12], eax
.LBB2:
	.loc 1 133 0
	mov	DWORD PTR [rbp-20], 0
	jmp	.L32
.L34:
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+344]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+344], rax
.LBB3:
	.loc 1 134 0
	mov	eax, 0
	mov	QWORD PTR [rbp-8], rax
	.loc 1 135 0
	lea	rdx, [rbp-8]
	mov	rax, QWORD PTR [rbp-40]
	mov	esi, OFFSET FLAT:.LC24
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_fscanf
	mov	DWORD PTR [rbp-16], eax
	.loc 1 136 0
	cmp	DWORD PTR [rbp-16], 1
	je	.L33
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+280]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+280], rax
	.loc 1 136 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4488
	mov	ecx, 136
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+288]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+288], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+296]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+296], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC25
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+304]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+304], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+312]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+312], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+320]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+320], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.get_matrix[rip+328]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+328], rdx
	jmp	.L35
.L33:
	.loc 1 137 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-48]
	mov	rax, QWORD PTR [rax+8]
	mov	edx, DWORD PTR [rbp-20]
	sal	rdx, 3
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rdx], rax
.LBE3:
	.loc 1 133 0
	add	DWORD PTR [rbp-20], 1
	mov	rax, QWORD PTR __gcov0.get_matrix[rip+336]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+336], rax
.L32:
	.loc 1 133 0 is_stmt 0 discriminator 1
	mov	eax, DWORD PTR [rbp-20]
	cmp	eax, DWORD PTR [rbp-12]
	jb	.L34
.LBE2:
	.loc 1 139 0 is_stmt 1
	mov	edx, DWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rbp-48]
	mov	DWORD PTR [rax], edx
	.loc 1 140 0
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.get_matrix[rip+352]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+352], rdx
.L35:
	mov	rdx, QWORD PTR __gcov0.get_matrix[rip+360]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_matrix[rip+360], rdx
	.loc 1 141 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	get_matrix, .-get_matrix
	.section	.rodata
	.align 8
.LC26:
	.string	"Invalid amount of expected threads"
.LC27:
	.string	"Failed to create thread"
	.text
	.globl	get_threads
	.type	get_threads, @function
get_threads:
.LFB5:
	.loc 1 149 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 64
	call	mcount
	mov	QWORD PTR [rbp-40], rdi
	mov	QWORD PTR [rbp-48], rsi
	mov	QWORD PTR [rbp-56], rdx
	mov	QWORD PTR [rbp-64], rcx
	.loc 1 150 0
	cmp	QWORD PTR [rbp-48], 0
	jg	.L37
	mov	rax, QWORD PTR __gcov0.get_threads[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip], rax
	.loc 1 150 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4503
	mov	ecx, 150
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_threads[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+8], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_threads[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+16], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC26
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_threads[rip+24]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+24], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_threads[rip+32]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+32], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_threads[rip+40]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+40], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.get_threads[rip+48]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_threads[rip+48], rdx
	jmp	.L38
.L37:
	.loc 1 151 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-48]
	mov	esi, 8
	mov	rdi, rax
	call	calloc
	mov	QWORD PTR [rbp-16], rax
	.loc 1 152 0
	cmp	QWORD PTR [rbp-16], 0
	jne	.L39
	mov	rax, QWORD PTR __gcov0.get_threads[rip+56]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+56], rax
	.loc 1 152 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4503
	mov	ecx, 152
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_threads[rip+64]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+64], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_threads[rip+72]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+72], rax
	mov	rdx, QWORD PTR iv_msgs[rip+40]
	mov	rax, QWORD PTR stdout[rip]
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_threads[rip+80]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+80], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_threads[rip+88]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+88], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_threads[rip+96]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+96], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.get_threads[rip+104]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_threads[rip+104], rdx
	jmp	.L38
.L39:
	.loc 1 153 0 is_stmt 1
	cmp	QWORD PTR [rbp-64], 0
	jne	.L40
	mov	rax, QWORD PTR __gcov0.get_threads[rip+112]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+112], rax
	.loc 1 153 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4503
	mov	ecx, 153
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_threads[rip+120]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+120], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_threads[rip+128]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+128], rax
	mov	rdx, QWORD PTR iv_msgs[rip]
	mov	rax, QWORD PTR stdout[rip]
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_threads[rip+136]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+136], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_threads[rip+144]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+144], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_threads[rip+152]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+152], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.get_threads[rip+160]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_threads[rip+160], rdx
	jmp	.L38
.L40:
	.loc 1 158 0 is_stmt 1
	mov	DWORD PTR [rbp-28], 0
	.loc 1 174 0
	mov	rax, QWORD PTR [rbp-48]
	mov	esi, 32
	mov	rdi, rax
	call	calloc
	mov	QWORD PTR [rbp-8], rax
	.loc 1 176 0
	cmp	QWORD PTR [rbp-8], 0
	jne	.L41
	mov	rax, QWORD PTR __gcov0.get_threads[rip+168]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+168], rax
	.loc 1 176 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4503
	mov	ecx, 176
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_threads[rip+176]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+176], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_threads[rip+184]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+184], rax
	mov	rdx, QWORD PTR iv_msgs[rip+40]
	mov	rax, QWORD PTR stdout[rip]
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_threads[rip+192]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+192], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_threads[rip+200]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+200], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_threads[rip+208]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+208], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	free
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.get_threads[rip+216]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_threads[rip+216], rdx
	jmp	.L38
.L41:
.LBB4:
	.loc 1 182 0 is_stmt 1
	mov	QWORD PTR [rbp-24], 0
	jmp	.L42
.L44:
	mov	rax, QWORD PTR __gcov0.get_threads[rip+288]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+288], rax
	.loc 1 186 0
	mov	rax, QWORD PTR [rbp-24]
	sal	rax, 5
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-40]
	mov	QWORD PTR [rdx], rax
	.loc 1 188 0
	mov	rax, QWORD PTR [rbp-24]
	sal	rax, 5
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	DWORD PTR [rdx+16], eax
	.loc 1 189 0
	mov	rax, QWORD PTR [rbp-24]
	sal	rax, 5
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-48]
	mov	QWORD PTR [rdx+8], rax
	.loc 1 190 0
	mov	rax, QWORD PTR [rbp-24]
	sal	rax, 5
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	add	rax, rdx
	mov	rdx, QWORD PTR [rbp-24]
	lea	rcx, [0+rdx*8]
	mov	rdx, QWORD PTR [rbp-56]
	add	rdx, rcx
	mov	QWORD PTR [rax+24], rdx
	.loc 1 192 0
	mov	rax, QWORD PTR [rbp-24]
	sal	rax, 5
	mov	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-24]
	lea	rcx, [0+rax*8]
	mov	rax, QWORD PTR [rbp-16]
	add	rax, rcx
	mov	rcx, rdx
	mov	edx, OFFSET FLAT:thread_routine_debug
	mov	esi, 0
	mov	rdi, rax
	call	pthread_create
	mov	DWORD PTR [rbp-28], eax
	.loc 1 193 0
	cmp	DWORD PTR [rbp-28], 0
	je	.L43
	mov	rax, QWORD PTR __gcov0.get_threads[rip+224]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+224], rax
	.loc 1 193 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4503
	mov	ecx, 193
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_threads[rip+232]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+232], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_threads[rip+240]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+240], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC27
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_threads[rip+248]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+248], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_threads[rip+256]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+256], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_threads[rip+264]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+264], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	free
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	free
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.get_threads[rip+272]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_threads[rip+272], rdx
	jmp	.L38
.L43:
	.loc 1 182 0 is_stmt 1
	add	QWORD PTR [rbp-24], 1
	mov	rax, QWORD PTR __gcov0.get_threads[rip+280]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_threads[rip+280], rax
.L42:
	.loc 1 182 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR [rbp-24]
	cmp	rax, QWORD PTR [rbp-48]
	jl	.L44
.LBE4:
	.loc 1 197 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-64]
	mov	rdx, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	.loc 1 198 0
	mov	rax, QWORD PTR [rbp-16]
	mov	rdx, QWORD PTR __gcov0.get_threads[rip+296]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_threads[rip+296], rdx
.L38:
	.loc 1 199 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	get_threads, .-get_threads
	.section	.rodata
.LC28:
	.string	"Invalid Matrix: no data"
.LC29:
	.string	"Failed to create threads"
.LC30:
	.string	"Waiting..."
.LC31:
	.string	"Got %ld\n"
	.text
	.globl	get_matrix_determinant
	.type	get_matrix_determinant, @function
get_matrix_determinant:
.LFB6:
	.loc 1 207 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 80
	call	mcount
	mov	QWORD PTR [rbp-56], rdi
	mov	QWORD PTR [rbp-64], rsi
	mov	QWORD PTR [rbp-72], rdx
	.loc 1 208 0
	cmp	QWORD PTR [rbp-56], 0
	jne	.L46
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip], rax
	.loc 1 208 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4516
	mov	ecx, 208
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+8], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+16], rax
	mov	rdx, QWORD PTR iv_msgs[rip]
	mov	rax, QWORD PTR stdout[rip]
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+24]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+24], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+32]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+32], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+40]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+40], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	jmp	.L55
.L46:
	.loc 1 209 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-56]
	mov	rax, QWORD PTR [rax+8]
	test	rax, rax
	jne	.L48
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+48]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+48], rax
	.loc 1 209 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4516
	mov	ecx, 209
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+56]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+56], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+64]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+64], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC28
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+72]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+72], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+80]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+80], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+88]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+88], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.get_matrix_determinant[rip+96]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+96], rdx
	jmp	.L55
.L48:
	.loc 1 211 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-64]
	mov	esi, 8
	mov	rdi, rax
	call	calloc
	mov	QWORD PTR [rbp-16], rax
	.loc 1 212 0
	cmp	QWORD PTR [rbp-16], 0
	jne	.L49
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+104]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+104], rax
	.loc 1 212 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4516
	mov	ecx, 212
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+120]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+120], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+128]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+128], rax
	mov	rdx, QWORD PTR iv_msgs[rip+40]
	mov	rax, QWORD PTR stdout[rip]
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+136]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+136], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+144]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+144], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+152]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+152], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.get_matrix_determinant[rip+160]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+160], rdx
	jmp	.L55
.L49:
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+112]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+112], rax
	.loc 1 218 0 is_stmt 1
	mov	QWORD PTR [rbp-48], 0
	.loc 1 219 0
	lea	rcx, [rbp-48]
	mov	rdx, QWORD PTR [rbp-16]
	mov	rsi, QWORD PTR [rbp-64]
	mov	rax, QWORD PTR [rbp-56]
	mov	rdi, rax
	call	get_threads
	mov	QWORD PTR [rbp-8], rax
	.loc 1 220 0
	cmp	QWORD PTR [rbp-8], 0
	jne	.L50
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+168]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+168], rax
	.loc 1 220 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4516
	mov	ecx, 220
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+184]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+184], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+192]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+192], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC29
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+200]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+200], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+208]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+208], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+216]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+216], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	free
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.get_matrix_determinant[rip+224]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+224], rdx
	jmp	.L55
.L50:
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+176]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+176], rax
	.loc 1 221 0 is_stmt 1
	mov	edi, OFFSET FLAT:.LC30
	call	puts
.LBB5:
	.loc 1 225 0
	mov	QWORD PTR [rbp-40], 0
	jmp	.L51
.L52:
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+248]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+248], rax
	.loc 1 226 0 discriminator 2
	mov	rax, QWORD PTR [rbp-40]
	lea	rdx, [0+rax*8]
	mov	rax, QWORD PTR [rbp-8]
	add	rax, rdx
	mov	rax, QWORD PTR [rax]
	mov	esi, 0
	mov	rdi, rax
	call	pthread_join
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+232]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+232], rax
	.loc 1 227 0 discriminator 2
	mov	rax, QWORD PTR [rbp-40]
	mov	rsi, rax
	mov	edi, OFFSET FLAT:.LC31
	mov	eax, 0
	call	printf
	.loc 1 225 0 discriminator 2
	add	QWORD PTR [rbp-40], 1
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+240]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+240], rax
.L51:
	.loc 1 225 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR [rbp-40]
	cmp	rax, QWORD PTR [rbp-64]
	jl	.L52
.LBE5:
	.loc 1 229 0 is_stmt 1
	mov	eax, 0
	mov	QWORD PTR [rbp-32], rax
.LBB6:
	.loc 1 230 0
	mov	QWORD PTR [rbp-24], 0
	jmp	.L53
.L54:
	mov	rax, QWORD PTR __gcov0.get_matrix_determinant[rip+256]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+256], rax
	.loc 1 232 0 discriminator 2
	mov	rax, QWORD PTR [rbp-24]
	lea	rdx, [0+rax*8]
	mov	rax, QWORD PTR [rbp-16]
	add	rax, rdx
	movsd	xmm0, QWORD PTR [rax]
	movsd	xmm1, QWORD PTR [rbp-32]
	addsd	xmm0, xmm1
	movsd	QWORD PTR [rbp-32], xmm0
	.loc 1 230 0 discriminator 2
	add	QWORD PTR [rbp-24], 1
.L53:
	.loc 1 230 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR [rbp-24]
	cmp	rax, QWORD PTR [rbp-64]
	jl	.L54
.LBE6:
	.loc 1 235 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	free
	.loc 1 236 0
	mov	rax, QWORD PTR [rbp-8]
	mov	rdi, rax
	call	free
	.loc 1 237 0
	mov	rax, QWORD PTR [rbp-48]
	mov	rdi, rax
	call	free
	.loc 1 240 0
	mov	rdx, QWORD PTR [rbp-72]
	mov	rax, QWORD PTR [rbp-32]
	mov	QWORD PTR [rdx], rax
	.loc 1 241 0
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.get_matrix_determinant[rip+264]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+264], rdx
.L55:
	mov	rdx, QWORD PTR __gcov0.get_matrix_determinant[rip+272]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_matrix_determinant[rip+272], rdx
	.loc 1 243 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	get_matrix_determinant, .-get_matrix_determinant
	.globl	matrix_copy
	.type	matrix_copy, @function
matrix_copy:
.LFB7:
	.loc 1 251 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 40
	.cfi_offset 3, -24
	call	mcount
	mov	QWORD PTR [rbp-40], rdi
	.loc 1 253 0
	mov	rax, QWORD PTR [rbp-40]
	mov	eax, DWORD PTR [rax]
	mov	DWORD PTR [rbp-32], eax
	.loc 1 254 0
	mov	edx, DWORD PTR [rbp-32]
	mov	eax, DWORD PTR [rbp-32]
	imul	eax, edx
	mov	eax, eax
	mov	esi, 8
	mov	rdi, rax
	call	calloc
	mov	QWORD PTR [rbp-24], rax
	.loc 1 255 0
	mov	edx, DWORD PTR [rbp-32]
	mov	eax, DWORD PTR [rbp-32]
	imul	eax, edx
	mov	eax, eax
	lea	rdx, [0+rax*8]
	mov	rax, QWORD PTR [rbp-40]
	mov	rcx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rcx
	mov	rdi, rax
	call	memmove
	.loc 1 256 0
	mov	rax, QWORD PTR [rbp-32]
	mov	rdx, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR __gcov0.matrix_copy[rip]
	add	rcx, 1
	mov	QWORD PTR __gcov0.matrix_copy[rip], rcx
	mov	rcx, rax
	mov	rbx, rdx
	.loc 1 257 0
	mov	eax, ecx
	add	rsp, 40
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	matrix_copy, .-matrix_copy
	.section	.rodata
.LC32:
	.string	"info_ptr"
.LC33:
	.string	"%lu\n"
.LC34:
	.string	"Out"
	.text
	.globl	thread_routine_debug
	.type	thread_routine_debug, @function
thread_routine_debug:
.LFB8:
	.loc 1 262 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 80
	call	mcount
	mov	QWORD PTR [rbp-72], rdi
	.loc 1 263 0
	cmp	QWORD PTR [rbp-72], 0
	jne	.L59
	mov	rax, QWORD PTR __gcov0.thread_routine_debug[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine_debug[rip], rax
	.loc 1 263 0 is_stmt 0 discriminator 1
	mov	ecx, OFFSET FLAT:__PRETTY_FUNCTION__.4536
	mov	edx, 263
	mov	esi, OFFSET FLAT:.LC6
	mov	edi, OFFSET FLAT:.LC32
	call	__assert_fail
.L59:
	mov	rax, QWORD PTR __gcov0.thread_routine_debug[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine_debug[rip+8], rax
	.loc 1 264 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-72]
	mov	rdx, QWORD PTR [rax]
	mov	QWORD PTR [rbp-32], rdx
	mov	rdx, QWORD PTR [rax+8]
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rax+16]
	mov	QWORD PTR [rbp-16], rdx
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR [rbp-8], rax
	.loc 1 265 0
	mov	eax, DWORD PTR [rbp-16]
	mov	DWORD PTR [rbp-56], eax
	.loc 1 266 0
	mov	rax, QWORD PTR [rbp-24]
	mov	QWORD PTR [rbp-40], rax
	.loc 1 267 0
	mov	rax, QWORD PTR [rbp-32]
	mov	eax, DWORD PTR [rax]
	mov	DWORD PTR [rbp-52], eax
	.loc 1 269 0
	mov	eax, DWORD PTR [rbp-52]
	imul	eax, eax, 2000000000
	mov	eax, eax
	cqo
	idiv	QWORD PTR [rbp-40]
	mov	QWORD PTR [rbp-48], rax
	.loc 1 270 0
	mov	rax, QWORD PTR [rbp-48]
	mov	rsi, rax
	mov	edi, OFFSET FLAT:.LC33
	mov	eax, 0
	call	printf
	.loc 1 272 0
	jmp	.L60
.L62:
	mov	rax, QWORD PTR __gcov0.thread_routine_debug[rip+40]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine_debug[rip+40], rax
	.loc 1 273 0
	cmp	DWORD PTR [rbp-56], 0
	jne	.L61
	mov	rax, QWORD PTR __gcov0.thread_routine_debug[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine_debug[rip+16], rax
	.loc 1 273 0 is_stmt 0 discriminator 1
	mov	rcx, QWORD PTR [rbp-48]
	movabs	rdx, -6067343680855748867
	mov	rax, rcx
	mul	rdx
	mov	rax, rdx
	shr	rax, 26
	imul	rax, rax, 100000000
	sub	rcx, rax
	mov	rax, rcx
	test	rax, rax
	jne	.L61
	mov	rax, QWORD PTR __gcov0.thread_routine_debug[rip+24]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine_debug[rip+24], rax
	.loc 1 274 0 is_stmt 1
	mov	rax, QWORD PTR stderr[rip]
	mov	rdx, QWORD PTR [rbp-48]
	mov	esi, OFFSET FLAT:.LC33
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
.L61:
	.loc 1 272 0
	sub	QWORD PTR [rbp-48], 1
	mov	rax, QWORD PTR __gcov0.thread_routine_debug[rip+32]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine_debug[rip+32], rax
.L60:
	.loc 1 272 0 is_stmt 0 discriminator 1
	cmp	QWORD PTR [rbp-48], 0
	jne	.L62
	mov	rax, QWORD PTR __gcov0.thread_routine_debug[rip+48]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine_debug[rip+48], rax
	.loc 1 275 0 is_stmt 1
	mov	edi, OFFSET FLAT:.LC34
	call	puts
	mov	rax, QWORD PTR __gcov0.thread_routine_debug[rip+56]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine_debug[rip+56], rax
	.loc 1 276 0
	mov	edi, 0
	call	pthread_exit
	.cfi_endproc
.LFE8:
	.size	thread_routine_debug, .-thread_routine_debug
	.section	.rodata
.LC35:
	.string	"Failed to get minor"
.LC36:
	.string	"Failed to convert matrix"
	.text
	.globl	thread_routine
	.type	thread_routine, @function
thread_routine:
.LFB9:
	.loc 1 281 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 112
	call	mcount
	mov	QWORD PTR [rbp-104], rdi
	.loc 1 282 0
	cmp	QWORD PTR [rbp-104], 0
	jne	.L64
	mov	rax, QWORD PTR __gcov0.thread_routine[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip], rax
	.loc 1 282 0 is_stmt 0 discriminator 1
	mov	ecx, OFFSET FLAT:__PRETTY_FUNCTION__.4548
	mov	edx, 282
	mov	esi, OFFSET FLAT:.LC6
	mov	edi, OFFSET FLAT:.LC32
	call	__assert_fail
.L64:
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+8], rax
	.loc 1 283 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-104]
	mov	rdx, QWORD PTR [rax]
	mov	QWORD PTR [rbp-32], rdx
	mov	rdx, QWORD PTR [rax+8]
	mov	QWORD PTR [rbp-24], rdx
	mov	rdx, QWORD PTR [rax+16]
	mov	QWORD PTR [rbp-16], rdx
	mov	rax, QWORD PTR [rax+24]
	mov	QWORD PTR [rbp-8], rax
	.loc 1 289 0
	mov	rax, QWORD PTR [rbp-32]
	mov	eax, DWORD PTR [rax]
	mov	DWORD PTR [rbp-92], eax
	.loc 1 290 0
	mov	rax, QWORD PTR [rbp-24]
	mov	DWORD PTR [rbp-88], eax
	.loc 1 291 0
	mov	eax, 0
	mov	QWORD PTR [rbp-72], rax
	.loc 1 292 0
	mov	eax, 0
	mov	QWORD PTR [rbp-80], rax
	.loc 1 293 0
	mov	QWORD PTR [rbp-64], 0
	.loc 1 294 0
	mov	rax, QWORD PTR [rbp-32]
	mov	rdi, rax
	call	matrix_copy
	mov	ecx, eax
	mov	rax, rdx
	mov	DWORD PTR [rbp-48], ecx
	mov	QWORD PTR [rbp-40], rax
	.loc 1 298 0
	mov	DWORD PTR [rbp-84], 0
.LBB7:
	.loc 1 299 0
	mov	eax, DWORD PTR [rbp-16]
	mov	DWORD PTR [rbp-96], eax
	jmp	.L65
.L71:
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+176]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+176], rax
.LBB8:
	.loc 1 301 0
	mov	edx, DWORD PTR [rbp-96]
	lea	rax, [rbp-48]
	mov	esi, 0
	mov	rdi, rax
	call	get_minor
	mov	QWORD PTR [rbp-64], rax
	.loc 1 304 0
	cmp	QWORD PTR [rbp-64], 0
	jne	.L66
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+16], rax
	.loc 1 304 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4548
	mov	ecx, 304
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+32]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+32], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+40]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+40], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC35
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+48]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+48], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+56]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+56], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+64]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+64], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+72]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+72], rax
	lea	rax, [rbp-48]
	mov	rdi, rax
	call	matrix_kill
	mov	rax, -1
	jmp	.L72
.L66:
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+24]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+24], rax
	.loc 1 309 0 is_stmt 1
	lea	rdx, [rbp-80]
	mov	rax, QWORD PTR [rbp-64]
	mov	rsi, rdx
	mov	rdi, rax
	call	gauss
	mov	DWORD PTR [rbp-84], eax
	.loc 1 310 0
	cmp	DWORD PTR [rbp-84], 0
	je	.L68
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+80]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+80], rax
	.loc 1 310 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4548
	mov	ecx, 310
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+88]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+88], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+96]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+96], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC36
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+104]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+104], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+112]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+112], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+120]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+120], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+128]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+128], rax
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	matrix_kill
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+136]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+136], rax
	lea	rax, [rbp-48]
	mov	rdi, rax
	call	matrix_kill
	mov	rax, -1
	mov	rdx, QWORD PTR __gcov0.thread_routine[rip+144]
	add	rdx, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+144], rdx
	jmp	.L72
.L68:
	.loc 1 311 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-40]
	mov	edx, DWORD PTR [rbp-96]
	sal	rdx, 3
	add	rax, rdx
	movsd	xmm1, QWORD PTR [rax]
	movsd	xmm0, QWORD PTR [rbp-80]
	mulsd	xmm0, xmm1
	mov	eax, DWORD PTR [rbp-96]
	and	eax, 1
	test	eax, eax
	jne	.L69
	.loc 1 311 0 is_stmt 0 discriminator 1
	movabs	rax, 4607182418800017408
	mov	rdx, QWORD PTR __gcov0.thread_routine[rip+152]
	add	rdx, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+152], rdx
	jmp	.L70
.L69:
	.loc 1 311 0 discriminator 2
	movabs	rax, -4616189618054758400
	mov	rdx, QWORD PTR __gcov0.thread_routine[rip+160]
	add	rdx, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+160], rdx
.L70:
	.loc 1 311 0 discriminator 3
	mov	QWORD PTR [rbp-112], rax
	movsd	xmm2, QWORD PTR [rbp-112]
	mulsd	xmm0, xmm2
	movsd	QWORD PTR [rbp-56], xmm0
	.loc 1 312 0 is_stmt 1 discriminator 3
	movsd	xmm0, QWORD PTR [rbp-72]
	addsd	xmm0, QWORD PTR [rbp-56]
	movsd	QWORD PTR [rbp-72], xmm0
	.loc 1 313 0 discriminator 3
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	matrix_kill
	.loc 1 314 0 discriminator 3
	mov	rax, QWORD PTR [rbp-64]
	mov	rdi, rax
	call	free
.LBE8:
	.loc 1 299 0 discriminator 3
	mov	eax, DWORD PTR [rbp-88]
	add	DWORD PTR [rbp-96], eax
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+168]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+168], rax
.L65:
	.loc 1 299 0 is_stmt 0 discriminator 1
	mov	eax, DWORD PTR [rbp-96]
	cmp	eax, DWORD PTR [rbp-92]
	jb	.L71
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+184]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+184], rax
.LBE7:
	.loc 1 317 0 is_stmt 1
	mov	rdx, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rbp-72]
	mov	QWORD PTR [rdx], rax
	.loc 1 318 0
	lea	rax, [rbp-48]
	mov	rdi, rax
	call	matrix_kill
	mov	rax, QWORD PTR __gcov0.thread_routine[rip+192]
	add	rax, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+192], rax
	.loc 1 320 0
	mov	edi, 0
	call	pthread_exit
.L72:
	mov	rdx, QWORD PTR __gcov0.thread_routine[rip+200]
	add	rdx, 1
	mov	QWORD PTR __gcov0.thread_routine[rip+200], rdx
	.loc 1 321 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	thread_routine, .-thread_routine
	.globl	gauss
	.type	gauss, @function
gauss:
.LFB10:
	.loc 1 330 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	call	mcount
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	.loc 1 331 0
	cmp	QWORD PTR [rbp-24], 0
	jne	.L74
	mov	rax, QWORD PTR __gcov0.gauss[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip], rax
	.loc 1 331 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4566
	mov	ecx, 331
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.gauss[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+8], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.gauss[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+16], rax
	mov	rdx, QWORD PTR iv_msgs[rip+40]
	mov	rax, QWORD PTR stdout[rip]
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.gauss[rip+24]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+24], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.gauss[rip+32]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+32], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.gauss[rip+40]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+40], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.gauss[rip+48]
	add	rdx, 1
	mov	QWORD PTR __gcov0.gauss[rip+48], rdx
	jmp	.L75
.L74:
	.loc 1 332 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rax+8]
	test	rax, rax
	jne	.L76
	mov	rax, QWORD PTR __gcov0.gauss[rip+56]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+56], rax
	.loc 1 332 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4566
	mov	ecx, 332
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.gauss[rip+64]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+64], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.gauss[rip+72]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+72], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC28
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.gauss[rip+80]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+80], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.gauss[rip+88]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+88], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.gauss[rip+96]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+96], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, -1
	mov	rdx, QWORD PTR __gcov0.gauss[rip+104]
	add	rdx, 1
	mov	QWORD PTR __gcov0.gauss[rip+104], rdx
	jmp	.L75
.L76:
.LBB9:
	.loc 1 334 0 is_stmt 1
	mov	DWORD PTR [rbp-16], 0
	jmp	.L77
.L83:
	mov	rax, QWORD PTR __gcov0.gauss[rip+144]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+144], rax
	.loc 1 336 0
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-16]
	mov	ecx, eax
	mov	eax, DWORD PTR [rbp-16]
	add	rax, rcx
	sal	rax, 3
	add	rax, rdx
	movsd	xmm1, QWORD PTR [rax]
	movsd	xmm0, QWORD PTR .LC39[rip]
	andpd	xmm0, xmm1
	movsd	xmm1, QWORD PTR .LC40[rip]
	ucomisd	xmm1, xmm0
	jbe	.L78
	mov	rax, QWORD PTR __gcov0.gauss[rip+112]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+112], rax
	.loc 1 337 0
	mov	edx, DWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-24]
	mov	esi, edx
	mov	rdi, rax
	call	search_below_nzero_swap
.L78:
	.loc 1 338 0
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-16]
	mov	ecx, eax
	mov	eax, DWORD PTR [rbp-16]
	add	rax, rcx
	sal	rax, 3
	add	rax, rdx
	movsd	xmm1, QWORD PTR [rax]
	movsd	xmm0, QWORD PTR .LC39[rip]
	andpd	xmm0, xmm1
	movsd	xmm1, QWORD PTR .LC40[rip]
	ucomisd	xmm1, xmm0
	jbe	.L88
	mov	rax, QWORD PTR __gcov0.gauss[rip+128]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+128], rax
	.loc 1 339 0
	jmp	.L82
.L88:
	mov	rax, QWORD PTR __gcov0.gauss[rip+120]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+120], rax
	.loc 1 340 0
	mov	edx, DWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-24]
	mov	esi, edx
	mov	rdi, rax
	call	annihilate_below
.L82:
	.loc 1 334 0
	add	DWORD PTR [rbp-16], 1
	mov	rax, QWORD PTR __gcov0.gauss[rip+136]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+136], rax
.L77:
	.loc 1 334 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	cmp	eax, DWORD PTR [rbp-16]
	ja	.L83
.LBE9:
	.loc 1 343 0 is_stmt 1
	movabs	rax, 4607182418800017408
	mov	QWORD PTR [rbp-8], rax
.LBB10:
	.loc 1 344 0
	mov	DWORD PTR [rbp-12], 0
	jmp	.L84
.L85:
	mov	rax, QWORD PTR __gcov0.gauss[rip+152]
	add	rax, 1
	mov	QWORD PTR __gcov0.gauss[rip+152], rax
	.loc 1 345 0 discriminator 2
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-12]
	mov	ecx, eax
	mov	eax, DWORD PTR [rbp-12]
	add	rax, rcx
	sal	rax, 3
	add	rax, rdx
	movsd	xmm0, QWORD PTR [rax]
	movsd	xmm1, QWORD PTR [rbp-8]
	mulsd	xmm0, xmm1
	movsd	QWORD PTR [rbp-8], xmm0
	.loc 1 344 0 discriminator 2
	add	DWORD PTR [rbp-12], 1
.L84:
	.loc 1 344 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	cmp	eax, DWORD PTR [rbp-12]
	ja	.L85
.LBE10:
	.loc 1 346 0 is_stmt 1
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rdx], rax
	.loc 1 347 0
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.gauss[rip+160]
	add	rdx, 1
	mov	QWORD PTR __gcov0.gauss[rip+160], rdx
.L75:
	.loc 1 348 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	gauss, .-gauss
	.globl	search_below_nzero_swap
	.type	search_below_nzero_swap, @function
search_below_nzero_swap:
.LFB11:
	.loc 1 353 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	call	mcount
	mov	QWORD PTR [rbp-24], rdi
	mov	DWORD PTR [rbp-28], esi
	.loc 1 354 0
	mov	eax, DWORD PTR [rbp-28]
	add	eax, 1
	mov	DWORD PTR [rbp-12], eax
	.loc 1 355 0
	jmp	.L90
.L93:
	mov	rax, QWORD PTR __gcov0.search_below_nzero_swap[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.search_below_nzero_swap[rip+8], rax
	.loc 1 356 0
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-12]
	mov	ecx, eax
	mov	eax, DWORD PTR [rbp-28]
	add	rax, rcx
	sal	rax, 3
	add	rax, rdx
	movsd	xmm1, QWORD PTR [rax]
	movsd	xmm0, QWORD PTR .LC39[rip]
	andpd	xmm0, xmm1
	movsd	xmm1, QWORD PTR .LC40[rip]
	ucomisd	xmm1, xmm0
	seta	al
	xor	eax, 1
	test	al, al
	je	.L91
	.loc 1 357 0
	jmp	.L92
.L91:
	.loc 1 355 0
	add	DWORD PTR [rbp-12], 1
	mov	rax, QWORD PTR __gcov0.search_below_nzero_swap[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.search_below_nzero_swap[rip], rax
.L90:
	.loc 1 355 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	cmp	eax, DWORD PTR [rbp-12]
	ja	.L93
.L92:
	.loc 1 358 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-12]
	mov	ecx, eax
	mov	eax, DWORD PTR [rbp-28]
	add	rax, rcx
	sal	rax, 3
	add	rax, rdx
	movsd	xmm1, QWORD PTR [rax]
	movsd	xmm0, QWORD PTR .LC39[rip]
	andpd	xmm0, xmm1
	movsd	xmm1, QWORD PTR .LC40[rip]
	ucomisd	xmm1, xmm0
	jbe	.L100
	mov	rax, QWORD PTR __gcov0.search_below_nzero_swap[rip+24]
	add	rax, 1
	mov	QWORD PTR __gcov0.search_below_nzero_swap[rip+24], rax
	.loc 1 359 0
	jmp	.L89
.L100:
	mov	rax, QWORD PTR __gcov0.search_below_nzero_swap[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.search_below_nzero_swap[rip+16], rax
	.loc 1 360 0
	mov	edx, DWORD PTR [rbp-28]
	mov	ecx, DWORD PTR [rbp-12]
	mov	rax, QWORD PTR [rbp-24]
	mov	esi, ecx
	mov	rdi, rax
	call	swap_strings
.LBB11:
	.loc 1 361 0
	mov	QWORD PTR [rbp-8], 0
	mov	rax, QWORD PTR __gcov0.search_below_nzero_swap[rip+32]
	add	rax, 1
	mov	QWORD PTR __gcov0.search_below_nzero_swap[rip+32], rax
	jmp	.L97
.L98:
	mov	rax, QWORD PTR __gcov0.search_below_nzero_swap[rip+40]
	add	rax, 1
	mov	QWORD PTR __gcov0.search_below_nzero_swap[rip+40], rax
	.loc 1 362 0 discriminator 2
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-12]
	mov	ecx, eax
	mov	rax, QWORD PTR [rbp-8]
	add	rax, rcx
	sal	rax, 3
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-12]
	mov	esi, eax
	mov	rax, QWORD PTR [rbp-8]
	add	rax, rsi
	sal	rax, 3
	add	rax, rcx
	movsd	xmm1, QWORD PTR [rax]
	movsd	xmm0, QWORD PTR .LC41[rip]
	xorpd	xmm0, xmm1
	movsd	QWORD PTR [rdx], xmm0
	.loc 1 361 0 discriminator 2
	add	QWORD PTR [rbp-8], 1
.L97:
	.loc 1 361 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	mov	eax, eax
	cmp	rax, QWORD PTR [rbp-8]
	jg	.L98
.L89:
.LBE11:
	.loc 1 363 0 is_stmt 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	search_below_nzero_swap, .-search_below_nzero_swap
	.globl	swap_strings
	.type	swap_strings, @function
swap_strings:
.LFB12:
	.loc 1 368 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	call	mcount
	mov	QWORD PTR [rbp-24], rdi
	mov	DWORD PTR [rbp-28], esi
	mov	DWORD PTR [rbp-32], edx
.LBB12:
	.loc 1 369 0
	mov	DWORD PTR [rbp-12], 0
	jmp	.L102
.L103:
	mov	rax, QWORD PTR __gcov0.swap_strings[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.swap_strings[rip], rax
.LBB13:
	.loc 1 371 0 discriminator 2
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-28]
	mov	ecx, eax
	mov	eax, DWORD PTR [rbp-12]
	add	rax, rcx
	sal	rax, 3
	add	rax, rdx
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR [rbp-8], rax
	.loc 1 372 0 discriminator 2
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-28]
	mov	ecx, eax
	mov	eax, DWORD PTR [rbp-12]
	add	rax, rcx
	sal	rax, 3
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-32]
	mov	esi, eax
	mov	eax, DWORD PTR [rbp-12]
	add	rax, rsi
	sal	rax, 3
	add	rax, rcx
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR [rdx], rax
	.loc 1 373 0 discriminator 2
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-32]
	mov	ecx, eax
	mov	eax, DWORD PTR [rbp-12]
	add	rax, rcx
	sal	rax, 3
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-8]
	mov	QWORD PTR [rdx], rax
.LBE13:
	.loc 1 369 0 discriminator 2
	add	DWORD PTR [rbp-12], 1
.L102:
	.loc 1 369 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	cmp	eax, DWORD PTR [rbp-12]
	ja	.L103
	mov	rax, QWORD PTR __gcov0.swap_strings[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.swap_strings[rip+8], rax
.LBE12:
	.loc 1 375 0 is_stmt 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	swap_strings, .-swap_strings
	.globl	annihilate_below
	.type	annihilate_below, @function
annihilate_below:
.LFB13:
	.loc 1 387 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	call	mcount
	mov	QWORD PTR [rbp-24], rdi
	mov	DWORD PTR [rbp-28], esi
.LBB14:
	.loc 1 388 0
	mov	eax, DWORD PTR [rbp-28]
	add	eax, 1
	mov	DWORD PTR [rbp-4], eax
	jmp	.L105
.L106:
	mov	rax, QWORD PTR __gcov0.annihilate_below[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.annihilate_below[rip+8], rax
	.loc 1 389 0 discriminator 2
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-4]
	mov	ecx, eax
	mov	eax, DWORD PTR [rbp-28]
	add	rax, rcx
	sal	rax, 3
	add	rax, rdx
	movsd	xmm1, QWORD PTR [rax]
	movsd	xmm0, QWORD PTR .LC41[rip]
	xorpd	xmm0, xmm1
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-28]
	mov	ecx, eax
	mov	eax, DWORD PTR [rbp-28]
	add	rax, rcx
	sal	rax, 3
	add	rax, rdx
	movsd	xmm1, QWORD PTR [rax]
	divsd	xmm0, xmm1
	mov	edx, DWORD PTR [rbp-4]
	mov	ecx, DWORD PTR [rbp-28]
	mov	rax, QWORD PTR [rbp-24]
	mov	esi, ecx
	mov	rdi, rax
	call	add_string
	.loc 1 388 0 discriminator 2
	add	DWORD PTR [rbp-4], 1
	mov	rax, QWORD PTR __gcov0.annihilate_below[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.annihilate_below[rip], rax
.L105:
	.loc 1 388 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	cmp	eax, DWORD PTR [rbp-4]
	ja	.L106
	mov	rax, QWORD PTR __gcov0.annihilate_below[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.annihilate_below[rip+16], rax
.LBE14:
	.loc 1 390 0 is_stmt 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	annihilate_below, .-annihilate_below
	.globl	add_string
	.type	add_string, @function
add_string:
.LFB14:
	.loc 1 395 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 40
	call	mcount
	mov	QWORD PTR [rbp-24], rdi
	mov	DWORD PTR [rbp-28], esi
	mov	DWORD PTR [rbp-32], edx
	movsd	QWORD PTR [rbp-40], xmm0
.LBB15:
	.loc 1 396 0
	mov	DWORD PTR [rbp-4], 0
	jmp	.L108
.L109:
	mov	rax, QWORD PTR __gcov0.add_string[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.add_string[rip], rax
	.loc 1 397 0 discriminator 2
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-32]
	mov	ecx, eax
	mov	eax, DWORD PTR [rbp-4]
	add	rax, rcx
	sal	rax, 3
	add	rdx, rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-32]
	mov	esi, eax
	mov	eax, DWORD PTR [rbp-4]
	add	rax, rsi
	sal	rax, 3
	add	rax, rcx
	movsd	xmm1, QWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-24]
	mov	rcx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-28]
	mov	esi, eax
	mov	eax, DWORD PTR [rbp-4]
	add	rax, rsi
	sal	rax, 3
	add	rax, rcx
	movsd	xmm0, QWORD PTR [rax]
	mulsd	xmm0, QWORD PTR [rbp-40]
	addsd	xmm0, xmm1
	movsd	QWORD PTR [rdx], xmm0
	.loc 1 396 0 discriminator 2
	add	DWORD PTR [rbp-4], 1
.L108:
	.loc 1 396 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	cmp	eax, DWORD PTR [rbp-4]
	ja	.L109
	mov	rax, QWORD PTR __gcov0.add_string[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.add_string[rip+8], rax
.LBE15:
	.loc 1 398 0 is_stmt 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	add_string, .-add_string
	.section	.rodata
	.align 8
.LC42:
	.string	"Failed to copy numbers to minor"
	.text
	.globl	get_minor
	.type	get_minor, @function
get_minor:
.LFB15:
	.loc 1 404 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	rbx
	sub	rsp, 72
	.cfi_offset 3, -24
	call	mcount
	mov	QWORD PTR [rbp-72], rdi
	mov	DWORD PTR [rbp-76], esi
	mov	DWORD PTR [rbp-80], edx
	.loc 1 405 0
	cmp	QWORD PTR [rbp-72], 0
	jne	.L111
	mov	rax, QWORD PTR __gcov0.get_minor[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip], rax
	.loc 1 405 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4622
	mov	ecx, 405
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_minor[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+8], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_minor[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+16], rax
	mov	rdx, QWORD PTR iv_msgs[rip]
	mov	rax, QWORD PTR stdout[rip]
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_minor[rip+24]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+24], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_minor[rip+32]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+32], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_minor[rip+40]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+40], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.get_minor[rip+48]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_minor[rip+48], rdx
	jmp	.L112
.L111:
	.loc 1 406 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-72]
	mov	edx, DWORD PTR [rax]
	mov	rax, QWORD PTR [rbp-72]
	mov	eax, DWORD PTR [rax]
	imul	eax, edx
	mov	DWORD PTR [rbp-44], eax
	.loc 1 408 0
	mov	rax, QWORD PTR [rbp-72]
	mov	eax, DWORD PTR [rax]
	lea	edx, [rax-1]
	mov	rax, QWORD PTR [rbp-72]
	mov	eax, DWORD PTR [rax]
	sub	eax, 1
	imul	eax, edx
	mov	eax, eax
	mov	esi, 8
	mov	rdi, rax
	call	calloc
	mov	QWORD PTR [rbp-40], rax
	.loc 1 409 0
	cmp	QWORD PTR [rbp-40], 0
	jne	.L113
	mov	rax, QWORD PTR __gcov0.get_minor[rip+56]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+56], rax
	.loc 1 409 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4622
	mov	ecx, 409
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_minor[rip+64]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+64], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_minor[rip+72]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+72], rax
	mov	rdx, QWORD PTR iv_msgs[rip+40]
	mov	rax, QWORD PTR stdout[rip]
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_minor[rip+80]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+80], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_minor[rip+88]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+88], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_minor[rip+96]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+96], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.get_minor[rip+104]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_minor[rip+104], rdx
	jmp	.L112
.L113:
	.loc 1 411 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-72]
	mov	rax, QWORD PTR [rax+8]
	mov	QWORD PTR [rbp-32], rax
	.loc 1 416 0
	mov	DWORD PTR [rbp-52], 0
.LBB16:
	.loc 1 417 0
	mov	DWORD PTR [rbp-48], 0
	jmp	.L114
.L118:
	mov	rax, QWORD PTR __gcov0.get_minor[rip+128]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+128], rax
	.loc 1 419 0
	mov	rax, QWORD PTR [rbp-72]
	mov	ecx, DWORD PTR [rax]
	mov	eax, DWORD PTR [rbp-48]
	mov	edx, 0
	div	ecx
	mov	eax, edx
	cmp	eax, DWORD PTR [rbp-80]
	je	.L115
	mov	rax, QWORD PTR __gcov0.get_minor[rip+112]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+112], rax
	.loc 1 419 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR [rbp-72]
	mov	ebx, DWORD PTR [rax]
	mov	eax, DWORD PTR [rbp-48]
	mov	edx, 0
	div	ebx
	cmp	eax, DWORD PTR [rbp-76]
	jne	.L116
.L115:
	.loc 1 420 0 is_stmt 1
	jmp	.L117
.L116:
	.loc 1 421 0
	mov	eax, DWORD PTR [rbp-52]
	lea	rdx, [0+rax*8]
	mov	rax, QWORD PTR [rbp-40]
	add	rdx, rax
	mov	eax, DWORD PTR [rbp-48]
	lea	rcx, [0+rax*8]
	mov	rax, QWORD PTR [rbp-32]
	add	rax, rcx
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR [rdx], rax
	.loc 1 422 0
	add	DWORD PTR [rbp-52], 1
	mov	rax, QWORD PTR __gcov0.get_minor[rip+120]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+120], rax
.L117:
	.loc 1 417 0
	add	DWORD PTR [rbp-48], 1
.L114:
	.loc 1 417 0 is_stmt 0 discriminator 1
	mov	eax, DWORD PTR [rbp-48]
	cmp	eax, DWORD PTR [rbp-44]
	jb	.L118
.LBE16:
	.loc 1 425 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-72]
	mov	eax, DWORD PTR [rax]
	lea	edx, [rax-1]
	mov	rax, QWORD PTR [rbp-72]
	mov	eax, DWORD PTR [rax]
	sub	eax, 1
	imul	eax, edx
	cmp	eax, DWORD PTR [rbp-52]
	je	.L119
	mov	rax, QWORD PTR __gcov0.get_minor[rip+136]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+136], rax
	.loc 1 425 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4622
	mov	ecx, 425
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_minor[rip+144]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+144], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_minor[rip+152]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+152], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	edx, OFFSET FLAT:.LC42
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_minor[rip+160]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+160], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_minor[rip+168]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+168], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_minor[rip+176]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+176], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	free
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.get_minor[rip+184]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_minor[rip+184], rdx
	jmp	.L112
.L119:
	.loc 1 426 0 is_stmt 1
	mov	esi, 16
	mov	edi, 1
	call	calloc
	mov	QWORD PTR [rbp-24], rax
	.loc 1 427 0
	cmp	QWORD PTR [rbp-24], 0
	jne	.L120
	mov	rax, QWORD PTR __gcov0.get_minor[rip+192]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+192], rax
	.loc 1 427 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR stdout[rip]
	mov	r8d, OFFSET FLAT:__PRETTY_FUNCTION__.4622
	mov	ecx, 427
	mov	edx, OFFSET FLAT:.LC6
	mov	esi, OFFSET FLAT:.LC7
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_minor[rip+200]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+200], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_minor[rip+208]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+208], rax
	mov	rdx, QWORD PTR iv_msgs[rip+40]
	mov	rax, QWORD PTR stdout[rip]
	mov	esi, OFFSET FLAT:.LC9
	mov	rdi, rax
	mov	eax, 0
	call	fprintf
	mov	rax, QWORD PTR __gcov0.get_minor[rip+216]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+216], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rdi, rax
	call	fflush
	mov	rax, QWORD PTR __gcov0.get_minor[rip+224]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+224], rax
	mov	edi, OFFSET FLAT:.LC10
	call	perror
	mov	rax, QWORD PTR __gcov0.get_minor[rip+232]
	add	rax, 1
	mov	QWORD PTR __gcov0.get_minor[rip+232], rax
	mov	rax, QWORD PTR stdout[rip]
	mov	rsi, rax
	mov	edi, 10
	call	fputc
	mov	rax, QWORD PTR [rbp-40]
	mov	rdi, rax
	call	free
	mov	eax, 0
	mov	rdx, QWORD PTR __gcov0.get_minor[rip+240]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_minor[rip+240], rdx
	jmp	.L112
.L120:
	.loc 1 429 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-72]
	mov	eax, DWORD PTR [rax]
	lea	edx, [rax-1]
	mov	rax, QWORD PTR [rbp-24]
	mov	DWORD PTR [rax], edx
	.loc 1 430 0
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rbp-40]
	mov	QWORD PTR [rax+8], rdx
	.loc 1 432 0
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR __gcov0.get_minor[rip+248]
	add	rdx, 1
	mov	QWORD PTR __gcov0.get_minor[rip+248], rdx
.L112:
	.loc 1 433 0
	add	rsp, 72
	pop	rbx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	get_minor, .-get_minor
	.section	.rodata
.LC43:
	.string	"Size = %u\n"
.LC44:
	.string	"%4lg"
	.text
	.globl	print_matrix
	.type	print_matrix, @function
print_matrix:
.LFB16:
	.loc 1 439 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	call	mcount
	mov	QWORD PTR [rbp-24], rdi
	mov	rax, QWORD PTR __gcov0.print_matrix[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.print_matrix[rip], rax
	.loc 1 440 0
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	mov	esi, eax
	mov	edi, OFFSET FLAT:.LC43
	mov	eax, 0
	call	printf
.LBB17:
	.loc 1 441 0
	mov	DWORD PTR [rbp-8], 0
	jmp	.L122
.L125:
	mov	rax, QWORD PTR __gcov0.print_matrix[rip+32]
	add	rax, 1
	mov	QWORD PTR __gcov0.print_matrix[rip+32], rax
.LBB18:
	.loc 1 442 0
	mov	DWORD PTR [rbp-4], 0
	jmp	.L123
.L124:
	mov	rax, QWORD PTR __gcov0.print_matrix[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.print_matrix[rip+8], rax
	.loc 1 443 0 discriminator 2
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rax+8]
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	imul	eax, DWORD PTR [rbp-8]
	mov	ecx, eax
	mov	eax, DWORD PTR [rbp-4]
	add	rax, rcx
	sal	rax, 3
	add	rax, rdx
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR [rbp-32], rax
	movsd	xmm0, QWORD PTR [rbp-32]
	mov	edi, OFFSET FLAT:.LC44
	mov	eax, 1
	call	printf
	.loc 1 442 0 discriminator 2
	add	DWORD PTR [rbp-4], 1
.L123:
	.loc 1 442 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	cmp	eax, DWORD PTR [rbp-4]
	ja	.L124
	mov	rax, QWORD PTR __gcov0.print_matrix[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.print_matrix[rip+16], rax
.LBE18:
	.loc 1 444 0 is_stmt 1
	mov	edi, 10
	call	putchar
	.loc 1 441 0
	add	DWORD PTR [rbp-8], 1
	mov	rax, QWORD PTR __gcov0.print_matrix[rip+24]
	add	rax, 1
	mov	QWORD PTR __gcov0.print_matrix[rip+24], rax
.L122:
	.loc 1 441 0 is_stmt 0 discriminator 1
	mov	rax, QWORD PTR [rbp-24]
	mov	eax, DWORD PTR [rax]
	cmp	eax, DWORD PTR [rbp-8]
	ja	.L125
	mov	rax, QWORD PTR __gcov0.print_matrix[rip+40]
	add	rax, 1
	mov	QWORD PTR __gcov0.print_matrix[rip+40], rax
.LBE17:
	.loc 1 447 0 is_stmt 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	print_matrix, .-print_matrix
	.section	.rodata
.LC45:
	.string	"%lld.%6lld\n"
	.text
	.globl	print_diff
	.type	print_diff, @function
print_diff:
.LFB17:
	.loc 1 452 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	call	mcount
	mov	rax, rdi
	mov	r8, rsi
	mov	rsi, rax
	mov	rdi, rdx
	mov	rdi, r8
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-48], rdx
	mov	QWORD PTR [rbp-40], rcx
	mov	rax, QWORD PTR __gcov0.print_diff[rip]
	add	rax, 1
	mov	QWORD PTR __gcov0.print_diff[rip], rax
	.loc 1 453 0
	mov	rdx, QWORD PTR [rbp-48]
	mov	rax, QWORD PTR [rbp-32]
	sub	rdx, rax
	mov	rax, rdx
	mov	QWORD PTR [rbp-16], rax
	.loc 1 454 0
	mov	rdx, QWORD PTR [rbp-40]
	mov	rax, QWORD PTR [rbp-24]
	sub	rdx, rax
	mov	rax, rdx
	mov	QWORD PTR [rbp-8], rax
	.loc 1 455 0
	cmp	QWORD PTR [rbp-8], 0
	jns	.L127
	.loc 1 457 0
	add	QWORD PTR [rbp-8], 1000000
	.loc 1 458 0
	sub	QWORD PTR [rbp-16], 1
	mov	rax, QWORD PTR __gcov0.print_diff[rip+8]
	add	rax, 1
	mov	QWORD PTR __gcov0.print_diff[rip+8], rax
.L127:
	.loc 1 460 0
	mov	rdx, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rbp-16]
	mov	rsi, rax
	mov	edi, OFFSET FLAT:.LC45
	mov	eax, 0
	call	printf
	mov	rax, QWORD PTR __gcov0.print_diff[rip+16]
	add	rax, 1
	mov	QWORD PTR __gcov0.print_diff[rip+16], rax
	.loc 1 461 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	print_diff, .-print_diff
	.section	.rodata
	.align 16
	.type	__PRETTY_FUNCTION__.4458, @object
	.size	__PRETTY_FUNCTION__.4458, 18
__PRETTY_FUNCTION__.4458:
	.string	"proceed_arguments"
	.type	__PRETTY_FUNCTION__.4470, @object
	.size	__PRETTY_FUNCTION__.4470, 5
__PRETTY_FUNCTION__.4470:
	.string	"main"
	.type	__PRETTY_FUNCTION__.4477, @object
	.size	__PRETTY_FUNCTION__.4477, 9
__PRETTY_FUNCTION__.4477:
	.string	"get_long"
	.type	__PRETTY_FUNCTION__.4488, @object
	.size	__PRETTY_FUNCTION__.4488, 11
__PRETTY_FUNCTION__.4488:
	.string	"get_matrix"
	.type	__PRETTY_FUNCTION__.4503, @object
	.size	__PRETTY_FUNCTION__.4503, 12
__PRETTY_FUNCTION__.4503:
	.string	"get_threads"
	.align 16
	.type	__PRETTY_FUNCTION__.4516, @object
	.size	__PRETTY_FUNCTION__.4516, 23
__PRETTY_FUNCTION__.4516:
	.string	"get_matrix_determinant"
	.align 16
	.type	__PRETTY_FUNCTION__.4536, @object
	.size	__PRETTY_FUNCTION__.4536, 21
__PRETTY_FUNCTION__.4536:
	.string	"thread_routine_debug"
	.type	__PRETTY_FUNCTION__.4548, @object
	.size	__PRETTY_FUNCTION__.4548, 15
__PRETTY_FUNCTION__.4548:
	.string	"thread_routine"
	.type	__PRETTY_FUNCTION__.4566, @object
	.size	__PRETTY_FUNCTION__.4566, 6
__PRETTY_FUNCTION__.4566:
	.string	"gauss"
	.type	__PRETTY_FUNCTION__.4622, @object
	.size	__PRETTY_FUNCTION__.4622, 10
__PRETTY_FUNCTION__.4622:
	.string	"get_minor"
	.local	__gcov0.print_diff
	.comm	__gcov0.print_diff,24,16
	.local	__gcov0.print_matrix
	.comm	__gcov0.print_matrix,48,32
	.local	__gcov0.get_minor
	.comm	__gcov0.get_minor,256,32
	.local	__gcov0.add_string
	.comm	__gcov0.add_string,16,16
	.local	__gcov0.annihilate_below
	.comm	__gcov0.annihilate_below,24,16
	.local	__gcov0.swap_strings
	.comm	__gcov0.swap_strings,16,16
	.local	__gcov0.search_below_nzero_swap
	.comm	__gcov0.search_below_nzero_swap,48,32
	.local	__gcov0.gauss
	.comm	__gcov0.gauss,168,32
	.local	__gcov0.thread_routine
	.comm	__gcov0.thread_routine,208,32
	.local	__gcov0.thread_routine_debug
	.comm	__gcov0.thread_routine_debug,64,32
	.local	__gcov0.matrix_copy
	.comm	__gcov0.matrix_copy,8,8
	.local	__gcov0.get_matrix_determinant
	.comm	__gcov0.get_matrix_determinant,280,32
	.local	__gcov0.get_threads
	.comm	__gcov0.get_threads,304,32
	.local	__gcov0.get_matrix
	.comm	__gcov0.get_matrix,368,32
	.local	__gcov0.matrix_kill
	.comm	__gcov0.matrix_kill,24,16
	.local	__gcov0.get_long
	.comm	__gcov0.get_long,88,32
	.local	__gcov0.main
	.comm	__gcov0.main,288,32
	.local	__gcov0.proceed_arguments
	.comm	__gcov0.proceed_arguments,248,32
	.text
	.type	_GLOBAL__sub_I_65535_0_iv_msgs, @function
_GLOBAL__sub_I_65535_0_iv_msgs:
.LFB18:
	.loc 1 461 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	.loc 1 461 0
	mov	edi, OFFSET FLAT:.LPBX0
	call	__gcov_init
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	_GLOBAL__sub_I_65535_0_iv_msgs, .-_GLOBAL__sub_I_65535_0_iv_msgs
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_65535_0_iv_msgs
	.data
	.align 32
	.type	__gcov_.print_diff, @object
	.size	__gcov_.print_diff, 40
__gcov_.print_diff:
	.quad	.LPBX0
	.long	18
	.long	-1813137857
	.long	1967469709
	.zero	4
	.long	3
	.zero	4
	.quad	__gcov0.print_diff
	.section	.rodata
	.align 8
.LC46:
	.string	"/home/bu99y/code/repos/learning/Seminars/Determinant/ivmatrix.gcda"
	.data
	.align 32
	.type	.LPBX0, @object
	.size	.LPBX0, 112
.LPBX0:
	.long	875575338
	.zero	4
	.quad	0
	.long	-2123551037
	.zero	4
	.quad	.LC46
	.quad	__gcov_merge_add
	.quad	0
	.quad	0
	.quad	0
	.quad	0
	.quad	0
	.quad	0
	.quad	0
	.long	18
	.zero	4
	.quad	.LPBX1
	.align 32
	.type	__gcov_.print_matrix, @object
	.size	__gcov_.print_matrix, 40
__gcov_.print_matrix:
	.quad	.LPBX0
	.long	17
	.long	-1214729553
	.long	1311540327
	.zero	4
	.long	6
	.zero	4
	.quad	__gcov0.print_matrix
	.align 32
	.type	__gcov_.get_minor, @object
	.size	__gcov_.get_minor, 40
__gcov_.get_minor:
	.quad	.LPBX0
	.long	16
	.long	-1999657345
	.long	1043162417
	.zero	4
	.long	32
	.zero	4
	.quad	__gcov0.get_minor
	.align 32
	.type	__gcov_.add_string, @object
	.size	__gcov_.add_string, 40
__gcov_.add_string:
	.quad	.LPBX0
	.long	15
	.long	-1246363294
	.long	-1192601709
	.zero	4
	.long	2
	.zero	4
	.quad	__gcov0.add_string
	.align 32
	.type	__gcov_.annihilate_below, @object
	.size	__gcov_.annihilate_below, 40
__gcov_.annihilate_below:
	.quad	.LPBX0
	.long	14
	.long	460401317
	.long	1946099778
	.zero	4
	.long	3
	.zero	4
	.quad	__gcov0.annihilate_below
	.align 32
	.type	__gcov_.swap_strings, @object
	.size	__gcov_.swap_strings, 40
__gcov_.swap_strings:
	.quad	.LPBX0
	.long	13
	.long	198408618
	.long	-1192601709
	.zero	4
	.long	2
	.zero	4
	.quad	__gcov0.swap_strings
	.align 32
	.type	__gcov_.search_below_nzero_swap, @object
	.size	__gcov_.search_below_nzero_swap, 40
__gcov_.search_below_nzero_swap:
	.quad	.LPBX0
	.long	12
	.long	-1992080360
	.long	-746406143
	.zero	4
	.long	6
	.zero	4
	.quad	__gcov0.search_below_nzero_swap
	.align 32
	.type	__gcov_.gauss, @object
	.size	__gcov_.gauss, 40
__gcov_.gauss:
	.quad	.LPBX0
	.long	11
	.long	1593697641
	.long	1236225744
	.zero	4
	.long	21
	.zero	4
	.quad	__gcov0.gauss
	.align 32
	.type	__gcov_.thread_routine, @object
	.size	__gcov_.thread_routine, 40
__gcov_.thread_routine:
	.quad	.LPBX0
	.long	10
	.long	1422927369
	.long	124436446
	.zero	4
	.long	26
	.zero	4
	.quad	__gcov0.thread_routine
	.align 32
	.type	__gcov_.thread_routine_debug, @object
	.size	__gcov_.thread_routine_debug, 40
__gcov_.thread_routine_debug:
	.quad	.LPBX0
	.long	9
	.long	859103232
	.long	1382886419
	.zero	4
	.long	8
	.zero	4
	.quad	__gcov0.thread_routine_debug
	.align 32
	.type	__gcov_.matrix_copy, @object
	.size	__gcov_.matrix_copy, 40
__gcov_.matrix_copy:
	.quad	.LPBX0
	.long	8
	.long	-672544950
	.long	-614602264
	.zero	4
	.long	1
	.zero	4
	.quad	__gcov0.matrix_copy
	.align 32
	.type	__gcov_.get_matrix_determinant, @object
	.size	__gcov_.get_matrix_determinant, 40
__gcov_.get_matrix_determinant:
	.quad	.LPBX0
	.long	7
	.long	-321448027
	.long	-841102476
	.zero	4
	.long	35
	.zero	4
	.quad	__gcov0.get_matrix_determinant
	.align 32
	.type	__gcov_.get_threads, @object
	.size	__gcov_.get_threads, 40
__gcov_.get_threads:
	.quad	.LPBX0
	.long	6
	.long	-514177794
	.long	-1710495143
	.zero	4
	.long	38
	.zero	4
	.quad	__gcov0.get_threads
	.align 32
	.type	__gcov_.get_matrix, @object
	.size	__gcov_.get_matrix, 40
__gcov_.get_matrix:
	.quad	.LPBX0
	.long	5
	.long	-2084391529
	.long	-1003135565
	.zero	4
	.long	46
	.zero	4
	.quad	__gcov0.get_matrix
	.align 32
	.type	__gcov_.matrix_kill, @object
	.size	__gcov_.matrix_kill, 40
__gcov_.matrix_kill:
	.quad	.LPBX0
	.long	4
	.long	-1239520057
	.long	-1633276034
	.zero	4
	.long	3
	.zero	4
	.quad	__gcov0.matrix_kill
	.align 32
	.type	__gcov_.get_long, @object
	.size	__gcov_.get_long, 40
__gcov_.get_long:
	.quad	.LPBX0
	.long	3
	.long	2086771714
	.long	-1925271195
	.zero	4
	.long	11
	.zero	4
	.quad	__gcov0.get_long
	.align 32
	.type	__gcov_.main, @object
	.size	__gcov_.main, 40
__gcov_.main:
	.quad	.LPBX0
	.long	2
	.long	2107230739
	.long	-2121822232
	.zero	4
	.long	36
	.zero	4
	.quad	__gcov0.main
	.align 32
	.type	__gcov_.proceed_arguments, @object
	.size	__gcov_.proceed_arguments, 40
__gcov_.proceed_arguments:
	.quad	.LPBX0
	.long	1
	.long	1482951195
	.long	-1793143331
	.zero	4
	.long	31
	.zero	4
	.quad	__gcov0.proceed_arguments
	.align 32
	.type	.LPBX1, @object
	.size	.LPBX1, 144
.LPBX1:
	.quad	__gcov_.print_diff
	.quad	__gcov_.print_matrix
	.quad	__gcov_.get_minor
	.quad	__gcov_.add_string
	.quad	__gcov_.annihilate_below
	.quad	__gcov_.swap_strings
	.quad	__gcov_.search_below_nzero_swap
	.quad	__gcov_.gauss
	.quad	__gcov_.thread_routine
	.quad	__gcov_.thread_routine_debug
	.quad	__gcov_.matrix_copy
	.quad	__gcov_.get_matrix_determinant
	.quad	__gcov_.get_threads
	.quad	__gcov_.get_matrix
	.quad	__gcov_.matrix_kill
	.quad	__gcov_.get_long
	.quad	__gcov_.main
	.quad	__gcov_.proceed_arguments
	.section	.rodata
	.align 16
.LC39:
	.long	4294967295
	.long	2147483647
	.long	0
	.long	0
	.align 8
.LC40:
	.long	0
	.long	1018167296
	.align 16
.LC41:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.text
.Letext0:
	.file 2 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 3 "/usr/lib/gcc/x86_64-linux-gnu/4.8/include/stddef.h"
	.file 4 "/usr/include/stdint.h"
	.file 5 "/usr/include/stdio.h"
	.file 6 "/usr/include/libio.h"
	.file 7 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h"
	.file 8 "/usr/include/x86_64-linux-gnu/bits/time.h"
	.file 9 "ivmatrix.h"
	.file 10 "iv_standard.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xf31
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF138
	.byte	0x1
	.long	.LASF139
	.long	.LASF140
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF0
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF1
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x4
	.long	.LASF7
	.byte	0x2
	.byte	0x83
	.long	0x5e
	.uleb128 0x4
	.long	.LASF8
	.byte	0x2
	.byte	0x84
	.long	0x5e
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF9
	.uleb128 0x4
	.long	.LASF10
	.byte	0x2
	.byte	0x8b
	.long	0x5e
	.uleb128 0x4
	.long	.LASF11
	.byte	0x2
	.byte	0x8d
	.long	0x5e
	.uleb128 0x5
	.byte	0x8
	.uleb128 0x6
	.byte	0x8
	.long	0xa0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF12
	.uleb128 0x4
	.long	.LASF13
	.byte	0x3
	.byte	0xd4
	.long	0x42
	.uleb128 0x4
	.long	.LASF14
	.byte	0x4
	.byte	0x33
	.long	0x3b
	.uleb128 0x4
	.long	.LASF15
	.byte	0x4
	.byte	0x37
	.long	0x42
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.long	.LASF16
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.long	.LASF17
	.uleb128 0x4
	.long	.LASF18
	.byte	0x5
	.byte	0x30
	.long	0xe1
	.uleb128 0x7
	.long	.LASF48
	.byte	0xd8
	.byte	0x6
	.byte	0xf5
	.long	0x261
	.uleb128 0x8
	.long	.LASF19
	.byte	0x6
	.byte	0xf6
	.long	0x57
	.byte	0
	.uleb128 0x8
	.long	.LASF20
	.byte	0x6
	.byte	0xfb
	.long	0x9a
	.byte	0x8
	.uleb128 0x8
	.long	.LASF21
	.byte	0x6
	.byte	0xfc
	.long	0x9a
	.byte	0x10
	.uleb128 0x8
	.long	.LASF22
	.byte	0x6
	.byte	0xfd
	.long	0x9a
	.byte	0x18
	.uleb128 0x8
	.long	.LASF23
	.byte	0x6
	.byte	0xfe
	.long	0x9a
	.byte	0x20
	.uleb128 0x8
	.long	.LASF24
	.byte	0x6
	.byte	0xff
	.long	0x9a
	.byte	0x28
	.uleb128 0x9
	.long	.LASF25
	.byte	0x6
	.value	0x100
	.long	0x9a
	.byte	0x30
	.uleb128 0x9
	.long	.LASF26
	.byte	0x6
	.value	0x101
	.long	0x9a
	.byte	0x38
	.uleb128 0x9
	.long	.LASF27
	.byte	0x6
	.value	0x102
	.long	0x9a
	.byte	0x40
	.uleb128 0x9
	.long	.LASF28
	.byte	0x6
	.value	0x104
	.long	0x9a
	.byte	0x48
	.uleb128 0x9
	.long	.LASF29
	.byte	0x6
	.value	0x105
	.long	0x9a
	.byte	0x50
	.uleb128 0x9
	.long	.LASF30
	.byte	0x6
	.value	0x106
	.long	0x9a
	.byte	0x58
	.uleb128 0x9
	.long	.LASF31
	.byte	0x6
	.value	0x108
	.long	0x299
	.byte	0x60
	.uleb128 0x9
	.long	.LASF32
	.byte	0x6
	.value	0x10a
	.long	0x29f
	.byte	0x68
	.uleb128 0x9
	.long	.LASF33
	.byte	0x6
	.value	0x10c
	.long	0x57
	.byte	0x70
	.uleb128 0x9
	.long	.LASF34
	.byte	0x6
	.value	0x110
	.long	0x57
	.byte	0x74
	.uleb128 0x9
	.long	.LASF35
	.byte	0x6
	.value	0x112
	.long	0x65
	.byte	0x78
	.uleb128 0x9
	.long	.LASF36
	.byte	0x6
	.value	0x116
	.long	0x34
	.byte	0x80
	.uleb128 0x9
	.long	.LASF37
	.byte	0x6
	.value	0x117
	.long	0x49
	.byte	0x82
	.uleb128 0x9
	.long	.LASF38
	.byte	0x6
	.value	0x118
	.long	0x2a5
	.byte	0x83
	.uleb128 0x9
	.long	.LASF39
	.byte	0x6
	.value	0x11c
	.long	0x2b5
	.byte	0x88
	.uleb128 0x9
	.long	.LASF40
	.byte	0x6
	.value	0x125
	.long	0x70
	.byte	0x90
	.uleb128 0x9
	.long	.LASF41
	.byte	0x6
	.value	0x12e
	.long	0x98
	.byte	0x98
	.uleb128 0x9
	.long	.LASF42
	.byte	0x6
	.value	0x12f
	.long	0x98
	.byte	0xa0
	.uleb128 0x9
	.long	.LASF43
	.byte	0x6
	.value	0x130
	.long	0x98
	.byte	0xa8
	.uleb128 0x9
	.long	.LASF44
	.byte	0x6
	.value	0x131
	.long	0x98
	.byte	0xb0
	.uleb128 0x9
	.long	.LASF45
	.byte	0x6
	.value	0x132
	.long	0xa7
	.byte	0xb8
	.uleb128 0x9
	.long	.LASF46
	.byte	0x6
	.value	0x134
	.long	0x57
	.byte	0xc0
	.uleb128 0x9
	.long	.LASF47
	.byte	0x6
	.value	0x136
	.long	0x2bb
	.byte	0xc4
	.byte	0
	.uleb128 0xa
	.long	.LASF141
	.byte	0x6
	.byte	0x9a
	.uleb128 0x7
	.long	.LASF49
	.byte	0x18
	.byte	0x6
	.byte	0xa0
	.long	0x299
	.uleb128 0x8
	.long	.LASF50
	.byte	0x6
	.byte	0xa1
	.long	0x299
	.byte	0
	.uleb128 0x8
	.long	.LASF51
	.byte	0x6
	.byte	0xa2
	.long	0x29f
	.byte	0x8
	.uleb128 0x8
	.long	.LASF52
	.byte	0x6
	.byte	0xa6
	.long	0x57
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x268
	.uleb128 0x6
	.byte	0x8
	.long	0xe1
	.uleb128 0xb
	.long	0xa0
	.long	0x2b5
	.uleb128 0xc
	.long	0x7b
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x261
	.uleb128 0xb
	.long	0xa0
	.long	0x2cb
	.uleb128 0xc
	.long	0x7b
	.byte	0x13
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x2d1
	.uleb128 0xd
	.long	0xa0
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF53
	.uleb128 0x4
	.long	.LASF54
	.byte	0x7
	.byte	0x3c
	.long	0x42
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF55
	.uleb128 0x7
	.long	.LASF56
	.byte	0x10
	.byte	0x8
	.byte	0x1e
	.long	0x314
	.uleb128 0x8
	.long	.LASF57
	.byte	0x8
	.byte	0x20
	.long	0x82
	.byte	0
	.uleb128 0x8
	.long	.LASF58
	.byte	0x8
	.byte	0x21
	.long	0x8d
	.byte	0x8
	.byte	0
	.uleb128 0x7
	.long	.LASF59
	.byte	0x10
	.byte	0x9
	.byte	0x1b
	.long	0x339
	.uleb128 0x8
	.long	.LASF60
	.byte	0x9
	.byte	0x1c
	.long	0xb2
	.byte	0
	.uleb128 0x8
	.long	.LASF61
	.byte	0x9
	.byte	0x1d
	.long	0x98
	.byte	0x8
	.byte	0
	.uleb128 0x4
	.long	.LASF62
	.byte	0x9
	.byte	0x20
	.long	0x314
	.uleb128 0x7
	.long	.LASF63
	.byte	0x20
	.byte	0x9
	.byte	0x22
	.long	0x381
	.uleb128 0xe
	.string	"ptr"
	.byte	0x9
	.byte	0x23
	.long	0x381
	.byte	0
	.uleb128 0x8
	.long	.LASF64
	.byte	0x9
	.byte	0x25
	.long	0x5e
	.byte	0x8
	.uleb128 0x8
	.long	.LASF65
	.byte	0x9
	.byte	0x26
	.long	0xb2
	.byte	0x10
	.uleb128 0x8
	.long	.LASF66
	.byte	0x9
	.byte	0x27
	.long	0x38c
	.byte	0x18
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x387
	.uleb128 0xd
	.long	0x339
	.uleb128 0x6
	.byte	0x8
	.long	0xcf
	.uleb128 0xf
	.long	.LASF142
	.byte	0x4
	.byte	0xa
	.byte	0x3f
	.long	0x3c3
	.uleb128 0x10
	.long	.LASF67
	.sleb128 0
	.uleb128 0x10
	.long	.LASF68
	.sleb128 1
	.uleb128 0x10
	.long	.LASF69
	.sleb128 2
	.uleb128 0x10
	.long	.LASF70
	.sleb128 3
	.uleb128 0x10
	.long	.LASF71
	.sleb128 4
	.uleb128 0x10
	.long	.LASF72
	.sleb128 5
	.byte	0
	.uleb128 0x11
	.long	.LASF78
	.byte	0x1
	.byte	0x10
	.long	0x57
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.long	0x44b
	.uleb128 0x12
	.long	.LASF73
	.byte	0x1
	.byte	0x10
	.long	0x57
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x12
	.long	.LASF74
	.byte	0x1
	.byte	0x10
	.long	0x44b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x13
	.string	"fd"
	.byte	0x1
	.byte	0x10
	.long	0x451
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x12
	.long	.LASF75
	.byte	0x1
	.byte	0x10
	.long	0x45d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x14
	.long	.LASF81
	.long	0x473
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.4458
	.uleb128 0x15
	.long	.LASF76
	.byte	0x1
	.byte	0x14
	.long	0x2cb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x15
	.long	.LASF77
	.byte	0x1
	.byte	0x17
	.long	0x57
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x2cb
	.uleb128 0x6
	.byte	0x8
	.long	0x457
	.uleb128 0x6
	.byte	0x8
	.long	0xd6
	.uleb128 0x6
	.byte	0x8
	.long	0x5e
	.uleb128 0xb
	.long	0xa0
	.long	0x473
	.uleb128 0xc
	.long	0x7b
	.byte	0x11
	.byte	0
	.uleb128 0xd
	.long	0x463
	.uleb128 0x11
	.long	.LASF79
	.byte	0x1
	.byte	0x25
	.long	0x57
	.quad	.LFB1
	.quad	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x530
	.uleb128 0x12
	.long	.LASF73
	.byte	0x1
	.byte	0x25
	.long	0x57
	.uleb128 0x3
	.byte	0x91
	.sleb128 -100
	.uleb128 0x12
	.long	.LASF74
	.byte	0x1
	.byte	0x25
	.long	0x44b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0x15
	.long	.LASF80
	.byte	0x1
	.byte	0x27
	.long	0x2ef
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x16
	.string	"end"
	.byte	0x1
	.byte	0x28
	.long	0x2ef
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x16
	.string	"fd"
	.byte	0x1
	.byte	0x2b
	.long	0x457
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x15
	.long	.LASF75
	.byte	0x1
	.byte	0x2c
	.long	0x5e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x15
	.long	.LASF77
	.byte	0x1
	.byte	0x2d
	.long	0x57
	.uleb128 0x3
	.byte	0x91
	.sleb128 -92
	.uleb128 0x14
	.long	.LASF81
	.long	0x540
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.4470
	.uleb128 0x15
	.long	.LASF82
	.byte	0x1
	.byte	0x33
	.long	0x339
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x15
	.long	.LASF83
	.byte	0x1
	.byte	0x40
	.long	0xcf
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.byte	0
	.uleb128 0xb
	.long	0xa0
	.long	0x540
	.uleb128 0xc
	.long	0x7b
	.byte	0x4
	.byte	0
	.uleb128 0xd
	.long	0x530
	.uleb128 0x11
	.long	.LASF84
	.byte	0x1
	.byte	0x51
	.long	0x57
	.quad	.LFB2
	.quad	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x5c0
	.uleb128 0x12
	.long	.LASF85
	.byte	0x1
	.byte	0x51
	.long	0x45d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x13
	.string	"str"
	.byte	0x1
	.byte	0x51
	.long	0x2cb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x14
	.long	.LASF81
	.long	0x5d0
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.4477
	.uleb128 0x15
	.long	.LASF86
	.byte	0x1
	.byte	0x54
	.long	0x57
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x15
	.long	.LASF87
	.byte	0x1
	.byte	0x55
	.long	0x9a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x16
	.string	"val"
	.byte	0x1
	.byte	0x57
	.long	0x5e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xb
	.long	0xa0
	.long	0x5d0
	.uleb128 0xc
	.long	0x7b
	.byte	0x8
	.byte	0
	.uleb128 0xd
	.long	0x5c0
	.uleb128 0x17
	.long	.LASF115
	.byte	0x1
	.byte	0x69
	.quad	.LFB3
	.quad	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x601
	.uleb128 0x12
	.long	.LASF88
	.byte	0x1
	.byte	0x69
	.long	0x601
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x339
	.uleb128 0x11
	.long	.LASF89
	.byte	0x1
	.byte	0x77
	.long	0x57
	.quad	.LFB4
	.quad	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.long	0x6bf
	.uleb128 0x13
	.string	"fd"
	.byte	0x1
	.byte	0x77
	.long	0x457
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x12
	.long	.LASF88
	.byte	0x1
	.byte	0x77
	.long	0x601
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x14
	.long	.LASF81
	.long	0x6cf
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.4488
	.uleb128 0x15
	.long	.LASF60
	.byte	0x1
	.byte	0x7c
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x15
	.long	.LASF77
	.byte	0x1
	.byte	0x7d
	.long	0x57
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x15
	.long	.LASF90
	.byte	0x1
	.byte	0x84
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x18
	.quad	.LBB2
	.quad	.LBE2-.LBB2
	.uleb128 0x16
	.string	"i"
	.byte	0x1
	.byte	0x85
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x18
	.quad	.LBB3
	.quad	.LBE3-.LBB3
	.uleb128 0x15
	.long	.LASF91
	.byte	0x1
	.byte	0x86
	.long	0xcf
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xb
	.long	0xa0
	.long	0x6cf
	.uleb128 0xc
	.long	0x7b
	.byte	0xa
	.byte	0
	.uleb128 0xd
	.long	0x6bf
	.uleb128 0x11
	.long	.LASF92
	.byte	0x1
	.byte	0x94
	.long	0x78b
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.long	0x78b
	.uleb128 0x12
	.long	.LASF88
	.byte	0x1
	.byte	0x94
	.long	0x381
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x12
	.long	.LASF93
	.byte	0x1
	.byte	0x94
	.long	0x5e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x12
	.long	.LASF94
	.byte	0x1
	.byte	0x94
	.long	0x38c
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x12
	.long	.LASF95
	.byte	0x1
	.byte	0x94
	.long	0x791
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x14
	.long	.LASF81
	.long	0x7ad
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.4503
	.uleb128 0x15
	.long	.LASF96
	.byte	0x1
	.byte	0x97
	.long	0x78b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x15
	.long	.LASF77
	.byte	0x1
	.byte	0x9e
	.long	0x57
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x15
	.long	.LASF97
	.byte	0x1
	.byte	0xae
	.long	0x797
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x18
	.quad	.LBB4
	.quad	.LBE4-.LBB4
	.uleb128 0x16
	.string	"i"
	.byte	0x1
	.byte	0xb6
	.long	0x5e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x2dd
	.uleb128 0x6
	.byte	0x8
	.long	0x797
	.uleb128 0x6
	.byte	0x8
	.long	0x344
	.uleb128 0xb
	.long	0xa0
	.long	0x7ad
	.uleb128 0xc
	.long	0x7b
	.byte	0xb
	.byte	0
	.uleb128 0xd
	.long	0x79d
	.uleb128 0x11
	.long	.LASF98
	.byte	0x1
	.byte	0xce
	.long	0x57
	.quad	.LFB6
	.quad	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.long	0x88c
	.uleb128 0x12
	.long	.LASF88
	.byte	0x1
	.byte	0xce
	.long	0x381
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x12
	.long	.LASF75
	.byte	0x1
	.byte	0xce
	.long	0x5e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x13
	.string	"ret"
	.byte	0x1
	.byte	0xce
	.long	0x38c
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x14
	.long	.LASF81
	.long	0x89c
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.4516
	.uleb128 0x15
	.long	.LASF94
	.byte	0x1
	.byte	0xd3
	.long	0x38c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x15
	.long	.LASF97
	.byte	0x1
	.byte	0xda
	.long	0x797
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x15
	.long	.LASF99
	.byte	0x1
	.byte	0xdb
	.long	0x78b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x15
	.long	.LASF100
	.byte	0x1
	.byte	0xe5
	.long	0xcf
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x19
	.quad	.LBB5
	.quad	.LBE5-.LBB5
	.long	0x86d
	.uleb128 0x16
	.string	"i"
	.byte	0x1
	.byte	0xe1
	.long	0x5e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.byte	0
	.uleb128 0x18
	.quad	.LBB6
	.quad	.LBE6-.LBB6
	.uleb128 0x16
	.string	"i"
	.byte	0x1
	.byte	0xe6
	.long	0x5e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.byte	0
	.uleb128 0xb
	.long	0xa0
	.long	0x89c
	.uleb128 0xc
	.long	0x7b
	.byte	0x16
	.byte	0
	.uleb128 0xd
	.long	0x88c
	.uleb128 0x11
	.long	.LASF101
	.byte	0x1
	.byte	0xfa
	.long	0x339
	.quad	.LFB7
	.quad	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0x8df
	.uleb128 0x12
	.long	.LASF102
	.byte	0x1
	.byte	0xfa
	.long	0x381
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x15
	.long	.LASF103
	.byte	0x1
	.byte	0xfc
	.long	0x339
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x1a
	.long	.LASF104
	.byte	0x1
	.value	0x105
	.long	0x98
	.quad	.LFB8
	.quad	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.long	0x972
	.uleb128 0x1b
	.long	.LASF105
	.byte	0x1
	.value	0x105
	.long	0x98
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x14
	.long	.LASF81
	.long	0x982
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.4536
	.uleb128 0x1c
	.long	.LASF97
	.byte	0x1
	.value	0x108
	.long	0x344
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1c
	.long	.LASF106
	.byte	0x1
	.value	0x109
	.long	0xb2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x1d
	.string	"num"
	.byte	0x1
	.value	0x10a
	.long	0x5e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1c
	.long	.LASF60
	.byte	0x1
	.value	0x10b
	.long	0xb2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x1c
	.long	.LASF107
	.byte	0x1
	.value	0x10d
	.long	0xbd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.uleb128 0xb
	.long	0xa0
	.long	0x982
	.uleb128 0xc
	.long	0x7b
	.byte	0x14
	.byte	0
	.uleb128 0xd
	.long	0x972
	.uleb128 0x1a
	.long	.LASF108
	.byte	0x1
	.value	0x118
	.long	0x98
	.quad	.LFB9
	.quad	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.long	0xa8d
	.uleb128 0x1b
	.long	.LASF105
	.byte	0x1
	.value	0x118
	.long	0x98
	.uleb128 0x3
	.byte	0x91
	.sleb128 -120
	.uleb128 0x14
	.long	.LASF81
	.long	0xa9d
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.4548
	.uleb128 0x1c
	.long	.LASF97
	.byte	0x1
	.value	0x11b
	.long	0x344
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1c
	.long	.LASF60
	.byte	0x1
	.value	0x121
	.long	0xb2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -108
	.uleb128 0x1c
	.long	.LASF109
	.byte	0x1
	.value	0x122
	.long	0xb2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.uleb128 0x1c
	.long	.LASF100
	.byte	0x1
	.value	0x123
	.long	0xcf
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x1c
	.long	.LASF110
	.byte	0x1
	.value	0x124
	.long	0xcf
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x1c
	.long	.LASF111
	.byte	0x1
	.value	0x125
	.long	0x601
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x1c
	.long	.LASF103
	.byte	0x1
	.value	0x126
	.long	0x339
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1c
	.long	.LASF77
	.byte	0x1
	.value	0x12a
	.long	0x57
	.uleb128 0x3
	.byte	0x91
	.sleb128 -100
	.uleb128 0x18
	.quad	.LBB7
	.quad	.LBE7-.LBB7
	.uleb128 0x1d
	.string	"i"
	.byte	0x1
	.value	0x12b
	.long	0xb2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0x18
	.quad	.LBB8
	.quad	.LBE8-.LBB8
	.uleb128 0x1c
	.long	.LASF112
	.byte	0x1
	.value	0x137
	.long	0xcf
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xb
	.long	0xa0
	.long	0xa9d
	.uleb128 0xc
	.long	0x7b
	.byte	0xe
	.byte	0
	.uleb128 0xd
	.long	0xa8d
	.uleb128 0x1a
	.long	.LASF113
	.byte	0x1
	.value	0x149
	.long	0x57
	.quad	.LFB10
	.quad	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.long	0xb47
	.uleb128 0x1b
	.long	.LASF88
	.byte	0x1
	.value	0x149
	.long	0x601
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1b
	.long	.LASF100
	.byte	0x1
	.value	0x149
	.long	0x38c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x14
	.long	.LASF81
	.long	0xb57
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.4566
	.uleb128 0x1c
	.long	.LASF114
	.byte	0x1
	.value	0x157
	.long	0xcf
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x19
	.quad	.LBB9
	.quad	.LBE9-.LBB9
	.long	0xb27
	.uleb128 0x1d
	.string	"i"
	.byte	0x1
	.value	0x14e
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x18
	.quad	.LBB10
	.quad	.LBE10-.LBB10
	.uleb128 0x1d
	.string	"i"
	.byte	0x1
	.value	0x158
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.byte	0
	.uleb128 0xb
	.long	0xa0
	.long	0xb57
	.uleb128 0xc
	.long	0x7b
	.byte	0x5
	.byte	0
	.uleb128 0xd
	.long	0xb47
	.uleb128 0x1e
	.long	.LASF116
	.byte	0x1
	.value	0x160
	.quad	.LFB11
	.quad	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.long	0xbc3
	.uleb128 0x1b
	.long	.LASF88
	.byte	0x1
	.value	0x160
	.long	0x601
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1f
	.string	"i"
	.byte	0x1
	.value	0x160
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x1d
	.string	"j"
	.byte	0x1
	.value	0x162
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x18
	.quad	.LBB11
	.quad	.LBE11-.LBB11
	.uleb128 0x1d
	.string	"i"
	.byte	0x1
	.value	0x169
	.long	0x5e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.byte	0
	.uleb128 0x20
	.long	.LASF117
	.byte	0x1
	.value	0x16f
	.quad	.LFB12
	.quad	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.long	0xc4f
	.uleb128 0x1b
	.long	.LASF88
	.byte	0x1
	.value	0x16f
	.long	0x601
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1b
	.long	.LASF118
	.byte	0x1
	.value	0x16f
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x1b
	.long	.LASF119
	.byte	0x1
	.value	0x16f
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x18
	.quad	.LBB12
	.quad	.LBE12-.LBB12
	.uleb128 0x1d
	.string	"i"
	.byte	0x1
	.value	0x171
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x18
	.quad	.LBB13
	.quad	.LBE13-.LBB13
	.uleb128 0x1c
	.long	.LASF91
	.byte	0x1
	.value	0x173
	.long	0xcf
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1e
	.long	.LASF120
	.byte	0x1
	.value	0x182
	.quad	.LFB13
	.quad	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0xca9
	.uleb128 0x1b
	.long	.LASF88
	.byte	0x1
	.value	0x182
	.long	0x601
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1f
	.string	"i"
	.byte	0x1
	.value	0x182
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x18
	.quad	.LBB14
	.quad	.LBE14-.LBB14
	.uleb128 0x1d
	.string	"j"
	.byte	0x1
	.value	0x184
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0x20
	.long	.LASF121
	.byte	0x1
	.value	0x18a
	.quad	.LFB14
	.quad	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0xd22
	.uleb128 0x1b
	.long	.LASF88
	.byte	0x1
	.value	0x18a
	.long	0x601
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1b
	.long	.LASF122
	.byte	0x1
	.value	0x18a
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x1f
	.string	"to"
	.byte	0x1
	.value	0x18a
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1b
	.long	.LASF109
	.byte	0x1
	.value	0x18a
	.long	0xcf
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x18
	.quad	.LBB15
	.quad	.LBE15-.LBB15
	.uleb128 0x1d
	.string	"i"
	.byte	0x1
	.value	0x18c
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0x1a
	.long	.LASF123
	.byte	0x1
	.value	0x193
	.long	0x601
	.quad	.LFB15
	.quad	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.long	0xdf1
	.uleb128 0x1b
	.long	.LASF88
	.byte	0x1
	.value	0x193
	.long	0x381
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x1b
	.long	.LASF124
	.byte	0x1
	.value	0x193
	.long	0xb2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -92
	.uleb128 0x1b
	.long	.LASF125
	.byte	0x1
	.value	0x193
	.long	0xb2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x14
	.long	.LASF81
	.long	0xe01
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.4622
	.uleb128 0x1c
	.long	.LASF126
	.byte	0x1
	.value	0x196
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x1c
	.long	.LASF127
	.byte	0x1
	.value	0x198
	.long	0x98
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1c
	.long	.LASF128
	.byte	0x1
	.value	0x19b
	.long	0x98
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1d
	.string	"j"
	.byte	0x1
	.value	0x1a0
	.long	0xb2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x1c
	.long	.LASF129
	.byte	0x1
	.value	0x1aa
	.long	0x601
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x18
	.quad	.LBB16
	.quad	.LBE16-.LBB16
	.uleb128 0x1d
	.string	"i"
	.byte	0x1
	.value	0x1a1
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.byte	0
	.uleb128 0xb
	.long	0xa0
	.long	0xe01
	.uleb128 0xc
	.long	0x7b
	.byte	0x9
	.byte	0
	.uleb128 0xd
	.long	0xdf1
	.uleb128 0x1e
	.long	.LASF130
	.byte	0x1
	.value	0x1b6
	.quad	.LFB16
	.quad	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.long	0xe72
	.uleb128 0x1b
	.long	.LASF88
	.byte	0x1
	.value	0x1b6
	.long	0x381
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x18
	.quad	.LBB17
	.quad	.LBE17-.LBB17
	.uleb128 0x1d
	.string	"i"
	.byte	0x1
	.value	0x1b9
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x18
	.quad	.LBB18
	.quad	.LBE18-.LBB18
	.uleb128 0x1d
	.string	"j"
	.byte	0x1
	.value	0x1ba
	.long	0xb2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1e
	.long	.LASF131
	.byte	0x1
	.value	0x1c3
	.quad	.LFB17
	.quad	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.long	0xecd
	.uleb128 0x1b
	.long	.LASF80
	.byte	0x1
	.value	0x1c3
	.long	0x2ef
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1f
	.string	"end"
	.byte	0x1
	.value	0x1c3
	.long	0x2ef
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1c
	.long	.LASF132
	.byte	0x1
	.value	0x1c5
	.long	0x2d6
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1c
	.long	.LASF133
	.byte	0x1
	.value	0x1c6
	.long	0x2d6
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x21
	.long	.LASF143
	.quad	.LFB18
	.quad	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x22
	.long	.LASF134
	.byte	0x5
	.byte	0xa9
	.long	0x29f
	.uleb128 0x22
	.long	.LASF135
	.byte	0x5
	.byte	0xaa
	.long	0x29f
	.uleb128 0xb
	.long	0x2cb
	.long	0xf0a
	.uleb128 0xc
	.long	0x7b
	.byte	0x5
	.byte	0
	.uleb128 0x23
	.long	.LASF136
	.byte	0xa
	.byte	0x49
	.long	0xefa
	.uleb128 0x9
	.byte	0x3
	.quad	iv_msgs
	.uleb128 0x23
	.long	.LASF137
	.byte	0x1
	.byte	0xa
	.long	0xbd
	.uleb128 0x9
	.byte	0x3
	.quad	GLOBAL_COUNTER
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF92:
	.string	"get_threads"
.LASF54:
	.string	"pthread_t"
.LASF38:
	.string	"_shortbuf"
.LASF141:
	.string	"_IO_lock_t"
.LASF114:
	.string	"output"
.LASF135:
	.string	"stderr"
.LASF27:
	.string	"_IO_buf_end"
.LASF93:
	.string	"amount"
.LASF65:
	.string	"minor_index"
.LASF121:
	.string	"add_string"
.LASF25:
	.string	"_IO_write_end"
.LASF2:
	.string	"unsigned int"
.LASF113:
	.string	"gauss"
.LASF73:
	.string	"argc"
.LASF19:
	.string	"_flags"
.LASF89:
	.string	"get_matrix"
.LASF68:
	.string	"IVFOPENFAIL"
.LASF87:
	.string	"endptr"
.LASF110:
	.string	"temp_result"
.LASF31:
	.string	"_markers"
.LASF104:
	.string	"thread_routine_debug"
.LASF98:
	.string	"get_matrix_determinant"
.LASF85:
	.string	"save"
.LASF116:
	.string	"search_below_nzero_swap"
.LASF59:
	.string	"matrix_s"
.LASF137:
	.string	"GLOBAL_COUNTER"
.LASF94:
	.string	"results"
.LASF69:
	.string	"IVINVALPID"
.LASF14:
	.string	"uint32_t"
.LASF134:
	.string	"stdout"
.LASF30:
	.string	"_IO_save_end"
.LASF16:
	.string	"float"
.LASF86:
	.string	"base"
.LASF106:
	.string	"index"
.LASF122:
	.string	"added"
.LASF100:
	.string	"result"
.LASF55:
	.string	"long long unsigned int"
.LASF131:
	.string	"print_diff"
.LASF117:
	.string	"swap_strings"
.LASF29:
	.string	"_IO_backup_base"
.LASF40:
	.string	"_offset"
.LASF33:
	.string	"_fileno"
.LASF56:
	.string	"timeval"
.LASF13:
	.string	"size_t"
.LASF108:
	.string	"thread_routine"
.LASF115:
	.string	"matrix_kill"
.LASF77:
	.string	"cond"
.LASF140:
	.string	"/home/bu99y/code/repos/learning/Seminars/Determinant"
.LASF123:
	.string	"get_minor"
.LASF22:
	.string	"_IO_read_base"
.LASF126:
	.string	"old_amount"
.LASF78:
	.string	"proceed_arguments"
.LASF50:
	.string	"_next"
.LASF58:
	.string	"tv_usec"
.LASF52:
	.string	"_pos"
.LASF101:
	.string	"matrix_copy"
.LASF124:
	.string	"string"
.LASF119:
	.string	"second"
.LASF139:
	.string	"ivmatrix.c"
.LASF12:
	.string	"char"
.LASF46:
	.string	"_mode"
.LASF76:
	.string	"filename"
.LASF49:
	.string	"_IO_marker"
.LASF143:
	.string	"_GLOBAL__sub_I_65535_0_iv_msgs"
.LASF20:
	.string	"_IO_read_ptr"
.LASF61:
	.string	"data"
.LASF133:
	.string	"micros"
.LASF90:
	.string	"nelems"
.LASF23:
	.string	"_IO_write_base"
.LASF53:
	.string	"long long int"
.LASF28:
	.string	"_IO_save_base"
.LASF64:
	.string	"threads_num"
.LASF142:
	.string	"ERROR_MESSAGES"
.LASF127:
	.string	"new_data"
.LASF60:
	.string	"size"
.LASF130:
	.string	"print_matrix"
.LASF111:
	.string	"minor"
.LASF132:
	.string	"seconds"
.LASF41:
	.string	"__pad1"
.LASF42:
	.string	"__pad2"
.LASF43:
	.string	"__pad3"
.LASF44:
	.string	"__pad4"
.LASF45:
	.string	"__pad5"
.LASF70:
	.string	"IVNEGSIZE"
.LASF71:
	.string	"IVINVALARGNUM"
.LASF37:
	.string	"_vtable_offset"
.LASF96:
	.string	"array"
.LASF74:
	.string	"argv"
.LASF83:
	.string	"determinant"
.LASF103:
	.string	"copy"
.LASF88:
	.string	"this"
.LASF112:
	.string	"delta_result"
.LASF120:
	.string	"annihilate_below"
.LASF21:
	.string	"_IO_read_end"
.LASF75:
	.string	"nthreads"
.LASF138:
	.string	"GNU C 4.8.2 -masm=intel -mtune=generic -march=x86-64 -g -O0 -std=c11 -p -fprofile-arcs -ftest-coverage -fstack-protector"
.LASF5:
	.string	"short int"
.LASF6:
	.string	"long int"
.LASF91:
	.string	"temp"
.LASF15:
	.string	"uint64_t"
.LASF125:
	.string	"column"
.LASF102:
	.string	"copied"
.LASF72:
	.string	"IVALLOCFAIL"
.LASF39:
	.string	"_lock"
.LASF57:
	.string	"tv_sec"
.LASF9:
	.string	"sizetype"
.LASF3:
	.string	"long unsigned int"
.LASF35:
	.string	"_old_offset"
.LASF99:
	.string	"threads"
.LASF48:
	.string	"_IO_FILE"
.LASF62:
	.string	"matrix"
.LASF129:
	.string	"new_matrix"
.LASF0:
	.string	"unsigned char"
.LASF51:
	.string	"_sbuf"
.LASF128:
	.string	"old_data"
.LASF24:
	.string	"_IO_write_ptr"
.LASF118:
	.string	"first"
.LASF11:
	.string	"__suseconds_t"
.LASF10:
	.string	"__time_t"
.LASF95:
	.string	"info_save"
.LASF97:
	.string	"info"
.LASF67:
	.string	"IVPTRNULL"
.LASF7:
	.string	"__off_t"
.LASF63:
	.string	"thread_meta"
.LASF4:
	.string	"signed char"
.LASF1:
	.string	"short unsigned int"
.LASF80:
	.string	"begin"
.LASF66:
	.string	"to_save"
.LASF79:
	.string	"main"
.LASF105:
	.string	"info_ptr"
.LASF81:
	.string	"__PRETTY_FUNCTION__"
.LASF82:
	.string	"current"
.LASF17:
	.string	"double"
.LASF107:
	.string	"cycles"
.LASF32:
	.string	"_chain"
.LASF136:
	.string	"iv_msgs"
.LASF109:
	.string	"factor"
.LASF18:
	.string	"FILE"
.LASF34:
	.string	"_flags2"
.LASF36:
	.string	"_cur_column"
.LASF8:
	.string	"__off64_t"
.LASF47:
	.string	"_unused2"
.LASF26:
	.string	"_IO_buf_base"
.LASF84:
	.string	"get_long"
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits

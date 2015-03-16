.extern main
.extern sys_exit

.globl _start
_start:
	movq	(%rsp), %rdi		# argc
	lea	8(%rsp), %rsi		# argv

	call	main

	mov	%rax, %rdi
	call	sys_exit

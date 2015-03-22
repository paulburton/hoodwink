#include "util.h"
#include "x86_64/syscall.h"

.text

#define SYSCALL(name, ret, ...)			\
.if	X86_64_NR_##name != -1;			\
.globl sys_##name;				\
sys_##name:					\
	movl	$X86_64_NR_##name, %eax;	\
.if	VA_NUM_ARGS_NOZERO(__VA_ARGS__) >= 4;	\
	mov	%rcx, %r10;			\
.endif;						\
	syscall;				\
	retq;					\
.endif;

#include "syscall-list.h"

SYSCALL(arch_prctl, int, int code, unsigned long addr)
SYSCALL(clone, long, unsigned long clone_flags, unsigned long newsp, int *parent_tidptr, int *child_tidptr, int tls_val)
SYSCALL(rt_sigreturn, void)

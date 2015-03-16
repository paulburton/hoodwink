#include "util.h"
#include "x86_64/syscall.h"

.text

#define SYSCALL(name, ret, ...)			\
.globl sys_##name;				\
sys_##name:					\
	movl	$X86_64_NR_##name, %eax;	\
.if	VA_NUM_ARGS(__VA_ARGS__) >= 4;		\
	mov	%rcx, %r10;			\
.endif;						\
	syscall;				\
	retq;

#include "syscall-list.h"
